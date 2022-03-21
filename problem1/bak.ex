#include <stdio.h>
#include <stdlib.h>

int is_whitespace_func(const unsigned char *buffer, int num_bytes) {
    unsigned char c;
    switch (num_bytes) {
        case 1:
            c = buffer[0];
            if (c == 0x20 || c == 0x9 || c == 0xA || c == 0xD ||
                c == '-'  || c == '"' || c == '[' || c == ']' || c == '(' || c == ')' ||
                c == '.'  || c == ',' || c == ':' || c == ';' || c == '?' || c == '!') {
                return 1;
            } else {
                return 0;
            }

        case 3:
            if ((buffer[0] == 226) && (buffer[1] == 128)) {
                if (buffer[2] == 157 || buffer[2] == 156 || buffer[2] == 147 || buffer[2] == 166)
                    return 1;
            }
            return 0;
        default:
            return 0;
    }
}


int is_vowel_func(const unsigned char *buffer, int num_bytes) {
    unsigned char c;
    switch (num_bytes) {
        case 1:
            c = buffer[0];
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                return 1;
            } else {
                return 0;
            }
        case 2:

            if (buffer[0] == 195) {
                if (buffer[1] == 161 || buffer[1] == 129 || buffer[1] == 160 || buffer[1] == 128 || buffer[1] == 168 ||
                    buffer[1] == 170 || buffer[1] == 162 || buffer[1] == 169 || buffer[1] == 163 || buffer[1] == 172 ||
                    buffer[1] == 173 || buffer[1] == 137 || buffer[1] == 130 || buffer[1] == 131 || buffer[1] == 138 ||
                    buffer[1] == 136 || buffer[1] == 141 || buffer[1] == 140 || buffer[1] == 179 || buffer[1] == 147 ||
                    buffer[1] == 178 || buffer[1] == 146 || buffer[1] == 180 || buffer[1] == 148 || buffer[1] == 181 ||
                    buffer[1] == 149 || buffer[1] == 186 || buffer[1] == 154 || buffer[1] == 185 || buffer[1] == 153
                        )
                    return 1;
            }
            return 0;
        default:
            return 0;
    }
}


int main(int argc, char *argv[]) {


    int words;
    int words_begin_vowel;
    int words_end_consonant;
    int is_whitespace;
    int previous_whitespace;
    int is_vowel;
    int previous_vowel;


    unsigned char buffer[4]; //buffer to read up to 4 bytes
    unsigned long bytes_read = 0; // either 1 or 0 to determine if the while loop should end
    int num_bytes; // num bytes read in the buffer

    for (int i = 1; i < argc; i++) {

        words = 0;
        words_begin_vowel = 0;
        words_end_consonant = 0;
        is_whitespace = 0;
        previous_whitespace = 0;
        is_vowel = 0;
        previous_vowel = 0;

        FILE *ptr;
        ptr = fopen(argv[i], "rb");  // r for read, b for binary

        printf("----------------------------------------\nNow opening file: %s\n----------------------------------------\n", argv[i]);
        if (!ptr) {
            printf("File not found");
            exit(1);
        }
        words = 0;
        words_begin_vowel = 0;
        words_end_consonant = 0;

        do {
            bytes_read = fread(buffer, 1, 1, ptr); //read first byte

            int buffer_manipulated = buffer[0] >> 4; //shift it right 4 bits

            //manipulate the binary to identify if we should read 1-4 bytes
            if (buffer_manipulated == 15) {
                fseek(ptr, -1, SEEK_CUR);
                bytes_read = fread(buffer, 4, 1, ptr);
                num_bytes = 4;
            } else if (buffer_manipulated == 14) {
                fseek(ptr, -1, SEEK_CUR);
                bytes_read = fread(buffer, 3, 1, ptr);
                num_bytes = 3;
            } else if (buffer_manipulated < 8) {
                num_bytes = 1;
            } else {
                fseek(ptr, -1, SEEK_CUR);
                bytes_read = fread(buffer, 2, 1, ptr);
                num_bytes = 2;
            }

            is_whitespace = is_whitespace_func(buffer, num_bytes);
            is_vowel = is_vowel_func(buffer, num_bytes);


            if (is_whitespace && previous_whitespace == 0) {
                words++;
            }

            if (is_whitespace && previous_vowel) {
                words_end_consonant++;
            }

            if (previous_whitespace && is_vowel) {
                words_begin_vowel++;
            }

            previous_whitespace = is_whitespace;
            previous_vowel = is_vowel;

        } while (bytes_read != 0);

        //this is to adjust if there was no whitepace after the last word
        if (previous_whitespace == 0) {
            words++;
        }
        //this is to account if there was no whitespace after the last word, and that word was a vowel.
        if (previous_vowel) {
            words_end_consonant++;
        }

        printf("There are %d words in the text \n", words);
        printf("There are %d words that begin in vowels.\n", words_begin_vowel);
        printf("There are %d words that end in consonants.\n", words_end_consonant);


        fclose(ptr);

    }
}
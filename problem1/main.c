//
// Created by gundruke on 3/18/22.
//
#include <stdio.h>
#include <string.h>

void getUTF8char(FILE *buffer, unsigned char *utf8char){

    utf8char[0] =  fgetc(buffer); // first byte

    if(utf8char[0] < 0xC0){
        // one byte
        return;
    }
    else if(utf8char[0] < 0xE0){
        // two byte
        utf8char[1] = fgetc(buffer); // second byte
        return;
    }
    else if(utf8char[0] < 0xF0) {
        // three
        utf8char[1] = fgetc(buffer); // second byte
        utf8char[2] = fgetc(buffer); //third byte
        return;
    }
    else{
        // four
        utf8char[1] = fgetc(buffer); // second byte
        utf8char[2] = fgetc(buffer); //third byte
        utf8char[3] = fgetc(buffer); // 4th byte
        return;
    }
}

int is_vowel(const unsigned char *utf8char){
    int numBytes = strlen(utf8char);
    if (numBytes == 1){
                //         a                      e                      i                      o                       u
        return utf8char[0] == 0x61 || utf8char[0] == 0x65 || utf8char[0] == 0x69 || utf8char[0] == 0x6f || utf8char[0] == 0x75 ||
                //          A                      E                      I                      O                       U
                utf8char[0] == 0x41 || utf8char[0] == 0x45 || utf8char[0] == 0x49 || utf8char[0] == 0x4f || utf8char[0] == 0x55;
    }
    else if(numBytes == 2){
        if (utf8char[0] == 0xc3 ){
                    //         á                      à                      â                      ã
            return utf8char[1] == 0xa1 || utf8char[1] == 0xa0 || utf8char[1] == 0xa2 || utf8char[1] == 0xa3 ||
                    //          Á                      À                      Â                      Ã
                    utf8char[1] == 0x81 || utf8char[1] == 0x80 || utf8char[1] == 0x82 || utf8char[1] == 0x83 ||
                    //          é                      è                      ê
                    utf8char[1] == 0xa9 || utf8char[1] == 0xa8 || utf8char[1] == 0xaa ||
                    //          É                      È                       Ê
                    utf8char[1] == 0x89 || utf8char[1] == 0x88 || utf8char[1] == 0x8a ||
                    //          í                         ì
                    utf8char[1] == 0xad || utf8char[1] == 0xac ||
                    //          Í                         Ì
                    utf8char[1] == 0x8d || utf8char[1] == 0x8c ||
                    //          ó                      ò                      ô                      õ
                    utf8char[1] == 0xb3 || utf8char[1] == 0xb2 || utf8char[1] == 0xb4 || utf8char[1] == 0xb5 ||
                    //          Ó                      Ò                      Ô                      Õ
                    utf8char[1] == 0x93 || utf8char[1] == 0x92 || utf8char[1] == 0x94 || utf8char[1] == 0x95 ||
                    //           ú                     ù
                    utf8char[1] == 0xba || utf8char[1] == 0xb9 ||
                    //          Ú                     Ù
                    utf8char[1] == 0x9a || utf8char[1] == 0x99;
        }

    }

    return 0;
}

int is_whitespace(const unsigned char *utf8char){
    int numBytes = strlen(utf8char);

    if (numBytes == 1){
                //        space                  tab                newline                return
        return utf8char[0] == 0x20 || utf8char[0] == 0x9 || utf8char[0] == 0xa || utf8char[0] == 0xd ;
    }
    return 0;
}

int is_separation_symbol(const unsigned char *utf8char){
    int numBytes = strlen(utf8char);

    if (numBytes == 1){
                // - [ ] ( ) "
        return utf8char[0] == 0x2d || utf8char[0] == 0x5b || utf8char[0] == 0x5d ||
               utf8char[0] == 0x28 || utf8char[0] == 0x29 || utf8char[0] == 0x22;
    }
    else if (numBytes == 3){
        if (utf8char[0] == 0xe2 && utf8char[1] == 0x80){
            //                   “                    ”
            return  utf8char[2] == 0x9c || utf8char[2] == 0x9d;
        }
    }
    return 0;
}

int is_punctuation(const unsigned char *utf8char){
    int numBytes = strlen(utf8char);

    if (numBytes == 1){
        //   .   ,   :   ;   ?   !
        return utf8char[0] == 0x2e || utf8char[0] == 0x2c || utf8char[0] == 0x3a ||
               utf8char[0] == 0x3b || utf8char[0] == 0x3f || utf8char[0] == 0x21;
    }
    else if (numBytes == 3){
        if (utf8char[0] == 0xe2 && utf8char[1] == 0x80){
            //          dash (0xE28093)      ellipsis (0xE280A6)
            return  utf8char[2] == 0x93 || utf8char[2] == 0xa6;
        }
    }
    return 0;
}

int is_apostrophe(const unsigned char *utf8char){
    int numBytes = strlen(utf8char);

    if (numBytes == 1){
        return utf8char[0] == 0x27;
    }
    else if (numBytes == 3){
        if (utf8char[0] == 0xe2 && utf8char[1] == 0x80){
            return utf8char[2] == 0x98 || utf8char[2] == 0x99;
        }
    }
    return 0;
}

int is_underscore(const unsigned char *utf8char){
    int numBytes = strlen(utf8char);

    return numBytes == 1 && utf8char[0] == 0x5f;
}

int is_consonant(const unsigned char *utf8char){
    int numBytes = strlen(utf8char);

    if (numBytes == 1){
                // BCDFGHJKLMNPQRSTVWXYZ
        return utf8char[0] == 0x42 || utf8char[0] == 0x43 || utf8char[0] == 0x44 || utf8char[0] == 0x46 ||
               utf8char[0] == 0x47 || utf8char[0] == 0x48 || utf8char[0] == 0x4a || utf8char[0] == 0x4b ||
               utf8char[0] == 0x4c || utf8char[0] == 0x4d || utf8char[0] == 0x4e || utf8char[0] == 0x50 ||
               utf8char[0] == 0x51 || utf8char[0] == 0x52 || utf8char[0] == 0x53 || utf8char[0] == 0x54 ||
               utf8char[0] == 0x56 || utf8char[0] == 0x57 || utf8char[0] == 0x58 || utf8char[0] == 0x59 ||
               utf8char[0] == 0x5a ||
               // bcdfghjklmnpqrstvwxyz
                utf8char[0] == 0x62 || utf8char[0] == 0x63 || utf8char[0] == 0x64 || utf8char[0] == 0x66 ||
                utf8char[0] == 0x67 || utf8char[0] == 0x68 || utf8char[0] == 0x6a || utf8char[0] == 0x6b ||
                utf8char[0] == 0x6c || utf8char[0] == 0x6d || utf8char[0] == 0x6e || utf8char[0] == 0x70 ||
                utf8char[0] == 0x71 || utf8char[0] == 0x72 || utf8char[0] == 0x73 || utf8char[0] == 0x74 ||
                utf8char[0] == 0x76 || utf8char[0] == 0x77 || utf8char[0] == 0x78 || utf8char[0] == 0x79 ||
                utf8char[0] == 0x7a
                ;
    }
    else if(numBytes == 2){
        if (utf8char[0] == 0xc3 ){
            return utf8char[1] == 0xa7 || utf8char[1] == 0x87;
        }
    }

    return 0;
}

int is_alpha_numeric(const unsigned char *utf8char){
    return is_vowel(utf8char) || is_consonant(utf8char) ||
           utf8char[0] == 0x30 || utf8char[0] == 0x31 || utf8char[0] == 0x32 || utf8char[0] == 0x33 ||
           utf8char[0] == 0x34 || utf8char[0] == 0x35 || utf8char[0] == 0x36 || utf8char[0] == 0x37 ||
           utf8char[0] == 0x38 || utf8char[0] == 0x39;
}

int main(int argc, char *argv[]) {
    int letter;

    int total_words;
    int vowel_begin;
    int consonant_end;

    int in_word;
    int last_char_consonant;


    if (argc >= 2){
        for(int i = 1; i < argc; i++){
            total_words = 0;
            vowel_begin = 0;
            consonant_end = 0;

            in_word = 0;

            FILE *file;
            file = fopen(argv[i], "rb");

 	    if (file == NULL){
                printf("File %s doesn't exits.\n", argc[i])
            }

            char utf8character[5];

            memset(utf8character, 0, sizeof(utf8character));
            getUTF8char(file, utf8character);

            while (utf8character[0] != EOF){
                if (in_word){
                    if (is_alpha_numeric(utf8character) || is_underscore(utf8character) || is_apostrophe(utf8character)){
                        last_char_consonant = is_consonant(utf8character);
                    }

                    if (is_whitespace(utf8character) || is_separation_symbol(utf8character) || is_punctuation(utf8character)){
                        in_word = 0;
                        if (last_char_consonant){
                            consonant_end++;
                        }
                    }


                }else{
                    if (is_alpha_numeric(utf8character) || is_underscore(utf8character)){
                        in_word = 1;
                        total_words++;

                        if (is_vowel(utf8character)){
                            vowel_begin++;
                        }

                        last_char_consonant = is_consonant(utf8character);

                    }
                }
                memset(utf8character, 0, sizeof(utf8character));
                getUTF8char(file, utf8character);
            }

            fclose(file);

            // total number of words, number of words beginning with a
            //vowel and number of words ending with a consonant for each of the supplied files
            printf("\n================ STATUS ================\n");
            printf("Current ile name            : %s\n", argv[i]);
            printf("Total number of words       : %d\n", total_words);
            printf("Words beginning with vowel  : %d\n", vowel_begin);
            printf("Words ending with consonant : %d\n", consonant_end);
            printf("=================  END  ================\n\n\n");
        }
    }
    else{
        printf("You need to supply some text files.");
    }
}
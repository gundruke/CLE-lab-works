#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libgen.h>
#include <unistd.h>

static void printUsage(char *cmdName) {
    fprintf(stderr, "\nSynopsis: %s OPTIONS [filename / positive number]\n"
                    " OPTIONS:\n"
                    " -h --- print this help\n"
                    " -f --- filename\n"
                    " -n --- positive number\n", cmdName);
}

void read_matrix(double *mat, FILE *file, int mat_order) {
    for (int j = 0; j < (mat_order * mat_order); ++j) {
        fread(&mat[j], sizeof(double), 1, file);
    }
}


int gaussElimination(int mat_order, double *mat) {
    int i, j, k;
    int swapCount = 0;
    for (i = 0; i < mat_order - 1; i++) {
        //Partial Pivoting
        for (k = i + 1; k < mat_order; k++) {
            //If diagonal element(absolute value) is smaller than any of the terms below it
            if (fabs(mat[(i * mat_order) + i]) < fabs(mat[(k * mat_order) + i])) {
                //Swap the rows
                swapCount++;
                for (j = 0; j < mat_order; j++) {
                    double temp;
                    temp = mat[(i * mat_order) + j];
                    mat[(i * mat_order) + j] = mat[(k * mat_order) + j];
                    mat[(k * mat_order) + j] = temp;
                }
            }
        }
        //Begin Gauss Elimination
        for (k = i + 1; k < mat_order; k++) {
            double term = mat[(k * mat_order) + i] / mat[(i * mat_order) + i];
            for (j = 0; j < mat_order; j++) {
                mat[(k * mat_order) + j] = mat[(k * mat_order) + j] - term * mat[(i * mat_order) + j];
            }
        }
    }
    return swapCount;
}


double determinant(int mat_order, double *mat) {
    double det = 1;
    int i;
    int swapCount = gaussElimination(mat_order, mat);
    for (i = 0; i < mat_order; i++) {
        det = det * mat[(i * mat_order) + i];
    }
    return det * pow(-1, swapCount);
}


int main(int argc, char *argv[]) {
    int opt; /* selected option */
    char *fName = "no name"; /* file name (initialized to "no name" by default) */
    int val = -1; /* numeric value (initialized to -1 by default) */
    opterr = 0;
    do {
        switch ((opt = getopt(argc, argv, "f:n:h"))) {
            case 'f': /* file name */
                if (optarg[0] == '-') {
                    fprintf(stderr, "%s: file name is missing\n", basename(argv[0]));
                    printUsage(basename(argv[0]));
                    return EXIT_FAILURE;
                }


                FILE *file;
                int num_matrices;
                int matrix_order;

                double t0, t1, t2; /* time limits */
                t2 = 0.0;


                for (int i = 2; i < argc; i++) {


                    // Opening file in reading mode
                    file = fopen(argv[i], "rb");

                    if (!file) {
                        printf("File %s does not exist \n", argv[i]);
                        break;
                    }

                    printf("\n================ STATUS ================\n");
                    printf("Current file name            : %s\n", argv[i]);

                    fread(&num_matrices, sizeof(int), 1, file);
                    printf("Number of matrices to be read = %d \n", num_matrices);
                    fread(&matrix_order, sizeof(int), 1, file);
                    printf("Matrices order = %d \n\n", matrix_order);


                    for (int i = 1; i <= num_matrices; i++) {
                        t0 = ((double) clock()) / CLOCKS_PER_SEC;
                        printf("Processing matrix  : %d\n", i);
                        double *matrix = malloc((matrix_order * matrix_order) * sizeof(double));
                        read_matrix(matrix, file, matrix_order);

                        /*
                         *to print the matrix
                         *
                         * for(int j = 0; j < (matrix_order * matrix_order); ++j){
                            printf("%.2f ",matrix[j]);
                            if (((j+1) % matrix_order) == 0){
                                printf("\n");
                            }
                        }*/

                        t1 = ((double) clock()) / CLOCKS_PER_SEC;
                        t2 += t1 - t0;

                        printf("Determinant : %e\n\n", determinant(matrix_order, matrix));

                        free(matrix);
                    }
                    printf("=================  END  ================\n\n\n");
                    // Closing the file
                    fclose(file);
                }

                printf("\nElapsed time = %.6f s\n", t2);


                break;
            case 'n': /* numeric argument */
                if (atoi(optarg) <= 0) {
                    fprintf(stderr, "%s: non positive number\n", basename(argv[0]));
                    printUsage(basename(argv[0]));
                    return EXIT_FAILURE;
                }
                val = (int) atoi(optarg);
                break;
            case 'h': /* help mode */
                printUsage(basename(argv[0]));
                return EXIT_SUCCESS;
            case '?': /* invalid option */
                fprintf(stderr, "%s: invalid option\n", basename(argv[0]));
                printUsage(basename(argv[0]));
                return EXIT_FAILURE;
            case -1:
                break;
        }
    } while (opt != -1);
    if (argc == 1) {
        fprintf(stderr, "%s: invalid format\n", basename(argv[0]));
        printUsage(basename(argv[0]));
        return EXIT_FAILURE;
    }
//    int o; /* counting variable */
//    printf("File name = %s\n", fName);
//    printf("Numeric value = %d\n", val);
//    for (o = 0; o < argc; o++)
//        printf("Word %d = %s\n", o, argv[o]);
    return EXIT_SUCCESS;


}
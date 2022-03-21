#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void read_matrix(double* mat, FILE* file, int mat_order){
    for(int j = 0; j < (mat_order * mat_order); ++j){
        fread(&mat[j], sizeof(double), 1, file);
    }
}


int gaussElimination(int mat_order, double* mat){
    int i,j,k;
    int swapCount=0;
    for(i=0; i < mat_order-1; i++){
        //Partial Pivoting
        for(k = i+1; k < mat_order; k++){
            //If diagonal element(absolute value) is smaller than any of the terms below it
            if(fabs(mat[(i*mat_order) + i]) < fabs(mat[(k*mat_order) + i])){
                //Swap the rows
                swapCount++;
                for(j=0; j < mat_order; j++){
                    double temp;
                    temp = mat[(i * mat_order) + j];
                    mat[(i*mat_order) +j] = mat[(k*mat_order) + j];
                    mat[(k * mat_order) + j] = temp;
                }
            }
        }
        //Begin Gauss Elimination
        for(k = i+1; k < mat_order;  k++){
            double term = mat[(k * mat_order) + i]/ mat[(i * mat_order) + i];
            for(j=0; j<mat_order; j++){
                mat[(k * mat_order) + j] = mat[(k * mat_order) + j] - term * mat[(i * mat_order) + j];
            }
        }
    }
    return swapCount;
}


double determinant(int mat_order, double* mat){
    double det=1;
    int i;
    int swapCount = gaussElimination(mat_order, mat);
    for(i = 0; i<mat_order; i++){
        det = det * mat[(i*mat_order) + i];
    }
    return det * pow(-1,swapCount);
}


int main() {
    FILE* file;
    int num_matrices;
    int matrix_order;

    // Opening file in reading mode
    file = fopen("mat128_32.bin", "rb");

    fread(&num_matrices, sizeof(int), 1, file);
    printf("Number of matrices to be read = %d \n", num_matrices);
    fread(&matrix_order, sizeof(int), 1, file);
    printf("Matrices order = %d \n\n", matrix_order);


    for(int i = 1; i <= num_matrices; i++){
        printf("Processing matrix  : %d\n", i);
        double* matrix = malloc((matrix_order * matrix_order) * sizeof(double));
        read_matrix(matrix, file, matrix_order);

        /*for(int j = 0; j < (matrix_order * matrix_order); ++j){
            printf("%.2f ",matrix[j]);
            if (((j+1) % matrix_order) == 0){
                printf("\n");
            }
        }*/

        printf("Determinant : %e\n\n", determinant(matrix_order, matrix));

        free(matrix);
    }
    // Closing the file
    fclose(file);
    return 0;
}

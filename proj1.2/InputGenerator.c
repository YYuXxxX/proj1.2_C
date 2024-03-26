#include "InputGenerator.h"
#include <stdlib.h>
#include <time.h>

void generateMatrix(int rows, int cols, int matrix[7][7]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

void writeInput(FILE *file, int rows, int cols, int matrix[7][7]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d", matrix[i][j]);
            if (j < cols - 1) {
                fprintf(file, ",");
            }
        }
        if (i < rows - 1) {
            fprintf(file, ";");
        }
    }
}

void generateInputFile(const char *filename) {
    FILE *file = fopen("D:\\CS110\\proj1.2\\input.txt", "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < 3; i++) {
        // For simplicity, using fixed sizes
        int inputRows = 5;
        int inputCols = 5;
        int kernelSize = 3;

        int inputMatrix[7][7], kernelMatrix[7][7];

        generateMatrix(inputRows, inputCols, inputMatrix);
        generateMatrix(kernelSize, kernelSize, kernelMatrix);

        writeInput(file, inputRows, inputCols, inputMatrix);
        fprintf(file, " ");
        writeInput(file, kernelSize, kernelSize, kernelMatrix);
        fprintf(file, "\n");
    }
    fclose(file);
}

void generateZeroPaddingInputFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    srand(time(NULL));

    for (int i = 0; i < 3; i++) {
        // For simplicity, using fixed sizes that are odd numbers
        int inputRows = 5;
        int inputCols = 5;
        int kernelSize = 3;

        int inputMatrix[7][7], kernelMatrix[7][7];

        generateMatrix(inputRows, inputCols, inputMatrix);
        generateMatrix(kernelSize, kernelSize, kernelMatrix);

        writeInput(file, inputRows, inputCols, inputMatrix);
        fprintf(file, " ");
        writeInput(file, kernelSize, kernelSize, kernelMatrix);
        fprintf(file, "\n");
    }

    fclose(file);
}

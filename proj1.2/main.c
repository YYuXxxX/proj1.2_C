#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputGenerator.h"

#define MAX_SIZE 100

typedef struct MatrixSize {
    int rows;
    int cols;
} MatrixSize;


void matrixConvolution(int inputRows, int inputCols, int inputMatrix[MAX_SIZE][MAX_SIZE],
                       int kernelRows, int kernelCols, int kernelMatrix[MAX_SIZE][MAX_SIZE],
                       int outputMatrix[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i <= inputRows - kernelRows; i++) {
        for (int j = 0; j <= inputCols - kernelCols; j++) {
            int sum = 0;
            for (int k = 0; k < kernelRows; k++) {
                for (int l = 0; l < kernelCols; l++) {
                    sum += inputMatrix[i + k][j + l] * kernelMatrix[k][l];
                }
            }
            outputMatrix[i][j] = sum;
        }
    }
}

void matrixConvolutionZeroPadding(int inputRows, int inputCols, int inputMatrix[MAX_SIZE][MAX_SIZE],
                              int kernelRows, int kernelCols, int kernelMatrix[MAX_SIZE][MAX_SIZE],
                              int outputMatrix[MAX_SIZE][MAX_SIZE]) {
    // Calculate padding width
    int padWidth = (kernelRows - 1) / 2;
    int paddedRows = inputRows + 2 * padWidth;
    int paddedCols = inputCols + 2 * padWidth;

    int paddedInput[MAX_SIZE][MAX_SIZE] = {0};
    for (int i = 0; i < inputRows; i++) {
        for (int j = 0; j < inputCols; j++) {
            paddedInput[i + padWidth][j + padWidth] = inputMatrix[i][j];
        }
    }

    // Perform convolution on the padded input matrix
    for (int i = 0; i <= paddedRows - kernelRows; i++) {
        for (int j = 0; j <= paddedCols - kernelCols; j++) {
            int sum = 0;
            for (int k = 0; k < kernelRows; k++) {
                for (int l = 0; l < kernelCols; l++) {
                    sum += paddedInput[i + k][j + l] * kernelMatrix[k][l];
                }
            }
            // Adjust the output index to match the original input matrix size
            outputMatrix[i][j] = sum;
        }
    }
}


void writeMatrixToFile(int rows, int cols, int matrix[MAX_SIZE][MAX_SIZE], const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Failed to open the file\n");
        return;
    }

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
    // Add an extra newline for separation between matrix outputs
    fprintf(file, "\n");
    fclose(file);
}

MatrixSize readMatrixFromString(char* s, int matrix[MAX_SIZE][MAX_SIZE]) {
    MatrixSize size = {0, 0};
    char *lineContext;
    char* lineToken = strtok_r(s, ";", &lineContext);
    int row = 0;
    while (lineToken != NULL) {
        int col = 0;
        char *numberContext;
        char* numberToken = strtok_r(lineToken, ",", &numberContext);
        while (numberToken != NULL) {
            matrix[row][col++] = atoi(numberToken);
            numberToken = strtok_r(NULL, ",", &numberContext);
        }
        if (row == 0) size.cols = col; // Set cols based on the first row
        row++;
        lineToken = strtok_r(NULL, ";", &lineContext);
    }
    size.rows = row;
    return size;
}

void processFile(const char* inputFilename, const char* outputFilename) {
    FILE* file = fopen(inputFilename, "r");
    if (file == NULL) {
        printf("Failed to open input file\n");
        return;
    }

    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int inputMatrix[MAX_SIZE][MAX_SIZE], kernelMatrix[MAX_SIZE][MAX_SIZE], outputMatrix[MAX_SIZE][MAX_SIZE];

        char* inputPart = strtok(buffer, " ");
        char* kernelPart = strtok(NULL, "\n");

        if (inputPart != NULL && kernelPart != NULL) {
            MatrixSize inputSize = readMatrixFromString(inputPart, inputMatrix);
            MatrixSize kernelSize = readMatrixFromString(kernelPart, kernelMatrix);

            matrixConvolution(inputSize.rows, inputSize.cols, inputMatrix, kernelSize.rows, kernelSize.cols, kernelMatrix, outputMatrix);
            writeMatrixToFile(inputSize.rows - kernelSize.rows + 1, inputSize.cols - kernelSize.cols + 1, outputMatrix, outputFilename);
        }
    }

    fclose(file);
}

void processZeroPaddingFile(const char* inputFilename, const char* outputFilename) {
    FILE* file = fopen(inputFilename, "r");
    if (file == NULL) {
        printf("Failed to open input file\n");
        return;
    }

    char buffer[4096];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int inputMatrix[MAX_SIZE][MAX_SIZE], kernelMatrix[MAX_SIZE][MAX_SIZE], outputMatrix[MAX_SIZE][MAX_SIZE];

        char* inputPart = strtok(buffer, " ");
        char* kernelPart = strtok(NULL, "\n");

        if (inputPart != NULL && kernelPart != NULL) {
            MatrixSize inputSize = readMatrixFromString(inputPart, inputMatrix);
            MatrixSize kernelSize = readMatrixFromString(kernelPart, kernelMatrix);
            matrixConvolutionZeroPadding(inputSize.rows, inputSize.cols, inputMatrix, kernelSize.rows, kernelSize.cols, kernelMatrix, outputMatrix);
            writeMatrixToFile(inputSize.rows, inputSize.cols, outputMatrix, outputFilename);
        }
    }

    fclose(file);
}


void clearOutputFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        fclose(file);
    }
}


int main() {
    const char* inputFilename = "D:\\CS110\\proj1.2\\input.txt";
    const char* outputFilename = "D:\\CS110\\proj1.2\\output.txt";

    clearOutputFile(outputFilename);

    //generateInputFile(inputFilename);
    generateZeroPaddingInputFile(inputFilename);


    //processFile(inputFilename, outputFilename);
    processZeroPaddingFile(inputFilename, outputFilename);

    return 0;
}

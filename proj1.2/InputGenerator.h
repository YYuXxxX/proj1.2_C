//
// Created by yuxin on 2024/3/20.
//

#ifndef PROJ1_2_INPUTGENERATOR_H
#define PROJ1_2_INPUTGENERATOR_H

#endif //PROJ1_2_INPUTGENERATOR_H

#ifndef INPUT_GENERATOR_H
#define INPUT_GENERATOR_H

#include <stdio.h>

void generateMatrix(int rows, int cols, int matrix[7][7]);
void writeInput(FILE *file, int rows, int cols, int matrix[7][7]);
void generateInputFile(const char *filename);
void generateZeroPaddingInputFile(const char *filename);

#endif // INPUT_GENERATOR_H


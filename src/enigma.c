#include "constraints.h"
#include "enigma.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



void printNumbersAsString(int lines[nLines][nCharsPerLine])
{
	for (int idx = 0; idx < nLines; idx++)
	{
		char line[nCharsPerLine+1];
		for (int idx2 = 0; idx2 < nCharsPerLine; idx2++)
		{
			line[idx2] = lines[idx][idx2];
		}
		line[nCharsPerLine] = '\0';
		printf("%s\n", line);
	}
}

void decipher(const int *line, int key, int *result){

    for (int idx = 0; idx < nCharsPerLine; idx++)
        result[idx] = line[idx];

    int* rotorKeys = (int*)malloc(sizeof(int) * nRotors);
    int remainder = key;
    for (int idx = 0; idx < nRotors; idx++){
        int divisor = pow(10, (nRotors - (1 + idx)));
        rotorKeys[idx] = (int)(remainder / divisor);
        remainder = (int)(remainder % divisor);
    }

    for (int rotorIdx = 0; rotorIdx < nRotors; rotorIdx++){
        int displacement = rotorKeys[rotorIdx];
        for (int idx = 0; idx < nCharsPerLine; idx++){
            result[idx] = result[idx] - displacement++;
        }
    }

    free(rotorKeys);
}


#include "constraints.h"
#include "enigma.h"



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

int* decipher(int line[], int key)
{
	int rawData[nCharsPerLine];

	for (int idx = 0; idx < nCharsPerLine; idx++)
	{
		rawData[idx] = line[idx];
	}

	int* rotorKeys = (int*)malloc(sizeof(int) * nRotors);
	int remainder = key;
	for (int idx = 0; idx < nRotors; idx++)
	{
		int divisor = pow(10, (nRotors - (1 + idx)));
		rotorKeys[idx] = (int)(remainder / divisor);
		remainder = (int)(remainder % divisor);
	}


	for (int rotorIdx = 0; rotorIdx < nRotors; rotorIdx++)
	{
		int displacement = rotorKeys[rotorIdx];
		for (int idx = 0; idx < nCharsPerLine; idx++)
		{
			rawData[idx] = rawData[idx] - displacement++;
		}
	}

	free(rotorKeys);
	return rawData;
}

void enigma()
{
	printf("ESTO ES LA ENTRADA: \n");
	printNumbersAsString(ciphered);
	printf("\n");
	printf("\n");

	printf("DESCIFRANDO...: \n");
	int deciphered[nLines][nCharsPerLine];
	for (int idx = 0; idx < nLines; idx++)
	{
		for (int lineKey = (int)pow(10, nRotors - 1); lineKey < (int)pow(10, nRotors); lineKey++)
		{
			int* p_deciphered = decipher(ciphered[idx], lineKey);
			
			char decipheredLine[nCharsPerLine];
			for (int idx = 0; idx < nCharsPerLine; idx++)
			{
				decipheredLine[idx] = p_deciphered[idx];
			}
			
			char stringKey[nRotors + 1];
			sprintf_s(stringKey, "%d", lineKey);
			if (!strncmp(stringKey, decipheredLine, nRotors))
			{
				for (int idx2 = 0; idx2 < nCharsPerLine; idx2++)
				{
					deciphered[idx][idx2] = decipheredLine[idx2];
				}
				printf("Descifrada linea %d con clave %d\n", idx, lineKey);
				break;
			}
		}
	}
	
	printf("\n");
	printf("ESTO ES LA SALIDA:\n");
	printNumbersAsString(deciphered);
	printf("\n");
	printf("\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 512

typedef unsigned char byte;

//create a file and return name as cstring
char* nameFile(char* fileName, int fileNumber);

//return true if begining of jpg is found
bool foundImage(byte buffer[], size_t length);


int main(int argc, char **argv) 
{
	FILE *card = fopen("card.raw", "r");
	FILE *outfile  = NULL;
   
	if (card == NULL)
	{
	   printf("File not found!");
	   return 1;
	}
	
	//file number (0 - 49)
	int fileNumber = 0;
	
	//name of new image file
	char *fileName = malloc(10 * sizeof(char));
	
	//tmp buffer to read too
	byte buffer[BUFFER_SIZE];
	
	//length of buffer
	size_t length = (sizeof(buffer) / sizeof(byte));
	
	//check if !EOF 
	while (fread(&buffer, sizeof(buffer), 1, card) == 1) 
	{
		if (foundImage(buffer, length))
		{
			if (outfile != NULL)
				fclose(outfile);
	
			outfile = fopen(nameFile(fileName, fileNumber), "w");
			fwrite(&buffer, sizeof(buffer), 1, outfile);
			fileNumber++;
		}
		else if (!(foundImage(buffer, length)) && (outfile != NULL))
		{
			fwrite(&buffer, sizeof(buffer), 1, outfile);
		}
	}
	
	//delete fileName
	free(fileName);
	fclose(card);
    return 0;
}

char* nameFile(char* fileName, int fileNumber)
{ 
	if ((fileNumber > 9) && (fileNumber < 50))
	{
		snprintf(fileName, 10, "0%d.jpg", fileNumber);
		return fileName;
	}
	else if ((fileNumber < 0) || (fileNumber > 49))
	{
		printf("Invalid number (must be between 0 and 49)!\n");
		exit(1);
	}
	snprintf(fileName, 10, "00%d.jpg", fileNumber);
	return fileName;
}

bool foundImage(byte buffer[], size_t length)
{
	// beginning of a jpg
	byte header_1[] = {0xff, 0xd8, 0xff, 0xe0}; 
	byte header_2[] = {0xff, 0xd8, 0xff, 0xe1}; 
	
	for (int i = 0; i < sizeof(header_1); i++)
	{
		if ((buffer[i] != header_1[i]) && (buffer[i] != header_2[i]))
			return false;
	}
	return true;
}






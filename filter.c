#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
//despues de definir una macro no hay que poner ;
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

int main(int argc, char *argv[])
{
	int bytes_read;
	int i = 0;
	int j = 0;
	int buffer_len;
	char *buffer = calloc(BUFFER_SIZE, sizeof(char));
	//char *filter = argv[1];
	char *line;
	line = calloc(50, sizeof(char));
	//bytes_read = read(0, buffer, BUFFER_SIZE);
	while (buffer[i] != '\n')
	{	
		bytes_read = read(0, buffer, BUFFER_SIZE);
		buffer_len = strlen(buffer);
		while(i < buffer_len)
		{
			line[j] = buffer[i];
			i++;
			j++;
		}
		buffer[buffer_len] = '\0';
		if (bytes_read < BUFFER_SIZE)
			break;

		//sentence = memmove(sentence, buffer, strlen(buffer));
		printf("buffer[i]: %c\n", buffer[i]);
		printf("buffer: %s\n", buffer);
		//printf("bucle: %i\n", i);
		i = 0;
	}
	printf("%i\n", i);
	printf("buffer: %s\n", buffer);
	printf("line: %s\n", line);
}
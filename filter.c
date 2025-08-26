#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

int find_and_replace(char *string, char *tofind)
{
	int i = 0;
	int j = 0;
	int len = strlen(tofind);

	if (tofind[j] == '\0')
		return 1;
	while (string[i] != '\0')
	{
		j = 0;
		while (tofind[j] != '\0' && (string[i + j]) != '\0' && (string[i + j]) == tofind[j])	
			j++;
		if (tofind[j] == '\0')
		{
			int k = 0;
			while(k < len)
			{
				string[i + k] = '*';
				k++;
			}
		}
		i++;
	}
	return 0;
}

char *gnl(char * line)
{
	int i = 0;
	int j = 0;
	int bytes_read;
	char *buffer = calloc(BUFFER_SIZE, sizeof(char));
	int finished = 0;
	int limit = BUFFER_SIZE;
	line = calloc(BUFFER_SIZE, sizeof(char));

	while (!finished)
	{	
		i = 0;
		bytes_read = read(0, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break;
		if (bytes_read < BUFFER_SIZE)
			break;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
			{
				line[j] = '\0';
				finished = 1;
				break;
			}
			if (j >= limit)
			{
				limit = limit + BUFFER_SIZE;
				char *tmp = realloc(line, limit + 1);
				//free(line); ya se hace en realloc
				line = tmp;
			}
			line[j] = buffer[i];
			i++;
			j++;
		}
	}
	free (buffer);
	line[j] = '\0';
	return line;
}


int main(int argc, char *argv[])
{

	char *filter = argv[1];
	char *line = gnl(line);
	
	find_and_replace(line, filter);

	printf("%s", line);
	free(line);
	return 0;
}


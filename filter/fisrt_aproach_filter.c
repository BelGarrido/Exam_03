#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 50
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
	int i;
	int j = 0;
	int bytes_read;
	int finished = 0;
	int limit = BUFFER_SIZE;
	char buffer[BUFFER_SIZE];
	line = malloc(BUFFER_SIZE);

	if(!line)
		return NULL;
	while (!finished)
	{	
		i = 0;
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return NULL;
		else if (bytes_read == 0)
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
				if (!tmp)
					return NULL;
				line = tmp;
			}
			line[j] = buffer[i];
			i++;
			j++;
		}
	}
	line[j] = '\0';
	return line;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		perror("Error");
		return 2;
	}
	char *filter = argv[1];
	char *line = gnl(line);
	if (!line)
	{
		perror("Error");
		return 1;
	}
	find_and_replace(line, filter);
	printf("%s", line);
	free(line);
	return 0;
}


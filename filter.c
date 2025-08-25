#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
//despues de definir una macro no hay que poner ;
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

void *find_and_replace(char *s, char *filter)
{
	int i = 0;
	int j = 0;
	char *new;
	new = malloc(strlen(s));

	while(filter[j] != '\0')
	{
		while(s[i] != '\0')
		{

		}
	}
	return NULL;
}
int main(int argc, char *argv[])
{
	int bytes_read;
	int i = 0;
	int j = 0;
	char *buffer = calloc(BUFFER_SIZE, sizeof(char));
	char *filter = argv[1];
	char *line;
	int finished = 0;
	line = calloc(BUFFER_SIZE, sizeof(char));
	int limit = BUFFER_SIZE;
	while (!finished)
	{	
		i = 0;
		bytes_read = read(0, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break;
		if (bytes_read < BUFFER_SIZE)
			break;
		while(i < bytes_read)
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
				char *tmp = realloc(line, limit);
				//free(line); ya se hace en realloc
				line = tmp;
			}
			line[j] = buffer[i];
			i++;
			j++;
		}		
	}
	free (buffer);
	printf("line: %s\n", line);
	free(line);
}

// no se como gestionar la memoria y copiar todo en un string sin causar problemas

char *ft_strjoin(char *s1, char *s2)
{
	char *result;
	int i = 0;
	int j = 0;

	result = malloc(strlen(s1) + strlen(s2) * sizeof(char));
	if(!result)
		return NULL;
	while(s1[i] != '\0')
	{
		result[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while(s2[i] != '\0')
	{
		result[j] = s2[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return result;
}

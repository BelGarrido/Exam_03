#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
//despues de definir una macro no hay que poner ;
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

char* create_filter(int filter_size){
	char *ast;
	int z = 0;

	ast = calloc(filter_size, sizeof(char) + 1);
	while(z < filter_size)
	{
		ast[z] = '*';
		z++;
	}
	ast[z] = '\0';
	return ast;
}
void find_and_replace(char *string, char *tofind)
{
	int i = 0;
	int j = 0;
	char *ast;

	if (tofind[j] == '\0')
		return ;
	while (string[i] != '\0')
	{
		j = 0;
		while (tofind[j] != '\0' && (string[i + j]) != '\0' && (string[i + j]) == tofind[j])
			j++;
		if (tofind[j] == '\0')
		{
			ast = create_filter(strlen(tofind));
			memmove(string + i, ast, strlen(ast));
			free(ast);
		}
		i++;
	}
	return ;
}

char *gnl(char * line)
{
	int i = 0;
	int j = 0;
	int bytes_read;
	char buffer[BUFFER_SIZE];
	int limit = BUFFER_SIZE;

	line = calloc(BUFFER_SIZE, sizeof(char));

	while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
	{	
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
			{
				line[j] = '\0';
				return line;
			}
			if (j >= limit)
			{
				limit = limit + BUFFER_SIZE;
				line = realloc(line, limit + 1);
			}
			line[j] = buffer[i];
			i++;
			j++;
		}
	}
	return NULL;
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


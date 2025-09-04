#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
//despues de definir una macro no hay que poner ;
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

char* create_filter(int filter_size)
{
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

char *gnl(char *line)
{
	int i = 0;
	int j = 0;
	int bytes_read;
	char buffer[BUFFER_SIZE];
	int limit = BUFFER_SIZE;

	line = calloc(BUFFER_SIZE, sizeof(char));
	//comprobación de seguridad
	while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
	{	
		i = 0;
		printf("bucle de bytes > 0 ---> %i\n", bytes_read);
		while (i < bytes_read)
		{
			printf("bucle de bytes i < bytes read\n");
			if (j >= limit)
			{
				printf("bucle de j > limits: realloc\n");
				limit = limit + BUFFER_SIZE;
				line = realloc(line, limit + 1);
				//comprobación de seguridad
			}
			line[j] = buffer[i];
			i++;
			j++;
		}
		printf("salida\n");
	}
/* 	while(buffer[i] != '\0')
	{
		line[j] = buffer[i];
		i++;
		j++;
	} */
	if (bytes_read == 0)
	{
		printf("bucle de bytes < 0\n");
		if (line && line[0] != '\0')
		{
			buffer[0] = '\0';
			return line;
		}
		free(line);
		return NULL;
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Uso: %s <palabra_a_filtrar>\n", argv[0]);
		return 2;
	}
	char *filter = argv[1];
	char *line;
	
	while (line = gnl(line))
	{
		find_and_replace(line, filter);
		printf("%s", line);
		free(line);
	}
	if (!line)
	{
		fprintf(stderr, "Error: no se pudo leer ninguna línea\n");
		return 1;
	}
	return 0;
}


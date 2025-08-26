#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
//despues de definir una macro no hay que poner ;
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

char* create_filter(char* str){
	char* filter;
	int tofind_len = strlen(str);
	int z = 0;
	filter = malloc (tofind_len*sizeof(char));
	while(z<tofind_len){
		filter[z]='*';
		z++;
	}
	return filter;
}
int find_and_replace(char *string, char *tofind)
{
	int i = 0;
	int j = 0;
	char *filter;
	//filter = "************************************";
	if (tofind[j] == '\0')
		return 0;
	while (string[i] != '\0')
	{
		j = 0;
		while (tofind[j] != '\0' && (string[i + j]) == tofind[j])
		{
			j++;
			//comprobación de n (?)
		}
		if (tofind[j] == '\0')
		{
			filter = create_filter(tofind);
			memmove(string + i, filter, strlen(filter));
			//return (i);
		}
		i++;
	}
	free(filter);
	return 0;
}

char *gnl(char * line)
{
	int i = 0;
	int j = 0;
	int bytes_read;
	line = calloc(BUFFER_SIZE, sizeof(char));
	char buffer[BUFFER_SIZE];
	int finished = 0;
	int limit = BUFFER_SIZE;
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
				char *tmp = realloc(line, limit+1);
				//free(line); ya se hace en realloc
				line = tmp;
			}
			line[j] = buffer[i];
			i++;
			j++;
		}		
	}
	line[j]='\0';
	//free (buffer);
	//printf("line: %s\n", line);
	return line;

}


int main(int argc, char *argv[])
{

	char *filter = argv[1];
	char *line = gnl(line);
	
	find_and_replace(line, filter);

	printf("%s", line);
	return 0;
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

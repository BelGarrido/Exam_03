//hay que añadir todas las librerias
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

char *ft_strchr(char *s, int c)
{
	int i = 0;
	while(s[1] != c)
		i++;
	if (s[i] == c)
		return s + i;
	else
		return NULL;
}

size_t ft_strlen(char *s)
{
	size_t i = 0;
	while(s[i] != '\0')
		i++;
	return i;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	while (--n > 0)
		((char*)dest)[n - 1] = ((char*)src)[n - 1];
	return dest;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if(!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1); //sospecho que hay que quitar este free, ya que no se reserva memoria para s1 aqui
	*s1 = tmp;
	return 1;
}

int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest > src)
		return ft_memcpy(dest, src, n);
	else if(dest == src)
		return dest;
		size_t i = ft_strlen(((char*)src) - 1); //mal (?)
	while (i >= 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i--;
	}
	return dest;
}

char *get_next_line(int fd)
{
		//debug
	printf("DEBUG 1: get_next_line\n");
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
		//debug
	printf("DEBUG 2: get_next_line\n");
	char *tmp = ft_strchr(b, '\n'); // bucle?
		//debug
	printf("DEBUG 3: get_next_line\n");
	while(!tmp)
	{
		//debug
		printf("DEBUG 1: get_next_line\n");
		if (!str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE);
		if(read_ret == -1)
			return NULL;
		b[read_ret] = 0;
	}
	if(!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	return ret;
}

// ---------------------------------

int main(void)
{
	int fd = open("txt.txt", O_RDONLY);
	char *line;
	while (line)
	{
		printf("DEBUG 1: main\n");
		line = get_next_line(fd);
		printf("main: %s", line);	
	}
	return 0;
}
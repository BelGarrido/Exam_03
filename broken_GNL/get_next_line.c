//hay que añadir todas las librerias
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 50
#endif

char *ft_strchr(char *s, int c)
{
	int i = 0;
	while(s[i] != '\0') //[1] cambiar por [i]
	{
		if (s[i] == c)
			return s + i;
		i++;
	} 
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
	if (n != 0) //aqui habia segfault
	{
		while (n > 0)
		{
			((char*)dest)[n - 1] = ((char*)src)[n - 1];
			n--;
		}
	}
	return dest;
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 + 1);
	if(!tmp)
		return 0;
	//printf("DEBUG 2: str_append_mem\n");
	ft_memcpy(tmp, *s1, size1); // segfalut cuando s1 esta vacio
	//printf("DEBUG 3: str_append_mem\n");
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	//free(*s1); //sospecho que hay que quitar este free, ya que no se reserva memoria para s1 aqui
	*s1 = tmp;
	return 1;
}

int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2) + 1); 
}

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	char		*d;
	const char	*s;
	int			i;

	d = (char *)dest;
	s = (const char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	if (d > s)
	{
		while (count--)
			d[count] = s[count];
	}
	else
	{
		while (i < (int)count)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

/* void *ft_memmove(void *dest, const void *src, size_t n)
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
} */

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	//static char * b = malloc(BUFFER_SIZE + 1 * sizeof(char));
	char *ret = "";
	printf("BUFFER before while: \"%s\"\n", b);
	char *tmp = ft_strchr(b, '\n'); // bucle infinito
	printf("TMP before while: \"%s\"\n", tmp);
	while(!tmp)
	{
		printf("DEBUG 1: gnl bucle tmp\n");
		//aqui copia en ret
		printf("BUFFER: %s\n", b);
		printf("RET_PREV: %s\n", ret);
		tmp = ft_strchr(b, '\n');
		if (tmp)
			break;
		if (!str_append_str(&ret, b))
			return NULL;
		printf("RET_POST: %s\n", ret);
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (b[0] == 0)
			break;
		printf("--------------Lectura: %i\n", read_ret);		
		if(read_ret == -1)
			return NULL;
		b[read_ret] = 0;
		if(read_ret == 0)
		{
			return ret;
		} 
	}
	printf("control\n");
	if(!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	printf("control2\n");
	printf("BUFFER after while: \"%s\"\n", b);
	printf("TMP after while: \"%s\"\n", tmp);

	ft_memmove(b, tmp + 1, ft_strlen(b) - (tmp - b - 1));
	//ft_memcpy(b, tmp, ft_strlen(b) - (tmp - b));
	printf("BUFFER fuera: %s\n", b);
	printf("return_ret length: %lu\n", ft_strlen(ret));			
	return ret;
}

// ---------------------------------

int main(void)
{
	int fd = open("txt.txt", O_RDONLY);
	char *line;
	while (line)
	{
		line = get_next_line(fd);
		printf("main: %s", line);	
	}
	return 0;
}
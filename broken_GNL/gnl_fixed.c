// #1 LIBRERIAS
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
// #1 
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

char *ft_strchr(char *s, int c)
{
	int i = 0;
	// reestructurar el bucle + [1]es incorrecto
	/* while(s[1] != c)
		i++; */
	while(s[i] != '\0')
	{
		if (s[i] == c)
			return s + i;
		i++;
	}
	return NULL;
}

size_t ft_strlen(char *s)
{
	// comprobación de seguridad de s
	if (!s) // añadido
		return 0; //añadido
	size_t i = 0;
	while(s[i] != '\0')
		i++;
	return i;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	// comprobación de seguridad no se si es necesario
	//while (--n > 0) cambio por bucle
	if (n != 0)
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
	// comprobación de (*s1)
	if (*s1)
		ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = '\0';
	free(*s1);
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
	//size_t i = ft_strlen(((char*)src) - 1);
	size_t i = 0;
	// condicion while (i >= 0) incorrecta
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		//i--;
		i++;
	}
	return dest;
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = ft_strchr(b, '\n');

	while(!tmp)
	{
		if (!str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE);
		if(read_ret == -1)
		{
			free(ret); // añadido
			return NULL;
		}
		// prefiero b[read_ret] = '\0' a b[read_ret] = 0;;
		//b[read_ret] = 0;
		b[read_ret] = '\0';
		// condicion de salida cuando se leen 0 bytes, es decir ya no hay nada que leer
		if (read_ret == 0) //añadido
		{
			if (ret && ret[0] != '\0') //añadido
			{
				// "vaciamos" el  buffer
				b[0] = '\0'; //añadido
				return(ret); //añadido
			}
			free(ret); //añadido
			return NULL; //añadido
		}
		// condición de avance en el bucle
		tmp = ft_strchr(b, '\n'); // añadido
	}
	if(!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	// actualizacion del buffer con lo que ya se ha copiado
	ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1); //añadido
	return ret;
}

// ---------------------------------

int main(void)
{
	int fd = open("txt.txt", O_RDONLY);
	char *line;

	if (fd == -1)
	{
		printf("Error opening file");
		return 1;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}
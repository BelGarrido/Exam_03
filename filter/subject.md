### FILTER.C

Escribe un programa que reciba un solo argumento s.
Tu programa debe leer desde la entrada stdin y escribir todo el contenido en la salida eestandar stdout, excepto que cada ocurrencia de s debe ser reemplazada por '*' (tantos asteriscos como la longitud de s).
TU programa se testeara con tamaños de bufer aleatorios, usando una función read personalizada. Por tanto el bufer que configures en tu programa se llenará con un número diferente de caracteres en cada llamada.
En caso de error durante una lectura o al hacer malloc debe imprimir 'Error: ' seguido del mensaje de error en stderr y devolver 1.
Funciones permitidas: read, write, strlen, memmem, memmove, malloc, calloc, realloc, free, printf, fprint, stdout, stderr, perror.

### 🟩 Funciones de Entrada/Salida

> `ssize_t read(int fd, void *buf, size_t count);`  
> - `fd`: descriptor de archivo (por ejemplo, 0 para stdin)  
> - `buf`: puntero al buffer donde guardar los datos leídos  
> - `count`: número máximo de bytes a leer  
> - Leer datos desde un archivo o entrada estándar.

> `ssize_t write(int fd, const void *buf, size_t count);`  
> - `fd`: descriptor de archivo (1 = stdout, 2 = stderr)  
> - `buf`: buffer con los datos a escribir  
> - `count`: número de bytes a escribir  
> - Escribir datos en un archivo o salida estándar.

> `int printf(const char *format, ...);`  
> - `format`: cadena de formato  
> - `...`: argumentos variables según el formato  
> - Imprimir texto en la salida estándar (stdout).

> `int fprintf(FILE *stream, const char *format, ...);`  
> - `stream`: flujo de salida (como stdout o stderr)  
> - `format`: cadena de formato  
> - `...`: argumentos variables  
> - Imprimir texto en un archivo o flujo específico.

> `void perror(const char *s);`  
> - `s`: mensaje personalizado  
> - Imprimir un mensaje de error relacionado con `errno`.

> `extern FILE *stdout;`  
> `extern FILE *stderr;`  
> - Son flujos estándar de salida y error, respectivamente. Se usan con `fprintf`, `fputs`, etc.

---

### 🟨 Funciones de Manejo de Memoria

> `void *malloc(size_t size);`  
> - `size`: cantidad de bytes a asignar  
> - Reservar memoria dinámica.

> `void *calloc(size_t nmemb, size_t size);`  
> - `nmemb`: número de elementos  
> - `size`: tamaño de cada elemento  
> - Reservar memoria e inicializarla en 0.

> `void *realloc(void *ptr, size_t size);`  
> - `ptr`: puntero a la memoria previamente reservada  
> - `size`: nuevo tamaño  
> - Cambiar el tamaño de un bloque de memoria.

> `void free(void *ptr);`  
> - `ptr`: puntero a memoria previamente reservada  
> - Liberar memoria dinámica.

---

### 🟦 Funciones de Manipulación de Memoria

> `size_t strlen(const char *s);`  
> - `s`: cadena de caracteres  
> - Obtener la longitud de una cadena (sin contar el `\0`).

> `void *memmem(const void *haystack, size_t haystacklen, const void *needle, size_t needlelen);`  
> - `haystack`: puntero al bloque de memoria donde buscar  
> - `haystacklen`: tamaño del bloque  
> - `needle`: lo que se desea encontrar  
> - `needlelen`: tamaño del patrón a buscar  
> - Buscar un bloque de memoria dentro de otro.

> `void *memmove(void *dest, const void *src, size_t n);`  
> - `dest`: destino  
> - `src`: origen  
> - `n`: número de bytes a copiar  
> - Copiar memoria manejando correctamente solapamientos.

# ✅ Corrección del ejercicio `filter.c`

## 📋 Subject
> Escribe un programa que reciba un solo argumento `s`.  
> El programa debe leer desde `stdin` y escribir en `stdout` todo el contenido, excepto que cada ocurrencia de `s` debe ser reemplazada por `'*'` (tantos asteriscos como la longitud de `s`).  
>
> El programa será testeado con tamaños de buffer aleatorios, usando una función `read` personalizada.  
> En caso de error en `read` o en `malloc/realloc/calloc` debe imprimir `Error: <mensaje>` en `stderr` y devolver `1`.  
>
> Funciones permitidas:  
> `read`, `write`, `strlen`, `memmem`, `memmove`, `malloc`, `calloc`, `realloc`, `free`, `printf`, `fprintf`, `stdout`, `stderr`, `perror`.

---

## 🔎 Observaciones sobre tu código

### ✔️ Cosas correctas
- Validación de número de argumentos (`argc != 2`).
- Uso de memoria dinámica (`malloc`, `calloc`, `realloc`, `free`).
- Manejo básico de errores con `perror`.
- Sustitución de ocurrencias de `s` en la cadena (`find_and_replace`).

---

### ❌ Problemas detectados
1. **Lectura incompleta**  
   - Tu función `gnl` solo lee **una línea** (hasta `\n`).  
   - El subject exige leer **todo `stdin`** hasta EOF.

2. **Patrones partidos entre lecturas**  
   - Como el buffer se llena con tamaños aleatorios, una ocurrencia de `s` puede quedar dividida en dos lecturas de `read`.  
   - Tu código no maneja ese caso → falla en encontrar el patrón.

3. **Salida con `printf`**  
   - El subject pide usar `write` para la salida estándar.  
   - Usar `printf` no garantiza comportamiento correcto bajo el corrector automático.

4. **Manejo de errores**  
   - En el caso de argumentos inválidos, llamas a `perror("Error")`.  
   - Como no hay `errno` establecido, imprime `"Error: Success"`, lo cual es incorrecto.  
   - El subject pedía `"Error: <mensaje>"` en `stderr`.

5. **Uso de funciones sugeridas**  
   - El enunciado sugería `memmem` y `memmove` para búsqueda y reemplazo.  
   - Tú reimplementaste la búsqueda “a mano”. Puede no penalizar, pero es arriesgado frente a un corrector estricto.

---

## ⚖️ Veredicto
**❌ El ejercicio NO pasa el subject.**

### Razones principales
- Solo procesa una línea en lugar de toda la entrada.  
- No maneja patrones que se dividen entre dos lecturas de `read`.  
- Uso incorrecto de `perror` para errores de argumentos.  
- Uso de `printf` en lugar de `write` para la salida.  

---

## 🔧 Recomendaciones para aprobar
1. Sustituir `gnl` por un bucle que lea **bloques de `stdin` hasta EOF**.  
2. Usar `memmem` para buscar ocurrencias de `s` dentro de cada bloque.  
3. Manejar correctamente el **resto de datos** si el patrón `s` queda partido entre dos lecturas.  
4. Usar siempre `write(1, buf, len)` para salida a `stdout`.  
5. Para errores en argumentos:  
   ```c
   fprintf(stderr, "Error: invalid arguments\n");
   return 1;
5. Para errores en read o memoria: 
	 ```c
	perror("Error");
	return 1;	

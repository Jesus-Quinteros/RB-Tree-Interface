# Red-Black Tree Interface

Este programa permite visualizar el funcionamiento básico de un Árbol Rojinegro basado en la teoría del libro Introduction to Algorithms (CLRS) implementado en lenguaje C, mediante el uso de la API de OpenGL.

## Características

- **Lenguaje:** C, cualquier estándar (c89, c99, c11, c17 o c23) funciona para este proyecto.
- **Gráficos**: OpenGL.
- **Correcciones:** Se implementa una corrección de la primera línea en la función `RB-Insert-Fixup` del libro en mención, asegurando así un buen funcionamiento tanto de la estructura del árbol como del programa.
- **Multiplataforma:** Para ello, se requiere diferente uso de las `.dll` en el archivo Makefile:
    - Para Windows `-lfreeglut -lopengl32 -lglu32 -lm`
    - Para Linux `-lGL -lGLU -lglut -lm`
- **Gestión de memoria:** uso de punteros y métodos nativos del lenguaje.
- **Arquitectura:** Modular.

## Requerimientos

1. Compilador para C: gcc
2. Herramienta para automatización de compilación y dependencias: GNU-Make
3. SO: Linux o Windows.
4. Las `.dll`s necesarias según el SO de ejecución.

- "`OpenGL`" ya viene integrado en los controladores de la tarjeta gráfica independiéntemente del SO, caso se presente algún problema se recomienda actualizar los drivers
  o consultar las páginas oficiales del proveedor de la GPU.

## Compilación

En ambos SO simplemente ejecutar:

```bash
make
```

Esto generá los archivos necesarios además del ejecutable principal `main`.

- Si se desea limpiar los archivos temporales generados por la compilación para una posterior y mejor recompilacion:

  ```bash
  make clean
  ```

## Ejecución

  Considerando que `"datafile"` es un archivo de texto que contiene los datos que procesará el programa (un dato por línea). Pueden ser los archivos del proyecto
  `data1`, `data2` o cualquier otro que se desee usar considerando el formato de los mismos.

- En Arch Linux:

  ```bash
  ./main < datafile
  ```

- En windows:

  ```bash
  // En PowerShell
  Get-Content datafile | ./main
  // En CMD
  main < datafile

## Contribuciones

  ¡Contribuciones son bienvenidas! Si tienes ideas para mejorar este proyecto, por favor, abre un issue o una pull request.

---

¡Esperamos que disfrutes programando o aprendiendo de este proyecto! Si tienes alguna pregunta o sugerencia, no dudes en contactarme.

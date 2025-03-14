#include <stdio.h>
#include <windows.h>
#include <ctype.h>  // Para toupper()


/*
1) Escribir un programa que copie un fichero de entrada en otro de salida convirtiendo en
mayúsculas todas las letras.

	//intento abrir el archivo que deseo copiar sino imprimo error.
	//creo el archivo dodne lo quieor copiar sino imprmo error.
	//cojo caracter del archivo original y paso a mayusculas.
	//pego la mayuscula y la meto en el archivo copia;
	//hago esto mientras que c!= EOF.
	//cierro los dors ficheros.
*/


// inicializacio de la funcion para copiar en mayusculas 
void copiarMayusculas();

main() {

	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	//invoco la funcion copiar  con mayusculas
	copiarMayusculas();

}

void copiarMayusculas() {
    char nombreArchivoOriginal[256];
    char nombreArchivoCopia[256];

    printf("Dame el NOMBRE DEL ARCHIVO QUE DESEAS COPIAR: ");
    gets(nombreArchivoOriginal);

    printf("Dame el NOMBRE EN EL QUE LO QUIERES COPIAR: ");
    gets(nombreArchivoCopia); 

    FILE* archivoOriginal;
    FILE* archivoCopia;

    // Abrir archivo original
    fopen_s(&archivoOriginal, nombreArchivoOriginal, "r");
    if (archivoOriginal == NULL) {
        printf("No se pudo abrir el archivo original.\n");
        return;
    }

    // Abrir archivo de copia
    fopen_s(&archivoCopia, nombreArchivoCopia, "w");
    if (archivoCopia == NULL) {
        printf("No se pudo abrir el archivo donde copiar.\n");
        fclose(archivoOriginal);
        return;
    }

    // Copiar caracteres en mayúsculas
    char c;
    while ((c = fgetc(archivoOriginal)) != EOF) {
        fputc(toupper(c), archivoCopia);
    }

    // Cerrar los archivos
    fclose(archivoOriginal);
    fclose(archivoCopia);

    printf("Archivo copiado correctamente en mayúsculas.\n");
}
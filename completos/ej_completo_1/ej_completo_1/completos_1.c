#include <stdio.h>
#include <windows.h>
/*
1) Se quiere programar una aplicación para gestionar el mantenimiento de un fichero directo
maestro de 10 productos. Por cada producto se almacena la siguiente información:
	• Descripción: la del producto. (20 caracteres)
	• Precio: el precio de venta del producto. (entero largo)
	• Existencias: las unidades disponibles de un producto. (entero)
	• Estado: indica si la posición está disponible u ocupada

El programa principal mostrará y gestionará un menú como el siguiente:
	i) Inicializar fichero: Crea el fichero con todas las posiciones disponibles.
	ii) Realizar operación: Pregunta si se quiere comprar o vender un producto, la
		posición del producto (código) y el número de unidades. Si se quiere comprar se
		acumularán las unidades compradas a las existencias del producto, si se quiere
		vender se restarán. Tener en cuenta que si se quieren vender más unidades de las
		existentes hay que mostrar mensaje de error.
	iii) Alta de producto. Pide los datos de un producto y lo da de alta en el fichero.
	iv) Baja de producto. Pide la posición del producto y marca como disponible esa
		
	v) Mostrar almacén: genera un informe a un fichero de texto con toda la información
		del fichero de productos, como el que sigue:
		Codigo Descripción Unidades Precio
		xxxxxx xxxxxxxxx xxxxxxxx xxxxx


	vi) Salir. Termina la ejecución del programa.

		Se pide:
			a) Definir el tipo de datos PRODUCTO que será el de los registros del fichero, de forma
			necesaria para que almacene los siguiente datos de un producto:
			Descripción: la del producto. (20 caracteres)
			Precio: el precio de venta del producto. (entero largo)
			Unidades: las unidades disponibles de un producto. (entero)
			b) Programar el programa principal para que muestre y gestione el menú indicado.
			c) Programar la función InicializarFichero para que se comporte como se ha descrito.
			d) Programar la función RealizarOperación para que se comporte como se ha indicado.
			e) Programar la función AltaProducto para que se comporte como se ha indicado.
			f) Programar la función BajaProducto para que se comporte como se ha indicado.
			g) Programar la función MostrarAlmacen para que se comporte como se ha indicado.
*/

//tamaños y ficheros
#define TAM 10
#define FICHERO "datos.txt"

//estructuras
typedef struct {
	char descripcion[20];
	int precio;
	int existencias;
	int estado;
}PRODUCTO;

//funciones
int menu();
void inicializarFichero();
void realizarOperacion();
void altaProducto();
void bajaProducto();
void mostrarAlmacen();

main() {

	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	
	void (*funciones[])() = { inicializarFichero,realizarOperacion,altaProducto,bajaProducto,mostrarAlmacen };

	int opc = menu();
	while(opc != 6) {
		(*funciones[opc- 1])();
		opc = menu();
	}

}

int menu() {
	int opc = -1;
	do {
		printf("dame un opcion:\n 1-Inicializar fichero\n 2-realizarOperacion\n 3-altaProducto\n 4-bajaProducto\n 5-mostrarAlmacen \n 6-SALIR \n  ");
		scanf_s("%d", &opc);
	} while (opc > 6 || opc < 0);
	return opc;
}

void inicializarFichero() {
	FILE* puntero_a_fichero;
	fopen_s(&puntero_a_fichero, FICHERO, "wb");    // w,wb,r,rb,a,ab  'w' simprelo crea desde cero exista o no y la 'a' si no exoiste lo crea y si existe añade.
	if (puntero_a_fichero == NULL) {
		printf("Error al inicializar el fichero");
		return;
	}
	PRODUCTO producto;
	for (int i = 0; i < TAM; i++) {
		producto.estado = 0;
		fseek(puntero_a_fichero, sizeof(producto)*(i), SEEK_SET); //me posiciono aunk en est caso no es necesario lo dejo como ejemplo
		fwrite(&producto,sizeof(producto), 1, puntero_a_fichero);
	}
	fclose(puntero_a_fichero);
}


void realizarOperacion() {
	//abrimos el puntero en modo lectura binaria mas escritura "rb+"
	FILE* puntero_a_fichero;
	fopen_s(&puntero_a_fichero, FICHERO, "rb+");
	if (puntero_a_fichero == NULL) {
		printf("Error al inicializar el fichero\n");
		return;
	}
	//preguntamos tipo de opereacion
	int opc = -1;
	do {
		printf("Que desea realizar 1-comprar, 2-venta\n");
		scanf_s("%d", &opc);
	} while (opc > 2 || opc < 1);
	//preguntamos posicion del prodcuto a modificar
	int pos = -1;
	do {
		printf("Conque proeducto deseas realizarla la operacion dame posicion del 0 al 9\n");
		scanf_s("%d", &pos);
	} while (pos > 9 || pos <0);
	//pido unidades
	printf("Para cauntas unidades deseas realizar esta opereacion?");
	int unidades;
	scanf_s("%d", &unidades);

	//nos posicionamos en el fichero
	PRODUCTO producto;
	fseek(puntero_a_fichero, sizeof(producto)*pos, SEEK_SET);
	fread(&producto, sizeof(producto), 1, puntero_a_fichero);

	if (producto.estado == 0) {
		printf("producto no inicializado\n");
		fclose(puntero_a_fichero);
		return;
	}
	else {
		if (opc == 1) {  //comprar
			producto.existencias + unidades;
			
		}
		else {  //vender
			if (unidades > producto.existencias) {
				printf("No hay suficientes unidades\n");
				fclose(puntero_a_fichero);
				return;
			}
			else {
				producto.existencias - unidades;
			}
		}
		fseek(puntero_a_fichero, sizeof(producto) * pos, SEEK_SET);
		fwrite(&producto, sizeof(producto), 1, puntero_a_fichero);
	}
	fclose(puntero_a_fichero);
}




void altaProducto(){

	//abro el fichero antes de nada ya que seria en vano preguntar y despues de todo que no exista el ficherio
	FILE* puntero_a_fichero;
	fopen_s(&puntero_a_fichero, FICHERO, "rb+");
	if (puntero_a_fichero == NULL) {
		printf("Error al inicializar el fichero\n");
		return;
	}

	//preguntamos posicion del prodcuto a modificar
	int pos = -1;
	do {
		printf("Conque proeducto deseas realizarla la operacion dame posicion del 0 al 9\n");
		scanf_s("%d", &pos);
	} while (pos > 9 || pos < 0);

	//creo el elemento producto
	PRODUCTO producto;
	fseek(puntero_a_fichero, sizeof(producto) * pos, SEEK_SET);
	fread(&producto, sizeof(producto), 1, puntero_a_fichero);  //posiciono el puntero pàra que apunte al producto aue deseamos dentor del ficchero
	if (producto.estado == 1) { //si ya existe el producto cancelo operacion
		printf("El prodcuto ya existe\n");
		fclose(puntero_a_fichero);
		return;
	}
	//si el producto no existe le meto los datos
	else {
		//pido los datos
		rewind(stdin);
		printf("Dame una descripcion de max 20 car;\n");
		gets(producto.descripcion);
		printf("Dame existencias;\n");
		scanf_s("%d", &producto.existencias);
		printf("Dime su precio;\n");
		scanf_s("%d", &producto.precio);
		producto.estado = 1;
		//me posiciono
		fseek(puntero_a_fichero, sizeof(producto) * pos, SEEK_SET);
		//escribo en el fichero los datos arriba solicitados
		fwrite(&producto, sizeof(producto), 1, puntero_a_fichero);
	}
	fclose(puntero_a_fichero);
}


void bajaProducto(){
	//abrimos fichero
	FILE* puntero_a_fichero;
	fopen_s(&puntero_a_fichero, FICHERO, "rb+");
	if (puntero_a_fichero == NULL) {
		printf("Error al abrir el fichero para dar de baja elproducto\n");
		return;
	};
	//preguntamos posicion
	 int pos = -1;
	do {
		printf("Dame la posicion del producto\n");
		scanf_s("%d", &pos);
	} while (pos < 0 || pos>9);

	PRODUCTO producto;
	//POSICIONAMOS
	fseek(puntero_a_fichero, sizeof(producto) * pos, SEEK_SET);
	//leemos
	fread(&producto, sizeof(producto),1, puntero_a_fichero);
	if (producto.estado == 1) {
		producto.estado = 0;
		printf("producto dado de baja\n");
	}
	else{
		printf("elproducto ya esta dado de baja\n");
	}
	fseek(puntero_a_fichero, sizeof(producto) * pos, SEEK_SET);	 // nos posicionamos
	fwrite(&producto, sizeof(producto), 1, puntero_a_fichero);   // prducto es lo que vamos a escribir, sizeof cuantos bites va a ocupar cada elemento(registro), 
	       														 // 1 es la cantidad de registros que queremos meter y punteor_a_fichero, apunta a la pos dentro del fichero.    
	fclose(puntero_a_fichero);
}



void mostrarAlmacen() {
	
	//abro el fichero 
	FILE* puntero_a_fichero;
	fopen_s(&puntero_a_fichero, FICHERO, "rb");
	if (puntero_a_fichero == NULL) {
		printf("No se pueod abrir el fichero original");
		return;
	}

	//pido nombre del fichero
	printf("Dame el nombre del fichero");
	char nombre[255];
	rewind(stdin);
	gets(nombre);
	//creo el informe al arbirlo
	FILE* puntero_a_fichero_informe;
	fopen_s(&puntero_a_fichero_informe, nombre, "w");
	if (puntero_a_fichero_informe == NULL) {
		printf("No se pueod abrir el informe.txt");
		fclose(puntero_a_fichero);
		return;
	}

	fprintf(puntero_a_fichero_informe, "%6s %20s %10s %10s \n", "codigo", "descripcion", "unidades", "precio");

	PRODUCTO producto;
	//fseek(puntero_a_fichero, sizeof(producto), SEEK_SET);  // es necesario poner fseek aqui ???

	for (int i = 0; i < TAM; i++) {
		fread(&producto, sizeof(producto), 1, puntero_a_fichero);
		if (producto.estado == 1) {
			fprintf(puntero_a_fichero_informe, " %6d %20s %10d %10d\n", i + 1, producto.descripcion, producto.existencias, producto.precio);
		}
	}
	fclose(puntero_a_fichero_informe);
	fclose(puntero_a_fichero);
}




















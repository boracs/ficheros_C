#include <stdio.h>
#include <windows.h>
#define TAM 10
#define ORIGINAL "original.txt"
#define INFORME "informe.txt"
FILE* poriginal;
FILE* pinforme;



//funciones
int menu();
void inicializar();
void altaCuwenta();
void bajaCuenta();
void realizarTransaccion();
void mostrarSaldos();



typedef struct{
	char titular[20];
	int id;
	int saldo;
	int estado;
}CUENTA;




/*
Se quiere programar una aplicación para gestionar el mantenimiento de un fichero directo
maestro de 10 cuentas de cliente. Por cada cuenta se almacenará la siguiente información:

− Titular: nombre del titular de la cuenta.
− IdCuenta: un identificador de la cuenta.
− Saldo. Capital disponible en la cuenta en este momento.
− Estado. Para saber si la posición está libre u ocupada.

El programa principal mostrará un menú como el siguiente:

i) Inicializar Fichero: Crea el fichero de cuentas con 10 posiciones vacías.

ii) Alta Cuenta: Pide los datos de una cuenta (posición, titular, NCuenta y saldo
	inicial) y la da de alta en el fichero.

iii) Realizar transacción: pregunta si se quiere ingresar o retirar dinero de la cuenta, se
	pide el código de la cuenta y el importe a ingresar o retirar. Si se quiere ingresar se
	sumará la cantidad introducida al saldo de la cuenta de la posición indicada, si se
	quiere retirar se restará a menos que no haya saldo suficiente, en este caso se dará
	mensaje de error.

iv) Baja Cuenta: Pide la posición de la cuenta a borrar, muestra sus datos y la da de
	baja.

v) MostrarSaldos. Genera un informe como el siguiente con los saldos de todas las
	cuentas
	Codigo Nombre Saldo
	xxxxxx xxxxxxxxx xxxxxxxx

vi) Salir. Termina la ejecución del programa.
	Se pide:
	a) Definir el tipo de datos CUENTA que será el de los registros del fichero, de forma
	necesaria para que almacene los datos de una cuenta:
	b) Programar el programa principal para que muestre y gestione el menú indicado.
	c) Programar la función AltaCuenta para que se comporte como se ha indicado.
	d) Programar la función BajaCuenta para que se comporte como se ha indicado.
	e) Programar la función RealizarTransacción para que se comporte como se ha indicado.
	f) Programar la función MostrarSaldos para que funcione como se ha descrito.


*/
main() {
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);

	void (*funciones[])() = { inicializar, altaCuwenta, realizarTransaccion, bajaCuenta, mostrarSaldos};

	int opc = menu();
		while (opc != 6) {
			system("cls");
			(funciones[opc - 1])();
			opc = menu();
		}
}

int menu()
{
	int opc = -1;
	do {
		printf("dAME UNA OPCION: \n 1-Inicializar \n 2-alta Cuenta \n 3- Realziar transaccion \n 4- Baja cuenta \n 5- Mostrar saldos \n 6- sALIR ");
		scanf_s("%d", &opc);
	} while (opc < 1 || opc>6);
	return opc;
}




void inicializar()
{
	fopen_s(&poriginal, ORIGINAL, "wb");
	if (poriginal == NULL) {
		printf("El fichero no se pueod abrir errror");
	}
	else {
		CUENTA reg;
		reg.estado = 0;
		for (int i = 0; i < TAM; i++) {
			fwrite(&reg, sizeof(reg), 1, poriginal);
		}
		printf("Fichero inicializado correctamente");
	}
	fclose(poriginal);
}

void altaCuwenta()   // porque pone los nombres tla cual en el fichero y no se ve en codigo binario??
{
	fopen_s(&poriginal, ORIGINAL, "rb+");
	if (poriginal == NULL) {
		printf("Error al abrir el fichero para dar de alta");
		return;
	}
	int pos = -1;
	do {
		printf("Dame una posicion donde deseas meter el producto");
		scanf_s("%d", &pos);
	} while (pos<0 || pos>TAM);

	CUENTA reg;
	fseek(poriginal, sizeof(reg) * pos, SEEK_SET);
	fread(&reg, sizeof(reg), 1, poriginal);

	if (reg.estado == 1) {
		printf("Esta posicion ya tienen un prodcuto asignado");
		fclose(poriginal);
		return;
	}
	else {
		printf("Dame el id de la cuenta");
		scanf_s("%d", &reg.id);

		printf("Dame el nombre de la cuenta");
		rewind(stdin);
		gets(reg.titular);

		printf("Dame el saldo de la cuenta");
		scanf_s("%d", &reg.saldo);

		reg.estado = 1;

		fseek(poriginal, sizeof(reg) * pos, SEEK_SET);
		fwrite(&reg, sizeof(reg), 1, poriginal);
		printf("Cuenta dada de alta exitosamente");
		fclose(poriginal);
	}
	
}



void bajaCuenta()
{
	fopen_s(&poriginal, ORIGINAL, "rb+");
	if (poriginal == NULL) {
		printf("Error al abrir el fichero para dar de alta");
		return;
	}
	int pos = -1;
	do {
		printf("Dame una posicion donde deseas meter el producto");
		scanf_s("%d", &pos);
	} while (pos<0 || pos>TAM);

	CUENTA reg;
	fseek(poriginal, sizeof(reg) * pos, SEEK_SET);
	fread(&reg, sizeof(reg), 1, poriginal);

	if (reg.estado == 0) {
		printf("No hay nada en esa posicion");
		fclose(poriginal);
		return;
	}
	else {
		fseek(poriginal, sizeof(reg) * pos, SEEK_SET);
		reg.estado = 0;
		fwrite(&reg, sizeof(reg), 1, poriginal);
		printf("Cuenta dada de baja exitosamente");
		fclose(poriginal);
	}

}


void realizarTransaccion()
{
	fopen_s(&poriginal, ORIGINAL, "rb+");
	if (poriginal == NULL) {
		printf("Error al abrir el fichero para dar de alta");
		return;
	}
	//preguntaba posicion
	int pos = -1;
	do {
		printf("Dame una posicion donde deseas realizar la operacion");
		scanf_s("%d", &pos);
	} while (pos<0 || pos>TAM);

	//leo el fichero en la posicion solicitada
	CUENTA reg;
	fseek(poriginal, sizeof(reg) * pos, SEEK_SET);
	fread(&reg, sizeof(reg), 1, poriginal);

	//vcompruebo qu eestado =1 si es cero salgo
	if (reg.estado == 0) {
		printf("Esta Cuenta no existe ");
		fclose(poriginal);
		return;
	}else{
		//pregunto que operacion quiere realizar
		int opc = -1;
		do {
			printf("Que deseas realizar 1-retirar Saldo 2-Ingrear Saldo 3-Salir");
			scanf_s("%d", &opc);
		} while (opc<1 || opc>3);
		if (opc == 3) { //si es 3 salgo
			printf("Operacion cancelada");
			fclose(poriginal);
			return;
		}
		else if (opc == 1) { //si es 1 saco dinero
			int cantidadAExtraer;
			printf("Cuadno dinero quieres sacar?");
			scanf_s("%d", &cantidadAExtraer);
			if (cantidadAExtraer > reg.saldo) {
				printf("No hay suficiente dinero");
			}
			else {
				reg.saldo -= cantidadAExtraer;
			}
		}
		else {      //si es dos meto dinero
			int cantidadAMeter;
			printf("Cuadno dinero quieres meter?");
			scanf_s("%d", &cantidadAMeter);
			reg.saldo += cantidadAMeter;

		}
		fseek(poriginal, sizeof(reg) * pos, SEEK_SET);
		fwrite(&reg, sizeof(reg), 1, poriginal);
		fclose(poriginal);



	}



}

void mostrarSaldos()
{
	fopen_s(&poriginal, ORIGINAL, "rb");
	if (poriginal == NULL) {
		printf("Error al abrir el fichero original");
		return;
	}

	fopen_s(&pinforme, INFORME, "w");
	if (pinforme == NULL) {
		printf("Error al abrir el INFORME");
		return;
	}

	//ESCRIBIMOS CABECERA 
	fprintf(pinforme, "%10s %10s %10s \n", "codigo", "nombre", "saldo");

	//creamos el registro
	CUENTA reg [TAM];

	//leemos del original
	fread(reg, sizeof(CUENTA), 10, poriginal);
	for (int i = 0; i < TAM; i++) {
		if (reg[i].estado == 1) {
			fprintf(pinforme, "%10d %10s %10d \n", reg[i].id, reg[i].titular, reg[i].saldo);
		}
	}
	fclose(poriginal);
	fclose(pinforme);

	//escribimos en el informe








}

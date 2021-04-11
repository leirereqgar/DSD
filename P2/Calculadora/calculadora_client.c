/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include <ctype.h>
#include <stdbool.h>
#include "calculadora.h"

void ayuda () {
	printf("Uso: ./calculadora_client localhost operando1 operador operando2\n");
	printf("- Para operaciones con escalares escribir el número y la operación: + - x /");
	printf("- Para operaciones con vectores escribirlos (x,y,z), los dos del mismo tamaño\n");
	printf("\tSe pueden sumar (+), restar(-), multiplicar (x) vectores y multiplicar un vector por un escalar\n");
	printf("- Para operaciones con matrices escribirlos [(x,y)(z,q)], las dos del mismo orden y cuadradas\n");
	printf("\tSe pueden sumar (+), restar(-), multiplicar (x) matrices y multiplicar una matriz por un escalar\n");
	printf("Es posible que haya que escapar los paréntesis y corchetes\n");
}

void basicas (char *host, int operando1, char operacion, int operando2) {
	CLIENT *clnt;
	res_calculo * result;

	#ifndef	DEBUG
		clnt = clnt_create (host, CALCULADORAPROG, CALCULADORAVER, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif	/* DEBUG */

	if(operacion == '+')
		result = suma_1(operando1, operando2, clnt);
	else if(operacion == '-')
		result = resta_1(operando1, operando2, clnt);
	else if(operacion == 'x')
		result = multiplicacion_1(operando1, operando2, clnt);
	else if(operacion == '/')
		result = division_1(operando1, operando2, clnt);
	else
		perror("Operación inválida\n");

	if(result == (res_calculo *) NULL)
		clnt_perror(clnt, "call failed");

	printf("El resultado es: %d\n", result->res_calculo_u.resultado);

	xdr_free(xdr_res_calculo, &result);

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}

void vectoriales (char * host, vec *operando1, char operacion, vec *operando2) {
	CLIENT *clnt;
	res_calculo_vectores * result;

	#ifndef DEBUG
		clnt = clnt_create (host, CALCULADORAPROG, CALCULADORAVER, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif	/* DEBUG */

	if(operacion == '+')
		result = sumavector_1(*operando1, *operando2, clnt);
	else if(operacion == '-')
		result = restavector_1(*operando1, *operando2, clnt);
	else if(operacion == 'x')
		result = multiplicacionvector_1(*operando1, *operando2, clnt);
	else
		perror("Operación inválida\n");

	if(result == (res_calculo_vectores *) NULL)
		clnt_perror(clnt, "call failed");

	printf("El resultado es: ");
	int tam = result->res_calculo_vectores_u.resultado.vec_len;
	for (unsigned int i = 0; i < tam; i++) {
		printf("%d,", result->res_calculo_vectores_u.resultado.vec_val[i]);
	}

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}

void vectorPorEscalar (char *host, vec *operando1, int operando2) {
	CLIENT *clnt;
	res_calculo_vectores * result;

	#ifndef DEBUG
		clnt = clnt_create (host, CALCULADORAPROG, CALCULADORAVER, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif	/* DEBUG */

	result = multiplicacionescalar_1(*operando1, operando2, clnt);

	printf("El resultado es: ");
	int tam = result->res_calculo_vectores_u.resultado.vec_len;
	for (unsigned int i = 0; i < tam; i++) {
		printf("%d,", result->res_calculo_vectores_u.resultado.vec_val[i]);
	}

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}

void matriciales (char *host, matriz *operando1, char operacion, matriz *operando2) {
	CLIENT *clnt;
	res_calculo_matrices * result;
	int escalar;

	#ifndef DEBUG
		clnt = clnt_create (host, CALCULADORAPROG, CALCULADORAVER, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif	/* DEBUG */

	if(operacion == '+')
		result = sumamatriz_1(*operando1, *operando2, clnt);
	else if(operacion == '-')
		result = restamatriz_1(*operando1, *operando2, clnt);
	else if(operacion == 'x')
		result = multiplicacionmatriz_1(*operando1, *operando2, clnt);
	else
		perror("Operación inválida\n");

	if(result == (res_calculo_matrices *) NULL)
		clnt_perror(clnt, "call failed");

	printf("El resultado es: ");
	int tam = result->res_calculo_matrices_u.resultado.orden;
	for (unsigned int i = 0; i < tam; i++) {
		for(unsigned int j = 0; j < tam; j++)
			printf("%d,", result->res_calculo_matrices_u.resultado.filas[i].vec_val[j]);
		printf("\n");
	}

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}

void matrizPorEscalar(char *host, matriz *operando1, int operando2) {
	CLIENT *clnt;
	res_calculo_matrices * result;

	#ifndef DEBUG
		clnt = clnt_create (host, CALCULADORAPROG, CALCULADORAVER, "udp");
		if (clnt == NULL) {
			clnt_pcreateerror (host);
			exit (1);
		}
	#endif	/* DEBUG */

	result = multiplicacionmatrizescalar_1(*operando1, operando2, clnt);

	printf("El resultado es: ");
	int tam = result->res_calculo_matrices_u.resultado.orden;
	for (unsigned int i = 0; i < tam; i++) {
		for(unsigned int j = 0; j < tam; j++)
			printf("%d,", result->res_calculo_matrices_u.resultado.filas[i].vec_val[j]);
		printf("\n");
	}

	#ifndef	DEBUG
		clnt_destroy (clnt);
	#endif	 /* DEBUG */
}

bool ambosEscalares (char *operando1, char *operando2) {
	return isdigit(operando1[0]) && isdigit(operando2[0]);
}

bool ambosVectores (char *operando1, char *operando2) {
	return operando1[0] == '(' && operando2[0] == '(';
}

bool ambosMatrices (char *operando1, char *operando2) {
	return operando1[0] == '[' && operando2[0] == '[';
}

bool soloUnVector (char *operando1, char *operando2) {
	return operando1[0] == '(' || operando2[0] == '(';
}

bool soloUnaMatriz (char *operando1, char *operando2) {
	return operando1[0] == '[' || operando2[0] == '[';
}

vec *crearVector (char *vector_caracteres) {
	vec *vector = 0;
	unsigned int tam = 1;

	for (unsigned int i = 0; i < strlen(vector_caracteres); i++) {
		if(vector_caracteres[i] == ',')
			tam++; //El tamaño será el número de comas más uno
	}

	vector = malloc(sizeof(vec));
	vector->vec_val = malloc(tam * sizeof(int));
	vector->vec_len = tam;

	int indice = 0;
	for (unsigned int i = 1; i < strlen(vector_caracteres); i++) {
		char buffer[256];

		unsigned int j = 0;
		while(vector_caracteres != '(' && vector_caracteres[i] != ',' && vector_caracteres[i] != ')') {
			buffer[j] = vector_caracteres[i];
			j++;
			i++;
		}
		buffer[j] = '\0';

		vector->vec_val[indice] = atoi(buffer);
		indice++;
	}

	return vector;
}

matriz *crearMatriz(char *mat_caracteres) {
	matriz *mat = 0;
	unsigned int filas = 0;

	for (unsigned int i = 0; i < strlen(mat_caracteres); i++){
		if(mat_caracteres[i] == '(')
			filas++;
	}

	mat = malloc(sizeof(matriz));
	mat->orden = filas;
	mat->filas = malloc(sizeof(vec[filas]));

	unsigned int i_fila = 0;
	for(unsigned i = 1; i < strlen(mat_caracteres)-1; i++) {
		char *buffer = malloc(sizeof(int)*256);

		unsigned int j = 0;
		while(mat_caracteres[i] != ')') {
			//printf("%c\n", mat_caracteres[i]);
			buffer[j] = mat_caracteres[i];
			j++;
			i++;
		}
		buffer[j] = ')';
		buffer[j+1] = '\0';

		mat->filas[i_fila] = *crearVector(buffer);
		i_fila++;
	}

	return mat;
}

void leerArgumentos (int argc, char **argv) {
	char *host = argv[1];
	char operacion = *argv[3];

	char *operando1 = argv[2];
	char *operando2 = argv[4];

	if(ambosEscalares(operando1, operando2))
		basicas(host, atoi(operando1), operacion, atoi(operando2));
	else if (ambosVectores(operando1, operando2)){
		vec *vector1 = crearVector(operando1);
		vec *vector2 = crearVector(operando2);

		vectoriales(host, vector1, operacion, vector2);
	}
	else if (ambosMatrices(operando1, operando2)) {
		matriz *matriz1 = crearMatriz(operando1);
		matriz *matriz2 = crearMatriz(operando2);

		matriciales(host, matriz1, operacion, matriz2);
	}
	else if (soloUnVector(operando1, operando2)) {
		if(isdigit(operando1[0])) {
			vec *vector = crearVector(operando2);

			vectorPorEscalar(host, vector, atoi(operando1));
		}
		else {//operando2 digito
			vec *vector = crearVector(operando1);

			vectorPorEscalar(host, vector, atoi(operando2));
		}
	}
	else if (soloUnaMatriz(operando1, operando2)) {
		if(isdigit(operando1[0])) {
			matriz *mat = crearMatriz(operando2);
			matrizPorEscalar(host, mat, atoi(operando1));
		}
		else {//operando2 digito
			matriz *mat = crearMatriz(operando1);
			matrizPorEscalar(host, mat, atoi(operando2));
		}
	}
	else
		printf("No sé que operación intentas hacer, pero no esta implementada");

}


int main (int argc, char **argv) {
	if (argc < 2) {
		ayuda();
		exit (1);
	}
	else {
		leerArgumentos(argc, argv);
	}
exit (0);
}

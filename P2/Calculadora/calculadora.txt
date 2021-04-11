typedef int vec<>; /*Vector esta reservada*/

struct matriz {
	u_int orden;
	vec * filas;
};

typedef struct matriz matriz;

union res_calculo switch (int err) {
	case 0:
		int resultado;
	default:
		void;
};

union res_calculo_vectores switch (int err) {
	case 0:
		vec resultado;
	default:
		void;
};

union res_calculo_matrices switch (int err) {
	case 0:
		matriz resultado;
	default:
		void;
};

program CALCULADORAPROG {
	version CALCULADORAVER {
		res_calculo SUMA(int, int)           = 1;
		res_calculo RESTA(int, int)          = 2;
		res_calculo MULTIPLICACION(int, int) = 3;
		res_calculo DIVISION(int, int)       = 4;

		res_calculo_vectores SUMAVECTOR(vec, vec)            = 5;
		res_calculo_vectores RESTAVECTOR(vec, vec)           = 6;
		res_calculo_vectores MULTIPLICACIONVECTOR(vec, vec)  = 7;
		res_calculo_vectores MULTIPLICACIONESCALAR(vec, int) = 8;

		res_calculo_matrices SUMAMATRIZ(matriz, matriz)                  = 9;
		res_calculo_matrices RESTAMATRIZ(matriz, matriz)                 = 10;
		res_calculo_matrices MULTIPLICACIONMATRIZ(matriz, matriz)        = 11;
		res_calculo_matrices MULTIPLICACIONMATRIZESCALAR(matriz, int) = 12;
	} = 1;
} = 0x20000001;

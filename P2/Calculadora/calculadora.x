union res_calculo switch (int err) {
	case 0:
		int resultado;
	default:
		void;
};

program CALCULADORAPROG {
	version CALCULADORAVER {
		res_calculo SUMA(int, int) = 1;
		res_calculo RESTA(int, int) = 2;
		res_calculo MULTIPLICACION(int, int) = 3;
		res_calculo DIVISION(int, int) = 4;
	} = 1;
} = 0x20000001;

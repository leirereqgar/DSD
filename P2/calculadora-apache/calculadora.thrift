typedef list<i32> vec

service Calculadora{
	void ping(),
	i32 suma(1:i32 num1, 2:i32 num2),
	i32 resta(1:i32 num1, 2:i32 num2),
	i32 multiplicacion(1:i32 num1, 2:i32 num2),
	i32 division(1:i32 num1, 2:i32 num2),

	vec sumavector(1:vec v1, 2:vec v2),
	vec restavector(1:vec v1, 2:vec v2),
	vec multiplicacionvector(1:vec v1, 2:vec v2),

	vec multiplicacionvectorescalar(1:vec v, 2:i32 escalar),
}

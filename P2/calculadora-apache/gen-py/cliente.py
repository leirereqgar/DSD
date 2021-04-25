from calculadora import Calculadora

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

import sys
import numpy as np

def ayuda():
	print("Ejecución: python operando1 operacion operando2")
	print("Para operaciones básicas: python num1 operacion num2, siendo num1 y num2 enteros")
	print("Para operaciones con vectores: python v operacion v")
	print("Para multiplicar un vector con un escalar: python v x num, siendo num un entero")
	print("Para ver este mensaje de ayuda: python -h")


def opBasicas(cliente, operando1, operacion, operando2):
	resultado = None

	if operacion == '+':
		resultado = cliente.suma(operando1, operando2)
	elif operacion == '-':
		resultado = cliente.resta(operando1, operando2)
	elif operacion == 'x':
		resultado = cliente.multiplicacion(operando1, operando2)
	elif operacion == '/':
		resultado = cliente.division(operando1, operando2)
	else:
		print("Operación con enteros no implementada")

	return resultado

def opVectores(cliente, operando1, operacion, operando2):
	resultado = None

	if operacion == '+':
		resultado = cliente.sumavector(operando1, operando2)
	elif operacion == '-':
		resultado = cliente.restavector(operando1, operando2)
	elif operacion == 'x':
		resultado = cliente.multiplicacionvector(operando1, operando2)
	else:
		print("Operación con vectores no implementada")

	return resultado


# Main

transport = TSocket.TSocket("localhost", 9090)
transport = TTransport.TBufferedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)

client = Calculadora.Client(protocol)

transport.open()

if len(sys.argv) < 4 or sys.argv[1] == "-h":
	ayuda()
else:
	print("hacemos ping al server")
	client.ping()

	resultado = 0
	operando1 = sys.argv[1]
	operacion = sys.argv[2]
	operando2 = sys.argv[3]

	if operando1.isdigit() and operando2.isdigit():
		resultado = opBasicas(client, int(operando1), str(operacion), int(operando2))
	elif operando1 == 'v' and operando2 == 'v':
		vecA = []
		vecB = []
		tam  = int(input("Introduzca el tamaño de los vectores:"))

		for i in range(tam):
			num = int(input("Introduzca un elemento para el primer vector: "))
			vecA.append(num)

		for i in range(tam):
			num = int(input("Introduzca un elemento para el segundo vector: "))
			vecB.append(num)

		resultado = opVectores(client, vecA, operacion, vecB)
	elif operando1 == 'v' and operando2.isdigit():
		v = []
		tam  = int(input("Introduzca el tamaño del vector:"))

		for i in range(tam):
			num = int(input("Introduzca un elemento para el vector: "))
			v.append(num)

		resultado = client.multiplicacionvectorescalar(v, int(operando2))
	else:
		print("Operación no implementada")

	print("El resultado es: " + str(resultado))

transport.close()

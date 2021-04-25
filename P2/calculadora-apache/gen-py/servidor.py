import glob
import sys

from calculadora import Calculadora

from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

import logging
import numpy as np

logging.basicConfig(level=logging.DEBUG)


class CalculadoraHandler:
	def __init__(self):
		self.log = {}

	def ping(self):
		print("me han hecho ping()")

	def suma(self, n1, n2):
		print("sumando " + str(n1) + " con " + str(n2))
		return n1 + n2

	def resta(self, n1, n2):
		print("restando " + str(n1) + " con " + str(n2))
		return n1 - n2

	def multiplicacion(self, n1, n2):
		print("multiplicando " + str(n1) + " con " + str(n2))
		return n1 * n2

	def division(self, n1, n2):
		print("dividiendo " + str(n1) + " con " + str(n2))
		return int(n1 / n2)

	# Op vectores
	def sumavector(self, v1, v2):
		print("sumando vector A con vector B")
		vA = np.array(v1)
		vB = np.array(v2)
		return vA + vB

	def restavector(self, v1, v2):
		print("restando vector A con vector B")
		vA = np.array(v1)
		vB = np.array(v2)
		return vA - vB

	def multiplicacionvector(self, v1, v2):
		print("multiplicando vector A con vector B")
		vA = np.array(v1)
		vB = np.array(v2)
		return vA * vB

	def multiplicacionvectorescalar(self, v, escalar):
		print("multiplicando un vector por un escalar")
		return np.array(v) * escalar



if __name__ == "__main__":
	handler = CalculadoraHandler()
	processor = Calculadora.Processor(handler)
	transport = TSocket.TServerSocket(host="127.0.0.1", port=9090)
	tfactory = TTransport.TBufferedTransportFactory()
	pfactory = TBinaryProtocol.TBinaryProtocolFactory()

	server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

	print("iniciando servidor...")
	server.serve()
	print("fin")

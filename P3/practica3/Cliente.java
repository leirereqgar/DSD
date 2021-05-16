package practica3;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.RemoteException;
import java.rmi.NotBoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Cliente {
	String host;
	int replica;

	Cliente (String host, int replica) {
		this.host = host;
		this.replica = replica;
	}

	public static void main (String args[]) throws RemoteException, NotBoundException {
		String host = "localhost";
		Scanner scanner = new Scanner(System.in);
		ArrayList<Cliente> clientes = new ArrayList<>();
		int total_clientes = 0;
		boolean continuar = true;
		Registry registry = LocateRegistry.getRegistry(host, 1099);
		Replicas_I replica_base = (Replicas_I) registry.lookup("Replica0");

		while (continuar) {
			System.out.println("Selecciona una operación: ");
			System.out.println("1 -> Registrar nuevo cliente.");
			System.out.println("2 -> Donar");
			System.out.println("3 -> Consultar total de donaciones");
			System.out.println("4 -> Finalizar ejecución");

			int opcion = Integer.parseInt(scanner.nextLine());

			switch (opcion) {
				case 1:
					int replica = replica_base.registrarCliente(total_clientes);
					//c.asignarReplica("" + replica);
					Cliente c = new Cliente(host, replica);
					clientes.add(c);

					System.out.println("Su id de cliente es: " + total_clientes + " y su réplica asignada es: " + replica);
					System.out.println("");

					total_clientes++;
				break;

				case 2:
					if (total_clientes == 0)
						System.out.println("No hay clientes registrados");
					else {
						System.out.println("Introduzca el id del cliente que va a donar: ");
						int id_cliente = Integer.parseInt(scanner.nextLine());

						if(0 <= id_cliente && id_cliente < total_clientes) {
							Cliente donante = clientes.get(id_cliente);
							System.out.println("Introduzca la cantidad que desea donar: ");
							int donacion = Integer.parseInt(scanner.nextLine());

							Replicas_I rep = (Replicas_I) registry.lookup("Replica" + donante.replica);
							rep.donar(id_cliente, donacion);
						}
					}

					System.out.println("");
				break;

				case 3:
				if (total_clientes == 0)
					System.out.println("No hay clientes registrados");
				else {
					System.out.println("Introduzca su id de cliente:");
					int id_cliente = Integer.parseInt(scanner.nextLine());

					if (0 <= id_cliente && id_cliente < total_clientes) {
						Cliente cliente = clientes.get(id_cliente);
						Replicas_I rep = (Replicas_I) registry.lookup("Replica" + cliente.replica);

						int total = rep.getTotalDonaciones(id_cliente);

						if (total > 0)
							System.out.println("El total de donaciones es " + total);
						else
							System.out.println("Done primero para ver el total");
					}
					else
						System.out.println("Id de cliente no válido");
				}
				System.out.println("");
				break;

				case 4:
					continuar = false;
					System.out.println("");
				break;

				default: System.out.println("Seleccione una opción válida");
			}
		}
	}

}

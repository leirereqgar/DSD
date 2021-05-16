package practica3;

import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Collection;
import java.util.HashMap;

public class Replicas extends UnicastRemoteObject implements Replicas_I {
	private static int total_replicas;
	private int id_replica;

	private HashMap<Integer, Integer> clientes_registrados = new HashMap<Integer, Integer>();
	private Registry registry;

	public Replicas(String host, int id, int total_replicas) throws RemoteException{
		registry = LocateRegistry.getRegistry(host, 1099);
		this.id_replica = id;
		Replicas.total_replicas = total_replicas;
	}

	public boolean getRegistrado (int id_cliente) throws RemoteException {
		return clientes_registrados.containsKey(id_cliente);
	}

	public boolean haDonado(int id_cliente) throws RemoteException {
		return clientes_registrados.get(id_cliente) > 0;
	}

	public int registrarCliente(int id_cliente) throws RemoteException, NotBoundException {
		int rep_min_registrados = id_replica;
		int min_total_registrados = getTotalClientes();
		boolean registrado = false;
		Replicas_I candidata = (Replicas_I) this;

		for (int i = 0; i < Replicas.total_replicas; i++) {
			if (i != this.id_replica) {
				candidata = (Replicas_I) registry.lookup("Replica" + i);

				registrado = candidata.getRegistrado(id_cliente);

				//Buscar la réplica que tiene menor número de clientes registrados
				int total_registrados_candidata = candidata.getTotalClientes();
				if(total_registrados_candidata < min_total_registrados) {
					rep_min_registrados = i;
					min_total_registrados = total_registrados_candidata;
				}
			}
		}

		if(!registrado) {
			if (rep_min_registrados != id_replica) {
				candidata = (Replicas_I) registry.lookup("Replica" + rep_min_registrados);
				candidata.registrarCliente(id_cliente);
			}
			else {
				System.out.println("Cliente " + id_cliente + " registrado en réplica " + this.id_replica);
				this.clientes_registrados.put(id_cliente, 0);
			}
		}

		return rep_min_registrados;
	}

	public int getTotalClientes() throws RemoteException {
		return clientes_registrados.size();
	}

	public void donar(int id_cliente, int cantidad) throws RemoteException {
		clientes_registrados.put(id_cliente, cantidad);

		System.out.println("Recibida donación de cliente " + id_cliente + " en réplica " + this.id_replica);
	}

	public int getSubtotalDonaciones() throws RemoteException {
		int subtotal = 0;

		for (int i : clientes_registrados.values())
			subtotal += i;

		return subtotal;
	}

	public int getTotalDonaciones(int id_cliente) throws RemoteException, NotBoundException {
		int total = -1;

		if(getRegistrado(id_cliente) && haDonado(id_cliente)) {
			total = getSubtotalDonaciones();
			for (int i = 0; i < Replicas.total_replicas; i++)
				if(i != id_replica)
					total +=((Replicas_I) registry.lookup("Replica" + i)).getSubtotalDonaciones();
		}

		return total;
	}
}

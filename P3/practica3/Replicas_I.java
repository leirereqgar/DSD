package practica3;

import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Replicas_I extends Remote {
	public boolean getRegistrado (int id_cliente) throws RemoteException;

	public int registrarCliente(int id_cliente) throws RemoteException, NotBoundException;

	public int getTotalClientes() throws RemoteException;

	public void donar(int id_cliente, int cantidad) throws RemoteException;

	public int getSubtotalDonaciones() throws RemoteException;

	public int getTotalDonaciones(int id_cliente) throws RemoteException, NotBoundException;
}

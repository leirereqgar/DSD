package practica3;

import java.rmi.Naming;
import java.rmi.RemoteException;
import java.net.MalformedURLException;

public class Servidor {
	static final int num_replicas = 2;

	public static void main (String [] args) {
		if (System.getSecurityManager() == null) {
			System.setSecurityManager(new SecurityManager());
		}

		try {
			for (int i = 0; i < num_replicas; i++) {
				Replicas replica = new Replicas("localhost", i, num_replicas);
				Naming.rebind("Replica" + i, replica);

				System.out.println("Desplegada réplica: " + i);
			}

		}
		catch(RemoteException | MalformedURLException e) {
			System.out.println("Exception: " + e.getMessage());
		}
	}
}

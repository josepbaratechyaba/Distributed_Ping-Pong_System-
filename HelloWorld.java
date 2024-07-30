import mpi.*;
import java.net.*;

public class HelloWorld {

    public static void main(String[] args) throws MPIException, UnknownHostException {

        MPI.Init(args);

        int size = MPI.COMM_WORLD.getSize();
        int rank = MPI.COMM_WORLD.getRank();
        String name = MPI.COMM_WORLD.getName();
        String hostname = InetAddress.getLocalHost().getHostName();

        System.out.println("Hello, World! I am process " + rank + " of " +
                           size + " on " + name + " on host " + hostname);

        MPI.Finalize();
    }
}

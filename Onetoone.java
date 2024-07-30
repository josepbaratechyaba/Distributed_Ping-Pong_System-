import mpi.*;
import java.nio.*;

public class Onetoone {

    public static void main(String[] args) throws MPIException {

        MPI.Init(args);

        int size = MPI.COMM_WORLD.getSize();
        int rank = MPI.COMM_WORLD.getRank();

        if (size < 2) {
            System.out.println("Enter at least 2 processes to have 1 Master and 1 worker");
            MPI.Finalize();
            System.exit(1);
        }

        IntBuffer buffer = MPI.newIntBuffer(1);

        if (rank == 0) {
            // Master node, always rank 0
            for (int i = 1; i < size; i++) {
                int pingMessage = i;
                buffer.put(0, pingMessage);
                MPI.COMM_WORLD.send(buffer, 1, MPI.INT, i, 0);
                System.out.println("Master sent ping to worker " + i);
                MPI.COMM_WORLD.recv(buffer, 1, MPI.INT, i, 1);
                int receivedMessage = buffer.get(0);
                System.out.println("Master received pong from worker " + receivedMessage);
            }
        } else {
            // Worker nodes
            MPI.COMM_WORLD.recv(buffer, 1, MPI.INT, 0, 0);
            int receivedMessage = buffer.get(0);
            System.out.println("Worker " + rank + " received ping from master");
            buffer.put(0, rank);
            MPI.COMM_WORLD.send(buffer, 1, MPI.INT, 0, 1);
        }

        MPI.Finalize();
    }
}

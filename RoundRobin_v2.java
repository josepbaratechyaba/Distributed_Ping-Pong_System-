import mpi.*;
import java.nio.*;
import java.util.Random;

public class RoundRobin_v2 {

    public static void main(String[] args) throws MPIException {

        MPI.Init(args);

        int size = MPI.COMM_WORLD.getSize();
        int rank = MPI.COMM_WORLD.getRank();

        if (size < 2) {
            System.out.println("Enter at least 2 processes to have 1 Master and 1 worker");
            MPI.Finalize();
            System.exit(1);
        }

        Random random = new Random();
        int bufferSize = 100;
        IntBuffer buffer = MPI.newIntBuffer(bufferSize);

        if (rank == 0) {
            // Master node
            int initialNumber = random.nextInt(100);
            buffer.put(0, initialNumber);
            MPI.COMM_WORLD.send(buffer, 1, MPI.INT, 1, 0);
            System.out.println("Master sent initial number: " + initialNumber);

            // Receive the final message
            buffer.clear();
            MPI.COMM_WORLD.recv(buffer, bufferSize, MPI.INT, size - 1, 0);
            System.out.print("Master received final numbers: ");
            for (int i = 0; i < size; i++) {
                System.out.print(buffer.get(i) + " ");
            }
            System.out.println();
        } else {
            // Worker nodes
            int sourceRank = rank - 1;
            int destinationRank = (rank + 1) % size;
            MPI.COMM_WORLD.recv(buffer, bufferSize, MPI.INT, sourceRank, 0);
            int receivedNumber = buffer.get(rank - 1);
            System.out.println("Worker " + rank + " received number: " + receivedNumber);
            int newNumber = random.nextInt(100);
            buffer.put(rank, newNumber);
            MPI.COMM_WORLD.send(buffer, bufferSize, MPI.INT, destinationRank, 0);
            System.out.println("Worker " + rank + " added number: " + newNumber);
        }

        MPI.Finalize();
    }
}

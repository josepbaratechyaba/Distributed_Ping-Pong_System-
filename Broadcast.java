import mpi.*;
import java.nio.charset.StandardCharsets;

public class Broadcast {

    public static void main(String[] args) throws MPIException {

        MPI.Init(args);

        int size = MPI.COMM_WORLD.getSize();
        int rank = MPI.COMM_WORLD.getRank();

        if (size < 2) {
            System.out.println("Enter at least 2 processes to have 1 Master and 1 worker");
            MPI.Finalize();
            System.exit(1);
        }

        int bufferSize = 1024;  // Buffer size, message cant be more than 1024 bytes then
        byte[] buffer = new byte[bufferSize];

        if (rank == 0) {
            // Master node, always rank 0
            String broadcastMessage = "sending Broadcast";
            byte[] messageBytes = broadcastMessage.getBytes(StandardCharsets.UTF_8);
            System.arraycopy(messageBytes, 0, buffer, 0, messageBytes.length);
            MPI.COMM_WORLD.bcast(buffer, bufferSize, MPI.BYTE, 0);
            System.out.println("Master sent broadcast message: " + broadcastMessage);
        } else {
            // Worker nodes, other ranks
            MPI.COMM_WORLD.bcast(buffer, bufferSize, MPI.BYTE, 0);
            String receivedMessage = new String(buffer, StandardCharsets.UTF_8).trim();
            System.out.println("Worker " + rank + " received broadcast message: " + receivedMessage);
        }

        MPI.Finalize();
    }
}

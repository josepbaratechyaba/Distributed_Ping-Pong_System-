import mpi.*;
import java.nio.charset.StandardCharsets;

public class RoundRobin {

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
            String message = "Master";  // Message that master will send
            byte[] messageBytes = message.getBytes(StandardCharsets.UTF_8);
            System.arraycopy(messageBytes, 0, buffer, 0, messageBytes.length);
            MPI.COMM_WORLD.send(buffer, bufferSize, MPI.BYTE, 1, 0);
            System.out.println("Master sent initial message");

            // Receive the final message
            MPI.COMM_WORLD.recv(buffer, bufferSize, MPI.BYTE, size - 1, 0);
            String receivedMessage = new String(buffer, StandardCharsets.UTF_8).trim();
            System.out.println("Master received final message: " + receivedMessage);
        } else {
            // Worker nodes, other ranks
            int sourceRank = rank - 1;
            int destinationRank = (rank + 1) % size;
            MPI.COMM_WORLD.recv(buffer, bufferSize, MPI.BYTE, sourceRank, 0);
            String receivedMessage = new String(buffer, StandardCharsets.UTF_8).trim();
            receivedMessage += " worker" + rank;
            buffer = new byte[bufferSize]; 
            byte[] updatedMessageBytes = receivedMessage.getBytes(StandardCharsets.UTF_8);
            System.arraycopy(updatedMessageBytes, 0, buffer, 0, updatedMessageBytes.length);
            MPI.COMM_WORLD.send(buffer, bufferSize, MPI.BYTE, destinationRank, 0);
            System.out.println("Worker " + rank + " received message and added its identifier");
        }

        MPI.Finalize();
    }
}
import mpi.*;
import java.nio.charset.StandardCharsets;

public class Broadcast {

    public static void main(String[] args) throws MPIException {

        MPI.Init(args);

        // returns the number of nodes
        int size = MPI.COMM_WORLD.getSize();

        //returns the rank of the processes
        int rank = MPI.COMM_WORLD.getRank();

        //error in case we don't have enough nodes
        if (size < 2) {
            System.out.println("Enter at least 2 processes to have 1 Master and 1 worker");
            MPI.Finalize();
            System.exit(1);
        }

        //initiating the buffer, which is the memory we will use to store the messages, in this case will be a byte one
        int bufferSize = 1024;  // Buffer size, message cant be more than 1024 bytes then
        byte[] buffer = new byte[bufferSize];

        if (rank == 0) {
            // Master node, always rank 0
            String broadcastMessage = "sending Broadcast";
            byte[] messageBytes = broadcastMessage.getBytes(StandardCharsets.UTF_8);
            System.arraycopy(messageBytes, 0, buffer, 0, messageBytes.length); // here we need to adapt the string message, It´s more complex than sendig an INT
            MPI.COMM_WORLD.bcast(buffer, bufferSize, MPI.BYTE, 0); //broadcast command in MPI
            System.out.println("Master sent broadcast message: " + broadcastMessage);
        } else {
            // Worker nodes, other ranks
            MPI.COMM_WORLD.bcast(buffer, bufferSize, MPI.BYTE, 0); // for the rest of nodes, broadcast receive command
            String receivedMessage = new String(buffer, StandardCharsets.UTF_8).trim();
            System.out.println("Worker " + rank + " received broadcast message: " + receivedMessage);
        }

        MPI.Finalize();
    }
}

import mpi.*;
import java.nio.*;

public class Onetoone {

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

        //initiating the buffer, which is the memory we will use to store the messages
        IntBuffer buffer = MPI.newIntBuffer(1);

        if (rank == 0) {
            // Master node, always rank 0
            for (int i = 1; i < size; i++) {
                int pingMessage = i; // i represents the worker to who we are going to send the message
                buffer.put(0, pingMessage);
                MPI.COMM_WORLD.send(buffer, 1, MPI.INT, i, 0);
                System.out.println("Master sent ping to worker " + i);
                MPI.COMM_WORLD.recv(buffer, 1, MPI.INT, i, 1);
                int receivedMessage = buffer.get(0);
                System.out.println("Master received pong from worker " + receivedMessage);
            }
        } else {
            // Worker nodes, other ranks
            MPI.COMM_WORLD.recv(buffer, 1, MPI.INT, 0, 0); // mpi receive command
            int receivedMessage = buffer.get(0); // message received
            System.out.println("Worker " + rank + " received ping from master"); //we send back the message with the rank num
            buffer.put(0, rank);
            MPI.COMM_WORLD.send(buffer, 1, MPI.INT, 0, 1);
        }

        MPI.Finalize();
    }
}

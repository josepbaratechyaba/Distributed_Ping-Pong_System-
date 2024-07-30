# README

## Introduction

This project contains the resolution of exercises by Josep Baratech for the Sony AI hiring process. The goal is to creare a Distributed Ping-Pong System. In my case I have chosen the use of Open MPI in a Docker-based development environment. The project includes various Java scripts to perform process communication operations using MPI, and it runs inside a Docker container to ensure portability and consistency.

## Project Overview

### Open MPI

Open MPI is an implementation of the Message Passing Interface (MPI) standard. It is designed for high performance on both single node and distributed memory computing environments, and is one of the topics that I have studied in my Data Engineering Bachelor´s subjects such like parallel programming.

### Docker

Once you clone the repo in VS code, if you have docker installed in your computer you should receive a pop up to build It, and should be automatically created. This step is optional, as you could run the scripts directly if you have java and open MPI installed in your machine. 

### Scripts

The project includes several scripts for testing and demonstrating MPI functionalities:

#### Test Scripts

1. **HelloWorld.java**
   - Each node prints its rank.
   
2. **MasterTest.java**
   - Demonstrates basic communication between two nodes.

#### Exercise Scripts

1. **OneToOne.java**
   - Implements one-to-one messaging between nodes.

2. **Broadcast.java**
   - Demonstrates broadcasting a string message in byte format from the master node to all worker nodes.

3. **RoundRobin.java**
   - Implements chain or ring communication where a message is passed from one node to the next, appending its identifier before forwarding.
   - **RoundRobin_v2.java**: A variation where each node appends a random number instead of its identifier.

## Execution Instructions

To execute the scripts, follow these steps:

1. **Compile the desired script**:
   ```sh
   javac -cp "/usr/local/lib/mpi.jar" #script_name (e.g., RoundRobin.java)

2. **Execute the output file**:
   ```sh
   mpirun --allow-run-as-root --mca plm_rsh_agent "ssh -o StrictHostKeyChecking=no" -np #number_of_nodes (e.g., 4) java -cp .:/usr/local/lib/mpi.jar #script_name (e.g., RoundRobin)


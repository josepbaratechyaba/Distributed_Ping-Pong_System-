# Utilizar una imagen base de Ubuntu
FROM ubuntu:20.04

# Establecer las variables de entorno necesarias para evitar errores de interacción en la instalación
ENV DEBIAN_FRONTEND=noninteractive

# Instalar dependencias
RUN apt-get update && apt-get install -y \
    build-essential \
    openjdk-11-jdk \
    wget \
    curl \
    gfortran \
    tar \
    sudo \
    && rm -rf /var/lib/apt/lists/*

# Descargar e instalar Open MPI
RUN wget https://download.open-mpi.org/release/open-mpi/v4.1/openmpi-4.1.1.tar.gz \
    && tar -xvf openmpi-4.1.1.tar.gz \
    && cd openmpi-4.1.1 \
    && ./configure --enable-mpi-java \
    && make all \
    && sudo make install

# Establecer las variables de entorno para Open MPI
ENV PATH=/usr/local/bin:$PATH
ENV LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
ENV CLASSPATH=/usr/local/share/openmpi/java/mpi.jar:$CLASSPATH

# Crear un directorio para la aplicación
WORKDIR /app

# Copiar el archivo fuente al contenedor
COPY src /app/src

# Compilar el archivo Java
RUN javac -cp /usr/local/share/openmpi/java/mpi.jar /app/src/HelloWorld.java

# Comando para ejecutar el programa
CMD ["mpirun", "-np", "5", "java", "-cp", "/app/src:/usr/local/share/openmpi/java/mpi.jar", "HelloWorld"]

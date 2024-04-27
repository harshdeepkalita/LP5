# Executing C++ Code

- Using g++ compiler

    - Cpmpiling the code
        ```bash
        g++ -o <name of executable that has to be created> <name of the file to be compiled>
        ```
    - Running the executable
        ```bash
        ./<name of the executable>
        ```

- Using gcc compiler
    - Compiling the code (default name)
        ```bash
        gcc <name of the file to be compiled> -lstdc++
        ```
     - Compiling the code with custom name
        ```bash
        gcc <name of the file to be compiled> -lstdc++ -o <name of the executable that has to be created>
        ```
    - Running the executable
        ```bash
        ./a.out
        ```
        or
        ```bash
        ./<name of the executable>
        ```

# OpenMP

- Stands for Open Multi-Processing
- It is an API that supports multi-platform shared memory multiprocessing programming in C, C++, and Fortran
- It consists of a set of compiler directives, library routines, and environment variables that influence run-time behavior
- OpenMP follows a shared memory model, where all threads can access the shared memory
- OpenMP is called a fork-join model because the program forks into multiple threads at the beginning of the parallel region and joins back to the main thread at the end of the parallel region.

### Compiling OpenMP code
- Using g++ compiler
    - Compiling the code
        ```bash
        g++ -fopenmp -o <name of executable that has to be created> <name of the file to be compiled>
        ```
    - Running the executable
        ```bash
        ./<name of the executable>
        ```
- Using gcc compiler
    - Compiling the code (default name)
        ```bash
        gcc <name of the file to be compiled> -lstdc++ -fopenmp
        ```
    - Compiling the code with custom name
        ```bash
        gcc <name of the file to be compiled> -lstdc++ -fopenmp -o <name of the executable that has to be created>
        ```
    - Running the executable
        ```bash
        ./a.out
        ```
        or
        ```bash
        ./<name of the executable>
        ``` 


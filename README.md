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
    


# 42 minitalk

The minitalk project from the 42 core curriculum, completed at 42 Prague in August 2023.

A set of two simple programs that communicate with each other using the SIGUSR1 and SIGUSR2 UNIX signals. The `server` program prints its process ID (PID) and then waits for a signal. The `client` program needs to be executed with the `server`'s PID as its first argument and any message (any combination of Unicode characters) as its second argument. The message is then broken down to bits and sent using the SIGUSR1 and SIGUSR2 signals to the `server` which prints it. The `server` sends a signal back to acknowledge receiving the message and the `client` prints `Message received`.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

sigset_t mask;

void signal_handler(int signum)
{
    // Signal handler for synchronization
    // This function does nothing, just returning from the handler will unblock the child process
}

int main()
{

    // Initialize signal mask
    sigemptyset(&mask);

    // Block SIGUSR1 in the parent process
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    // Fork a child process
    signal(SIGUSR1, signal_handler);

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        // Install signal handler for SIGUSR1

        // Wait for SIGUSR1 from the parent process
        sigsuspend(&mask);

        // Continue with child process after receiving SIGUSR1
        printf("Child: Received signal from parent.\n");

        // Rest of child process code...
    }
    else
    {
        // Parent process
        // Do something
        printf("Parent: Sending signal to child.\n");

        // Send SIGUSR1 signal to the child process
        kill(pid, SIGUSR1);

        printf("Parent: Signal sent to child.\n");
        // Rest of parent process code...
    }

    return 0;
}

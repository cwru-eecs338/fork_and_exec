#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int main() {

    printf("Parent Process.\n");
    fflush(stdout);

    pid_t process_id = fork();

    /*
     * At this point, there are two copies of the
     * program executing at this line. The way we
     * tell which is which is by the return value
     * of fork().
     *
     * But first, some error checking...
     */
    if (process_id < 0) {
        perror("Error occurred using fork()");
        exit(EXIT_FAILURE);
    }

    // OK, now we're sure that fork() worked...

    if (process_id == 0) {
        // This means we are the child process
        // (fork returns 0)
        int exit_status = child();

        // Use _exit() to terminate a child process,
        // since exit() performs extra cleanup that
        // should only be performed by the parent process
        _exit(exit_status);
    } else {
        // This means we are the parent...
        // (fork returns Process ID of child)
        printf("My child has ID: %d\n", process_id);
    }

    // Only the parent reaches this point in the
    // program, since the child used '_exit()'

    // We want to wait for our child to finish,
    // so we use the wait() call.
    // Give wait() the address (using '&') of
    // a variable into which the exit status
    // of the child is to be stored.
    int exit_status;
    pid_t child_id = wait(&exit_status);

    // Because we have possibly multiple children
    // and we're not sure which will finish first,
    // the return value of wait() gives us the
    // Process ID of the child that we just
    // finished waiting for:
    printf("The child with ID %d finished with status %d\n",
           child_id, exit_status);

    return EXIT_SUCCESS;
}

int child() {
    return EXIT_SUCCESS;
}

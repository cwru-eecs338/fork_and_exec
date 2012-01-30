#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>

int child(void);

int main() {

    printf("Parent Process.\n");
    fflush(stdout);

    pid_t process_id = fork();

    // At this point, there are two copies of the
    // program executing at this line. The way we
    // tell which is which is by the return value
    // of fork().
    //
    // But first, some error checking...
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
    printf("I'm the child process!\n");
    fflush(stdout);

    // We want to run the "ls" command to list
    // files in the current working directory
    // with long, human readable descriptions.
    //
    // In the shell we'd type "ls -l -h", but
    // using exec(), "ls", "-l", and "-h" are
    // separate arguments to the call. Note that
    // the first argument to any program is its
    // name (in this case "ls").
    //
    // Also note that we don't have to specify the
    // full path of "ls", since "execlp" will use
    // the PATH like the shell does to find the
    // command "ls".
    execlp("ls",             // command name
           "ls", "-l", "-h", // arguments to command
           (char *) NULL     // NULL termination of argument list
          );

    // If exec() worked, then the execution
    // of the child process is replaced with
    // the execution of "ls", so the child
    // no longer exists.

    // Therefore, if exex() returns,
    // something bad happened...
    perror("Error calling exec()");
    return EXIT_FAILURE;
}

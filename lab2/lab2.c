#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for execlp
#include <wait.h>

int main() {

  char *input = NULL;
  size_t n = 0;

  while (1) {

    // Get the input
    printf("Enter programs to run.\n> ");
    ssize_t len = getline(&input, &n, stdin);

    // Check if the input was valid
    if (len == -1) {
      perror("Line not read \n");
      free(input);
      break;
    }

    // Tokenize (remove the \n at the end)
    if (len > 0 && input[len - 1] == '\n') {
      input[len - 1] = '\0';
    }

    // Fork
    pid_t cpid = fork();

    // Throw exception if it is not properly created
    if (cpid < 0) {
      perror("Fork failed.\n");
      free(input);
      break;
    }

    // Parent fork
    else if (cpid > 0) {

      int status = 0;
      if (waitpid(cpid, &status, 0) == -1) {
        perror("Waitpid failed.\n");
        exit(EXIT_FAILURE);
      }
      /*
      if (WIFEXITED(status)) {
        printf("Child extended.");
      }
      */
    }

    else {
      // Child branch, call execlp
      execlp(input, input, NULL);
      perror("Exec failure.\n");
      exit(EXIT_FAILURE);
    }
  }
}

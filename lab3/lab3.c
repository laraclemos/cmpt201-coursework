#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  // Start by allocating the array space
  char *array[5];

  // Define an i variable that will be used inside the array
  int i = 0;

  // Do the rest of the code inside a while true loop
  while (1) {
    // print the message to enter input
    printf("Enter input: ");

    // Define some variables to use with getline()
    char *input = NULL;
    size_t n = 0;

    ssize_t len = getline(&input, &n, stdin);

    if (len == -1) {
      perror("Line not read.\n");
      free(input);
      break;
    }

    if (len > 0 && input[len - 1] == '\n') {
      input[len - 1] = '\0';
    }

    // Check if item i == 5. If no, then allocate the array to the ith space.
    // If yes, do a for loop to shift the array elements down
    if (i == 5) {
      free(array[0]);
      for (int k = 0; k < i - 1; k++) {
        // Replace kth element with kth + 1 element
        array[k] = array[k + 1];
      }
      i = 4;
    }

    // Assign the input to the ith element
    array[i] = input;

    // Increment variable i
    i++;

    // Check if input was "print" -> if yes, do a for loop that goes up to i and prints each line
    // stored
    if (strcmp(input, "print") == 0) {
      for (int k = 0; k < i; k++) {
        printf("%s\n", array[k]);
      }
    }
  }

  for (int k = 0; k < i; k++) {
    free(array[k]);
  }

  return 0;
}

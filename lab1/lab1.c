#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  // Define the strings
  char *input = NULL;
  char *saveptr, *ret;
  size_t n = 0;

  // Keep prompting for text until the user leaves
  while (1) {
    // Prompt for text
    printf("Please enter some text: ");
    size_t len = getline(&input, &n, stdin);

    // Stop if the line failed
    if (len < 0) {
      perror("Line Failed");
      free(input);
      return 0;
    }

    printf("Tokens: \n");
    // Print each token in a new line
    ret = strtok_r(input, " ", &saveptr);
    while (ret != NULL) {
      printf("%s\n", ret);
      ret = strtok_r(NULL, " ", &saveptr);
    }
  }
  // free variables
  free(input);
  return 0;
}

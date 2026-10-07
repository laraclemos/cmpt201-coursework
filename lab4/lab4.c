#define _DEFAULT_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int HEAP_SIZE = 256;
int BLOCK_SIZE = 128;
int BUF_SIZE = 256;

struct header {
  uint64_t size;
  struct header *next;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int fill_value) {
  block->next = next;
  block->size = size;
  memset(block + 1, fill_value, size - sizeof(struct header));
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    perror("snprintf");
    exit(EXIT_FAILURE);
  }
  write(STDOUT_FILENO, buf, len);
}

int main(void) {
  void *start_address = sbrk(0);
  if (sbrk(HEAP_SIZE) == (void *)-1) {
    perror("sbrk");
    exit(EXIT_FAILURE);
  }

  struct header *my_block1 = (struct header *)start_address;
  struct header *my_block2 = (struct header *)((char *)my_block1 + BLOCK_SIZE);

  initialize_block(my_block1, BLOCK_SIZE, NULL, 0);
  initialize_block(my_block2, BLOCK_SIZE, my_block1, 1);

  print_out("First block's starting address: %p\n", &my_block1, sizeof(my_block1));
  print_out("Second block's starting address: %p\n", &my_block2, sizeof(my_block2));
  print_out("First block's .size: %lu\n", &my_block1->size, sizeof(my_block1));
  print_out("First block's .next: %p\n", &my_block1->next, sizeof(my_block1));
  print_out("Second block's .size: %lu\n", &my_block2->size, sizeof(my_block2));
  print_out("Second block's .next: %p\n", &my_block2->next, sizeof(my_block2));

  uint8_t *data1 = (uint8_t *)(my_block1 + 1);
  uint8_t *data2 = (uint8_t *)(my_block2 + 1);
  for (int i = 0; i < BLOCK_SIZE - sizeof(struct header); i++) {
    uint64_t byte = data1[i];
    print_out("%d\n", &byte, sizeof(byte));
  }
  for (int j = 0; j < BLOCK_SIZE - sizeof(struct header); j++) {
    uint64_t byte = data2[j];
    print_out("%d\n", &byte, sizeof(byte));
  }
}

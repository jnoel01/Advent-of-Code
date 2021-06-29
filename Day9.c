#include <limits.h>
#include <stdbool.h>
#include <stdio.h>


#define MAX_NUMBER_STRING_SIZE 16

int* parse(const char* filename, int* count) {
  FILE* fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Couldn't open file.\n");
    exit(EXIT_FAILURE);
  }

  *count = count_lines(fp);
  int* numbers = (int*)malloc(sizeof(int) * *count);
  for (int i = 0; i < *count; i++) {
    char buf[MAX_NUMBER_STRING_SIZE] = {0};
    fgets(buf, MAX_NUMBER_STRING_SIZE, fp);
    numbers[i] = atoi(buf);
  }
  fclose(fp);
  return numbers;
}


bool valid_number(int* numbers, int i, int preamble_length) {
  for (int j = 0; j < preamble_length; j++) {
    for (int k = j + 1; k < preamble_length; k++) {
      if (numbers[i - preamble_length + j] + numbers[i - preamble_length + k] == numbers[i]) {
        return true;
      }
    }
  }
  return false;
}


int part1(const char* filename, int preamble_length) {
  int count = 0;
  int* numbers = parse(filename, &count);

  for (int i = preamble_length; i < count; i++) {
    if (!valid_number(numbers, i, preamble_length)) {
      return numbers[i];
    }
  }
  return -1;
}


int part2(const char* filename, int preamble_length) {
  int count = 0;
  int* numbers = parse(filename, &count);

  int invalid_target = part1(filename, preamble_length);

  for (int size = 2; size <= count; size++) {
    for (int i = 0; i + size - 1 < count; i++) {
      int total = 0;
      for (int j = 0; j < size; j++) {
        total += numbers[i + j];
      }
      if (total == invalid_target) {
        int min = INT_MAX;
        int max = 0;

        for (int j = 0; j < size; j++) {
          if (numbers[i + j] > max) max = numbers[i + j];
          if (numbers[i + j] < min) min = numbers[i + j];
        }
        return min + max;
      }
    }
  }
  return -1;
}

int day9() {
  printf("====== Day 9 ======\n");
  printf("Part 1: %d\n", part1("data/day9.txt", 25));
  printf("Part 2: %d\n", part2("data/day9.txt", 25));
  return EXIT_SUCCESS;
}

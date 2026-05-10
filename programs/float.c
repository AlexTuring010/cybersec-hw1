#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>

void print_flag() {
  FILE * fp = fopen("flag", "r");
  char flag[256];
  memset(flag, 0, sizeof(flag));
  fread(flag, sizeof(char), sizeof(flag) / sizeof(char), fp);
  fclose(fp);
  printf("Here is your flag: %s\n", flag);
}

int main(int argc, char ** argv) {
  double number;
  printf("Gimme a number: ");
  int len = read(0, &number, sizeof(number));
  if (len != sizeof(number)) {
    printf("Failed\n");
    exit(1);
  }
  if (number != number) {
    // they'll never get the flag
    printf("That's the right number!\n");
    print_flag();
  } else {
    printf("No flag for you X)\n");
  }
  exit(0);
}



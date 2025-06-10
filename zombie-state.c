#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s\n", argv[0]);
    return 1;
  }

  short num_children = atoi(argv[1]);
  if (num_children <= 0) {
    printf("Error: Number of child processes must be a positive integer.\n");
    return 1;
  }

  for (int i = 0; i < num_children; i++) {
    pid_t pid = fork();

    if (pid < 0) {
      perror("Fork failed!");
      return 1;
    } else if (pid == 0) {
      printf("Child Process %d: PID = %d\n", i + 1, getpid());
      exit(0);
    }
  }

  for (int i = 0; i < num_children; i++) {
    wait(NULL);
  }

  printf("All child processes have been created and completed.\n");
  return 0;
}
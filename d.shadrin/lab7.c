#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

static volatile sig_atomic_t skip = 0;

void on_alarm(int s) {
  (void)s;
  skip = 1;
}

int main(void) {
  int fd = open("file.txt", O_RDONLY);
  struct stat st;
  fstat(fd, &st);
  off_t size = st.st_size;
  char *p = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

  signal(SIGALRM, on_alarm);

  int n;
  while (1) {
    printf("Line: ");
    fflush(stdout);
    skip = 0;
    alarm(5);
    int r = scanf("%d", &n);
    alarm(0);

    if (skip) {
      putchar('\n');
      for (off_t i = 0; i < size; i++)
        putchar(p[i]);
      putchar('\n');
      break;
    }
    if (r != 1) {
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      continue;
    }
    if (n == 0)
      break;

    off_t i = 0, start = 0;
    int k = 1;
    while (i < size && k < n)
      if (p[i++] == '\n') {
        k++;
        start = i;
      }

    if (k < n) {
      puts("Not line");
      continue;
    }

    while (start < size && p[start] != '\n')
      putchar(p[start++]);
    putchar('\n');
  }

  munmap(p, size);
  close(fd);
  return 0;
}

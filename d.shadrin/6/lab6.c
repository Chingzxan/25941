#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
static volatile sig_atomic_t time_skip = 0;

void on_alarm(int sig) {
  (void)sig;
  time_skip = 1;
}

int main(void) {
  int fd = open("file.txt", O_RDONLY);

  int n;
  signal(SIGALRM, on_alarm);
  alarm(5);
  printf("Line:");
  int r = scanf("%d", &n);
  alarm(0);
  if (time_skip) {
    char ch;
    lseek(fd, 0, SEEK_SET);
    while (read(fd, &ch, 1) == 1)
      putchar(ch);
    putchar('\n');
  }
  while (!time_skip) {
    int k = 1;
    off_t start = 0;
    char ch;
    if (r == 1) {
      if (n == 0)
        break;
      lseek(fd, 0, SEEK_SET);

      while (read(fd, &ch, 1) == 1 && k < n) {
        if (ch == '\n') {
          k++;
          start = lseek(fd, 0, SEEK_CUR);
        }
      }
      if (k < n) {
        puts("Not this line");
      } else {
        lseek(fd, start, SEEK_SET);
        while (read(fd, &ch, 1) == 1 && ch != '\n')
          putchar(ch);
        putchar('\n');
      }
    } else {
      printf("Not chislo\n");
      if (r != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
      }
    }
    printf("Line:");
    r = scanf("%d", &n);
  }
  close(fd);
  return 0;
}

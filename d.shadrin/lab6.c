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

  while (1) {
    printf("Line: ");

    time_skip = 0;
    alarm(5);
    int r = scanf("%d", &n);
    alarm(0);

    if (time_skip) {
      putchar('\n');
      char ch;
      lseek(fd, 0, SEEK_SET);
      while (read(fd, &ch, 1) == 1)
        putchar(ch);
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

    int k = 1;
    off_t start = 0;
    char ch;

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
  }

  close(fd);
  return 0;
}

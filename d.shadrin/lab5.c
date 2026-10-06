#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  int fd = open("file.txt", O_RDONLY);
  int n;
  while (scanf("%d", &n) == 1 && n != 0) {
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

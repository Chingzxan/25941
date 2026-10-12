#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  int fd = open("file.txt", O_RDONLY);
  int n;
  while (1) {
    int r = scanf("%d", &n);
    if (r == 1) {
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

    } else {
      printf("Not chislo\n");
      if (r != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
      }
    }
  }

  close(fd);
  return 0;
}

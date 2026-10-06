#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct massiv {
  char *strok;
  struct massiv *next;
} massiv;

void mas(char *buf, massiv **xoy) {

  massiv *new_strok = malloc(sizeof(massiv));
  new_strok->strok = malloc(strlen(buf) + 1);
  memcpy(new_strok->strok, buf, strlen(buf) + 1);
  new_strok->next = NULL;

  if (*xoy == NULL) {
    *xoy = new_strok;
  } else {
    massiv *s = *xoy;
    while (s->next != NULL)
      s = s->next;
    s->next = new_strok;
  }
}
int main() {
  massiv *xoy = NULL;

  char buf[512];
  while (fgets(buf, sizeof(buf), stdin) != NULL) {
    if (buf[0] == '.') {
      break;
    } else {
      mas(buf, &xoy);
    }
  }
  for (massiv *p = xoy; p != NULL; p = p->next)
    printf("%s", p->strok);
  while (xoy != NULL) {
    massiv *t = xoy;
    free(t->strok);
    xoy = xoy->next;
    free(t);
  }
  return 0;
}

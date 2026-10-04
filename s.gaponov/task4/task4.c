#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char *text;
    struct Node *next;
};

int main(void) {
    struct Node *head = NULL;
    struct Node *tail = NULL;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (buffer[0] == '.') {
            break;
        }

        struct Node *node = malloc(sizeof(struct Node));
        if (node == NULL) {
            perror("malloc");
            return 1;
        }

        node->text = malloc(strlen(buffer) + 1);
        if (node->text == NULL) {
            perror("malloc");
            free(node);
            return 1;
        }

        strcpy(node->text, buffer);
        node->next = NULL;

        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    struct Node *current = head;

    while (current != NULL) {
        printf("%s", current->text);
        current = current->next;
    }

    while (head != NULL) {
        struct Node *next = head->next;
        free(head->text);
        free(head);
        head = next;
    }

    return 0;
}
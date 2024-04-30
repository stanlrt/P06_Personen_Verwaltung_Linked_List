#include "node.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_node(void* data) {
  Node* node = (Node*)malloc(sizeof(Node));
  if (node == NULL) {
    fprintf(stderr, "Failed to allocate memory for a new node.\n");
    return NULL;
  }
  if (data != NULL) {
    node->data = data;
  } else {
    node->data = NULL;
  }
  node->next = NULL;
  return node;
}

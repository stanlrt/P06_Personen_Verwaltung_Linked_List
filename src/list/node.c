#include "node.h"

#include <stdlib.h>

Node* createNewNode(void* data) {
  Node* node = (Node*)malloc(sizeof(Node));
  if (node == NULL) {
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

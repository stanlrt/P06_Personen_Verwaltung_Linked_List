#ifndef NODE_H
#define NODE_H

typedef struct Node {
  void* data;
  struct Node* next;
} Node;

/**
 * @brief Create a new node
 * @param data [OPTIONAL] The data to store in the node
 * @param next [OPTIONAL] The next node in the list
 * @return The new node
 */
Node* create_node(void* data);

#endif  // NODE_H

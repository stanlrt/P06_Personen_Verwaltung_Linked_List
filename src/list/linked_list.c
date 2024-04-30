
#include "linked_list.h"

#define _GNU_SOURCE
#include <file-printing.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sorting.h"

LinkedList* create_linked_list(void) {
  LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
  if (list == NULL) {
    fprintf(stderr, "Failed to allocate memory for a new linked list.\n");
    return NULL;
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

Node* getNodeAtIndex(LinkedList* list, int index) {
  if (index < 0 || index >= list->size) {
    return NULL;
  }
  Node* current = list->head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }
  return current;
}

static void* getNodeAtIndexGeneric(void* dataStructure, size_t index) {
  LinkedList* list = (LinkedList*)dataStructure;
  return getNodeAtIndex(list, index);
}

Node* insertAtStart(LinkedList* list, void* data, bool allowDuplicates,
                    int (*ComparisonFunction)(const void*, const void*)) {
  if (!allowDuplicates && contains(list, data, ComparisonFunction)) return NULL;
  Node* node = create_node(data);
  if (list->size == 0) {
    list->tail = node;
  } else {
    node->next = list->head;
  }
  list->head = node;
  list->size++;
}

Node* insertAtEnd(LinkedList* list, void* data, bool allowDuplicates,
                  int (*ComparisonFunction)(const void*, const void*)) {
  if (!allowDuplicates && contains(list, data, ComparisonFunction)) return NULL;
  Node* node = create_node(data);
  if (list->size == 0) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
  list->size++;
}

Node* insertAtIndex(LinkedList* list, void* data, int index,
                    bool allowDuplicates,
                    int (*ComparisonFunction)(const void*, const void*)) {
  if (!allowDuplicates && contains(list, data, ComparisonFunction)) return NULL;
  if (index < 0) return NULL;
  if (index == 0) {
    insertAtStart(list, data, allowDuplicates, ComparisonFunction);
    return list->head;
  }
  if (index >= list->size) {
    insertAtEnd(list, data, allowDuplicates, ComparisonFunction);
    return list->tail;
  }
  Node* node = create_node(data);
  Node* currentNodeAtIndex = getNodeAtIndex(list, index - 1);
  node->next = currentNodeAtIndex->next;
  currentNodeAtIndex->next = node;
  list->size++;
}

Node* sortedInsert(LinkedList* list, void* data, bool allowDuplicates,
                   int (*ComparisonFunction)(const void*, const void*)) {
  if (!allowDuplicates && contains(list, data, ComparisonFunction)) return NULL;
  if (list->size == 0) {
    insertAtStart(list, data, allowDuplicates, ComparisonFunction);
    return list->head;
  }
  if (ComparisonFunction(data, list->head->data) <= 0) {
    insertAtStart(list, data, allowDuplicates, ComparisonFunction);
    return list->head;
  }
  if (ComparisonFunction(data, list->tail->data) > 0) {
    insertAtEnd(list, data, allowDuplicates, ComparisonFunction);
    return list->tail;
  }

  Node* current = list->head;
  while (current->next != NULL &&
         ComparisonFunction(data, current->next->data) > 0) {
    current = current->next;
  }
  Node* newNode = create_node(data);
  newNode->next = current->next;
  current->next = newNode;
  list->size++;
}

bool deleteNode(LinkedList* list, void* data,
                int (*ComparisonFunction)(const void*, const void*)) {
  if (list->size == 0) return false;
  bool matchFound = false;
  for (size_t i = 0; i < list->size; i++) {
    if (ComparisonFunction(data, getNodeAtIndex(list, i)->data) == 0) {
      matchFound = true;
      deleteAtIndex(list, i);
    }
  }
  return matchFound;
}

void deleteAtStart(LinkedList* list) {
  if (list->size == 0) {
    return;
  }
  Node* temp = list->head;
  list->head = list->head->next;
  free(temp);
  list->size--;
}

void deleteAtEnd(LinkedList* list) {
  if (list->size == 0) {
    return;
  }
  Node* nextToLast = getNodeAtIndex(list, list->size - 2);
  free(nextToLast->next);
  nextToLast->next = NULL;
  list->tail = nextToLast;
  list->size--;
}

void deleteAtIndex(LinkedList* list, int index) {
  if (index < 0 || index >= list->size) {
    return;
  }
  if (index == 0) {
    deleteAtStart(list);
    return;
  }
  if (index == list->size - 1) {
    deleteAtEnd(list);
    return;
  }
  Node* nodeToDelete = getNodeAtIndex(list, index);
  nodeToDelete->next = nodeToDelete->next->next;
  free(nodeToDelete);
  list->size--;
}

void deleteList(LinkedList* list) {
  while (list->size > 0) {
    deleteAtStart(list);
  }
  free(list);
}

/**
 * @brief Swaps the two given nodes in the given linked list, by swapping their
 * data.
 *
 * @param list The linked list to swap nodes in.
 * @param index1 The index of the first node to swap.
 * @param index2 The index of the second node to swap.
 *
 * @note If the nodes contain other information as data, this function will not
 * work as expected.
 */
static void swapNodes(void* list, size_t index1, size_t index2) {
  if (index1 == index2) return;
  LinkedList* linkedList = (LinkedList*)list;

  // Ensure index1 is the smaller index
  if (index1 > index2) {
    size_t temp = index1;
    index1 = index2;
    index2 = temp;
  }

  Node* previous1 = NULL;
  Node* previous2 = NULL;
  Node* current1 = linkedList->head;
  Node* current2 = linkedList->head;
  size_t index = 0;

  // Find the node at index1
  for (size_t i = 0; i < index1; i++) {
    previous1 = current1;
    current1 = current1->next;
  }

  // Find the node at index2
  for (size_t i = 0; i < index2; i++) {
    previous2 = current2;
    current2 = current2->next;
  }

  if (current1 == NULL || current2 == NULL) return;

  if (current1->next == current2) {
    if (previous1 != NULL) previous1->next = current2;
    current1->next = current2->next;
    current2->next = current1;
  } else {
    Node* temp = current2->next;
    if (previous1 != NULL) previous1->next = current2;
    current2->next = current1->next;
    previous2->next = current1;
    current1->next = temp;
  }

  if (index1 == 0) linkedList->head = current2;
  if (index2 == linkedList->size - 1) linkedList->tail = current1;
}

bool contains(LinkedList* list, void* data,
              int (*Comparator)(const void*, const void*)) {
  for (size_t i = 0; i < list->size; i++) {
    if (Comparator(data, getNodeAtIndex(list, i)->data) == 0) {
      return true;
    }
  }
  return false;
}

void sort(LinkedList* list,
          int (*ComparisonFunction)(const void*, const void*)) {
  quick_sort(list, list->size, sizeof(Node), getNodeAtIndexGeneric,
             ComparisonFunction, swapNodes);
}

void save_list_to_file(LinkedList* list, const char* filename,
                       FileFormat format,
                       char* nodeDataToString(const void*, FileFormat)) {
  FILE* file = fopen(filename, "w");
  if (!file) {
    fprintf(stderr, "Failed to open file %s\n", filename);
    return;
  }
  for (size_t i = 0; i < list->size; i++) {
    fprintf(file, "%s",
            nodeDataToString(getNodeAtIndex(list, i)->data, format));
    if (i < list->size - 1) {
      fprintf(file, format == CSV ? "," : "\n");
    }
  }
  fclose(file);
}

void load_list_from_file(LinkedList* list, const char* filename,
                         FileFormat format,
                         void* parseNodeData(const char*, FileFormat),
                         int (*ComparisonFunction)(const void*, const void*),
                         int nodeDataAttributesCount) {
  FILE* file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Failed to open file %s\n", filename);
    return;
  }

  char buffer[1024];
  char* tokens[nodeDataAttributesCount];

  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    char* line = strdup(buffer);
    switch (format) {
      case CSV: {
        int tokenCount = 0;
        char* token = strtok(line, ",");
        while (token != NULL && tokenCount < nodeDataAttributesCount) {
          tokens[tokenCount] = token;
          fprintf(stderr, "Token %d: %s\n", tokenCount,
                  token);  // Debugging output
          token = strtok(NULL, ",");
          tokenCount++;
        }
        if (tokenCount == nodeDataAttributesCount) {
          char* csvLine = strdup(tokens[0]);
          for (int j = 1; j < nodeDataAttributesCount; j++) {
            strcat(csvLine, ",");
            strcat(csvLine, tokens[j]);
          }
          void* data = parseNodeData(csvLine, CSV);
          free(csvLine);
          if (data != NULL) {  // Check if data parsed correctly
            Node* node = create_node(data);
            insertAtEnd(list, node->data, false, ComparisonFunction);
          } else {
            fprintf(stderr, "Failed to parse data into a valid structure.\n");
          }
        } else {
          fprintf(stderr, "Expected %d tokens, but got %d.\n",
                  nodeDataAttributesCount, tokenCount);
        }
      } break;
      case TXT:
        void* data = parseNodeData(line, TXT);
        Node* node = create_node(data);
        insertAtEnd(list, node->data, false, ComparisonFunction);
        break;
      default:
        fprintf(stderr, "Invalid file format.");
        break;
    }
    free(line);  // Free the duplicated line
  }
  fclose(file);
}

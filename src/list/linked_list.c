
#include "linked_list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sorting.h"

LinkedList* createNewLinkedList(void) {
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

void insertAtStart(LinkedList* list, void* data, bool allowDuplicates,
                   int (*ComparisonFunction)(const void*, const void*)) {
  if (!allowDuplicates && contains(list, data, ComparisonFunction)) return;
  Node* node = createNewNode(data);
  if (list->size == 0) {
    list->tail = node;
  } else {
    node->next = list->head;
  }
  list->head = node;
  list->size++;
}

void insertAtEnd(LinkedList* list, void* data, bool allowDuplicates,
                 int (*ComparisonFunction)(const void*, const void*)) {
  if (!allowDuplicates && contains(list, data, ComparisonFunction)) return;
  Node* node = createNewNode(data);
  if (list->size == 0) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
  list->size++;
}

void insertAtIndex(LinkedList* list, void* data, int index,
                   bool allowDuplicates,
                   int (*ComparisonFunction)(const void*, const void*)) {
  if (!allowDuplicates && contains(list, data, ComparisonFunction)) return;
  if (index < 0) return;
  if (index == 0) {
    insertAtStart(list, data, allowDuplicates, ComparisonFunction);
    return;
  }
  if (index >= list->size) {
    insertAtEnd(list, data, allowDuplicates, ComparisonFunction);
    return;
  }
  Node* node = createNewNode(data);
  Node* currentNodeAtIndex = getNodeAtIndex(list, index - 1);
  node->next = currentNodeAtIndex->next;
  currentNodeAtIndex->next = node;
  list->size++;
}

void sortedInsert(LinkedList* list, void* data, bool allowDuplicates,
                  int (*ComparisonFunction)(const void*, const void*)) {
  if (!allowDuplicates && contains(list, data, ComparisonFunction)) return;
  if (list->size == 0) {
    insertAtStart(list, data, allowDuplicates, ComparisonFunction);
    return;
  }
  if (ComparisonFunction(data, list->head->data) <= 0) {
    insertAtStart(list, data, allowDuplicates, ComparisonFunction);
    return;
  }
  if (ComparisonFunction(data, list->tail->data) > 0) {
    insertAtEnd(list, data, allowDuplicates, ComparisonFunction);
    return;
  }

  Node* current = list->head;
  while (current->next != NULL &&
         ComparisonFunction(data, current->next->data) > 0) {
    current = current->next;
  }
  Node* newNode = createNewNode(data);
  newNode->next = current->next;
  current->next = newNode;
  list->size++;
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

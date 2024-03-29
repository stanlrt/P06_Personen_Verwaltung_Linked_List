#include "linked_list.h"

#include <stdlib.h>

LinkedList* createLinkedList(void) {
  LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
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

void insertAtStart(LinkedList* list, void* data) {
  Node* node = createNewNode(data);
  node->next = list->head;
  list->head = node;
  list->size++;
}

void insertAtEnd(LinkedList* list, void* data) {
  Node* node = createNewNode(data);
  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  }
}

void insertAtIndex(LinkedList* list, void* data, int index) {
  if (index < 0) {
    return;
  }
  if (index == 0) {
    insertAtStart(list, data);
    return;
  }
  if (index >= list->size) {
    insertAtEnd(list, data);
    return;
  }
  Node* node = createNewNode(data);
  Node* currentNodeAtIndex = getNodeAtIndex(list, index);
  node->next = currentNodeAtIndex->next;
  currentNodeAtIndex->next = node;
  list->size++;
}

void sortedInsert(LinkedList* list, void* data,
                  int (*Comparator)(const void*, const void*)) {
  if (list->size == 0) {
    insertAtStart(list, data);
    return;
  }
  Node* current = list->head;
  int index = 0;
  while (current->next != NULL && Comparator(data, current->next->data) < 0) {
    current = current->next;
    index++;
  }
  insertAtIndex(list, data, index);
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

void swapNodes(LinkedList* list, int index1, int index2) {
  if (index1 == index2) {
    return;
  }
  Node* node1 = getNodeAtIndex(list, index1);
  Node* node2 = getNodeAtIndex(list, index2);
  void* temp = node1->data;
  node1->data = node2->data;
  node2->data = temp;
}

// TODO use QuickSort
void sort(LinkedList* list, int (*Comparator)(const void*, const void*)) {
  for (int i = 0; i < list->size; i++) {
    for (int j = 0; j < list->size - 1; j++) {
      if (Comparator(getNodeAtIndex(list, j)->data,
                     getNodeAtIndex(list, j + 1)->data) > 0) {
        swapNodes(list, j, j + 1);
      }
    }
  }
}

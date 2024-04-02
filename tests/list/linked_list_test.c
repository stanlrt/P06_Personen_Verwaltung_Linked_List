#include "linked_list.h"

#include <assert.h>
#include <stdio.h>

#include "linked_list.h"
#include "node.h"

static int basic_integer_compare(const void* a, const void* b) {
  if (*(int*)a > *(int*)b) return 1;
  if (*(int*)a < *(int*)b) return -1;
  return 0;
}

static void test_list_insert(void) {
  // BEGIN-STUDENTS-TO-ADD-CODE
  // arrange
  LinkedList* list = createNewLinkedList();
  int val1 = 10;
  int val2 = 20;
  Node* node1 = createNewNode((void*)&val1);
  Node* node2 = createNewNode((void*)&val2);

  // act
  insertAtEnd(list, node1, false, basic_integer_compare);
  insertAtEnd(list, node2, false, basic_integer_compare);

  // assert
  assert(*(int*)list->head->data == 10);
  assert(*(int*)list->tail->data == 20);

  // END-STUDENTS-TO-ADD-CODE
}

static void test_list_remove(void) {
  // BEGIN-STUDENTS-TO-ADD-CODE
  // arrange

  // act
  assert(1 == 2);

  // assert

  // END-STUDENTS-TO-ADD-CODE
}

static void test_list_clear(void) {
  // BEGIN-STUDENTS-TO-ADD-CODE
  // arrange

  // act
  assert(1 == 2);

  // assert

  // END-STUDENTS-TO-ADD-CODE
}
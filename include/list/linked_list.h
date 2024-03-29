#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"

typedef struct LinkedList {
  Node* head;
  Node* tail;
  int size;
} LinkedList;

/**
 * @brief Comparator function type definition
 * @param a The first element to compare
 * @param b The second element to compare
 * @return An integer less than, equal to, or greater than zero if a is found,
 * respectively, to be less than, to match, or be greater than b.
 */
typedef int (*Comparator)(const void*, const void*);

/**
 * @brief Create a new list object
 */
LinkedList* createLinkedList(void);

/**
 * @brief Get the node at a specific index in the list
 * @param list The list to get the node from
 * @param index The index to get the node at
 * @return The node at the specific index
 * @note If the index does not correspond to an exisitng node,
 * `NULL` will be returned.
 */
Node* getNodeAtIndex(LinkedList* list, int index);

/**
 * @brief Insert data at the start of the list
 * @param list The list to insert into
 * @param data The data to insert
 */
void insertAtStart(LinkedList* list, void* data);

/**
 * @brief Insert data at the end of the list
 * @param list The list to insert into
 * @param data The data to insert
 */
void insertAtEnd(LinkedList* list, void* data);

/**
 * @brief Insert data at a specific index in the list
 * @param list The list to insert into
 * @param data The data to insert
 * @param index The index to insert at.
 * @note If the index is larger than the size of
 * the list, the data will be inserted at the end of the list.
 */
void insertAtIndex(LinkedList* list, void* data, int index);

/**
 * @brief Insert data into the list in a sorted manner
 * @param list The list to insert into
 * @param data The data to insert
 * @param Comparator The comparator function to use
 * @note The list must be sorted before this function is called. You can use the
 * `sort` function.
 */
void sortedInsert(LinkedList* list, void* data,
                  int (*Comparator)(const void*, const void*));

/**
 * @brief Delete the data at the start of the list
 * @param list The list to delete from
 */
void deleteAtStart(LinkedList* list);

/**
 * @brief Delete the data at the end of the list
 * @param list The list to delete from
 */
void deleteAtEnd(LinkedList* list);

/**
 * @brief Delete the data at a specific index in the list
 * @param list The list to delete from
 * @param index The index to delete at
 */
void deleteAtIndex(LinkedList* list, int index);

/**
 * @brief Delete the entire list
 * @param list The list to delete
 */
void deleteList(LinkedList* list);

/**
 * @brief Swap the data at two specific indices in the list
 * @param list The list to swap in
 * @param index1 The first index to swap
 * @param index2 The second index to swap
 */
void swap(LinkedList* list, int index1, int index2);

/**
 * @brief Sort the list using a comparator function
 * @param list The list to sort
 * @param Comparator The comparator function to use
 */
void sort(LinkedList* list, int (*Comparator)(const void*, const void*));

#endif  // LINKED_LIST_H

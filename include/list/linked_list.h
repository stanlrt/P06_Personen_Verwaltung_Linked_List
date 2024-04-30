#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

#include "file-printing.h"
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
 * @brief Creates a new list
 */
LinkedList* create_linked_list(void);

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
 * @param allowDuplicates Whether to allow duplicates
 * @return The node that was inserted
 */
Node* insertAtStart(LinkedList* list, void* data, bool allowDuplicates,
                    int (*Comparator)(const void*, const void*));

/**
 * @brief Insert data at the end of the list
 * @param list The list to insert into
 * @param data The data to insert
 * @param allowDuplicates Whether to allow duplicates
 * @param Comparator The comparison function to use
 *
 * @return The node that was inserted
 */
Node* insertAtEnd(LinkedList* list, void* data, bool allowDuplicates,
                  int (*Comparator)(const void*, const void*));

/**
 * @brief Insert data at a specific index in the list
 * @param list The list to insert into
 * @param data The data to insert
 * @param index The index to insert at.
 * @param allowDuplicates Whether to allow duplicates
 * @param Comparator The comparison function to use
 *
 * @return The node that was inserted
 * @note If the index is larger than the size of
 * the list, the data will be inserted at the end of the list.
 */
Node* insertAtIndex(LinkedList* list, void* data, int index,
                    bool allowDuplicates,
                    int (*Comparator)(const void*, const void*));

/**
 * @brief Insert data into the list in a sorted manner
 * @param list The list to insert into
 * @param data The data to insert
 * @param Comparator The comparator function to use
 * @param allowDuplicates Whether to allow duplicates
 * @return The node that was inserted
 * @note The list must be sorted before this function is called. You can use the
 * `sort` function.
 */
Node* sortedInsert(LinkedList* list, void* data, bool allowDuplicates,
                   int (*Comparator)(const void*, const void*));

/**
 * @brief Delete all instances of a specific data element from the list
 * @param list The list to delete from
 * @param data The data to delete
 * @param Comparator The comparison function to use
 */
bool deleteNode(LinkedList* list, void* data,
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
void swapNodesAtIndex(LinkedList* list, int index1, int index2);

/**
 * @brief Sort the list using a comparator function
 * @param list The list to sort
 * @param Comparator The comparator function to use
 */
void sort(LinkedList* list, int (*Comparator)(const void*, const void*));

/**
 * @brief Check if the list contains a specific data element
 * @param list The list to check
 * @param data The data to check for
 * @param Comparator The comparator function to use
 * @return `true` if the list contains the data, `false` otherwise
 */
bool contains(LinkedList* list, void* data,
              int (*Comparator)(const void*, const void*));

/**
 * @brief Save the list to a file
 * @param list The list to save
 * @param filename The filename to save to
 * @param format The format to save in
 * @param nodeDataToString The function to convert the node data to a string
 */
void save_list_to_file(LinkedList* list, const char* filename,
                       FileFormat format,
                       char* nodeDataToString(const void*, FileFormat));

/**
 * @brief Load the list from a file
 * @param list The list to load into
 * @param filename The filename to load from
 * @param format The format to load in
 * @param parseNodeData The function to convert the node data from a string
 */
void load_list_from_file(LinkedList* list, const char* filename,
                         FileFormat format,
                         void* parseNodeData(const char*, FileFormat),
                         int (*ComparisonFunction)(const void*, const void*),
                         int nodeDataAttributesCount);

#endif  // LINKED_LIST_H

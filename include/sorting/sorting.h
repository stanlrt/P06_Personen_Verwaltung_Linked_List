#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef SORTING_H
#define SORTING_H

/**
 * @brief Compares the two given items.
 *
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return An integer less than, equal to, or greater than zero if a is found,
 *         respectively, to be less than, to match, or be greater than b.
 */
typedef int (*ComparisonFunction)(const void* a, const void* b);

/**
 * @brief Swaps the two given items in the given data structure.
 *
 * @param dataStructure The data structure to swap items in.
 * @param index1 The index of the first item to swap.
 * @param index2 The index of the second item to swap.
 */
typedef void (*SwappingFunction)(void* dataStructure, size_t index1,
                                 size_t index2);

/**
 * @brief Accesses the item at the given index in the given data structure.
 *
 * @param dataStructure The data structure to access.
 * @param index The index of the item to access.
 * @return The item at the given index.
 */
typedef void* (*AccessFunction)(void* dataStructure, size_t index);

/**
 * @brief Sorts the given array in-place, using the quick sort algorithm.
 *
 * @param dataStructure The data structure to sort.
 * @param numberOfItems The number of items in the data structure.
 * @param itemSize The size of each item in the data structure.
 * @param comparisonFunction The function to use to compare array items.
 * @param swappingFunction The function to use to swap array items.
 */
void quick_sort(void* array, size_t number_of_items, size_t item_size,
                AccessFunction access_function,
                ComparisonFunction comparison_function,
                SwappingFunction swapping_function);

#endif  // SORTING_H

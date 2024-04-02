#include "sorting.h"

/**
 * Partitions the given array and returns the new pivot index.
 * Rules for partitioning:
 * 1. The pivot is the last element in the array.
 * 2. The pivot is placed in the correct position in the array, such that all
 *    elements to the left of the pivot are less than the pivot, and all
 * elements to the right of the pivot are greater than or equal to the pivot.
 *
 * @param numberOfItems The number of items in the data structure.
 * @param itemSize The size of each item in the data structure.
 * @param comparisonFunction The function to use to compare array items.
 * @return The new pivot index.
 */
static size_t partition_and_get_new_pivot_index(
    void* dataStructure, size_t numberOfItems, size_t itemSize,
    AccessFunction accessFunction, ComparisonFunction comparisonFunction,
    SwappingFunction swappingFunction) {
  size_t i = 0;
  for (size_t j = 0; j < numberOfItems - 1; j++) {
    if (comparisonFunction(accessFunction(dataStructure, j),
                           accessFunction(dataStructure, numberOfItems - 1)) <
        0) {
      swappingFunction(dataStructure, i, j);
      i++;
    }
  }
  swappingFunction(dataStructure, i, numberOfItems - 1);
  return i;
}

void quick_sort(void* dataStructure, size_t numberOfItems, size_t itemSize,
                AccessFunction accessFunction,
                ComparisonFunction comparisonFunction,
                SwappingFunction swappingFunction) {
  if (numberOfItems < 2) return;
  size_t pivotIndex = partition_and_get_new_pivot_index(
      dataStructure, numberOfItems, itemSize, accessFunction,
      comparisonFunction, swappingFunction);
  quick_sort(dataStructure, pivotIndex, itemSize, accessFunction,
             comparisonFunction,
             swappingFunction);  // Recursively sort the left part
  quick_sort(dataStructure, numberOfItems - pivotIndex - 1, itemSize,
             accessFunction, comparisonFunction,
             swappingFunction);  // Recursively sort the right part
}
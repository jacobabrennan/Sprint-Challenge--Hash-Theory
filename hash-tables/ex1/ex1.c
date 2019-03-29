#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{
    // Allocate memory for hash table, setup default resultant answer pair
    HashTable *ht = create_hash_table(16);
    Answer *result = NULL;

    // Iterate on array until an index complements a previously iterated index
    for(int index_test=0; index_test < length; index_test++)
    {

        // Get weight at index and calculate needed complementary weight
        int weight_test = weights[index_test];
        int weight_complement = limit-weight_test;

        // Check for complementary weight in hash table.
        // If not found, associate needed weight with index
        int index_complement = hash_table_retrieve(ht, weight_test);
        if(-1 == index_complement)
        {
            hash_table_insert(ht, weight_complement, index_test);
        }

        // If complementary weight is found,
        // construct resultant answer pair and stop iterating
        else
        {
            // Allocate memory for resultant answer pair
            result = malloc(sizeof(Answer));
            // Ensure that larger weight is stored in index_1
            if(weight_test >= weight_complement)
            {
                result->index_1 = index_test;
                result->index_2 = index_complement;
            }
            else
            {
                result->index_1 = index_test;
                result->index_2 = index_complement;
            }
            // Stop iterating (answer already found)
            break;
        }
    }

    // Cleanup and return resultant answer pair
    destroy_hash_table(ht);
    return result;
}

void print_answer(Answer *answer)
{
  if (answer != NULL) {
    printf("%d %d\n", answer->index_1, answer->index_2);
  } else {
    printf("NULL\n");
  }
}

#ifndef TESTING
int main(void)
{

  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1);  // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer* answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2);  // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer* answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3);  // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer* answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4);  // {6, 2}

  return 0;
}
#endif

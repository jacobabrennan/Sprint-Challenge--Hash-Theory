#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

#define NO_LOCATION "NONE"

char **reconstruct_trip(Ticket **tickets, int length)
{
    // Allocate memory for hash table and resultant route
    HashTable *ht = create_hash_table(16);
    char **route = malloc(length * sizeof(char *));

    // Iterate over tickets array, associate each source with a destination
    for(int index=0; index < length; index++)
    {
        hash_table_insert(ht, tickets[index]->source, tickets[index]->destination);
    }

    // Add each destination to the route, in order
    char *location = NO_LOCATION;
    for(int index=0; index < length; index++)
    {
        location = hash_table_retrieve(ht, location);
        route[index] = location;
    }

    // Cleanup and return resultant route
    destroy_hash_table(ht);
    return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++) {
    printf("%s\n", route[i]);
  }
}



#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  return 0;
}
#endif

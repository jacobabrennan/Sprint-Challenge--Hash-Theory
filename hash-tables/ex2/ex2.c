#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

#define NO_LOCATION "NONE"

char **reconstruct_trip(Ticket **tickets, int length)
{
    HashTable *ht = create_hash_table(16);
    char **route = malloc(length * sizeof(char *));

    // YOUR CODE HERE
    Ticket *ticket_start;
    for(int index=0; index < length; index++)
    {
        Ticket *ticket_indexed = tickets[index];
        if(0 == strcmp(NO_LOCATION, ticket_indexed->source))
        {
            ticket_start = ticket_indexed;
            continue;
        }
        hash_table_insert(ht, ticket_indexed->source, ticket_indexed->destination);
    }
    char *location = ticket_start->destination;
    for(int index=0; index < length; index++)
    {
        route[index] = location;
        location = hash_table_retrieve(ht, location);
    }

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

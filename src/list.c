#include "list.h"

#include <stdlib.h>
#include <string.h>

/*  Create the linked list */
struct List* CreateList(void)
{
  struct List *head = malloc(sizeof(struct List));
  head->next = NULL;
  return head;
}

/*  Delete the linked list */
void removeList(struct List *list)
{
  ClearList(list);
  free(list);
  list = NULL;
}

/*  Add leaf by username */
void AddLeaf(const char *username, struct List *head)
{
  struct List *leaf = CreateList();
  strcpy(leaf->username, username);
  leaf->next = head->next;
  head->next = leaf;
}

/*  Remove leaf by name */
int RemoveLeafByName(const char *username, struct List *head)
{
  struct List *currentLeaf = head->next;
  struct List *prevLeaf = head;
  while (currentLeaf) {
    if (strcmp(currentLeaf->username, username) == 0) {
      prevLeaf->next = currentLeaf->next;
      free(currentLeaf);
      return 0;
    }

    prevLeaf = currentLeaf;
    currentLeaf = currentLeaf->next;
  }

  return -1;
}

/*  Clear the list */
void ClearList(struct List *head)
{
  struct List **currentLeaf = &head->next;
  
  struct List *leafToDelete = NULL;
  while (*currentLeaf) {
    leafToDelete = *currentLeaf;
    *currentLeaf = (*currentLeaf)->next;

    free(leafToDelete);
    leafToDelete = NULL;
  }
}

#pragma once

#define MAX_USERNAME_LENGTH 50

struct List {
  char username[MAX_USERNAME_LENGTH];
  struct List *next;
};

/*  Create the linked list */
struct List* CreateList(void);

/*  Delete the linked list */
void RemoveList(struct List *list);

/*  Add leaf by username */
void AddLeaf(const char *username, struct List *head);

/*  Remove leaf by name */
int RemoveLeafByName(const char *username, struct List *head);

/*  Clear the list */
void ClearList(struct List *head);

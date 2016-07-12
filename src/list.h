#pragma once

#define MAX_USERNAME_LENGTH 50

struct List {
  char username[MAX_USERNAME_LENGTH];
  struct List *next;
};

/*  Create the linked list */
struct List* createList(void);

/*  Delete the linked list */
void removeList(struct List *list);

/*  Add leaf by username */
void addLeaf(const char *username, struct List *head);

/*  Remove leaf by name */
int removeLeafByName(const char *username, struct List *head);

/*  Clear the list */
void clearList(struct List *head);

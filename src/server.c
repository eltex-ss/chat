#include "common.h"
#include "list.h"

#define MAX_USERS_COUNT 100
#define MAX_USER_NAME_LENGHT 40

void closeQueue(int queue_id)
{
  msgctl(queue_id, IPC_RMID, 0);
}

void printList(struct List *head)
{
  struct List *currentElem = head->next;

  printf("List:\n");
  while (currentElem) {
    printf("%s\n", currentElem->username);
    currentElem = currentElem->next;
  }
}

int main(void)
{
  int queue_key = ftok("/home/Alexander/Projects/SummerSchool/chat/server.c",
                       1);
  int queue_id = msgget(queue_key, IPC_CREAT | 0666);
  struct Message message;
  char user_names[MAX_USERS_COUNT][MAX_USER_NAME_LENGHT];
  
  if (queue_id == -1) {
    printf("Error, msgget\n");
  }
  while (1) {
    if (msgrcv(queue_id, &message, messageMaxSize, 1, 0) == -1) {
      printf("Error, msgrcv\n");
      msgctl(queue_id, IPC_RMID, 0);
    }
    printf("Message: %s\n", message.text);
  }

  return 0;  
}

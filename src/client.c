#include "common.h"

static int queue_id;

void OpenQueue(void)
{
  int queue_key = ftok("/home/Alexander/Projects/SummerSchool/chat/server.c", 1);
  
  queue_id = msgget(queue_key, 0666);
  if (queue_id == -1) {
    perror("Error, msgget\n");
    exit(1);
  }
}

void SendNickname(void)
{
  struct Message message;
  char *buf;
  size_t buf_size;

  printf("Your nickname: ");
  getline(&buf, &buf_size, stdin);
  message.type = 1;
  sprintf(message.text, "%s", buf);
  if (msgsnd(queue_id, &message, messageMaxSize, 1) == -1) {
    perror("Error, send nickname\n");
    exit(1);
  }
}

void ReadAndSend(void)
{
  char *buf;
  size_t buf_size;
  struct Message message;
  
  message.type = 3;
  while (1) {
    printf("Write a message:\n");
    getline(&buf, &buf_size, stdin);
    strcpy(message.text, buf);
    if (msgsnd(queue_id, &message, messageMaxSize, 1) == -1) {
      perror("Error, send message\n");
      exit(1);
    }
  }
}

int main(void)
{
  OpenQueue();
  SendNickname();
  ReadAndSend();
  
  return 0;
}

#include "common.h"

static int server_queue;
static int messages_queue;
static char nickname[16];

void OpenQueues(void)
{
  char path_to_file[] = "/home/Alexander/Projects/SummerSchool/chat/server.c";
  key_t server_queue_key = ftok(path_to_file, 1);
  key_t messages_queue_key = ftok(path_to_file, 2);

  server_queue = msgget(server_queue_key, 0666);
  if (server_queue == -1) {
    perror("Error, msgget\n");
    exit(1);
  }
  messages_queue = msgget(messages_queue_key, 0666);
  if (messages_queue == -1) {
    perror("Error, msgget\n");
    exit(1);
  }
}

void SendMessage(struct Message *message)
{
  if (msgsnd(server_queue, message, messageMaxSize, 0) == -1) {
    perror("Error, send message\n");
    exit(1);
  }
}

void SendNickname(void)
{
  struct Message message;
  char white_space;

  printf("Choose nickname. Note that it must be <= 15 length\n");
  printf("Your nickname: ");
  scanf("%s", nickname);
  scanf("%c", &white_space);
  message.type = 1;
  sprintf(message.text, "Connected new user: %s", nickname);
  SendMessage(&message);
}

void ReadAndSend(void)
{
  char *buf;
  size_t buf_size;
  struct Message message;
  
  message.type = 3;
  while (message.type == 3) {
    printf("Write a message:\n");
    getline(&buf, &buf_size, stdin);
    buf[strlen(buf)-1] = '\0';
    if (buf_size > 2 && buf[0] == ':' && buf[1] =='q' ) {
      message.type = 2;
      sprintf(message.text, "User disconnected: %s", nickname);
    }
    else {
      sprintf(message.text, "%s: %s", nickname, buf);
    }
    SendMessage(&message);
  }
}

void ReadMessages(void)
{
  struct Message message;

  while (1) {
    if (msgrcv(messages_queue, &message, messageMaxSize, 0, 0) == -1) {
      perror("Error, msgrcv\n");
    }
    
    if (message.text[0] == 'U')
      return;

    printf("%s\n", message.text);
  }
}

int main(void)
{
  int errorStatus;

  OpenQueues();
  SendNickname();
  if (fork() == 0) {
    /*  Read input from keyboard and send to it to server */
    close(stdout);
    ReadAndSend();
    exit(0);
  }

  if (fork() == 0) { 
    /*  Read messages from server */
    ReadMessages();
    exit(0);
  } else {
    close(stdout);
  }

  for (int i = 0; i < 2; ++i)
    wait(&errorStatus);

  return 0;
}

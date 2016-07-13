#include "common.h"
#include "list.h"

#define MAX_USERS_COUNT 100
#define MAX_USER_NAME_LENGHT 40

static int server_queue;
static int messages_queue;

void CreateQueues(void)
{ 
  char path_to_file[] = "/home/Alexander/Projects/SummerSchool/chat/server.c";
  key_t server_queue_key    = ftok(path_to_file, 1);
  key_t messages_queue_key  = ftok(path_to_file, 2);

  server_queue = msgget(server_queue_key, IPC_CREAT | 0666);
  if (server_queue == -1) {
    perror("Error, Can't create the queue\n");
    exit(1);
  }
  messages_queue = msgget(messages_queue_key, IPC_CREAT | 0666);
  if (messages_queue == -1) {
    perror("Error, Can't create the queue\n");
    exit(1);
  }
}

void RemoveQueues(void)
{
  msgctl(server_queue, IPC_RMID, 0);
  msgctl(messages_queue, IPC_RMID, 0);
}

void SendMessage(struct Message *message)
{
  message->type = 1;
  if (msgsnd(messages_queue, message, messageMaxSize, 0) == -1) {
    perror("Error, msgsnd\n");
  }
}

void StartReceiving(void)
{ 
  struct  Message message;
  struct  List *usernames = CreateList();
  /*  struct  List *user = NULL; */
  
  while (1) {
    if (msgrcv(server_queue, &message, messageMaxSize, 0, 0) == -1) {
      perror("Error, msgrcv\n");
      msgctl(server_queue, IPC_RMID, 0);
    }
    switch (message.type) {
      case 1:
        /*  New user connected */
        /*  AddLeaf(message.text, usernames); */
        usleep(1);
        SendMessage(&message);
        break;
      case 2:
        /*  User disconected */
        /*  RemoveLeafByName(message.text, usernames); */
        SendMessage(&message);
        /*  TODO: close fork() and send notification */
        break;
      case 3:
        /*  Send message to all */
        /*  TODO: ^ */
        SendMessage(&message);
        break;
    }

    printf("%s\n", message.text);
  }
}

int main(void)
{
  char input, white_space;
  int status;

  CreateQueues();
  pid_t receive_id = fork();
  if (receive_id == 0) {
    StartReceiving();
    exit(0);
  }

  if (fork() == 0) {
    while (1) {
      scanf("%c", &input);
      scanf("%c", &white_space);
      if (input =='q') {
        break;
      }
      close(stdout);
    }
    kill(receive_id, SIGKILL);
    exit(0);
  } else {
    close(stdout);
  }
  for (int i = 0; i < 2; ++i) {
    wait(&status);
  }

  RemoveQueues();
  return 0;  
}

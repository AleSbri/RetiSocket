#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080

void *saluta(void *arg){
  char * msg="sono la funzione saluta";
  int sd = *(int *) arg;
  write(sd,msg,strlen(msg));
  close(sd);
  free(arg);

}

int main(int argc, char const *argv[]) {
  int thread_fd, server_fd , new_socket ;
  struct sockaddr_in address,client_addr;
//  char *hello = "ciao sono il server multi";

  socklen_t client_len;
  pthread_t tid;

  	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
    perror("errore socket");
    exit(0);
  }

  address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

  if(bind(server_fd,(struct sockaddr *)&address,sizeof(address))<0){
    perror("errore nel binding");
    exit(1);
  }

  if(listen(server_fd,3)<0){
    perror("errore nel listening");
    exit(1);
  }

  while(1){
    client_len = sizeof(client_addr);
    if (new_socket=accept(server_fd,(struct sockaddr *)&client_addr,client_len)<0) {
      perror("accept errore");
      exit(1);
    }

    thread_fd = (int *)malloc(sizeof(int));

    thread_fd=new_socket;

    pthread_create(&tid,NULL,saluta,(void *)thread_fd);

  }

}

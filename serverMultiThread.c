#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdint.h>

#define PORT 8080

void *saluta(void * arg){
	int32_t buffer;
	char *data=(char*)&buffer;
	int size=sizeof(buffer);
  int sd = *((int *) arg);
	int valread = read( sd , data , size);
	int buffer1 = ntohl(buffer);
	             printf("%d\n",data);
	buffer1 = buffer1 +25;
	int32_t converted_number = htonl(buffer1);
	char *data1=(char*)&converted_number;
	int size1=sizeof(converted_number);
  write(sd,data1,size1);
	
	close(sd);
	//free(arg);

	//pthread_exit(NULL);

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
    printf("sto aspettando il cliente\n");
    client_len = sizeof(address);
    if ((new_socket=accept(server_fd,(struct sockaddr *)&address,&client_len))<0) {
      perror("accept errore");
      exit(1);
    }

    pthread_create(&tid,NULL,saluta,&new_socket);

  }

}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define on_error(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); exit(1); }


void getipAddr(char ipbuf[], int fd)
{

	struct sockaddr_storage addr;
	socklen_t len = sizeof(addr);


	printf("getpeername = %d\n", getpeername(fd, (struct sockaddr*)&addr, &len));

	struct sockaddr_in *in = (struct sockaddr_in *)&addr;
 
	inet_ntop(AF_INET, &in->sin_addr, ipbuf, 200);
	
	fprintf(stdout, "clientip = %s\n", ipbuf);
}


int main (int argc, char *argv[]) {
  if (argc < 2) on_error("Usage: %s [port]\n", argv[0]);

  int port = atoi(argv[1]);

  int server_fd, client_fd, err;
  struct sockaddr_in server, client;
  char buf[BUFFER_SIZE];

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) on_error("Could not create socket\n");

  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  int opt_val = 1;
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

  err = bind(server_fd, (struct sockaddr *) &server, sizeof(server));
  if (err < 0) on_error("Could not bind socket\n");

  err = listen(server_fd, 128);
  if (err < 0) on_error("Could not listen on socket\n");

  printf("Server is listening on %d\n", port);

  while (1) {
    socklen_t client_len = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr *) &client, &client_len);
    char addrs[256]={0};
    getipAddr(addrs, client_fd);
    if (client_fd < 0) on_error("Could not establish new connection\n");

    while (1) {
      memset(buf, 0, sizeof(buf));
      int read = recv(client_fd, buf, BUFFER_SIZE, 0);

      if (!read) break; // done reading
      if (read < 0) on_error("Client read failed\n");
      fprintf(stdout, "buf=%s\n", buf);
      err = send(client_fd, "recv:", 5, 0);
      err = send(client_fd, buf, read, 0);
      err = send(client_fd, "\r\n", 2, 0);
      
      if (err < 0) on_error("Client write failed\n");
    }
  }

  return 0;
}

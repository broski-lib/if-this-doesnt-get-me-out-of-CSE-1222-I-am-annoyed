#include "http.h"
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // Parse Args
  std::string addr_port = static_cast<std::string>(http::DEFAULT_PORT);
  for (int i = 1; i < argc; i++) {

    std::string argument = argv[i];
    if (argument == "-h") {
      std::cout << "Usage: " << argv[0] << " [-p port]\n";
      return EXIT_SUCCESS;
    }
    if (argument == "-p") {
      if (i + 1 < argc) {
        addr_port = argv[i + 1];
        i++;
      } else {
        std::cout << "Argument '-p' called, but no port specified\n";
        return EXIT_FAILURE;
      }
    }
  }

  int socketfd = http::listen_tcp("", addr_port);
  if (socketfd == -1) {
    return EXIT_FAILURE;
  }

  socklen_t sin_size;
  struct sockaddr_storage their_addr; // connector's address info
  int new_fd;
  char s[INET6_ADDRSTRLEN];
  while (1) { // main accept() loop
    sin_size = sizeof their_addr;
    new_fd = accept(socketfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
      perror("accept");
      continue;
    }

    inet_ntop(
        their_addr.ss_family,
        http::get_in_addr((struct sockaddr *)&their_addr),
        s,
        sizeof s);
    printf("server: got connection from %s\n", s);

    if (!fork()) {     // this is the child process
      close(socketfd); // child doesn't need the listener
      if (send(
              new_fd,
              "HTTP/1.1 200 OK\r\nConnection: Close\r\n\r\nHello, world!",
              13,
              0) == -1)
        perror("send");
      close(new_fd);
      exit(0);
    }
    close(new_fd); // parent doesn't need this
  }
}

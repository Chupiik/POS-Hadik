#ifndef CLIENT_H
#define CLIENT_H

struct ClientInfo {
	int riadky;
	int stlpce;
	int fd;
	int* gameOver;
};

void* handle_input(void* arg);
void* handle_output(void* arg);
int main_client(int port);

#endif

#ifndef SERVER_H
#define SERVER_H

int main_server(int riadky, int stlpce, int pocet_jedla);
void* client_thread(void* arg);

#endif // SERVER_H

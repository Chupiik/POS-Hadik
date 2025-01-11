#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

void start_client_process(int port) {
    printf("Connecting to the server on port %d...\n", port);
    main_client(port);
}

int main() {
    printf("Starting the Snake Game client...\n");
	printf("Enter the server port number to connect to: ");
	int port;
	scanf("%d", &port);

	start_client_process(port);
    return 0;
}

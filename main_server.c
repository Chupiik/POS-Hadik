#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "server.h"

void start_server_process(int riadky, int stlpce, int pocet_jedla, int typ, int port) {
    printf("Starting server process on port %d...\n", port);
    main_server(riadky, stlpce, pocet_jedla, typ, port);
}

int main() {
    printf("Starting the Snake Game server...\n");

	printf("Enter the number of rows: ");
	int riadky;
	scanf("%d", &riadky);

	printf("Enter the number of columns: ");
	int stlpce;
	scanf("%d", &stlpce);

	if (riadky < 10 || stlpce < 10) {
		printf("Rows and columns must be at least 10.\n");
		exit(EXIT_FAILURE);
	}

	printf("Enter the number of food: ");
	int jedlo;
	scanf("%d", &jedlo);

	printf("Choose the type of game level: \n");
	printf("1 - No walls \n");
	printf("2 - Randomly generated walls \n");
	int typ_plochy;
	scanf("%d", &typ_plochy);

	printf("Enter the server port number: ");
	int port;
	scanf("%d", &port);

	start_server_process(riadky, stlpce, jedlo, typ_plochy, port);

    return 0;
}

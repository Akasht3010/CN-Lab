#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int s = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in sadd;
	sadd.sin_family = AF_INET;
	sadd.sin_addr.s_addr = htonl(INADDR_ANY);
	sadd.sin_port = htons(1999);

	socklen_t slen = sizeof(sadd);

	bind(s, (struct sockaddr*) &sadd, slen);

	printf("Server connected!\n");

	listen(s, 1);

	struct sockaddr_in cadd;

	socklen_t clen = sizeof(cadd);

	int a = accept(s, (struct sockaddr*) &cadd, &clen);

	printf("Client connected!\n");

	while (1)
	{
		char b1[1024];
		recv(a, b1, sizeof(b1), 0);

		FILE* f = fopen(b1, "r");

		char b2[1024];
		fread(b2, sizeof(b2), 1, f);

		fclose(f);

		send(a, b2, sizeof(b2), 0);

		printf("File sent!\n");
	}

	close(s);
}
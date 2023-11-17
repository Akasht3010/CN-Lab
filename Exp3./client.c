#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int s = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in sadd;
	sadd.sin_family = AF_INET;
	sadd.sin_addr.s_addr = inet_addr("127.0.0.1");
	sadd.sin_port = htons(1999);

	socklen_t slen = sizeof(sadd);

	connect(s, (struct sockaddr*) &sadd, slen);

	while (1)
	{
		printf("Enter a message: ");

		char b[1024];
		fgets(b, sizeof(b), stdin);

		send(s, b, sizeof(b), 0);

		printf("Message sent!\n");
	}

	close(s);
}

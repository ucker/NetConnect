/*
	Author: netsimpler@163.com
	Date: 2017-4-22
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "get_information.h"
#include "convert_qrcode.h"
#include "get_ssl_svg.h"
using namespace std;
int main() {
	int sockfd, newfd;
	char getChar[4096];
	struct sockaddr_in ina;
	struct sockaddr_in outa;
	ina.sin_family = AF_INET;
	ina.sin_port = htons(8888);
	ina.sin_addr.s_addr = INADDR_ANY;
	memset(ina.sin_zero, 0, 8);
	socklen_t sin_size;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		//printf("sock error\n");
		perror("");
		exit(1);
	}
  printf("my ip is:%s\n", inet_ntoa(ina.sin_addr));
	if (bind(sockfd, (struct sockaddr*)&ina, sizeof(struct sockaddr)) == -1) {
		//printf("bind error\n");
		perror("");
		exit(1);
	}
	if (listen(sockfd, 10) == -1) {
		//printf("listen error\n");
		perror("");
		exit(1);
	}
	while (1) {
		sin_size = sizeof(struct sockaddr_in);
		if ((newfd = accept(sockfd, (struct sockaddr*)&outa, &sin_size)) == -1) {
			printf("accept error\n");
			continue;
		}
		printf("Connect from: %s\n", inet_ntoa(outa.sin_addr));
		if (recv(newfd, getChar, 4096, 0) == -1) {
		    //printf("recv error\n");
			perror("");
			exit(1);
		}
		printf("receive string: ");
		for (int ii = 0; getChar[ii] != '\0'; ii++) printf("%c", getChar[ii]);
    string svg_string;
    get_ssl_svg(svg_string);
		if (send(newfd, svg_string.c_str(), svg_string.size(), 0) == -1) {
			//printf("send error\n");
			perror("");
			exit(1);
		}
	}
	return 0;
}

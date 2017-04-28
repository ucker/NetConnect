//GET
//return two ip address
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "get_information.h"
using namespace std;


int get_information(string& out_ip, string& in_ip)
{
    int num;

    int socket_get_information;

    struct sockaddr_in serv_get_information;
    //struct hostent *nlp_host_of_f_young;
    //change to string
    const char* sndBuf_get_information = "GET / HTTP/1.1\r\nUser-Agent: RCloudViewer-Android/3.2.0\r\nHost: test.f-young.cn\r\nAccept-Encoding: gzip\r\n\r\n";
    char rcvBuf_get_information[1024];
    //char buffer[1024];
    //nlp_host_of_f_young = gethostbyname("test.f-young.cn");
    if ((socket_get_information = socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        perror("");
        exit(1);
    }

    memset(&serv_get_information,0,sizeof(serv_get_information));
    serv_get_information.sin_family = AF_INET;
    serv_get_information.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_get_information.sin_addr.s_addr=inet_addr("202.111.54.213");//((struct in_addr *)(nlp_host_of_f_young->h_addr))->s_addr;
    serv_get_information.sin_port=htons(80);

    if ((connect(socket_get_information, (struct sockaddr *)&serv_get_information, sizeof(serv_get_information)))<0)
    {
        //perror("connet error!");
        perror("");
        exit(1);
    }

    if ((num = send(socket_get_information,sndBuf_get_information,1024, 0))<0)
   {
        perror("");
        exit(1);
    }

    //puts("send success!\n");

    //do{

        if ((num = recv(socket_get_information, rcvBuf_get_information, 1024, 0))<0)
        {
            perror("");
            system("pause");
            exit(1);
        }
        /*
        else if (num>0)
        {
            rcvBuf_get_information.append(buffer.cbegin(), buffer.cend());
        }
        */
    //} while (num>0);


    close(socket_get_information);
    //cout<<rcvBuf_get_information<<endl;
    //need process ip
    in_ip = "";
    out_ip = "";
    for (int i = 0; i != rcvBuf_get_information[i] != '\0' & i < 1024; i++)
    {
      if (rcvBuf_get_information[i] == 'm')
      {
        if (rcvBuf_get_information[i + 1] == 's' & rcvBuf_get_information[i + 2] == 'c' & rcvBuf_get_information[i + 3] == 'g' & rcvBuf_get_information[i + 4] == 'i' & rcvBuf_get_information[i + 5] == 'p' & rcvBuf_get_information[i + 6] == '=')
        {
            i += 6;
            while (rcvBuf_get_information[++i] != '&') out_ip += rcvBuf_get_information[i];
        }
      }
      else if (rcvBuf_get_information[i] == 'w')
      {
        if (rcvBuf_get_information[i + 1] == 'l' & rcvBuf_get_information[i + 2] == 'a' & rcvBuf_get_information[i + 3] == 'n' & rcvBuf_get_information[i + 4] == 'u' & rcvBuf_get_information[i + 5] == 's' & rcvBuf_get_information[i + 6] == 'e' )
        if (rcvBuf_get_information[i + 7] == 'r' & rcvBuf_get_information[i + 8] == 'i' & rcvBuf_get_information[i + 9] == 'p' & rcvBuf_get_information[i + 10] == '=')
        {
            i += 10;
            while (rcvBuf_get_information[++i] != '&') in_ip += rcvBuf_get_information[i];
            break;
        }
      }
    }
    //cout << in_ip<<' '<<out_ip<<endl;
    return 0;

}

#include <cstdio>
#include <vector>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "get_url.h"
#include "get_information.h"
using namespace std;

SSL *ssl;
int sock;

int RecvPacket(string& qr_information)
{
    int len=100;
    int err;
    vector<char> buf(1000);
      //printf("\n");
      //printf("size = %d\n", sizeof(buf));
      len=SSL_read(ssl, buf.data(), 1000);
      qr_information.append(buf.cbegin(), buf.cend());
      len=SSL_read(ssl, buf.data(), 1000);
      qr_information.append(buf.cbegin(), buf.cend());
    //cout<<ss.str()<<endl;
      err = SSL_get_error(ssl, len);
      if (err == SSL_ERROR_WANT_READ)
          return 0;
      if (err == SSL_ERROR_WANT_WRITE)
          return 0;
      if (err == SSL_ERROR_ZERO_RETURN || err == SSL_ERROR_SYSCALL || err == SSL_ERROR_SSL)
          return -1;
}

int SendPacket(const char *buf)
{
    int len = SSL_write(ssl, buf, strlen(buf));
    if (len < 0) {
        int err = SSL_get_error(ssl, len);
        switch (err) {
        case SSL_ERROR_WANT_WRITE:
            return 0;
        case SSL_ERROR_WANT_READ:
            return 0;
        case SSL_ERROR_ZERO_RETURN:
        case SSL_ERROR_SYSCALL:
        case SSL_ERROR_SSL:
        default:
            return -1;
        }
    }
}


void log_ssl()
{
    int err;
    while (err = ERR_get_error()) {
        char *str = ERR_error_string(err, 0);
        if (!str)
            return;
        //printf(str);
        //printf("\n");
        //fflush(stdout);
    }
}


int main()
{
  cout <<   "Status: 200 OK\n"
       << "Content-Type: text/html\n"
       << "Cache-Control: no-cache\n"
       << "Expires: 0\n\n";    
  string in_ip, out_ip, qr_string;
  get_information(out_ip, in_ip);
  //cout<<"out ip is "<<out_ip<<endl;
  //cout<<"in ip is "<<in_ip<<endl;
    int s;
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (!s) {
        //printf("Error creating socket.\n");
        return -1;
    }
    //cout<<"fuck\n";
    struct sockaddr_in sa;
    //struct hostent *nlp_host;
    //nlp_host = gethostbyname("wifi.loocha.cn");
    memset (&sa, 0, sizeof(sa));
    sa.sin_family      = AF_INET;
    sa.sin_addr.s_addr = inet_addr("180.96.7.201");//((struct in_addr *)(nlp_host->h_addr))->s_addr; // address of google.ru
    sa.sin_port        = htons (443);
    socklen_t socklen = sizeof(sa);
    if (connect(s, (struct sockaddr *)&sa, socklen)) {
        //printf("Error connecting to server.\n");
        return -1;
    }
    SSL_library_init();
    SSLeay_add_ssl_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD *meth = TLSv1_2_client_method();
    SSL_CTX *ctx = SSL_CTX_new (meth);
    ssl = SSL_new (ctx);
    if (!ssl) {
        //printf("Error creating SSL.\n");
        log_ssl();
        return -1;
    }
    sock = SSL_get_fd(ssl);
    SSL_set_fd(ssl, s);
    int err = SSL_connect(ssl);
    if (err <= 0) {
        //printf("Error creating SSL connection.  err=%x\n", err);
        log_ssl();
        fflush(stdout);
        return -1;
    }
    //printf ("SSL connection using %s\n", SSL_get_cipher (ssl));

    //char *request = "GET / HTTP/1.1\r\nHost: www.zhihu.com\r\n\r\n";
    string request = "GET /0/wifi/qrcode?1=Android_college_3.2.0&did=862973039766980_89860117834008843883_9cbe255a69e71f49_460015352104293_&vv=3002000&server_did=3abd9ea4-e34f-4c7e-9e9f-25e0c5a833e3&sv=6.0.1_23&mm=PC&imsi=460015352104293&rl=1280*720&pubc=0&brasip=";

    request += out_ip;
    request += "&ulanip=";
    request += in_ip;
    request += "&wlanip=";
    request += in_ip;
    request += "&fr=265 HTTP/1.1\r\nAccept-Language: zh-CN,zh;q=0.8,en;q=0.6\r\nHost: wifi.loocha.cn\r\nConnection: Keep-Alive\r\nAccept-Encoding: text/html\r\n\r\n";
    SendPacket(request.c_str());
    string qr_information;
    RecvPacket(qr_information);
    //cout<<qr_information<<endl;
    qr_string = get_url(qr_information);
    //qr_string = "HIWF://5804542db9ea75af7d01ecd107";

  cout << "<!DOCTYPE html>"
       << "<html>"
       << "<head>"
       << "<title>qr code</title>"
       << "<script type=\"text/javascript\" src=\"/luci-static/netconnect/jquery.min.js\"></script><script type=\"text/javascript\" src=\"/luci-static/netconnect/qrcode.js\"></script>"
       << "</head>"
       << "<body>"
       << "<p>your ip is "
       << in_ip <<' '<<out_ip
       << "</p>";
       if (qr_string.length() == 39)
       cout << "<div id=\"qrcode\" style=\"width:100px; height:100px; margin-top:15px;\"></div>"
       << "<script type=\"text/javascript\"> var qrcode = new QRCode(document.getElementById(\"qrcode\"), { \
text: \""
       << qr_string
       << "\","
       << "width: 128,"
       << "height: 128,"
       << "colorDark : \"#000000\","
       << "colorLight : \"#ffffff\","
       << "correctLevel : QRCode.CorrectLevel.H});</script>";
       else cout << "<p>You have connected to the internet</p>"
       << "</body></html>";
    return 0;
}

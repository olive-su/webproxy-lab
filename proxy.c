#include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

void doit(int fd);
void parse_uri(char *uri, char *ip, char *port, char *path);
void connect_origin_server(int fd, char *buf, char *host, char *port, char *path);
void *thread(void *vargp);

int main(int argc, char **argv) 
{
    int listenfd, *connfd; // 프록시 서버 식별자, 원본 서버 식별자
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
    }

    listenfd = Open_listenfd(argv[1]); // 프록시 소켓 오픈
    while (1) {
        clientlen = sizeof(clientaddr);
        connfd = Malloc(sizeof(int));
        *connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); // (to client) 원본 서버로의 연결을 요청한다.
        Pthread_create(&tid, NULL, thread, connfd); // 쓰레드 생성
        /* 
            싱글 스레드 방식(스레드 사용 x)

            Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0); // (to client) 원본 서버 연결 정보 받음
            printf("Accepted connection from (%s, %s)\n", hostname, port);
            doit(connfd); // 트랜잭션 수행
            Close(connfd); // 연결 종료
        */
    }
}

/**
 * @brief 피어 쓰레드를 위한 쓰레드 루틴
 * 
 * @param vargp 쓰레드에 대한 포인터
 * @return void* 
 */
void *thread(void *vargp) 
{
    int connfd = *((int *)vargp);
    Pthread_detach(pthread_self()); // 자신의 쓰레드를 분리한다.
    Free(vargp); // 메인 쓰레드가 할당한 메모리를 해제한다.
    doit(connfd); // 다음 연결에 대한 트랜잭션을 수행한다.
    Close(connfd);
    return NULL;
}

/**
 * @brief http 트랜잭션을 처리한다.
 * 
 * @param int fd 프록시 서버 식별자
 * @return void
 */
void doit(int fd) 
{
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char host[MAXLINE], port[MAXLINE], path[MAXLINE];
    rio_t rio;

    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    if (!Rio_readlineb(&rio, buf, MAXLINE)) return;  // request line을 읽는다.
    printf("%s", buf); // Check request line
    
    /* 
        telnet 입력 예시
        Ex. GET http://localhost:5000/home.html HTTP/1.1 
    */
    sscanf(buf, "%s %s %s", method, uri, version); //method, uri, version 정보를 입력받는다.
    
    if (strcasecmp(method, "GET")) { // request method 종류가 GET이 아닐 경우 예외 처리
        printf("501 Not Implemented, Proxy does not implement this method");
        return;
    }

    /* Parse URI from GET request */
    parse_uri(uri, host, port, path); // uri를 host, port, path로 분리한다.
    connect_origin_server(fd, buf, host, port, path); // 원본 서버와의 연결을 수행한다.
}

/**
 * @brief 요청으로 들어온 uri를 host, port, path로 분리한다.
 * 
 * @param char* uri request uri
 * @param char* host parsed host from uri
 * @param char* port parsed port from uri 
 * @param char* path parsed path from uri
 * @return void 
 */
void parse_uri(char *uri, char *host, char *port, char *path)
{
    char *extracturi;
    char *p;

    /* 과정 1. "http://host:port/path" -> "host:port/path" */
    if(strstr(uri, "http://") != NULL) { // "http://" 가 uri에 존재하는 경우 "http://"를 지운다.
        extracturi = uri + 7;
        printf("extracturi : %s\n", extracturi); // uri 정제 과정 1
    }

    /* 과정 2. "host:port/path" -> "host:port" + "path" */
    p = strstr(extracturi, "/");
    strcpy(path, p);
    strncpy(host, extracturi, p - extracturi);
    *(host + (p - extracturi)) = '\0'; // strncpy_s 와 같은 기능
    // ↳ strncpy의 경우 Null 문자를 자동으로 채워주지 않아 문자열의 종료 시점을 알 수 없다.

    /* 과정 3. "host:port" -> "host" + "port" */
    p = strstr(host, ":") + 1;
    strcpy(port, p);
    strncpy(host, extracturi, p - host - 1);
    *(host + (p - host - 1)) = '\0';

    printf("ip : %s / port : %s / path : %s \n", host, port, path); // Check parsed data
}

/**
 * @brief 프록시 서버와 원본 서버를 연결한다.
 * 
 * @param int listenfd 프록시 서버 식별자
 * @param char* buf 원본 서버로 출력을 보낼 임시 버퍼
 * @param char* host 원본 서버 호스트
 * @param char* port 원본 서버 포트
 * @param char* path 원본 서버 파일 경로 및 파라미터
 * @return void
 */
void connect_origin_server(int listenfd, char *buf, char *host, char *port, char *path)
{
    int fd;
    rio_t rio;
    size_t n;

    fd = Open_clientfd(host, port); // 원본 서버의 식별자를 오픈한다.
    Rio_readinitb(&rio, fd); // 원본 서버의 읽기 버퍼 초기화

    /* request header 생성 */
    sprintf(buf, "GET %s HTTP/1.0\r\n", path);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Host: %s\r\n", host);
    Rio_writen(fd, buf, strlen(buf)); 
    sprintf(buf, "%s", user_agent_hdr); 
    Rio_writen(fd, buf, strlen(buf)); 
    sprintf(buf, "Connection: close\r\n");
    Rio_writen(fd, buf, strlen(buf)); 
    sprintf(buf, "Proxy-Connection: close\r\n");
    Rio_writen(fd, buf, strlen(buf)); 
    sprintf(buf, "\r\n");
    Rio_writen(fd, buf, strlen(buf));
    
    while((n = Rio_readlineb(&rio, buf, MAXLINE))!=0) // Return response header, response body
    {
        printf("proxy received %d bytes,then send\n",n);
        Rio_writen(listenfd,buf,n);
    }
    Close(fd); 
}

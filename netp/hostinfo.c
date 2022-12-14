/* $begin hostinfo */
#include "csapp.h"

int main(int argc, char **argv)
{
    struct addrinfo *p, *listp, hints;
    char buf[MAXLINE];
    int rc, flags;

    if (argc != 2 && argc != 3) { // (argv[1] : 호스트 네임, argv[2] : 서비스 네임)
	fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
	exit(0);
    }

    /* addrinfo 연결 리스트를 얻는다. */
    memset(&hints, 0, sizeof(struct addrinfo)); // hints 구조체 초기화
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP 소켓을 받는다는 사실 명시

    rc = getaddrinfo(argv[1], argv[2], &hints, &listp); // 도메인 네임 리턴
    if (rc != 0) { // 오류 발생
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(rc));
        exit(1);
    }

    /* addrinfo 연결 리스트를 순회한다. */
    flags = NI_NUMERICHOST; // 도메인 네임 대신에 10진수 숫자로 포팅된 형태로 리턴받는다.
    for (p = listp; p; p = p->ai_next) {
        getnameinfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf);
    }

    Freeaddrinfo(listp);

    exit(0);
}

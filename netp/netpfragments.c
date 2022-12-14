#include "csapp.h"

void fragments()
{
    int clientfd;

    /* $begin socketcall */
    /**
     * @brief create a socket descriptor
     * @details AF_INET : 32비트 IP주소를 사용하고 있음을 나타냄 @n SOCK_STERAM : 소켓이 엔드포인트임을 나타냄(TCP 프로토콜 방식)
     */
    clientfd = Socket(AF_INET, SOCK_STREAM, 0);
    /* $end socketcall */

    clientfd = clientfd; /* keep gcc happy */

    /* $begin inaddr */
    /* 32비트 IP 주소를 저장할 구조체 */
    struct in_addr {
        uint32_t  s_addr; /* 네트워크 바이트 주소 체계(빅엔디안) */
    };
    /* $end inaddr */

    /* $begin addrinfo */
    /**
     * @brief getaddrinfo가 리턴하는 소켓 주소들의 구조체 
     */
    struct addrinfo {
        int              ai_flags;     /* 추가적인 옵션 정의, Hints argument flags */
        int              ai_family;    /* 주소 체계(AF_INET, AF_INET6, AF_UNSPEC) First arg to socket function */
        int              ai_socktype;  /* socket type(SOCK_SREAM, SOCK_DGRAM), Second arg to socket function */
        int              ai_protocol;  /* 프로토콜을 식별하기 위한 매개변수 값(IPPROTO_XXX), Third arg to socket function  */
        char            *ai_canonname; /* 별칭 호스트 네임 -> 내부적으로 다시 질의, CNAME(Canonical hostname) */
        size_t           ai_addrlen;   /* ai_addr의 길이, Size of ai_addr struct */
        struct sockaddr *ai_addr;      /* socket 주소를 나타내는 구조체 포인터, Ptr to socket address structure */
        struct addrinfo *ai_next;      /* 다음 데이터의 포인터(linked list 이므로) Ptr to next item in linked list */
    };
    /* $end addrinfo */

    /* $begin sockaddr */
    /**
     * @brief IP socket address structure
     */
    struct sockaddr_in  {
        uint16_t        sin_family;  /* 주소 체계, Protocol family (always AF_INET) */
        uint16_t        sin_port;    /* 16 비트 포트 번호, Port number in network byte order */
        struct in_addr  sin_addr;    /* 32비트 IP 주소, IP address in network byte order */
        unsigned char   sin_zero[8]; /* 전체 크기를 16비트로 맞추기위한 패딩, Pad to sizeof(struct sockaddr) */
    };

    /**
     * @brief Generic socket address structure (for connect, bind, and accept)
     */
    struct sockaddr {
        uint16_t  sa_family;    /* 주소 체계, Protocol family */
        char      sa_data[14];  /* 해당 주소 체계에서 사용하는 주소 정보, Address data  */
    };	
    /* $end sockaddr */
}

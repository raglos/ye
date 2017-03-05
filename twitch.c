#define _GNU_SOURCE
/*
 * wrvc@github.com 2016-11-27
 * twitch.c
 * view twitch chat in your terminal.
 * Usage ./twitch <twitch_channel>
 * compiled as $ gcc -o twitch twitch.c -Wall -Wpedantic -ansi -march=native -O1 -g
 * valgrind gave no errors which means this is a professional program tbh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <ctype.h>
#include <time.h>

/* prints error and exits */
#define kys(c) do {               \
    fprintf(stderr, "%s\n", c);   \
    exit(1);                      \
} while (0)

/* Necessary for anonymously connecting to twitch chat */
#define TWITCH_USERNAME "NICK justinfan%d\r\n"
#define TWITCH_CHANNEL  "JOIN #%s\r\n"
#define TWITCH_SERVER   "irc.chat.twitch.tv"
#define TWITCH_PORT     6667

#define MYBUFSIZ 1024 * 2

/* twitch sends a ping every few minutes */
static const char *ping = "PING :tmi.twitch.tv\r\n";
/* twitch needs a pong response otherwise connection is killed */
static const char *pong = "PONG :tim.twitch.tv\r\n";
/* saves strlen() calls */
static const unsigned int pong_len = 21;

char *channel = NULL;
int connected = 0;

void handle_line(int, char*);

int main(int argc, char **argv) {

    int err = 0;
    int sock;
    unsigned int i = 0;
    char buf[ MYBUFSIZ +1];

    struct sockaddr_in             serv;
    struct hostent         *host = NULL;
    struct in_addr   **addr_list = NULL;

    if (!(argc >= 2)) {
        kys("You must pass the channel name!");
    }
    
    channel = argv[1];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) kys("Error could not create socket");

    host = gethostbyname( TWITCH_SERVER );
    if (!host)    kys("Error gethostbyname()");

    addr_list = (struct in_addr **) host->h_addr_list;
    
    serv.sin_addr.s_addr = inet_addr(inet_ntoa(*addr_list[0]));
    serv.sin_family      = AF_INET;
    serv.sin_port        = htons( TWITCH_PORT );

    err = connect(sock, (struct sockaddr *)&serv, sizeof serv);
    if (err < 0)  kys("Connection failed");

    /* create username */
    srand(time(0));
    i = (rand() % 12345) * 100;
    snprintf(buf, MYBUFSIZ, TWITCH_USERNAME, i);

    /* send to twitch.tv */
    send(sock, buf, strlen(buf), 0);

    while(1) {
        char pbuf[ MYBUFSIZ +1];
        memset(pbuf, '\0', MYBUFSIZ);
        if (recv(sock, pbuf, MYBUFSIZ, 0) < 1) {
            fprintf(stderr, "recv() error\n");
            break;
        }
        handle_line(sock, pbuf);
    }
    
    close(sock);
    return 0;
}

void handle_line(int sock, char *line) {

    unsigned int len;
    char *name_start = NULL;
    char *temp       = NULL;
    int j = 0;
    int k = 0;

    if (line == NULL)  return;
    if (*line == '\0') return;

    len = strlen(line);
    if (!len) return;


    if (!strcmp(line, ping)) {
        send(sock, pong, pong_len, 0);
        printf("[<-] PONG\n");
        return;
    }

    if (!connected) {
        if (strstr(line, "376")) {
            char buf[MYBUFSIZ+1];
            connected = 1;
            snprintf(buf, MYBUFSIZ, TWITCH_CHANNEL, channel);
            send(sock, buf, strlen(buf), 0);
            return;
        }
        return;
    }

    /* get rid of \r\n */
    line[len-2] = '\0';

    name_start = (char*) (line+1);
    temp = name_start;

    /* which part of the string has the name */
    /* the ! is usually <20 chars in, TODO: improve */ 
    while(*(temp++) != '!') {
        if (j == len-2) return;
        ++j;
    }

    /* where the message substring begins in the string */
    /* # is usually near the end. TODO: improve */
    temp = name_start;
    while(*(temp++) != '#') {
        if (k == len-2) return;
        ++k;
    }

    /* 4 is for padding message */
    /* TODO: const int strlen(channel) */
    k += strlen(channel) + 4;

    /* prints out like "[channel] name: message" */
    printf("[%s] %.*s: %s\n", channel, j, name_start, (char *)(line+k));
}


/* the usual suspects */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* socket includes */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define DEFAULT_PORT 11111



int main(int argc, char** argv)
{
    int                sockfd;
    struct sockaddr_in servAddr;
    char               buff[256];
    size_t             len;
    int                ret;


    /* Check for proper calling convention */
    if (argc != 2) {
        printf("usage: %s <IPv4 address>\n", argv[0]);
        return 0;
    }

    /* Create a socket that uses an internet IPv4 address,
     * Sets the socket to be stream based (TCP),
     * 0 means choose the default protocol. */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "ERROR: failed to create the socket\n");
        ret = -1;
        goto end;
    }

    /* Initialize the server address struct with zeros */
    memset(&servAddr, 0, sizeof(servAddr));

    /* Fill in the server address */
    servAddr.sin_family = AF_INET;             /* using IPv4      */
    servAddr.sin_port   = htons(DEFAULT_PORT); /* on DEFAULT_PORT */

    /* Get the server IPv4 address from the command line call */
    if (inet_pton(AF_INET, argv[1], &servAddr.sin_addr) != 1) {
        fprintf(stderr, "ERROR: invalid address\n");
        ret = -1;
        goto end;
    }

    /* Connect to the server */
    if ((ret = connect(sockfd, (struct sockaddr*) &servAddr, sizeof(servAddr)))
         == -1) {
        fprintf(stderr, "ERROR: failed to connect\n");
        goto end;
    }

    /* Get a message for the server from stdin */
    printf("Message for server: ");

    while(1) {

        memset(buff, 0, sizeof(buff));
        printf("Client: ");
        if (fgets(buff, sizeof(buff), stdin) == NULL) {
            fprintf(stderr, "ERROR: failed to get message for server\n");
            ret = -1;
            goto socket_cleanup;
        }
        len = strnlen(buff, sizeof(buff));

        /* Send the message to the server */
        if (write(sockfd, buff, len) != len) {
            fprintf(stderr, "ERROR: failed to write\n");
            ret = -1;
            goto socket_cleanup;
        }

        /* Check for server shutdown command */
        if (strncmp(buff, "shutdown", 8) == 0) {
            printf("Shutdown command issued!\n");
            // shutdown = 1;
            goto socket_cleanup;
        }

        /* Read the server data into our buff array */
        memset(buff, 0, sizeof(buff));
        if (read(sockfd, buff, sizeof(buff)-1) == -1) {
            fprintf(stderr, "ERROR: failed to read\n");
            ret = -1;
            goto socket_cleanup;
        }

        /* Print to stdout any data the server sends */
        printf("Server: %s\n", buff);

    }

    /* Cleanup and return */
socket_cleanup:
    close(sockfd);          /* Close the connection to the server       */
end:
    return ret;               /* Return reporting a success               */
}
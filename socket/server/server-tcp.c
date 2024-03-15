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



int main()
{
    int                ret; 
    int                sockfd;
    int                connd;
    struct sockaddr_in servAddr;
    struct sockaddr_in clientAddr;
    socklen_t          size = sizeof(clientAddr);
    char               buff[256];
    size_t             len;
    int                shutdown = 0;
    const char*        reply = "I hear ya fa shizzle!\n";



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
    servAddr.sin_family      = AF_INET;             /* using IPv4      */
    servAddr.sin_port        = htons(DEFAULT_PORT); /* on DEFAULT_PORT */
    servAddr.sin_addr.s_addr = INADDR_ANY;          /* from anywhere   */



    /* Bind the server socket to our port */
    if (bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
        fprintf(stderr, "ERROR: failed to bind\n");
        ret = -1;
        goto servsocket_cleanup;
    }

    /* Listen for a new connection, allow 5 pending connections */
    if (listen(sockfd, 5) == -1) {
        fprintf(stderr, "ERROR: failed to listen\n");
        ret = -1; 
        goto servsocket_cleanup;
    }



    /* Continue to accept clients until shutdown is issued */
    while (!shutdown) {
        printf("Waiting for a connection...\n");

        /* Accept client connections */
        if ((connd = accept(sockfd, (struct sockaddr*)&clientAddr, &size))
            == -1) {
            fprintf(stderr, "ERROR: failed to accept the connection\n\n");
            ret = -1; 
            goto servsocket_cleanup;
        }

        printf("Client connected successfully\n");


        while(1) {
            /* Read the client data into our buff array */
            memset(buff, 0, sizeof(buff));
            if ((ret = read(connd, buff, sizeof(buff)-1)) == -1) {
                fprintf(stderr, "ERROR: failed to read\n");
                goto clientsocket_cleanup;
            }

            /* Print to stdout any data the client sends */
            printf("Client: %s\n", buff);

            /* Check for server shutdown command */
            if (strncmp(buff, "shutdown", 8) == 0) {
                printf("Shutdown command issued!\n");
                shutdown = 1;
                goto servsocket_cleanup;
            }



            /* Write our reply into buff */
            memset(buff, 0, sizeof(buff));
            printf("Server: ");
            if (fgets(buff, sizeof(buff), stdin) == NULL) {
                fprintf(stderr, "ERROR: failed to get message for server\n");
                ret = -1;
                goto servsocket_cleanup;
            }
            len = strnlen(buff, sizeof(buff));

            /* Reply back to the client */
            if ((ret = write(connd, buff, len)) != len) {
                fprintf(stderr, "ERROR: failed to write\n");
                goto clientsocket_cleanup;
            }

        }



        /* Cleanup after this connection */
        close(connd);           /* Close the connection to the client   */
    }

    printf("Shutdown complete\n");


    /* Cleanup and return */
clientsocket_cleanup:
    close(connd);           /* Close the connection to the client   */
servsocket_cleanup:
    close(sockfd);          /* Close the socket listening for clients     */
end:
    return ret;               /* Return reporting a success               */

    /* Cleanup and return */
    close(sockfd);          /* Close the socket listening for clients   */
    return 0;               /* Return reporting a success               */
}
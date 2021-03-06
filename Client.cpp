//
// Created by yael on 12/24/18.
//

#include <netinet/in.h>
#include <netdb.h>
#include "Client.h"

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include <iostream>

Client* Client::instance = nullptr;

Client* Client::getInstance() {
    if (instance == nullptr) {
        instance = new Client();
    }
    return instance;
}

void Client::setPort(int port) {
    this->port = port;
}

void Client::setIp(string ipByName) {
    this->ipByName = ipByName;
}

void Client::openSocket() {
    struct sockaddr_in serv_addr;
    struct hostent *server;

/* Create a socket point */
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    server = gethostbyname(ipByName.c_str());

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(this->port);

/* Now connect to the server */
    if (connect(this->sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
}

void Client::writeData(string massege, double value) {
    massege = massege.substr(2, massege.length() - 3);
    string buffer = "set " + massege + " " + to_string(value) + "\r\n";
/* Send message to the server */
    if (send(this->sockfd, buffer.c_str(), strlen(buffer.c_str()), 0) < 0) {
        perror("send failed: ");
        exit(1);
    }
}

void Client::destroyClient() {
    if (instance != nullptr) {
        delete instance;
    }
    instance = nullptr;
}

void Client::closeSocket() {
    close(this->sockfd);
}

Client::~Client() {

}
//
// Created by yael on 12/20/18.
//

#include "Server.h"
#include <iostream>
#include "OpenServerCommand.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sstream>

using namespace std;

Server* Server::instance = nullptr;

Server *Server::getInstance() {
    if (instance == nullptr) {
        instance = new Server();
    }
    return instance;
}
void Server::destroyServer() {
    instance->closeSocket();
    if (instance != nullptr) {
        delete instance;
    }
    instance = nullptr;
}

void Server::setPort(int p) {
    this->port = p;
}

void Server::openSock() {
    int clilen;
    struct sockaddr_in serv_addr, cli_addr;

    /* First call to socket() function */
    this->serverSockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->serverSockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    //portno = 5001;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->port);

    cout << "bind" << endl;
    /* Now bind the host address using bind() call.*/
    if (bind(this->serverSockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    cout << "finish bind" << endl;

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(this->serverSockfd, 5);
    clilen = sizeof(cli_addr);

    cout << "accept" << endl;
    /* Accept actual connection from the client */
    cliSockfd = accept(this->serverSockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

    if (cliSockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    cout << "finish accept" << endl;
}

void Server::readLineBeforeStart(int cliSock) {
    char buf[BUFFER_SIZE];
    int n;
    bzero(buf, (BUFFER_SIZE - 1));
    n = read(cliSock, buf, (BUFFER_SIZE - 1));
    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
}

void Server::readData(int cliSock) {
    char buffer[BUFFER_SIZE], c;
    string msg;
    int n;
    while (true) {
        msg = "";
        // If connection is established then start communicating *//*
        bzero(buffer, (BUFFER_SIZE));
        n = read(cliSock, &c, 1);
        // n = read(cliSock, buffer, (BUFFER_SIZE - 1));
        while (c != '\n') {
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
            msg += c;
            n = read(cliSock, &c, 1);
        }

        /*if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }*/
        //updateTable(buffer);
        updateTable(msg);
        //printf("Here is the message: %s\n", buffer);
    }
}

int Server::getCliSock() {
    return this->cliSockfd;
}

void Server::updateTable(string massege) {
    vector<double> valuesFromSim = split(massege, ',');
    for (auto const &value : SymbolsTable::getInstance()->getSymbolsMap()) {
        string var = value.first;
        string path = value.second->path;
        //if (var != path) {
        int i = indexInMap(path);
        if (i != -1) {
            value.second->value = valuesFromSim.at(i);
            /*cout << var << "=" << valuesFromSim.at(i) << endl;*/
        }
        //}
    }
    //cout << "afterloop" << endl;
}

int Server::indexInMap(string path) {
    vector<string> names = SymbolsTable::getInstance()->getPaths();
    for (int i = 0; (unsigned int)i < names.size(); i++) {
        if (path[0] == '\"') {
            path = path.substr(1, path.length() - 2);
        }
        if (names[i] == path) {
            return i;
        }
    }
    return -1;
}

vector<double> Server::split(string info, char divide) {
    stringstream s(info);
    string part;
    vector<double> splitLine;

    while (getline(s, part, divide)) {
        splitLine.push_back(stod(part));
    }
    return splitLine;
}


void Server::closeSocket() {
    close(this->cliSockfd);
    cout << "closed";
}
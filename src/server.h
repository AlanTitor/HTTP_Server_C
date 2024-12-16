#ifndef SERVER_H
#define SERVER_H

#include"../includes/includes.h"

void handle_client(SOCKET client_socket);
char *read_html_file(const char *filename);

int test_WSAStartup_error(WSADATA wsadata);
int test_socket_error(SOCKET server_socket);
int test_bind_error(SOCKET server_socket, struct sockaddr_in server_addr);
int test_listen_error(SOCKET server_socket);

char test_file_error(FILE *file);
char test_content_error(char *content, FILE *file);
char test_bytes_read_error(size_t bytes_read, LONG file_size, FILE *file, char *content);

void test_recive_error(int recive);
void test_html_content_error(char *html_content);
void test_http_response_error(char *http_response, SOCKET client_socket, char *html_content);

#endif
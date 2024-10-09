//final
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 100
void *handle_client(void *client_socket);
void handle_error(const char *msg);
void forward_message(const char *message, int sender_sock);
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
int client_sockets[MAX_CLIENTS] = {0};
int main() {
int server_fd, client_socket;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_size;
pthread_t thread_id;
server_fd = socket(AF_INET, SOCK_STREAM, 0);
if (server_fd < 0) {
handle_error("Socket creation failed");
}
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = INADDR_ANY;
server_addr.sin_port = htons(PORT);
if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
handle_error("Bind failed");
}
if (listen(server_fd, MAX_CLIENTS) < 0) {
handle_error("Listen failed");
}
printf("Server listening on port %d\n", PORT);
while (1) {
addr_size = sizeof(client_addr);
client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_size);
if (client_socket < 0) {
perror("Client accept failed");
continue;
}
pthread_mutex_lock(&clients_mutex);
for (int i = 0; i < MAX_CLIENTS; i++) {
if (client_sockets[i] == 0) {
client_sockets[i] = client_socket;
break;
}
}
pthread_mutex_unlock(&clients_mutex);
if (pthread_create(&thread_id, NULL, handle_client, (void *)&client_socket) != 0) {
perror("Failed to create thread");
}
pthread_detach(thread_id); 
}
close(server_fd);
return 0;
}
void *handle_client(void *client_socket) {
int sock = *(int *)client_socket;
char buffer[BUFFER_SIZE];
int bytes_received;
while ((bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
buffer[bytes_received] = '\0';  
printf("Received message: %s\n", buffer);
forward_message(buffer, sock);
}
if (bytes_received < 0) {
perror("Recv failed");
}
pthread_mutex_lock(&clients_mutex);
for (int i = 0; i < MAX_CLIENTS; i++) {
if (client_sockets[i] == sock) {
client_sockets[i] = 0;
break;
}
}
pthread_mutex_unlock(&clients_mutex);
close(sock);
return NULL;
}
void forward_message(const char *message, int sender_sock) {
pthread_mutex_lock(&clients_mutex);
for (int i = 0; i < MAX_CLIENTS; i++) {
if (client_sockets[i] != 0 && client_sockets[i] != sender_sock) {
send(client_sockets[i], message, strlen(message), 0);
}
}
pthread_mutex_unlock(&clients_mutex);
}
void handle_error(const char *msg) {
perror(msg);
exit(EXIT_FAILURE);
}
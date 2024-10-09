
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUFFER_SIZE 1024
#define SHIFT 3 
void encrypt_message(char *message, int shift);
void decrypt_message(char *message, int shift);
int main() {
int sockfd;
struct sockaddr_in serv_addr;
char buffer[BUFFER_SIZE];
char username[256];
char password[256];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
perror("Socket creation failed");
exit(EXIT_FAILURE);
}
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
perror("Invalid address/ Address not supported");
close(sockfd);
exit(EXIT_FAILURE);
}
if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
perror("Connection failed");
close(sockfd);
exit(EXIT_FAILURE);
}
printf("Enter username: ");
fgets(username, sizeof(username), stdin);
username[strcspn(username, "\n")] = '\0'; 
printf("Enter password: ");
fgets(password, sizeof(password), stdin);
password[strcspn(password, "\n")] = '\0';
snprintf(buffer, sizeof(buffer), "REGISTER %s %s", username, password);
encrypt_message(buffer, SHIFT);
send(sockfd, buffer, strlen(buffer), 0);
memset(buffer, 0, sizeof(buffer));
recv(sockfd, buffer, sizeof(buffer), 0);
decrypt_message(buffer, SHIFT);
printf("Server: %s\n", buffer);
printf("Re-enter username for authentication: ");
fgets(username, sizeof(username), stdin);
username[strcspn(username, "\n")] = '\0';
printf("Re-enter password for authentication: ");
fgets(password, sizeof(password), stdin);
password[strcspn(password, "\n")] = '\0';
snprintf(buffer, sizeof(buffer), "AUTH %s %s", username, password);
encrypt_message(buffer, SHIFT);
send(sockfd, buffer, strlen(buffer), 0);
memset(buffer, 0, sizeof(buffer));
recv(sockfd, buffer, sizeof(buffer), 0);
decrypt_message(buffer, SHIFT);
printf("Server: %s\n", buffer);
while (1) {
printf("Enter message to send: ");
fgets(buffer, sizeof(buffer), stdin);
buffer[strcspn(buffer, "\n")] = '\0'; 
encrypt_message(buffer, SHIFT);
send(sockfd, buffer, strlen(buffer), 0);
memset(buffer, 0, sizeof(buffer));
recv(sockfd, buffer, sizeof(buffer), 0);
decrypt_message(buffer, SHIFT);
printf("Server: %s\n", buffer);
}
close(sockfd);
return 0;
}
void encrypt_message(char *message, int shift) {
for (int i = 0; i < strlen(message); i++) {
message[i] = (message[i] + shift) % 256;
}
}
void decrypt_message(char *message, int shift) {
for (int i = 0; i < strlen(message); i++) {
message[i] = (message[i] - shift + 256) % 256;
}
}

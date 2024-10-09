# encrypted_chat_model
This was created using C language with SSH algorithm  
OVERVIEW:
SSH, or secure shell, is a secure protocol and the most common way of safely administering remote servers. SSH provides a mechanism for establishing a cryptographically secured connection between two parties, authenticating each side to the other, and passing commands and output back and forth.

How does SSH algorithm works?

Client-server model:
A client program on a user's computer requests a connection to a server, which is controlled by a program installed by a server administrator.

Public key cryptography:
The client and server negotiate parameters and encryption methods, then create an encrypted session key. The server sends an encrypted challenge request to the client, who decrypts it and responds with a response. 
 
SSH tunneling:
SSH uses port forwarding to move packets across a network using a protocol or path that they normally couldn't use. 
 
Encryption:
SSH uses a variety of encryption methods, including symmetrical and asymmetrical encryption, and hashing. 
 
SSH Key Pairs:
SSH Key Pairs are a set of asymmetric keys that authenticate a user without requiring a password. 

 
PRE-REQUISITES:
  
1) To run C in Ubuntu install-
   sudo apt update
   sudo apt upgrade
   sudo apt install gcc
   sudo apt install gedit 
   

2)Libraries-
 sudo apt-get install libssl-dev

 
How does SSH is used in the project?
Secure Communication Channels
SSH can secure the communication channel between the client and server by encrypting all data transmitted over the network. This is crucial for protecting the contents of chat messages from eavesdropping.
Client-Server Communication: Instead of implementing custom encryption for the chat messages, you can tunnel the chat application through an SSH connection. The SSH protocol handles the encryption, ensuring that all data exchanged between the client and server is secure.
Tunneling: local port forwarding
                    Dynamic port forwarding

Using SSH in your encrypted chat project enhances security by ensuring encrypted communication, secure authentication, and protected file transfers. While SSH itself provides encryption and security for the transport layer, you may still want to implement additional layers of encryption for the messages themselves to achieve end-to-end security.
GET STARTED:
To start chatting :-
1) Run the  gcc final.c -pthread 
2) Run the gcc fcl.c -pthread

FEATURES:
1.Correct authentication
2.Alphanumeric,float,special character can be easily send 
3.Emoji sharing
4.Google drive links can be shared and easily opened
5.Pdf can be shared via link



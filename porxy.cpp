#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

/*
Your proxy will need one socket for talking to the client, and another socket for
talking to the server. Make sure to keep track of which one is which!
*/

int main(int argc, char * argv[]) {


	// 2 Arguments
	// argv[1] --> Port Number
	// argv[2] --> # of mistakes
	if (argc != 3) {
		cout << "Please enter a port number followed by the amount (integer) of mistakes you'd like" << endl;
		return 0;
	}

	int port_num = 8001;
	int num_mistakes = atoi(argv[1]);

	//cout << "Your port number is " << port_num << endl;
	cout << "You want " << num_mistakes << " mistakes" << endl;


	// Address initialization
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(80);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	cout << "Address initialization completed"<< endl;


	//----------------------------------------------------
	//------------------ LISTENING SIDE ------------------
	//---------------------------------------------------- 

	int listen_socket;
	listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_socket == -1) {
		cout << "Listening socket has failed." << endl;
	} else {
		cout << "Creating listening socket ID: " << listen_socket << endl;
	}

	int listen_bind;
	listen_bind = bind(listen_socket, (struct sockaddr*) &server_address,
		sizeof(struct sockaddr_in));
	if (listen_bind == -1) {
		cout << "Listening bind has failed." << endl;
	} else {
		cout << "Listening socket now bound to server server address." << endl;
	}

	int listen_status;
	listen_status = listen(listen_socket, 5);
	cout << "broken here" << endl;
	if (listen_status == -1) {
		cout << "Listening has failed" << endl;
	} else {
		cout << "Now listening " << endl;
	}
	
	//----------------------------------------------------
	//-------------------- DATA SIDE ---------------------
	//---------------------------------------------------- 

	//----------------------------------------------------
	//------------------- SERVER SIDE --------------------
	//---------------------------------------------------- 
	/*
	// Socket creation 
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == -1) {
		cout ("Server socket has failed.");
	} else {
		cout ("Creating socket for server...");
	}

	// Server side binding
	// The function of bind is to associate the socket with its local address
	// In doing this, clients can use that address to connect to the server
	int server_bind;
	server_bind = bind(server_socket, (struct sockaddr*) &server_address, 
		sizeof(struct sockaddr_in));
	if (server_bind == -1) {
		cout ("Server bind() call failed");
	} else {
		cout ("Binding server to server address");
	}

	// Server side listening 
	int listen_status;
	listen_status = listen(server_socket, 5);
	if (listen_status == -1) {
		cout ("Server listen() call failed");
	} else {
		cout ("Server is now listening...");
	}

	*/
	//----------------------------------------------------
	//-------------------- CLIENT SIDE -------------------
	//----------------------------------------------------


	// Socket creation 
	//int client_socket;
	//client_socket = socket(AF_INET, SOCK_STREAM, 0);
	//if (client_socket == -1) {
	//	cout << "Client socket has failed" << endl;
	//} else {
	//	cout << "Creating socket for client..." << endl;
	//}

	// Client address intilization

	/*
	struct sockaddr_in client_address;
	memset(&client_address, 0, sizeof(client_address));
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(port_num);
	client_address.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// Sending connection request to server
	int connect_status;
	connect_status = connect(client_socket, (struct sockaddr*) &client_address,
		sizeof(struct sockaddr_in));
	if (connect_status == -1) {
		cout << "Client connect() failed." << endl;
	} else {
		cout << "Client has connected to server." << endl;
	}
	*/


	//----------------------------------------------------
	//-------------------- SERVER CONN -------------------
	//----------------------------------------------------

	// Listening for connection requests
	while(1) {

		// Data sockets takes the connection from the listening socket
		// Cite --> https://blog.stephencleary.com/2009/05/using-socket-as-server-listening-socket.html
		int data_socket;
		cout << "test" << endl;
		// Data socket may now be used for both READ and WRITE
		data_socket = accept(listen_socket, NULL, NULL);

		cout << "test2 " <<data_socket << endl;
		if (data_socket == -1) {
			cout << "Data socket failed to accept listening socket\n" << endl;
		} else {
			cout << "Data socket is now listening..." << endl;
		}


		char rcv_message[1024];
		char msg_in[1024];
		int rcv_status;

		rcv_status = recv(data_socket, msg_in, sizeof(msg_in), 0);
		if (rcv_status == -1) {
			cout << "rcv failed" << endl;
		}

		cout << rcv_status << endl;


		char snd_message[1024] = {"GET / HTTP/1.0"};
		int count;

		count = send(data_socket, snd_message, 14, 0);
		if (count == -1) {
			cout << "Send call failed" << endl;
	}

	}
	
	return 0;
}

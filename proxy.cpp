#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>
#include <signal.h>

using namespace std;

// Function given by Omar, supposed to help with the bind issue
int listen_socket;

void catcher (int sig){
	close(listen_socket);
	printf("catcher with signal %d\n", sig);
	exit(0);
}

/*
Your proxy will need one socket for talking to the client, and another socket for
talking to the server. Make sure to keep track of which one is which!
*/

int main(int argc, char * argv[]) {

	signal(SIGINT, catcher);
	// 2 Arguments
	// argv[1] --> Port Number
	// argv[2] --> # of mistakes
	if (argc != 3) {
		cout << "Please enter a port number followed by the amount (integer) of mistakes you'd like" << endl;
		return 0;
	}

	int port_num = 8888;
	int num_mistakes = atoi(argv[1]);

	//cout << "Your port number is " << port_num << endl;
	cout << "You want " << num_mistakes << " mistakes" << endl;


	// Address initialization
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8327);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	cout << "Address initialization completed"<< endl;


	//----------------------------------------------------
	//------------------ LISTENING SIDE ------------------
	//---------------------------------------------------- 

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
	if (listen_status == -1) {
		cout << "Listening has failed" << endl;
	} else {
		cout << "Now listening " << endl;
	}

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

	// Client address intilization


	//----------------------------------------------------
	//-------------------- CLIENT SIDE -------------------
	//----------------------------------------------------

	// Address initialization 

	/*
	struct sockaddr_in client_address;
	memset(&client_address, 0, sizeof(client_address));
	client_address.sin_family = AF_INET;
	client_address.sin_port = htons(80);
	client_address.sin_addr.s_addr = htonl(INADDR_ANY);

	*/

	//----------------------------------------------------
	//-------------------- SERVER CONN -------------------
	//----------------------------------------------------

	// Listening for connection requests
	while(1) {

		// Data sockets takes the connection from the listening socket
		// Cite --> https://blog.stephencleary.com/2009/05/using-socket-as-server-listening-socket.html
		int data_socket = -1;
		// Data socket may now be used for both READ and WRITE
		data_socket = accept(listen_socket, NULL, NULL);

		if (data_socket == -1) {
			cout << "Data socket failed to accept listening socket\n" << endl;
		} else {
			cout << "Data socket is now listening..." << endl;
		}


		char rcv_message[1024];
		char msg_in[1024];
		int rcv_status;

		rcv_status = recv(data_socket, msg_in, 1024, 0);
		if (rcv_status == -1) {
			cout << "rcv failed" << endl;
		} else {
			cout << "Data socket receiving from client" << endl;
		}

		cout << "Your GET request - \n /--------------- \n" << msg_in << 
			"---------------/" << endl;

		// Getting the URL
		string getCopy(msg_in);

		int stripColon = getCopy.find("/");
		string stripHTTPGET = getCopy.substr(stripColon + 2);
		string newUrl = stripHTTPGET;
		newUrl = newUrl.erase(newUrl.find("/"));
		char charUrl[1024];
		strcpy(charUrl, newUrl.c_str());
		// I'm so sorry I'm doing some really stupid manipulation here
		
		//----------------
		
		cout << "Your URL is: " << newUrl << endl;
		

		struct sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(80);
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

		struct hostent *hostIP; 
		hostIP = gethostbyname(charUrl); 
		cout << "here is the address" << hostIP << endl;
		bcopy((char *) hostIP->h_addr, (char *)
			&server_addr.sin_addr.s_addr, hostIP->h_length);

		//----------------
		//cout << urlPointer1 << endl;
		cout << "past bcopy" << endl;

		int client_socket;
		client_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (client_socket == -1) {
			cout << "Client socket has failed" << endl;
		} else {
			cout << "Creating socket for client..." << endl;
		}
	
		int connect_status;
		connect_status = connect(client_socket, (struct sockaddr*) &server_addr,
			sizeof(struct sockaddr_in));
		if (connect_status == -1) {
			cout << "Client connect() failed." << endl;
		} else {
			cout << "Client has connected to server." << endl;
		}


	}
		return 0;


	}

	


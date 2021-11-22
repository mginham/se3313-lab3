#include "thread.h"
#include "socket.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace Sync;
using namespace std; // So that declarations don't have to be prefaced with 'std::'

int main(void)
{
	// Declare variables
	ByteArray clientMessage, serverMessage; // Stores the data that will be sent and received between the server and the client
	string userText; // String to receive the user input

	// Welcome the user 
	std::cout << "SE3313 Lab 3 Client" << std::endl;

	// Create our socket
	Socket socket("127.0.0.1", 3000);
	socket.Open(); // Open the connection
	
	while(userText != "done") {
		clientMessage.v.clear(); // Clear any data stored in the client message
		serverMessage.v.clear(); // Clear any data stored in the server message
		
		cout << "Enter your message: "; // Prompt the user for input
		cin >> userText; // Take in the input

		if(userText != "done") {
			clientMessage = ByteArray(userText); // Convert the client input into a byte message
			socket.Write(clientMessage); // Send the client message

			sleep(1); // Wait for a moment

			socket.Read(serverMessage); // Read the server message
			cout << serverMessage.ToString() << endl; // Print the received data
		}

		// Exit the loop if the client enters 'done'
	}

	socket.Close();

	cout << "Connection terminated" << endl; // Print that the connection has ended

	return 0;
}

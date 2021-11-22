
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
	///TODO: change up variable names
	ByteArray sending, receiving; ///TODO:
	string userInput;

	// Welcome the user 
	std::cout << "SE3313 Lab 3 Client" << std::endl;

	// Create our socket
	Socket socket("127.0.0.1", 3000);
	socket.Open(); ///TODO:
	
	while(userInput != "done") {
		sending.v.clear(); ///TODO:
		receiving.v.clear(); ///TODO:
		
		cout << "Enter your message: "; ///TODO:
		cin >> userInput; ///TODO:

		if(userInput != "done") { ///TODO:
			sending = ByteArray(userInput); ///TODO:

			socket.Write(sending); // Given
			sleep(1); ///TODO:
			socket.Read(receiving);

			cout << receiving.ToString() << endl; ///TODO:

		}
	}

	socket.Close();

	cout << "Connection terminated" << endl; ///TODO:

	return 0;
}

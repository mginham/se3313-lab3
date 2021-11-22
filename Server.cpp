#include "thread.h"
#include "socketserver.h"
#include <stdlib.h>
#include <time.h>
#include <list>
#include <vector>
#include <algorithm>
#include <signal.h> // Allows for SIGKILL command to be used

using namespace Sync;
using namespace std; // So that declarations don't have to be prefaced with 'std::'

std::vector<int> threadArray; // A dynamic array to track all created threads

// This thread handles the server operations
class ServerThread : public Thread
{
private:
    SocketServer& server;
public:
    ServerThread(SocketServer& server)
    : server(server)
    {}

    ~ServerThread()
    {
        // Cleanup: iterate through every object in the thread array and terminate it
        for(vector<int>::iterator x = threadArray.begin(); x != threadArray.end(); x++) {
            kill(*x, SIGKILL); // Terminate the current thread
        }
    }

    virtual long ThreadMain()
    {
        ByteArray textInput; // Text received from the client
        string temp; // Dummy string to help manipulate the string

        // Wait for a client socket connection
        Socket* newConnection = new Socket(server.Accept());

        threadArray.push_back(getpid()); // Get the process ID and add it to the thread array
        ServerThread* serverThread = new ServerThread(server); // Creating a new server thread

        // A reference to this pointer 
        Socket& socketReference = *newConnection;

        // Manipulate the received input so that it is not the same when it is transmitted back
	    while(true) { // Keeps loop open indefinitely  
            // Wait for data
            socketReference.Read(textInput);

            temp = textInput.ToString(); // Convert the data into a string
            cout << temp << endl; // Print the data string

            reverseLetters(temp); // Reverse the letters in the string

            textInput = ByteArray(temp); // Convert the modified text back into bytes

            // Send it back
            socketReference.Write(textInput);
        }
        
	    return 1;
    }
};

// Function that reverses the order of the letters in a string
void reverseLetters(string& text) {
    int textLength = text.length();

    // Swap the pairs of letters in the string
    for(int x = 0; x < textLength/2; x++) {
        swap(text[x], text[textLength - x - 1]);
    }
}


int main(void)
{
    std::cout << "I am a server." << std::endl;
	
    // Create our server
    SocketServer server(3000);    

    // Need a thread to perform server operations
    ServerThread serverThread(server);
	
    // This will wait for input to shutdown the server
    FlexWait cinWaiter(1, stdin);
    cinWaiter.Wait();

    // Shut down and clean up the server
    server.Shutdown();

}

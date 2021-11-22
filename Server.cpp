#include "thread.h"
#include "socketserver.h"
#include <stdlib.h>
#include <time.h>
#include <list>
#include <vector>
#include <algorithm>
#include <signal.h> ///TODO: what is this for?

using namespace Sync;
using namespace std; // So that declarations don't have to be prefaced with 'std::'

std::vector<int> threads; ///TODO:

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
        // Cleanup
        ///TODO: write comment for what this does
        for(vector<int>::iterator x = threads.begin(); x != threads.end(); x++) {
            kill(*x, SIGKILL);
        }
    }

    virtual long ThreadMain()
    {
        ///TODO: change up variable names
        ByteArray data; ///TODO: what is this for?
        string store; ///TODO: what is this for?

        // Wait for a client socket connection
        Socket* newConnection = new Socket(server.Accept());

        ///TODO: change up this section
        threads.push_back(getpid()); ///TODO: what is this for?
        ServerThread* serverThread = new ServerThread(server); ///TODO: what is this for?

        // A reference to this pointer 
        Socket& socketReference = *newConnection;

	    while(true) { ///TODO: what is the loop for?    
            // Wait for data
            socketReference.Read(data);

            store = data.ToString(); ///TODO:
            cout << store << endl; ///TODO:

            for(int x = 0; x < store.length(); x++) { ///TODO:
                store[x] = toupper(store[x]); ///TODO:
            }

            data = ByteArray(store); ///TODO:

            // Send it back
            socketReference.Write(data);
        }
        
	    return 1;
    }
};


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

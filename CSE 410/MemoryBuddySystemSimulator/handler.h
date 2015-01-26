#ifndef handler
#define handler

#include <iostream>
#include <sstream>
#include <vector>

#include "buddySystem.h"

using namespace std;

// Our delimiter between command parts
const string Delimiter(" ");


// Our handler class
class Handler
{
public:
    /// Constructor
    Handler();

    // Destructor
    ~Handler();

    // Initialize our system
    void Initialize(double exponent);

    // Function for parsing the command
    bool ReadCommand(string command);

    // Function for creating a request
    bool Request(string processName, double size);

    // Function for creating a release
    bool Release(string processName);

    // Display the buddy system
    void DisplayBuddySystem();

private:
    // Number of commands count
    int commandCount = 0;

    /// Pointer to our system
    BuddySystem mBuddySystem;

};

/// Constructor
Handler::Handler()
{

}

/// Destructor
Handler::~Handler()
{

}

void Handler::Initialize(double exponent)
{
    // Initialize size
    mBuddySystem.Initialize(exponent);
}

/// Reads a command by parsing the string
bool Handler::ReadCommand(string command)
{
    cout << "###############################" << endl;

    // Display
    cout << "// " << command << endl;


    commandCount += 1;

    // If it is a request
    if (command.substr(0, command.find(Delimiter)) == "Request")
    {
        // Split the command after the first whitespace
        string split = command.substr(command.find(Delimiter) + 1, command.size() - 1);

        // Get the process name
        string processName = split.substr(0, split.find(Delimiter));

        // Get size
        string size = split.substr(split.find(Delimiter) + 1, split.size() - 1);

        // Trim any excess whitespace
        if (size.find(Delimiter))
        {
            size = size.substr(0, size.find(Delimiter) - 1);
        }

        // Create a request
        Request(processName, stod(size));
    }

    // If it is a release
    if (command.substr(0, command.find(Delimiter)) == "Release")
    {
        // Split the command after the first whitespace
        string split = command.substr(command.find(Delimiter) + 1, command.size() - 1);

        // Get the process name
        string processName = split.substr(0, split.find(Delimiter));

        // Create a release
        Release(processName);
    }

    mBuddySystem.ClearDeletables();
}

bool Handler::Request(string processName, double size)
{
    mBuddySystem.Request(processName, size);
}

bool Handler::Release(string processName)
{
    mBuddySystem.Release(processName);
}

void Handler::DisplayBuddySystem()
{
    mBuddySystem.Display();
}
#endif
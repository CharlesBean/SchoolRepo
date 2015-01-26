/**
* CSE 410 - Project 5
* Charles Bean
* A44600967
* 10/31/2014
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "MMU.h"

using namespace std;

const long Base(2);

int main(int argc, char* argv[])
{
    // Check for the correct number of arguments (command line)
    if(argc != 5) {
        cerr << "Incorrect number of command line arguments." << endl;
        cerr << "Usage: " << argv[0] << " <VirtualMemory> <PageSize> <PhysicalMemory> d/n" << endl;
        exit(EXIT_FAILURE);
    }

    // Getting the variables
    unsigned long virtualMemoryExponent = stoul(argv[1]);
    unsigned long pageSizeExponent = stoul(argv[2]);
    unsigned long numberFrames = stoul(argv[3]); // Physical memory
    bool debugMode = ((string)argv[4] == "d");

    // Calc
    unsigned long virtualMemorySize = pow(Base, virtualMemoryExponent);
    unsigned long pageSize = pow(Base, pageSizeExponent);
    unsigned long numberPages = (virtualMemorySize / pageSize);


    // Display
    if (debugMode)
    {
        cout << endl << "// Output created for" << endl;
        cout << "// " << argv[0] << " " << virtualMemoryExponent << " " << pageSizeExponent << " "  << numberFrames << " "  << argv[4] << endl;
        cout << "// Number of pages: " << numberPages << endl;
    }


    // Create page table
    MMU Table(numberPages, debugMode);

    // Initializing frame table
    Table.InitializeFrameTable(numberFrames);


    // Getting input
    string input;

    while(getline(cin, input)) //< Get per line
    {
        // If there is an input
        if (input.length() > 0)
        {
            // Get the whitespace location
            unsigned long whitespaceIndex = input.find(' ');

            // Get the memory as long
            unsigned long memory = stoul(input.substr(0, whitespaceIndex));



            // Read or write flag
            bool writeFlag = (input.substr(whitespaceIndex + 1, input.length()) == "w");

            // Shift out the offset
            unsigned long pageNumber = memory >> (pageSizeExponent);

            Table.AddEntry(pageNumber, writeFlag);
        }
    }

    // Display final
    Table.Display();

    return 0;
}
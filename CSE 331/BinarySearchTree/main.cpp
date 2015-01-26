#include <iostream>
#include <vector>
#include <fstream>
#include "Tree.h"

using namespace std;

void test(int a)
{
    a += 100000;

    //cout << a << endl;
}

int main(int argc, char* argv[])
{
    // Create the binary search tree
    BinarySearchTree<int> searchTree;

    // Create the vector for initial storage
    std::vector<int> fileNumbers;

    // Create the inorder traversal vector
    std::vector<int> inOrderNumbers;

    // Create filter function
    int k = 2;

    auto isDivisibleByK = [k](int x){ return x % k == 0; };



    // Creating in-file stream
    ifstream infile(argv[1]);

    // If the stream/file isn't open
    if (!infile.is_open()) {
        // Notify and exit
        cout << "File could not be opened." << endl;
        exit(EXIT_FAILURE);
    }


    // Reading input into vector
    int input;
    while (infile >> input)
    {
        fileNumbers.push_back(input);
    }

    // Testing insert
    for (int element : fileNumbers)
    {
        searchTree.insert(element);
    }

    searchTree.display();

    // Testing delete
    searchTree.deleteNode(450);

    inOrderNumbers.clear();

    // In Order Traversal
    searchTree.inOrderTraverse(inOrderNumbers);

//    // Testing traversal
    for (auto element : inOrderNumbers)
    {
        cout << "..";
        cout << element << endl;
    }

    // Testing foreach
    searchTree.forEachInterval(0, 101, test);

    // Testing filter
    searchTree.filter(isDivisibleByK);

    // Displaying tree (orientation sideways)
    searchTree.display();

    searchTree.verifyBinarySearchTree() ? cout << "True" : cout << "False";
    cout << endl;

    return 0;
}

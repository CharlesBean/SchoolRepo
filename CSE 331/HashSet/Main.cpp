#include "HashSet.h"
#include "HashFunc.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void ForeachTest(string a)
{
    a += "-dog";

    if (a.length() > 13)
    {
        cout << a << endl;
    }
}

/**
 * Inserts all of the items from the vector into the set and then outputs statistics.
 */
template<class T>
void Test(vector<T> &items, HashSet<T> &set)
{
    for (T& x :items)
	{
		set.Insert(x);
	}

	cout << "Number of items: " << set.Size() << endl;
	cout << "Number of buckets: " << set.NumBuckets() << endl;
	cout << "Actual load factor: " << set.GetLoad() << endl;
	cout << "Max number of items in a bucket: " << set.MaxBucketSize() << endl;
	cout << "Percent of empty buckets: " << set.PercentEmptyBuckets() << endl;

    // Testing
    cout << "The set contains 'interlude': " << (set.Contains("interlude") ? "true" : "false") << endl;
    cout << "Removing 'interlude': " << (set.Remove("interlude") ? "true" : "false") << endl;
    cout << "The set contains 'interlude': " << (set.Contains("interlude") ? "true" : "false") << endl;
    cout << "Running function (x + 2) " << endl;
    //set.ForEach(ForeachTest);
    //set.Clear();
    //set.DisplayItems();
    //cout << "Is empty: " << (set.IsEmpty()) ? "true" : "false";

}

int main(int argc, char* argv[])
{
    // Check for the correct number of arguments (command line)
	if(argc != 3) {
		cerr << "Incorrect number of command line arguments." << endl;
		cerr << "Usage: " << argv[0] << " <filename> <loadfactor>" << endl;
		exit(EXIT_FAILURE);
	}

    // Create infile stream from 2nd argument
	ifstream infile(argv[1]);

	// check to see if file opening succeeded
	if (!infile.is_open()) {
		cout<<"Could not open file\n";
		exit(EXIT_FAILURE);
	}

    // Use the third parameter as loadFactor (convert to double)
	double loadFactor = stod(argv[2]);
	
	// Read words
	vector<string> words;
	string word;

    // Read the words from the file into the vector
	while (infile >> word) {
		words.push_back(word);
	}

    // Copy a hash from hashA, with loadFactor
	HashSet<string> setA(HashA, loadFactor);
	cout << "Testing Hash Algorithm A" << endl;
	Test(words, setA);
	
	cout << endl;

    // B
	HashSet<string> setB(HashB, loadFactor);
	cout << "Testing Hash Algorithm B" << endl;
	Test(words, setB);

	cout << endl;

    // C
	HashSet<string> setC(HashC, loadFactor);
	cout << "Testing Hash Algorithm C" << endl;
	Test(words, setC);
	
	return 0;
}
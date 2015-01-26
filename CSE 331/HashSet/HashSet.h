/**
 * A hash set.
 * Stub written by James Daly, 8 Oct 2014
 * Completed by Charles Bean
 */
#pragma once

#ifndef HASH_SET_H
#define HASH_SET_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <math.h>
#include <vector>
#include <list>

using namespace std;

template<class T>
class HashSet
{
public:
	HashSet(std::function<unsigned int(const T&)> hash, double loadFactor);
	HashSet(HashSet<T> &other);
	virtual ~HashSet();


	// Supplied Methods

    // Determines if the hashset is empty
	bool IsEmpty() const { return Size() == 0; }

    // Returns the size of the hashset
	unsigned int Size() const { return size; }

    // Returns the passed load factor
	double GetLoadFactor() const { return loadFactor; }

    // Displays the items in the hashset
	void DisplayItems() const { ForEach([](const T& item) { std::cout << item << std::endl; }); }

    // Calculates actual current load (capacity / number of buckets) (the mean # items per bucket)
	double GetLoad() const { return ((double)Size()) / (double)NumBuckets(); }



	// Methods that you must complete

    // Returns the number of buckets in our hashSet - O(1)
	unsigned int NumBuckets() const { return (int)mNumberBuckets; } // Complete

    // Checks if the table contains an item - O(1)
	bool Contains(const T& item) const; // Complete

    // Inserts an item into the hashSet - O(1)
	bool Insert(const T &item); // Complete

    // Removes an item from the hashSet - O(1)
	bool Remove(const T &item); // Complete

    // Clears the hashSet of items - O(n+k)
	void Clear(); // Complete

    // Performs a function over each hashSet item - O(n+k)
	void ForEach(std::function<void (const T&)> func) const; // Complete

    // Returns the size of the largest bucket (most items) - O(k)
	unsigned int MaxBucketSize() const; // Complete

    // Returns the percent of buckets without any items - O(k)
	double PercentEmptyBuckets() const; // Complete
	
private:
    // The number of elements in our HashSet
	unsigned int size = 0;

    // The factor by which we increase our bucket size if over
	double loadFactor;

    // Stores the hash function we use to give an item a key
	std::function<unsigned int (const T&)> hash;



    /**** Helpers ****/


    /* Data member variables */

    // The number of buckets (2^D)
    unsigned long mNumberBuckets;

    // Global depth (default of 1)
    unsigned long mGlobalDepth = 1;

    // Max depth (can be user overriden by manually entering values above..)
    unsigned long mMaxGlobalDepth = 20;

    // Max bucket size
    unsigned int mMaxBucketSize = 10;

    // Our bucket struct
    struct Bucket
    {
        // Our bucket's actual size (start at 0)
        unsigned int mSize = 0;

        // Our bucket's contents
        vector<shared_ptr<T> > mContents;

        // Function to increase size
        void Increment() { mSize += 1; }

        // Function to decrease size
        void Decrement() { mSize -= 1; }
    };

    // Our hash table - a vector of buckets (other vectors) who have members
    vector<Bucket> mHashStorage;

    // Temporary storage vector
    vector<shared_ptr<T> > tempStorage;


    /* Functions */

    // Function for creating the buckets
    bool CreateBuckets();

    // Function for inserting via key
    bool InsertViaKey(int bucketKey, const T& item);

    // Function for rehashing
    bool Rehash();

    // Function for checking overload (load factor)
    bool WillOverload();

    // Recalculate the global depth, and recalc number of buckets
    void Recalculate() { IncrementGlobalDepth(); mNumberBuckets = pow(2, mGlobalDepth); }

    // Increments the global depth by 1 (if under the limit)
    void IncrementGlobalDepth() { if (mGlobalDepth < mMaxGlobalDepth) mGlobalDepth += 1; }

    // Temporary storage function
    void TemporarilyStore(vector<shared_ptr<T> > &vector);
};

/**
 * Default constructor
 */
template<class T>
HashSet<T>::HashSet(std::function<unsigned int(const T&)> hash, double loadFactor):
	size(0),
	loadFactor(loadFactor),
	hash(hash)
{
    // Initialize the number of buckets
    mNumberBuckets = pow(2, mGlobalDepth);

	// Make our storage have 'x' buckets on default (based off global depth)
    mHashStorage.resize(mNumberBuckets);

    // Create the buckets initially
    CreateBuckets();
}

/**
 * Copy Constructor
 * Uses uniform instantiation to initialize itself
 * and then copies all of the items from the other set
 */
template<class T>
HashSet<T>::HashSet(HashSet<T> &other) :
	HashSet(other.hash, other.loadFactor)
{
	auto insertItem = [=](const T& x){ this->Insert(x); };
	other.ForEach(insertItem);
}

/**
 * Destructor
 * Any cleanup you need to do can be done here
 */
template<class T>
HashSet<T>::~HashSet()
{
	// Empty: You can put any steps necessary for cleanup here
}

/**
 * Returns true iff the item is in the set
 */
template<class T>
bool HashSet<T>::Contains(const T &item) const
{
    // Calculate the item key
	unsigned int bucketKey = hash(item);

    // Modulo number of buckets
    bucketKey %= mNumberBuckets;

    // RFor each member of the calculated bucket
    for (auto member : mHashStorage[bucketKey].mContents)
    {
        // If the member is what we are looking for (dereference pointer)
        if (member != nullptr && *member == item)
        {
            // The hashSet contains it
            return true;
        }
    }

    // Couldn't find the item
    return false;
}

/**
 * Inserts the item into the set.
 * Only one copy can exist in the set at a time.
 * Returns true iff the item was successfully added.
 */
template<class T>
bool HashSet<T>::Insert(const T &item)
{
    // If the element doesn't already exist in the hashSet
    if (!Contains(item))
    {
        if (!WillOverload())
        {
            // Create a key from the item using the hash function
            unsigned int bucketKey = hash(item);

            // Modulo the key by the size of the table
            bucketKey %= mNumberBuckets;

            // Insert into the set & return true/false
            return (InsertViaKey(bucketKey, item));
        }
        else // Rehash
        {
            // Perform the rehashing
            Rehash();

            // Call Insert() (which uses hash) on item after rehashing of table
            Insert(item);

            // Didn't insert yet
            return false;
        }
    }
    else // Element already exists
    {
        // Return false
        return false;
    }
}

/**
 * Removes the item from the set.
 * Returns true iff the item was successfully removed.
 */
template<class T>
bool HashSet<T>::Remove(const T &item)
{
    // Create a key from the item using the hash function
    unsigned int bucketKey = hash(item);

    // Modulo the key by the size of the table
    bucketKey %= mNumberBuckets;

    // For each member of the calculated bucket
    for (auto &member : mHashStorage[bucketKey].mContents)
    {
        // If the member is what we are looking for (dereference pointer)
        if (member != nullptr && *member == item)
        {
            //  Remove the item pointer
            member = nullptr;

            // Subtract one from total size
            size -= 1;

            // Subtract one from bucket size
            mHashStorage[bucketKey].Decrement();

            // The item was removed (from hashSet, not from vector it lives in)
            return true;
        }
    }

    // Wasn't removed
    return false;
}

/**
 * Removes all elements from the set.
 */
template<class T>
void HashSet<T>::Clear()
{
    //For each bucket (PASS BUCKET BY REFERENCE)
    for (Bucket &bucket : mHashStorage)
    {
        // Set the size to 0
        bucket.mSize = 0;

        // Clear the bucket contents
        bucket.mContents.clear();
    };

    // Set the size to zero
    size = 0;
}

/**
 * Invokes the function once on each item in the set.
 * The exact order is undefined.
 */
template<class T>
void HashSet<T>::ForEach(std::function<void (const T&)> func) const
{
    // For each bucket
	for (Bucket bucket : mHashStorage)
    {
        // If the bucket has members
        if (bucket.mSize > 0)
        {
            // Iterate over members
            for (shared_ptr<T> member : bucket.mContents)
            {
                // If they exist (point is valid)
                if (member != nullptr)
                {
                    // Call the function on the member
                    func(*member);
                }
            }
        }
    }
}

/**
 * Finds the maximum number of items in a bucket.
 */
template<class T>
unsigned int HashSet<T>::MaxBucketSize() const
{
    // Set value
    unsigned int biggestBucket = 0;

    // Go through each bucket
    for (Bucket bucket : mHashStorage)
    {
        // If bucket has a bigger size than biggest
        if (bucket.mSize > biggestBucket)
        {
            // Set the biggest to that bucket's size
            biggestBucket = bucket.mSize;
        }
    }

    // Return the biggest
    return biggestBucket;
}

/**
 * Finds which fraction of the buckets are empty
 * The result is returned as a percent
 */
template<class T>
double HashSet<T>::PercentEmptyBuckets() const
{
    // Keep two counts (doesn't have to be a total - can get from these two)
    double emptyCount = 0;
    double fullCount = 0;

    // For each bucket
	for (Bucket bucket : mHashStorage)
    {
        // If bucket empty, tick that counter - vice versa
        (bucket.mSize == 0) ? emptyCount += 1 : fullCount += 1;
    }

    // Calculate percentage (empty/ total) buckets
    double percentage = (emptyCount / (emptyCount + fullCount)) * 100.0;

    // Return
    return percentage;
}

/*** Helpers ***/

template<class T>
bool HashSet<T>::InsertViaKey(int bucketKey, const T &item)
{
    // If the bucket size is less than the maximum and the hash will not overload and the storage doesn't already contain
    if (mHashStorage[bucketKey].mSize < mMaxBucketSize)
    {
        // Create the shared_ptr
        shared_ptr<T> member = make_shared<T>(item);

        // Add the member to the bucket
        mHashStorage[bucketKey].mContents.push_back(member);

        // Increment the size total
        size += 1;

        // Increment the bucket size
        mHashStorage[bucketKey].Increment();

        // Insert complete
        return true;
    }
    else
    {
        // Insert not yet complete (recursize essentially)
        return false;
    }
}

template<class T>
bool HashSet<T>::CreateBuckets()
{
    // Iterate over the number of buckets
    for (int i = 0; i < mNumberBuckets; i++)
    {
        // Create the bucket
        Bucket bucket;

        // Add bucket to the hash
        mHashStorage[i] = bucket;
    }

    // Success
    return true;
}

template<class T>
bool HashSet<T>::Rehash()
{
    // Recalculate hash settings (global depth += 1, mNumberBuckets recalculate)
    Recalculate(); // Needs to be more efficient

    cout << "\tLoad factor exceeded... Increasing global depth to " << mGlobalDepth << ", and rehashing..." << endl;

    // If we wont overload now
    if (!WillOverload())
    {
        // Store the values temporarily
        TemporarilyStore(tempStorage);

        // Clear contents
        Clear();

        // Clear storage of buckets
        mHashStorage.clear();

        // Resize storage
        mHashStorage.resize(mNumberBuckets);

        // Create buckets
        CreateBuckets();

        // Re-insert
        for (shared_ptr<T> member : tempStorage)
        {
            if (member != nullptr)
            {
                // Reinsert the value
                Insert(*member);
            }
        }

        // Clear the temporary storage
        tempStorage.clear();

        // Return true (success)
        return true;
    }
    else // Will overload again...
    {
        // Rehash recursive
        Rehash();

        // Return false (fail)
        return false;
    }
}

/*
    Checks to see if the load factor will be overloaded IF we add a new element/member
 */
template<class T>
bool HashSet<T>::WillOverload()
{
    // If the size + 1 (because we WOULD be incrementing it, if we added a new element)
    //  results in a load factor greater than our maximum load factor (argument)
    return (
            ((double)size + 1) > (loadFactor * (double)mNumberBuckets)
    );
};

template<class T>
void HashSet<T>::TemporarilyStore(vector<shared_ptr<T> > &vector)
{
    //For each bucket (PASS BUCKET BY REFERENCE)
    for (Bucket &bucket : mHashStorage)
    {
        // If the bucket has members
        if (bucket.mContents.size() != 0)
        {
            // Push back the members onto the passed-by-reference vector
            for (auto member : bucket.mContents)
            {
                vector.push_back(member);
            };
        };
    };
};

#endif
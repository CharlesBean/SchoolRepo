#ifndef buddySystem
#define buddySystem

#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

#include "memoryBlock.h"

using namespace std;

class BuddySystem
{
public:
    BuddySystem();

    ~BuddySystem();

    vector<shared_ptr<MemoryBlock> > GetContents() { return mSystemContents; }

    void Initialize(double exponent);

    bool Request (string processName, double size);

    bool Release (string processName);

    bool CreateBlock(double bytes, double size, string processName, bool display = true);

    bool Split(shared_ptr<MemoryBlock> block, double i);

    bool Merge(shared_ptr<MemoryBlock> firstHalf, shared_ptr<MemoryBlock> secondHalf, double i);

    double GetMaximum() { return mMaxILists; }

    void AddBuddy(shared_ptr<MemoryBlock> block, double i);

    void Display();

    void ClearDeletables();

private:
    vector<shared_ptr<MemoryBlock> > mSystemContents;

    vector<vector<shared_ptr<MemoryBlock> > > mILists;

    vector<shared_ptr<MemoryBlock> > mToDelete;

    double mMaxILists;

    double mTotalMemory;
};

BuddySystem::BuddySystem()
{
}

BuddySystem::~BuddySystem()
{
}

void BuddySystem::Initialize(double exponent)
{
    // Set the max
    mMaxILists = exponent;

    // Set total memory
    mTotalMemory = pow(Base, exponent);

    // Create a shared pointer to our initial block
    shared_ptr<MemoryBlock> initialBlock = make_shared<MemoryBlock>(exponent);

    // Setting the starting address
    initialBlock->SetStartingAddress(exponent);

    // Reserving the space (EXPONENT IS DOUBLE - CARE)
    mILists.reserve(exponent + 1);

    // Add to the i-list for the exponent (last possible i-list)
    mILists[exponent].push_back(initialBlock);

    // Add to system contents
    mSystemContents.push_back(initialBlock);
}

bool BuddySystem::Request(string processName, double size)
{
    // Calculate the size we want
    for (double i = 0; i <= mMaxILists; i++)
    {
        // If we found the first exponent that gives just the right amount of storage (first greater than)
        if (pow(Base, i) > size)
        {
            // Try to create a block
            bool created = CreateBlock(i, size, processName);

            // Return the outcome
            return created;
        }
    }
}

bool BuddySystem::Release(string processName)
{
    // For each i-list
    for (int i = 0; i <= mMaxILists; i++)
    {
        // For each block in each i-list
        for (auto block : mILists[i])
        {
            // If the block has the correct process name
            if (block->GetProcessName() == processName)
            {
                // Display
                cout << "Releasing process " << block->GetProcessName() << ", Starting Address: ";

                // Displaying hex address
                printf("%x\n", block->GetStartingAddress());

                // Display buddy starting address
                cout << "Address of corresponding buddy: " << block->GetBuddy()->GetStartingAddress() << endl;

                // Display
                block->GetBuddy()->IsEmpty() ? cout << "Buddy is free. " << endl : cout << "Buddy is not free." << endl;

                // If the buddy is empty
                if (block->GetBuddy()->IsEmpty())
                    Merge(block, block->GetBuddy(), i);
            }
        }
    }
}

bool BuddySystem::CreateBlock(double exponent, double size, string processName, bool display)
{
    // Creating placeholder for our selected vector
    vector<shared_ptr<MemoryBlock > > selectedVector;

    // Placeholder for our current i-list
    double selectedIList = exponent;

    // The desired size of block we want (calculated by passed parameter - exponent)
    double desiredSize = pow(Base, exponent);


    /*** Creating block (Recursive on split) (Don't know why I used a while-loop... will change to for if I have time) ***/

    // While we are within maximum
    while (selectedIList <= mMaxILists)
    {
        // Display
        if (display)
            cout << "Evaluating " << selectedIList << "-List: ";

        // Initialze
        selectedVector = mILists[selectedIList];

        // If the vector isn't empty
        if (!selectedVector.empty())
        {
            if (display)
                cout << "Not Empty" << endl;

            // If the selected i-list is our desired size
            if (selectedIList == exponent)
            {
                // Iterate over each block in i-list
                for (auto block : selectedVector)
                {
                    // If the block is empty and has the correct size
                    if (block->IsEmpty() && block->GetSize() == desiredSize)
                    {
                        // Mark block as not empty
                        block->Fill();

                        // Set the blocks process
                        block->SetProcessName(processName);

                        // Set the processes size in the block
                        block->SetSize(size);

                        // Set the starting address
                        block->SetStartingAddress(selectedIList);

                        // Display
                        cout << "Created process " << processName << endl;

                        // Break loop and return that it was successful
                        return true;
                    }
                }
            }
            else // If this i-list is bigger than what we want
            {
                // For each memory block
                for (auto block : selectedVector)
                {
                    // If the block isn't taken
                    if (block->IsEmpty())
                    {
                        // Split the block
                        Split(block, selectedIList);

                        // Recursively call this function to restart
                        bool completed = CreateBlock(exponent, size, processName, false);

                        // Add any buddies
                        AddBuddy(block, selectedIList);

                        // Return completed flag
                        return completed;
                    }
                }
            }
        }
        else
        {
            if (display)
                cout << "Empty" << endl;
        }


        // If no block found in this list
        selectedIList += 1;
    }
}

bool BuddySystem::Split(shared_ptr<MemoryBlock> block, double i)
{
    // Display
    cout << "Splitting a block from " << i << "-List" << endl;

    // If the i-list of the block to be split is not empty
    if (!mILists[i].empty())
    {
        // Create two new blocks of memory of 1 magnitue (i-list) less than our block
        shared_ptr<MemoryBlock> firstHalf = make_shared<MemoryBlock>(i - 1);
        shared_ptr<MemoryBlock> secondHalf = make_shared<MemoryBlock>(i - 1);

        // Create buddies :)
        firstHalf->SetBuddy(secondHalf);
        secondHalf->SetBuddy(firstHalf);

        // Add these blocks to their respective i-list
        mILists[i-1].push_back(firstHalf);
        mILists[i-1].push_back(secondHalf);

        // Delete the bigger block
        mToDelete.push_back(block);

        return true;
    }
    else
    {
        return false;
    }
}

bool BuddySystem::Merge(shared_ptr<MemoryBlock> firstHalf, shared_ptr<MemoryBlock> secondHalf, double i)
{
    // Display
    cout << "Merging to create an entry in " << i + 1 << "-List " << endl;

    // If the i-list of the two blocks to be merged is not empty
    if (!mILists[i].empty())
    {
        // Create new block of double the size (1 + i-list)
        shared_ptr<MemoryBlock> mergedBlock = make_shared<MemoryBlock>(i + 1);

        // Add the block to it's respective i-list
        mILists[i+1].push_back(mergedBlock);

        // Create any buddies
        AddBuddy(mergedBlock, i+1);

        // Delete the old blocks
        mToDelete.push_back(firstHalf);
        mToDelete.push_back(secondHalf);

        return true;
    }
    else
    {
        return false;
    }

}

void BuddySystem::Display()
{
    cout << "############################" << endl;

    cout << "END" << endl;

    // For each i-list
    for (int i = 0; i <= mMaxILists; i++)
    {
        // if not empty - display
        if (!mILists[i].empty())
        {
            cout << i << "-List contains " << mILists[i].size() << " entries. Starting addresses: ";

            for (auto block : mILists[i])
            {
                cout << block->GetStartingAddress() << ", ";
            }

            cout << endl;
        }
    }
}

void BuddySystem::AddBuddy(shared_ptr<MemoryBlock> block, double i)
{
    // For all blocks in same i-list
    for (auto otherBlock : mILists[i])
    {
        // If we are looking at a brother block
        if (otherBlock != block)
        {
            double factor = pow(Base, mMaxILists - i);

            // If the size of the other block is (1/4 of total if 18, 1/8 of total if 17, etc... )
            if (otherBlock->GetStartingAddress() == (mTotalMemory/factor) && otherBlock->GetBuddy() != nullptr)
            {
                // Buddies :)
                block->SetBuddy(otherBlock);
                otherBlock->SetBuddy(block);
            }
        }
    }
}

void BuddySystem::ClearDeletables()
{
//    for (shared_ptr<MemoryBlock> block : mToDelete)
//    {
//        MemoryBlock *ptrToDelete = &(*block);
//        delete ptrToDelete;
//    }
}

#endif
/**
* CSE 410 - Project 5
* Charles Bean
* A44600967
* 10/31/2014
*/

#pragma once

#include <iostream>
#include <vector>
#include "PageTableEntry.h"
#include "FrameTable.h"

using namespace std;

/**
* A class representing our overall Memory Management Unit
*
*/
class MMU
{
public:
    // Constructor
    MMU();

    // Destructor
    ~MMU();

    // Size Constructor
    MMU(unsigned long tableSize, bool debugMode);

    // Add an entry
    void AddEntry(unsigned long pageNumber, bool writeFlag);

    // Our page table (vector) (not a class - just not worth extra code)
    vector<PageTableEntry> mPageTable;

    // Our frame table
    FrameTable mFrameTable;

    // Initialize the frame table
    void InitializeFrameTable(unsigned long numberFrames);

    // Display function
    void Display();

    // Timer control function
    void TickTimers();

    // Debug flag
    bool mDebugMode = false;

    // Page fault count
    unsigned long mPageFaults = 0;

    // Memory access count
    unsigned long mMemoryAccesses = 0;

    // Number of pages written to disk
    unsigned long mPagesWrittenToDisk = 0;
};

MMU::MMU()
{
}

MMU::~MMU()
{
}

MMU::MMU(unsigned long tableSize, bool debugMode)
{
    // Resize the page table
    mPageTable.resize(tableSize, PageTableEntry());

    // Set the debug flag
    mDebugMode = debugMode;
}

void MMU::InitializeFrameTable(unsigned long numberFrames)
{
    // Set desired number of frames in frame table
    mFrameTable.mNumberFrames = numberFrames;
}

void MMU::AddEntry(unsigned long pageNumber, bool writeFlag)
{
    // Timers handling
    TickTimers();


    // If the page is present in the frame table
    if (mPageTable[pageNumber].mPresentBit)
    {
        // If we are writing
        if (writeFlag)
        {
            // Alter both FrameTable and PageTable versions

            // The page has been modified (dirty!) in Page Table
            mPageTable[pageNumber].mModifiedBit = true;

            // Page modified in FrameTable
            mFrameTable.mEntries[mPageTable[pageNumber].mFrameNumber].mModifiedBit = true;
        }


        // Update the timestamp
        mPageTable[pageNumber].mTimestamp = 0;
        mFrameTable.mEntries[mPageTable[pageNumber].mFrameNumber].mTimestamp = 0;


        // Increment memory accesses count
        mMemoryAccesses += 1;

    }
    else // Page not in frame table right now and there is a frame table
    {
        // Filling the frame table
        if (mFrameTable.mEntries.size() < mFrameTable.mNumberFrames)
        {
            // Parameters (easier to read)
            unsigned long frameNumber = mFrameTable.mEntries.size(); // Frame number
            bool isModified = false; // If modified (dirty)
            bool isPresent = true; // Is now present


            // Change the pages members
            mPageTable[pageNumber].mTimestamp = 0; // Begin count
            mPageTable[pageNumber].mFrameNumber = frameNumber; // Set the frame number
            mPageTable[pageNumber].mModifiedBit = isModified; // Set if it is modified
            mPageTable[pageNumber].mPresentBit = isPresent; // Set if it is present
            mPageTable[pageNumber].mPageNumber = pageNumber; // Set the page number (naming)


            // Add the page to the frame table (not using pointers - represents a frame table better)
            mFrameTable.mEntries.push_back(mPageTable[pageNumber]);

            // Accesed the frame table, so increment count
            mMemoryAccesses += 1;


            // If debug
            if (mDebugMode)
            {
                cout << "Page NULL is replaced by Page " << pageNumber << endl;
                cout << "Page NULL was not dirty " << endl;
            }
        }
        else // If our table is now 'full' - we need to REPLACE
        {
            // We have a page fault (not initially empty cases - just replacement)
            mPageFaults += 1;


            // Select the default
            PageTableEntry leastRecentlyUsed = mFrameTable.mEntries[0];

            // Save frame number
            unsigned long frameNumber = 0;

            // Iterate over frame table (and find LRU)
            for (unsigned long i = 0; i < mFrameTable.mEntries.size(); i++)
            {
                // If we found a new LRU
                if (mFrameTable.mEntries[i].mTimestamp > leastRecentlyUsed.mTimestamp)
                {
                    // Reset
                    leastRecentlyUsed = mFrameTable.mEntries[i];

                    // Save index
                    frameNumber = i;
                }
            }


            // If the LRU is dirty
            if (leastRecentlyUsed.mModifiedBit)
            {
                // Write it to disk
                mPagesWrittenToDisk += 1;
            }


            // If debug display
            if (mDebugMode)
            {
                cout << "Page " << leastRecentlyUsed.mPageNumber << " is replaced by Page " << pageNumber << endl;
                cout << "Page " << leastRecentlyUsed.mPageNumber <<
                        ((leastRecentlyUsed.mModifiedBit) ? " is dirty" : " is not dirty") << endl;
            }


            /** Updating the PageTable entry, and the FrameTable entry **/

            // Update the page table entry
            mPageTable[pageNumber].mTimestamp = 0; // Begin count
            mPageTable[pageNumber].mFrameNumber = frameNumber; // Set the frame number
            mPageTable[pageNumber].mModifiedBit = false; // Set if it is modified
            mPageTable[pageNumber].mPresentBit = true; // Set if it is present
            mPageTable[pageNumber].mPageNumber = pageNumber; // Set the page number (naming)

            // Update the frame table entry
            mFrameTable.mEntries[frameNumber].mTimestamp = 0; // Reset count
            mFrameTable.mEntries[frameNumber].mFrameNumber = frameNumber;
            mFrameTable.mEntries[frameNumber].mModifiedBit = writeFlag;
            mFrameTable.mEntries[frameNumber].mPresentBit = true;
            mFrameTable.mEntries[frameNumber].mPageNumber = pageNumber;

            // Change page table
            mPageTable[leastRecentlyUsed.mPageNumber].mTimestamp = -1;
            mPageTable[leastRecentlyUsed.mPageNumber].mFrameNumber = -1;
            mPageTable[leastRecentlyUsed.mPageNumber].mModifiedBit = false;
            mPageTable[leastRecentlyUsed.mPageNumber].mPresentBit = false;


            // Increment memory accesses count
            mMemoryAccesses += 1;
        }
    }
}

void MMU::Display()
{
    // Display memory accesses and page faults
    cout << "Number of memory accesses = " << mMemoryAccesses << endl;
    cout << "Number of page faults (replacement) = " << mPageFaults << endl;

    // Count any disk writes that are left in memory
    long frameWritesLeft = 0;
    for (PageTableEntry frame : mFrameTable.mEntries)
    {
        // If the frame is dirty
        if (frame.mModifiedBit)
        {
            frameWritesLeft += 1;
        }
    }

    // Display number of disk writes
    cout << "Number of pages written to disk = " << mPagesWrittenToDisk + frameWritesLeft << endl;
}

void MMU::TickTimers()
{
    // Iterate over frame table
    for (unsigned long i = 0; i < mFrameTable.mEntries.size(); i++)
    {
        // Tick frame table version timer
        mFrameTable.mEntries[i].mTimestamp += 1;

        // Tick page table version timer
        mPageTable[mFrameTable.mEntries[i].mPageNumber].mTimestamp += 1;
    }
}
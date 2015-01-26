/**
* CSE 410 - Project 5
* Charles Bean
* A44600967
* 10/31/2014
*/

#pragma once

#include <iostream>
#include <vector>

/**
* A class representing a Page (an entry in our page table as well)
*   - Page Table is Logical Memory
*/
class PageTableEntry
{
public:
    // Constructor
    PageTableEntry();

    // Destructor
    ~PageTableEntry();

    // Non-default Constructor
    PageTableEntry(bool presentBit, bool modifiedBit, long frameNumber);

    // If the entry is present
    bool mPresentBit = false;

    // If the entry is dirty/modified
    bool mModifiedBit = false;

    // The frame number of the entry (default -1 to signal that it is null (not in the frame table))
    long mFrameNumber = -1;

    // The time this entry was created (default -1 (not assigned yet))
    long mTimestamp = -1;

    // The page number
    long mPageNumber = -1;
};

PageTableEntry::PageTableEntry()
{
}

PageTableEntry::~PageTableEntry()
{
}

PageTableEntry::PageTableEntry(bool presentBit, bool modifiedBit, long frameNumber) :
        mPresentBit(presentBit), mModifiedBit(modifiedBit), mFrameNumber(frameNumber)
{
}
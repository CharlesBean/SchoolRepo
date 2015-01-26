/**
* CSE 410 - Project 5
* Charles Bean
* A44600967
* 10/31/2014
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/**
* Class that represents a frame table (stores the physical memory)
*/
class FrameTable
{
public:
    // Constructor
    FrameTable();

    // Destructor
    ~FrameTable();

    // Our frame table (storage)
    vector<PageTableEntry> mEntries;

    // Number of frames
    unsigned long mNumberFrames = 0;
};

FrameTable::FrameTable()
{
}

FrameTable::~FrameTable()
{
}

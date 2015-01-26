#ifndef memoryBlock
#define memoryBlock

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

const double Base(2);

class MemoryBlock
{
public:
    MemoryBlock();

    MemoryBlock(double exponent);

    ~MemoryBlock();

    double GetSize() { return mSizeBytes; }

    void SetBuddy(shared_ptr<MemoryBlock> buddy) { mBuddy = buddy; }

    shared_ptr<MemoryBlock> GetBuddy() { return mBuddy; }

    string GetProcessName() { return mProcessName; }

    bool IsEmpty() { return mIsEmpty; }

    void Fill() { mIsEmpty = false; }

    void SetProcessName(string processName) { mProcessName = processName; }

    void SetSize(double size) { mProcessSize = size; }

    unsigned long GetStartingAddress() { return mStartingAddress; }

    unsigned long SetStartingAddress(double exponent) { mStartingAddress = powl(Base, exponent); }

    void Delete() { delete this; }


private:
    // Creating the addresses for the block
    unsigned long mStartingAddress;

    // The size of the block
    double mSizeBytes;

    // The process name
    string mProcessName = "";

    // The process size
    double mProcessSize;

    // Whether the block is empty
    bool mIsEmpty = true;

    // Any buddies this guy has!
    shared_ptr<MemoryBlock> mBuddy = nullptr;
};

MemoryBlock::MemoryBlock()
{
}

MemoryBlock::MemoryBlock(double exponent)
{
    mSizeBytes = pow(Base, exponent);
//    mIList = exponent; // Removed
}

MemoryBlock::~MemoryBlock()
{
}

#endif
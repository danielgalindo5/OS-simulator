#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <cstdint>

class VirtualMemory {
public:
    // You can change these if your professor wants different sizes
    static const int PAGE_SIZE   = 256;  // bytes per page
    static const int NUM_PAGES   = 16;   // pages in logical space
    static const int FRAME_COUNT = 8;    // frames in physical memory

    VirtualMemory();

    // Returns the byte stored at logicalAddress.
    // pageFault is set to true if this access caused a page fault.
    std::uint8_t readByte(std::uint16_t logicalAddress, bool &pageFault);

    // Writes 'value' into logicalAddress.
    // pageFault is set to true if this access caused a page fault.
    void writeByte(std::uint16_t logicalAddress, std::uint8_t value, bool &pageFault);

    // Prints stats like total accesses and page faults.
    void printStats() const;

private:
    struct PageTableEntry {
        bool valid;
        int  frameNumber;
        bool dirty;
    };

    PageTableEntry pageTable[NUM_PAGES];

    // Simulated physical memory
    std::uint8_t physicalMemory[FRAME_COUNT * PAGE_SIZE];

    // For replacement (simple FIFO) and reverse mapping
    int  frameToPage[FRAME_COUNT];  // which page is currently in each frame, -1 if free
    bool frameUsed[FRAME_COUNT];
    int  nextVictimFrame;           // pointer for FIFO replacement

    int  totalAccesses;
    int  totalPageFaults;

    // Translate a logical address and return the physical address.
    // Sets pageFault = true if a page fault occurred.
    int translate(std::uint16_t logicalAddress, bool &pageFault);

    // Load the page into some frame (may evict another page).
    void handlePageFault(int pageNumber);
};

#endif

#include "VirtualMemory.h"
#include <iostream>

using namespace std;

VirtualMemory::VirtualMemory()
    : nextVictimFrame(0),
      totalAccesses(0),
      totalPageFaults(0)
{
    // Initialize page table
    for (int i = 0; i < NUM_PAGES; ++i) {
        pageTable[i].valid      = false;
        pageTable[i].frameNumber = -1;
        pageTable[i].dirty      = false;
    }

    // Initialize frames
    for (int i = 0; i < FRAME_COUNT; ++i) {
        frameToPage[i] = -1;
        frameUsed[i]   = false;
    }

    // Initialize physical memory to zeros
    for (int i = 0; i < FRAME_COUNT * PAGE_SIZE; ++i) {
        physicalMemory[i] = 0;
    }
}

// Core translation: logical -> physical
int VirtualMemory::translate(std::uint16_t logicalAddress, bool &pageFault) {
    int page   = logicalAddress / PAGE_SIZE;
    int offset = logicalAddress % PAGE_SIZE;

    totalAccesses++;

    // Bounds check on page number
    if (page < 0 || page >= NUM_PAGES) {
        // In a real OS you'd raise an exception; here we just clamp.
        cout << "[VM] Invalid page number " << page << " from logical address "
             << logicalAddress << ".\n";
        pageFault = false;
        return 0;
    }

    if (!pageTable[page].valid) {
        // Page fault
        totalPageFaults++;
        handlePageFault(page);
        pageFault = true;
    } else {
        pageFault = false;
    }

    int frame = pageTable[page].frameNumber;
    int physicalAddress = frame * PAGE_SIZE + offset;
    return physicalAddress;
}

void VirtualMemory::handlePageFault(int pageNumber) {
    // 1) Try to find a free frame
    int chosenFrame = -1;
    for (int i = 0; i < FRAME_COUNT; ++i) {
        if (!frameUsed[i]) {
            chosenFrame = i;
            frameUsed[i] = true;
            break;
        }
    }

    // 2) If no free frame, evict using FIFO
    if (chosenFrame == -1) {
        chosenFrame = nextVictimFrame;

        int oldPage = frameToPage[chosenFrame];
        if (oldPage != -1) {
            // Evict old page
            // If pageTable[oldPage].dirty == true, we would "write back" to disk here.
            pageTable[oldPage].valid = false;
            pageTable[oldPage].frameNumber = -1;
        }

        nextVictimFrame = (nextVictimFrame + 1) % FRAME_COUNT;
    }

    // 3) Load new page into chosenFrame
    frameToPage[chosenFrame] = pageNumber;

    // Simulate reading from backing store:
    // for this project we just fill it with something deterministic
    // so you can see different values if you want.
    int base = chosenFrame * PAGE_SIZE;
    for (int i = 0; i < PAGE_SIZE; ++i) {
        // store lower 8 bits of "logical address" as the data
        std::uint16_t logicalAddr = static_cast<std::uint16_t>(pageNumber * PAGE_SIZE + i);
        physicalMemory[base + i] = static_cast<std::uint8_t>(logicalAddr & 0xFF);
    }

    // Update page table
    pageTable[pageNumber].valid      = true;
    pageTable[pageNumber].frameNumber = chosenFrame;
    pageTable[pageNumber].dirty      = false;

    cout << "[VM] Page fault: loaded page " << pageNumber
         << " into frame " << chosenFrame << ".\n";
}

std::uint8_t VirtualMemory::readByte(std::uint16_t logicalAddress, bool &pageFault) {
    int physicalAddress = translate(logicalAddress, pageFault);
    return physicalMemory[physicalAddress];
}

void VirtualMemory::writeByte(std::uint16_t logicalAddress,
                              std::uint8_t value,
                              bool &pageFault) {
    int physicalAddress = translate(logicalAddress, pageFault);
    physicalMemory[physicalAddress] = value;

    int page = logicalAddress / PAGE_SIZE;
    if (page >= 0 && page < NUM_PAGES) {
        pageTable[page].dirty = true;
    }
}

void VirtualMemory::printStats() const {
    cout << "\n=== Virtual Memory Statistics ===\n";
    cout << "Total memory accesses : " << totalAccesses << "\n";
    cout << "Total page faults     : " << totalPageFaults << "\n";
    if (totalAccesses > 0) {
        double rate = static_cast<double>(totalPageFaults) / totalAccesses;
        cout << "Page fault rate       : " << rate * 100.0 << " %\n";
    }
}

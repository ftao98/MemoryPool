/* ***********************************************
MYID   : Chen Fan
LANG   : G++
PROG   : MEMORYPOOL_CPP
************************************************ */

#include <iostream>

#include "memorypool.h"

MemoryPool::MemoryPool()
{
    int blocksize = MIN_BLOCK_SIZE;
    for (int i=0;i<INIT_LISTS;++i)
    {
        bllist_.push_back(new BlockList(blocksize));
        blocksize <<= 1;
    }
}

MemoryPool::~MemoryPool()
{
    for (auto i:bllist_)
    {
        delete i;
    }
}

MemBlock* MemoryPool::malloc(int size)
{
    size = (size - 1) / MIN_BLOCK_SIZE;
    int count = 0;
    while (size)
    {
        ++count;
        if (count == bllist_.size())
        {
            bllist_.push_back(new BlockList(bllist_[count-1]->blocksize()*2));
        }
        size /= 2;
    }
    return bllist_[count]->malloc();
}

void MemoryPool::travel()
{
    std::cout << "============\n";
    for (auto i:bllist_)
    {
        std::cout << "Size: " << i->blocksize() << " " << i->inuse << "/" << i->total() << "\n";
    }
    std::cout << "============\n";
}
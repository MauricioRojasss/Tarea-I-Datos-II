#include "PagedArray.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

PagedArray::PagedArray(const std::string& path, size_t numIntegers, size_t maxPages)
    : pageSize(1024), numPages((numIntegers + pageSize - 1) / pageSize), numPageFaults(0), numPageHits(0) {
    pages.resize(maxPages);
    filePath = path;
    file.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Error al abrir el archivo " << path << std::endl;
        exit(1);
    }
}

PagedArray::~PagedArray() {
    for (auto& page : pages) {
        if (page.dirty) {
            savePage(page.pageIndex);
        }
        delete[] page.data;
    }
    file.close();
}

void PagedArray::loadPage(size_t pageIndex) {
    if (pageTable.find(pageIndex) != pageTable.end()) {
        numPageHits++;
        return;
    }

    numPageFaults++;

    if (pageTable.size() == pages.size()) {
        size_t indexToReplace = rand() % pages.size();
        if (pages[indexToReplace].dirty) {
            savePage(pages[indexToReplace].pageIndex);
        }
        delete[] pages[indexToReplace].data;
        pageTable.erase(pages[indexToReplace].pageIndex);
        pages[indexToReplace] = Page(nullptr, 0, false);
    }

    int* data = new int[pageSize];
    file.seekg(pageIndex * pageSize * sizeof(int), std::ios::beg);
    file.read(reinterpret_cast<char*>(data), pageSize * sizeof(int));

    size_t freeIndex = 0;
    while (pages[freeIndex].data != nullptr) freeIndex++;
    pages[freeIndex] = Page(data, pageIndex, false);
    pageTable[pageIndex] = freeIndex;
}

void PagedArray::savePage(size_t pageIndex) {
    if (pageTable.find(pageIndex) == pageTable.end()) return;

    size_t index = pageTable[pageIndex];
    file.seekp(pageIndex * pageSize * sizeof(int), std::ios::beg);
    file.write(reinterpret_cast<char*>(pages[index].data), pageSize * sizeof(int));
    pages[index].dirty = false;
}

int& PagedArray::operator[](size_t index) {
    size_t pageIndex = index / pageSize;
    size_t offset = index % pageSize;

    loadPage(pageIndex);

    size_t memoryIndex = pageTable[pageIndex];
    pages[memoryIndex].dirty = true;

    return pages[memoryIndex].data[offset];
}

#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <vector>
#include <unordered_map>
#include <fstream>

class PagedArray {
private:
    struct Page {
        int* data;
        size_t pageIndex;
        bool dirty;

        Page(int* d = nullptr, size_t index = 0, bool isDirty = false)
            : data(d), pageIndex(index), dirty(isDirty) {}
    };

    size_t pageSize; // Número de enteros por página
    size_t numPages; // Número total de páginas en el archivo
    std::vector<Page> pages; // Páginas en memoria
    std::unordered_map<size_t, size_t> pageTable; // Mapea índices de página a índices de vector
    std::fstream file; // Archivo binario que se está ordenando
    std::string filePath;
    size_t numPageFaults;
    size_t numPageHits;

    void loadPage(size_t pageIndex);
    void savePage(size_t pageIndex);

public:
    PagedArray(const std::string& path, size_t numIntegers, size_t maxPages = 4);
    ~PagedArray();
    int& operator[](size_t index);
    size_t getPageFaults() const { return numPageFaults; }
    size_t getPageHits() const { return numPageHits; }
};

#endif

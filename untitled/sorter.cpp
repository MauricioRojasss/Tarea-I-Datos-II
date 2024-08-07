#include <iostream>
#include <fstream>
#include <cstring>
#include "PagedArray.h"

using namespace std;

int partition(PagedArray& arr, int start, int end) {
    int pivot = arr[end];
    int pIndex = start;

    for (int i = start; i < end; ++i) {
        if (arr[i] <= pivot) {
            swap(arr[i], arr[pIndex]);
            pIndex++;
        }
    }

    swap(arr[pIndex], arr[end]);
    return pIndex;
}

void quicksort(PagedArray& arr, int start, int end) {
    if (start < end) {
        int pivot = partition(arr, start, end);
        quicksort(arr, start, pivot - 1);
        quicksort(arr, pivot + 1, end);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        cerr << "Uso: sorter -input <INPUT FILE PATH> -output <OUTPUT FILE PATH> -alg <ALGORITMO>" << endl;
        return 1;
    }

    string inputPath = argv[2];
    string outputPath = argv[4];
    string algorithm = argv[6];

    // Copiar archivo de entrada a salida
    ifstream src(inputPath, ios::binary);
    ofstream dst(outputPath, ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();

    // Obtener el tamaño del archivo para calcular el número de enteros
    ifstream inFile(outputPath, ios::binary | ios::ate);
    size_t numIntegers = inFile.tellg() / sizeof(int);
    inFile.close();

    PagedArray arr(outputPath, numIntegers);

    // Ejecutar el algoritmo de ordenamiento
    if (algorithm == "QS") {
        quicksort(arr, 0, numIntegers - 1);
    } else {
        cerr << "Algoritmo no soportado: " << algorithm << endl;
        return 1;
    }

    cout << "Page Faults: " << arr.getPageFaults() << endl;
    cout << "Page Hits: " << arr.getPageHits() << endl;

    return 0;
}

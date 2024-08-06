#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#define SMALL_SIZE 512 * 1024 * 1024 // 512 MB
#define MEDIUM_SIZE 1024 * 1024 * 1024 // 1 GB
#define LARGE_SIZE 2 * 1024 * 1024 * 1024 // 2 GB

void generateFile(const std::string& outputPath, size_t size) {
    std::ofstream outFile(outputPath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return;
    }

    size_t numIntegers = size / sizeof(int);
    for (size_t i = 0; i < numIntegers; ++i) {
        int randomNumber = rand();
        outFile.write(reinterpret_cast<const char*>(&randomNumber), sizeof(int));
    }

    outFile.close();
    std::cout << "Archivo generado exitosamente: " << outputPath << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Uso: generator -size <SIZE> -output <OUTPUT FILE PATH>" << std::endl;
        return 1;
    }

    std::string sizeStr = argv[2];
    std::string outputPath = argv[4];
    size_t size;

    if (sizeStr == "SMALL") {
        size = SMALL_SIZE;
    } else if (sizeStr == "MEDIUM") {
        size = MEDIUM_SIZE;
    } else if (sizeStr == "LARGE") {
        size = LARGE_SIZE;
    } else {
        std::cerr << "Tamaño desconocido: " << sizeStr << std::endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(nullptr))); // Inicializar semilla

    generateFile(outputPath, size);

    return 0;
}

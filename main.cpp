#include <cstring>
#include <fstream>
#include <iostream>

#include "scripting.h"

// TODO: monte-carlo with better PDF
// TODO: write another data-oriented, lower-level version

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cerr << "No script specified.\n";
        return 1;
    }
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--")) {
            std::cerr << "Executing stdin.\n";
            if (!execute_script(std::cin)) {
                std::cerr << "Execution failed.\n";
            }
        } else {
            std::ifstream st(argv[i]);
            if (!st) {
                std::cerr << "Failed to open file " << argv[i] << ".\n";
                return 2;
            }
            std::cerr << "Executing " << argv[i] << ".\n";
            if (!execute_script(st)) {
                std::cerr << "Execution failed.\n";
            }
        }
    }
}

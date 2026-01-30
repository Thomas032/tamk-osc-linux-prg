#include <iostream>

int main(int argc, char* argv[]) {
    int words = argc-1;
    
    std::cout << "Number of command line arguments: " << words << std::endl;
    std::cout << "And they are: " << std::endl;

    for (int i = 0; i < words; i++) {
        std::cout << "\t" << argv[i+1] << std::endl;
    }

    return 0;
}
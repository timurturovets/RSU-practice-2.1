#include <cstring>
#include "task1.h"
#include "itask.h"

class task1 : public itask {
    void run() override {
        char key[BUFSIZ], input_file_path[BUFSIZ], output_file_path[BUFSIZ];

        std::cout << "Enter key: ";
        std::cin >> key;

        std::cout << "Enter input file path: ";
        std::cin >> input_file_path;

        std::cout << "Enter output file path: ";
        std::cin >> output_file_path;

        auto enc = new encoder(reinterpret_cast<unsigned char *>(key), sizeof(key)/sizeof(key[0]));
        std::cout << "0. Exit" << std::endl << "1. Encode a file" << std::endl << "2. Decode a file";
        std::cout << std::endl << "3. Change key";
        int choice;
        do {
            std::cout << std::endl << "Choose option: ";
            std::cin >> choice;

            if (choice == 3) {
                try {
                    unsigned char new_key[BUFSIZ];
                    std::cout << "Enter new key: ";
                    std::cin >> new_key;
                    enc->set_key(new_key, sizeof(new_key) / sizeof(new_key[0]));
                } catch (...) {
                    throw;
                }
            } else {
                try {
                    enc->encode(input_file_path, output_file_path, choice == 2);
                    std::cout << "Success!" << std::endl;
                } catch (std::ifstream::failure const &e) {
                    std::cerr << "ifstream failure: " << e.what() << std::endl;
                    throw;
                } catch (std::ofstream::failure const &e) {
                    std::cerr << "ofstream failure: " << e.what() << std::endl;
                    throw;
                }
            }
        } while(choice != 0);

        std::cout << "Bye!" << std::endl;
    }
};
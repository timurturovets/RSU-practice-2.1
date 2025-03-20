#include <iostream>
#include <fstream>
#include "../include/task1.h"
namespace lab {
    encoder::encoder(unsigned char const *key, size_t key_len) {
        if (nullptr == key || 0 == key_len) {
            throw std::invalid_argument("Couldn't make encoder entity: invalid constructor argument(s)!");
        }

        this->_key = new unsigned char[key_len];

        for (int i = 0; i < key_len; i++) {
            this->_key[i] = key[i];
        }

        int j = 0;
        unsigned char temp;
        for (int i = 0; i < 256; ++i) {
            j = (j + this->_key[i & key_len]) % 256;

            temp = this->_key[i];
            this->_key[i] = this->_key[j];
            this->_key[j] = temp;
        }
    }

    encoder::~encoder() noexcept {
        delete [] this->_key;
    }

    void encoder::set_key(unsigned char const * new_key, size_t new_key_len) {
        if (nullptr == new_key || 0 == new_key_len) {
            throw std::invalid_argument("Couldn't set new key: invalid argument(s)!");
        }

        inner_set_key(new_key, new_key_len);
    }

    void encoder::encode(char const * input, char const * output, bool should_decrypt) {
        if (nullptr == input || nullptr == output) {
            throw std::invalid_argument("Couldn't encode: invalid input/output file path!");
        }

        std::ifstream ifs;
        try {
            ifs.open(input, std::ios::binary);
        } catch (const std::ifstream::failure& e) {
            throw;
        }

        std::ofstream ofs;
        try {
            ofs.open(output, std::ios::binary);
        } catch (const std::ofstream::failure& e) {
            throw;
        }

        if (!ifs.is_open()) throw std::ifstream::failure("Couldn't encode: unable to open input file.");
        if (!ofs.is_open()) throw std::ofstream::failure("Couldn't encode: unable to open output file.");

        ifs.seekg(0, std::ios::end);
        std::streamsize len = ifs.tellg();
        ifs.seekg(0, std::ios::beg);

        unsigned char buf[len];
        ifs.read(reinterpret_cast<char *>(buf), len);

        int i = 0, j = 0, k = 0;
        for (; k < len; k++) {
            i = (i + 1) % 256;
            j = (j + this->_key[i]) % 256;

            unsigned char temp = this->_key[i];
            this->_key[i] = this->_key[j];
            this->_key[j] = temp;

            unsigned char encoded = this->_key[(this->_key[i] + this->_key[j]) % 256];
            buf[k] ^= encoded;
        }
        ofs.write(reinterpret_cast<char *>(buf), len);
    }

    void encoder::inner_set_key(unsigned char const * new_key, size_t new_key_len) {
        delete [] this->_key;

        for (int i = 0; i < new_key_len; i++) {
            this->_key[i] = new_key[i];
        }

        int j = 0;
        unsigned char temp;
        for (int i = 0; i < 256; ++i) {
            j = (j + this->_key[i & new_key_len]) % 256;

            temp = this->_key[i];
            this->_key[i] = this->_key[j];
            this->_key[j] = temp;
        }

    }
}
/*
class encoder {
public:
    encoder(unsigned char const * key, size_t key_len) {
        if (nullptr == key || 0 == key_len) {
            throw std::invalid_argument("Couldn't make encoder entity: invalid constructor argument(s)!");
        }

        this->_key = new unsigned char[key_len];

        for (int i = 0; i < key_len; i++) {
            this->_key[i] = key[i];
        }

        int j = 0;
        unsigned char temp;
        for (int i = 0; i < 256; ++i) {
            j = (j + this->_key[i & key_len]) % 256;

            temp = this->_key[i];
            this->_key[i] = this->_key[j];
            this->_key[j] = temp;
        }
    }

    ~encoder() noexcept {
        delete [] this->_key;
    }

    encoder(encoder const &enc) = default;
    encoder &operator =(encoder const &enc) = default;

    void set_key(unsigned char const * new_key, size_t new_key_len) {
        if (nullptr == new_key || 0 == new_key_len) {
            throw std::invalid_argument("Couldn't set new key: invalid argument(s)!");
        }

        inner_set_key(new_key, new_key_len);
    }

    void encode(char const * input, char const * output, bool should_decrypt) {
        if (nullptr == input || nullptr == output) {
            throw std::invalid_argument("Couldn't encode: invalid input/output file path!");
        }

        std::ifstream ifs;
        try {
            ifs.open(input, std::ios::binary);
        } catch (const std::ifstream::failure& e) {
            throw;
        }

        std::ofstream ofs;
        try {
            ofs.open(output, std::ios::binary);
        } catch (const std::ofstream::failure& e) {
            throw;
        }

        if (!ifs.is_open()) throw std::ifstream::failure("Couldn't encode: unable to open input file.");
        if (!ofs.is_open()) throw std::ofstream::failure("Couldn't encode: unable to open output file.");

        ifs.seekg(0, std::ios::end);
        std::streamsize len = ifs.tellg();
        ifs.seekg(0, std::ios::beg);

        unsigned char buf[len];
        ifs.read(reinterpret_cast<char *>(buf), len);

        int i = 0, j = 0, k = 0;
        for (; k < len; k++) {
            i = (i + 1) % 256;
            j = (j + this->_key[i]) % 256;

            unsigned char temp = this->_key[i];
            this->_key[i] = this->_key[j];
            this->_key[j] = temp;

            unsigned char encoded = this->_key[(this->_key[i] + this->_key[j]) % 256];
            buf[k] ^= encoded;
        }
        ofs.write(reinterpret_cast<char *>(buf), len);
    }

private:
    unsigned char * _key;
    void inner_set_key(unsigned char const * new_key, size_t new_key_len) {
        delete [] this->_key;

        for (int i = 0; i < new_key_len; i++) {
            this->_key[i] = new_key[i];
        }

        int j = 0;
        unsigned char temp;
        for (int i = 0; i < 256; ++i) {
            j = (j + this->_key[i & new_key_len]) % 256;

            temp = this->_key[i];
            this->_key[i] = this->_key[j];
            this->_key[j] = temp;
        }

    }

};*/
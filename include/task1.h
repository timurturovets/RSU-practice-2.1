#include <iostream>
#include <fstream>

namespace lab {
    class encoder {
    public:
        encoder(unsigned char const * key, size_t key_len);

        ~encoder() noexcept;

        encoder(encoder const &enc) = default;
        encoder &operator =(encoder const &enc) = default;

        void set_key(unsigned char const * new_key, size_t new_key_len);

        void encode(char const * input, char const * output, bool should_decrypt);

    private:
        unsigned char * _key;
        void inner_set_key(unsigned char const * new_key, size_t new_key_len);
    };
}
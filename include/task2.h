#include <cstdlib>
#include <stdexcept>
namespace lab {
    class logical_values_array {
    public:
        ~logical_values_array() noexcept = default;
        logical_values_array(logical_values_array const &lva) = default;
        logical_values_array &operator=(logical_values_array const &lva) = default;

        explicit logical_values_array(unsigned int value);

        static bool equals(logical_values_array &lva1, logical_values_array &lva2);

        [[nodiscard]] bool get_bit(size_t pos) const;

        bool operator[](size_t pos) const;

        logical_values_array operator~() const;

        logical_values_array operator&(logical_values_array const &lva) const;

        logical_values_array operator|(logical_values_array const &lva) const;

        logical_values_array operator^(logical_values_array const &lva) const;

        [[nodiscard]] logical_values_array implicate(logical_values_array const &lva) const;

        [[nodiscard]] logical_values_array coimplicate(logical_values_array const &lva) const;

        [[nodiscard]] logical_values_array equate(logical_values_array const &lva) const;

        [[nodiscard]] logical_values_array Pierce_arrow(logical_values_array const &lva) const;

        [[nodiscard]] logical_values_array Sheffer_stroke(logical_values_array const &lva) const;

        void to_string(char *dest) const;

    private:
        unsigned int _value;
    };
}
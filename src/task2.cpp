#include "../include/task2.h"

namespace lab {
    logical_values_array::logical_values_array(unsigned int value) {
        this->_value = value;
    }

    bool logical_values_array::equals(logical_values_array &lva1, logical_values_array &lva2) {
        return lva1._value == lva2._value;
    }

    [[nodiscard]] bool logical_values_array::get_bit(size_t pos) const {
        return (this->_value >> pos) & 1;
    }

    bool logical_values_array::operator[](size_t pos) const {
        return get_bit(pos);
    }

    logical_values_array logical_values_array::operator~() const {
        return logical_values_array(~this->_value);
    }

    logical_values_array logical_values_array::operator&(logical_values_array const &lva) const {
        return logical_values_array(_value & lva._value);
    }

    logical_values_array logical_values_array::operator|(logical_values_array const &lva) const {
        return logical_values_array(_value | lva._value);
    }

    logical_values_array logical_values_array::operator^(logical_values_array const &lva) const {
        return logical_values_array(_value ^ lva._value);
    }

    [[nodiscard]] logical_values_array logical_values_array::implicate(logical_values_array const &lva) const {
        return logical_values_array(~_value | lva._value);
    }

    [[nodiscard]] logical_values_array logical_values_array::coimplicate(logical_values_array const &lva) const {
        return logical_values_array(_value | ~lva._value);
    }

    [[nodiscard]] logical_values_array logical_values_array::equate(logical_values_array const &lva) const {
        return logical_values_array(~(_value ^ lva._value));
    }

    [[nodiscard]] logical_values_array logical_values_array::Pierce_arrow(logical_values_array const &lva) const {
        return logical_values_array(~(_value | lva._value));
    }

    [[nodiscard]] logical_values_array logical_values_array::Sheffer_stroke(logical_values_array const &lva) const {
        return logical_values_array(~(_value & lva._value));
    }

    void logical_values_array::to_string(char *dest) const {
        if (nullptr == dest) throw std::invalid_argument("Couldn't convert to string: destination pointer is null");
        for (int i = 31; i >= 0; i--) {
            *dest++ = ((_value >> i) & 1) ? '1' : '0';
        }
        *dest = '\0';
    }
}
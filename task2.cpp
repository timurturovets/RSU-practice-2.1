#pragma once
#include <iostream>
#include "itask.h"
#include "task2.h"

class task2 : public itask {
    void run() override {
        unsigned int val1, val2;

        std::cout << "Enter first number: ";
        std::cin >> val1;

        std::cout << "Enter second number: ";
        std::cin >> val2;

        logical_values_array lva1(val1), lva2(val2);

        auto lva3 = ~lva1;
        auto lva4 = lva1 & lva2;
        auto lva5 = lva1 | lva2;
        auto lva6 = lva1.coimplicate(lva2);
        auto lva7 = lva1.pierce_arrow(lva2);
        auto lva8 = lva1.sheffer_stroke(lva2);

        char lva1_str[32], lva2_str[32], buf[32];
        lva1.to_string(lva1_str);
        lva2.to_string(lva2_str);

        std::cout << "Operation\tResult" << std::endl << "------------------------------------------------" << std::endl;

        lva3.to_string(buf);
        std::cout << "Inversion\t" << buf << std::endl;

        lva4.to_string(buf);
        std::cout << "Logical AND\t" << buf << std::endl;

        lva5.to_string(buf);
        std::cout << "Logical OR\t" << buf << std::endl;

        lva6.to_string(buf);
        std::cout << "Coimplication\t" << buf << std::endl;

        lva7.to_string(buf);
        std::cout << "Pierce arrow\t" << buf << std::endl;

        lva8.to_string(buf);
        std::cout << "Sheffer stroke\t" << buf << std::endl;
    }
};
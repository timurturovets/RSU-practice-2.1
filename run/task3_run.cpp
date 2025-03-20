#include <iostream>
#include "../include/itask.h"
#include "../include/task3.h"
namespace lab {
    class task3 : public itask {
        void run() override {
            complex_num cn1(2.5, 0.5);
            complex_num cn2(2.28, 5.2);

            std::cout << "First complex number: " << cn1 << std::endl;
            std::cout << "Second complex number: " << cn2 << std::endl;

            std::cout << "cn1 + cn2 = " << cn1 + cn2 << std::endl;
            std::cout << "cn1 - cn2 = " << cn1 - cn2 << std::endl;
            std::cout << "cn1 * cn2 = " << cn1 * cn2 << std::endl;
            std::cout << "cn1 / cn2 = " << cn1 / cn2 << std::endl;

            std::cout << "cn1 absolute value before changing: " << cn1.abs() << std::endl;
            cn1 += cn2;
            std::cout << "cn1 absolute value after changing: " << cn1.abs() << std::endl;

            std::cout << "cn1 argument: " << cn1.arg() << std::endl;

            std::cout << "Success!" << std::endl;
        }
    };
}
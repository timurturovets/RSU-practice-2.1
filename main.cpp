#include <iostream>
#include <malloc.h>
#include "task1.cpp"

int main() {
    auto key = (unsigned char const *) malloc(sizeof(unsigned char const) * 5);
    encoder entity(key, 4);
}
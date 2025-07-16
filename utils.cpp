#include "utils.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

void insecure_function(const std::string& input) {
    char buf[64];
    sprintf(buf, input.c_str()); // format string vulnerability
    std::cout << "Echo: " << buf << std::endl;
}

void simulate_double_free() {
    char* ptr = (char*)malloc(128);
    strcpy(ptr, "Sensitive data");
    free(ptr);
    free(ptr); // double free
}

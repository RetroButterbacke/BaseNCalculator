#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>

std::string binMode(long input) {
    std::string output = "";
    for (int bit = 0; bit < 64; bit++) {
        if (std::pow(2, bit) > input) {
            for (int bitlength = bit - 1; bitlength >= 0; bitlength--) {
                if (std::pow(2, bitlength) <= input) {
                    output.append("1");
                    input -= std::pow(2, bitlength);
                } else {
                    output.append("0");
                }
            }
            break;
        }
    }
    return output;
}

long decMode(std::string input) {
    long output = 0;
    for (int bit = 0; bit < static_cast<int>(input.size()); bit++) {
        if (input.at(bit) == '1') {
            output += std::pow(2, input.size() - (bit + 1));
        }
    }
    return output;
}



int main() {
    printf("Please enter the mode you want to use <bin|dec|help>: ");
    std::string in;
    std::cin >> in;
    check:
        std::string input;
        if (in == "dec") {
            printf ("Please enter your number: ");
            dec:
            std::cin >> input;
            // Checks if input is a number elsewise asks again
            if (!std::isdigit(input[0])) {
                printf("Please use a number this calculator can't calculate strings: ");
                goto dec;
            }
            long out = decMode(input);
            printf("The result equals: %ld\n", out);
        } else if (in == "bin") {
            printf ("Please enter your number: ");
            bin:
            std::cin >> input;
            // Checks if input is a number elsewise asks again
            if (!std::isdigit(input[0])) {
                printf("Please use a number this calculator can't calculate strings: ");
                goto bin;
            }
            std::string out = binMode(std::stol(input));
            printf("The result equals: %s\n", out.c_str());
        } else if (in == "help") {
            printf("bin:\nInput: Decimal number -> Output: Binary number\ndec:\nInput: Binary number -> Output: Decimal number\n");
        } else {
            // If Input isn't an option the programm asks you to use one of the options
            printf("This isn't a mode for this calculator please use dec or bin: ");
            std::cin >> in;
            goto check;
        }
    return 0;
}
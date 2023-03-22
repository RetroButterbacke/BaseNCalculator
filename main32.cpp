#include <stdio.h>
#include <iostream>
#include <string>
#include <cmath>

std::string binMode(long input) {
    std::string output = "";
    for (int bit = 0; bit < 32; bit++) {
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

std::string octMode(long input) {
    std::string output = "";
    for (int pos = 0; pos < 20; pos++) {
        if (std::pow(8, pos) > input) {
            for (int octlength = pos - 1;  octlength >= 0; octlength--) {
                if (std::pow(8, octlength) <= input) {
                    int factor = input / std::pow(8, octlength);
                    output.append(std::to_string(factor));
                    input -= std::pow(8, octlength) * factor;
                } else {
                    output.append("0");
                }
            }
            break;
        }
    }
    return output;
}

std::string hexMode(long input) {
    std::string output = "0x";
    for (int pos = 0; pos < 16; pos++) {
        if (std::pow(16, pos) > input) {
            for (int hexlength = pos - 1; hexlength >= 0; hexlength--) {
                if (std::pow(16, hexlength) <= input) {
                    int factor = input / std::pow(16, hexlength);
                    if (factor < 10) {
                        output.append(std::to_string(factor));
                    } else {
                        switch(factor) {
                            case 10:
                                output.append("A");
                                break;
                            case 11:
                                output.append("B");
                                break;
                            case 12:
                                output.append("C");
                                break;
                            case 13:
                                output.append("D");
                                break;
                            case 14:
                                output.append("E");
                                break;
                            case 15:
                                output.append("F");
                                break;
                        }
                    }
                    input -= std::pow(16, hexlength) * factor;
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
    if (input[1] == 'x') {
        input = input.substr(2, 'x');
        int pos = static_cast<int>(input.length()) - 1;
            for (int length = 0; length < static_cast<int>(input.length()); length++) {
                if (static_cast<char>(input.c_str()[pos]) == 'A') {
                    output += std::pow(16, length) * 10;
                } else if (static_cast<char>(input.c_str()[pos]) == 'b') {
                    output += std::pow(16, length) * 11;
                } else if (static_cast<char>(input.c_str()[pos]) == 'c') {
                    output += std::pow(16, length) * 12;
                } else if (static_cast<char>(input.c_str()[pos]) == 'D') {
                    output += std::pow(16, length) * 13;
                } else if (static_cast<char>(input.c_str()[pos]) == 'E') {
                    output += std::pow(16, length) * 14;
                } else if (static_cast<char>(input.c_str()[pos]) == 'F') {
                    output += std::pow(16, length) * 15;
                } else {
                    output += std::pow(16, length) * (static_cast<int>(input.c_str()[pos]) - '0');
                }
                pos--;
            }
    } else {
        printf("Please enter the base in which this number was written in <oct|bin>: ");
        std::string in;
        std::cin >> in;
        if (in == "oct") {
            int pos = static_cast<int>(input.length()) - 1;
            for (int length = 0; length < static_cast<int>(input.length()); length++) {
                output += std::pow(8, length) * (static_cast<int>(input.c_str()[pos]) - '0');
                pos--;
            }
        } else if (in == "bin") {
            for (int bit = static_cast<int>(input.length()); bit > 0; bit--) {
                if (input.c_str()[bit - 1] == '1') {
                    output += std::pow(2, bit);
                }
            }
        } else {
            printf("Please use a mode from the list <oct|bin>: ");
        }
    }
    return output;
}



int main() {
    printf("Please enter the mode you want to use <bin|oct|dec|hex|help>: ");
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
        } else if (in == "hex") {
            printf ("Please enter your number: ");
            hex:
                std::cin >> input;
                if (!std::isdigit(input[0])) {
                    printf("Please use a number this calculator can't calculate strings: ");
                    goto hex;
                }
                std::string out = hexMode(std::stol(input));
                printf("The result is: %s\n", out.c_str());
        } else if (in == "oct") {
            printf ("Please enter your number: ");
            oct:
                std::cin >> input;
                if (!std::isdigit(input[0])) {
                    printf("Please use a number this calculator can't calculate strings: ");
                    goto oct;
                }
                std::string out = octMode(std::stol(input));
                printf("The result is: %s\n", out.c_str());
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
            printf("This isn't a mode for this calculator please use <bin|oct|dec|hex|help>: ");
            std::cin >> in;
            goto check;
        }
    return 0;
}
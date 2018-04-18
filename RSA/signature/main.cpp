#include <iostream>
#include <gmpxx.h>
#include <string>
#include <fstream>

mpz_class powm(mpz_class base, mpz_class power, mpz_class module) {
    mpz_class result = 1;
    mpz_class curr_exp = base;
    std::string binary_power = power.get_str(2);
    for (int i = binary_power.size() - 1; i >= 0; --i) {
        if (binary_power[i] == '1') {
            result = (result * curr_exp) % module;
        }
        curr_exp = (curr_exp * curr_exp) % module;
    }
    return result;
};


int main(int argc, char** argv) {
    if (argc != 6) {
        std::cout << "Wrong arguments number!" << std::endl;
    }
    mpz_class d(argv[1]);
    mpz_class n(argv[2]);
    mpz_class e(argv[3]);
    mpz_class x(argv[4]);
    mpz_class sign(argv[5]);

    std::cout << (powm(sign, e, n) == x) << std::endl;

    return 0;
}

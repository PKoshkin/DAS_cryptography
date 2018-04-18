#include <iostream>
#include <gmpxx.h>
#include <string>
#include <fstream>

mpz_class decrypt(mpz_class ciphertext, mpz_class d, mpz_class n) {
    mpz_class message = 1;
    mpz_class curr_exp = ciphertext;
    std::string binary_d = d.get_str(2);
    for (int i = binary_d.size() - 1; i >= 0; --i) {
        if (binary_d[i] == '1') {
            message = (message * curr_exp) % n;
        }
        curr_exp = (curr_exp * curr_exp) % n;
    }
    return message;
};


int main(int argc, char** argv) {
    if (argc != 5) {
        std::cout << "Wrong arguments number!" << std::endl;
    }
    mpz_class ciphertext(argv[1]);
    mpz_class d(argv[2]);
    mpz_class n(argv[3]);
    std::string filename(argv[4]);
    mpz_class message = decrypt(ciphertext, d, n);
    std::string hex_str = message.get_str(16);

    std::string result = "";
    for (size_t i = 0; i < hex_str.size(); i += 2) {
        result += stoi(hex_str.substr(i, 2), 0, 16);
    }

    std::ofstream file;
    file.open(filename);
    file << result;
    file.close();

    return 0;
}

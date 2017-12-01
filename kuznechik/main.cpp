#include <iostream>
#include <string>
#include <utility>
#include <array>
#include <chrono>

#include "block.h"
#include "lsx.h"
#include "key.h"
#include "kuznechik.h"
#include "data.h"

int main(int argc, char** argv) {
    Data data("multiply_map.txt", "L_matrix.txt", "L_inverse_matrix.txt");
    if (argc == 5) {
        if (std::string(argv[1]) == "F") {
            Block c = block_from_string(argv[2]);
            Block k1 = block_from_string(argv[3]);
            Block k2 = block_from_string(argv[4]);
            auto result = F(c, k1, k2, data);
            std::cout << to_string(result.first) << std::endl;
            std::cout << to_string(result.second) << std::endl;
            return 0;
        } else {
            std::cout << "Wrong args format!" << std::endl;
            return 0;
        }
    } else if (argc == 4) {
        if (std::string(argv[1]) == "LSX") {
            Block input = block_from_string(argv[2]);
            Block key = block_from_string(argv[3]);
            Block result = LSX(key, input, data);
            std::cout << to_string(result) << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "X") {
            Block input = block_from_string(argv[2]);
            Block key = block_from_string(argv[3]);
            Block result = X(key, input);
            std::cout << to_string(result) << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "encrypt") {
            Key key = key_from_string(argv[2]);
            Block block = block_from_string(argv[3]);
            Block result = encrypt(key, block, data);
            std::cout << to_string(result) << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "encrypt_time") {
            Key key = key_from_string(argv[2]);
            Block block = block_from_string(argv[3]);
            auto start = std::chrono::system_clock::now();
            Block result = encrypt(key, block, data);
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout << diff.count() << std::endl; // time in seconds
            return 0;
        } else if (std::string(argv[1]) == "decrypt") {
            Key key = key_from_string(argv[2]);
            Block block = block_from_string(argv[3]);
            Block result = decrypt(key, block, data);
            std::cout << to_string(result) << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "decrypt_time") {
            Key key = key_from_string(argv[2]);
            Block block = block_from_string(argv[3]);
            auto start = std::chrono::system_clock::now();
            Block result = decrypt(key, block, data);
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout << diff.count() << std::endl; // time in seconds
            return 0;
        } else if (std::string(argv[1]) == "multiply") {
            std::uint8_t a = atoi(argv[2]);
            std::uint8_t b = atoi(argv[3]);
            std::uint8_t result = multiply(a, b);
            std::cout << unsigned(result) << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "fast_multiply") {
            std::uint8_t a = atoi(argv[2]);
            std::uint8_t b = atoi(argv[3]);
            std::uint8_t result = fast_multiply(a, b, data);
            std::cout << unsigned(result) << std::endl;
            return 0;
        } else {
            std::cout << "Wrong args format!" << std::endl;
            return 0;
        }
    } else if (argc == 3) {
        if (std::string(argv[1]) == "R") {
            Block input = block_from_string(argv[2]);
            Block result = R(input, data);
            std::cout << to_string(result) << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "L") {
            Block input = block_from_string(argv[2]);
            Block result = L(input, data);
            std::cout << to_string(result) << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "L_inverse") {
            Block input = block_from_string(argv[2]);
            Block result = L_inverse(input, data);
            std::cout << to_string(result) << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "L_fast") {
            Block input = block_from_string(argv[2]);
            Block result = L_fast(input, data);
            std::cout << to_string(result) << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "S") {
            Block input = block_from_string(argv[2]);
            Block result = S(input);
            std::cout << to_string(result) << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "K") {
            Key a = key_from_string(argv[2]);
            std::array<Block, 10> keys = get_keys(a, data);
            for (std::size_t i = 0; i < 10; ++i) {
                std::cout << to_string(keys[i]) << std::endl;
            }
            return 0;
        } else {
            std::cout << "Wrong args format!" << std::endl;
            return 0;
        }
    } else if (argc == 2) {
        if (std::string(argv[1]) == "encrypt_speed") {
            Key key = key_from_string(std::string(256, '0'));
            Block block = block_from_string(std::string(128, '0'));
            auto start = std::chrono::system_clock::now();
            for (std::size_t i = 0; i < 64; ++i) {
                Block result = encrypt(key, block, data);
            }
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout << 1 / (diff.count() * 1024) << std::endl; // time in seconds
            return 0;
        } else if (std::string(argv[1]) == "decrypt_speed") {
            Key key = key_from_string(std::string(256, '0'));
            Block block = block_from_string(std::string(128, '0'));
            auto start = std::chrono::system_clock::now();
            for (std::size_t i = 0; i < 64; ++i) {
                Block result = decrypt(key, block, data);
            }
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout << 1 / (diff.count() * 1024) << std::endl; // time in seconds
            return 0;
        } else {
            std::cout << "Wrong args format!" << std::endl;
            return 0;
        }
    } else {
        std::cout << "Wrong arguments number!" << std::endl;
        return 0;
    }
}

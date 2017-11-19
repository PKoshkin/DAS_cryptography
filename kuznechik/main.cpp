#include <iostream>
#include <bitset>
#include <string>
#include <deque>
#include <utility>

#include "block.h"
#include "lsx.h"
#include "key.h"
#include "kuznechik.h"


int main(int argc, char** argv) {
    if (argc == 5) {
        if (std::string(argv[1]) == "F") {
            Block in_c(argv[2]);
            Block in_k1(argv[3]);
            Block in_k2(argv[4]);
            SplitedBlock c = split(in_c);
            SplitedBlock k1 = split(in_k1);
            SplitedBlock k2 = split(in_k2);
            auto result = F(c, k1, k2);
            std::cout << concatinate(result.first).to_string() << std::endl;
            std::cout << concatinate(result.second).to_string() << std::endl;
            return 0;
        } else {
            std::cout << "Wrong args format!" << std::endl;
            return 0;
        }
    } else if (argc == 4) {
        if (std::string(argv[1]) == "LSX") {
            Block input(argv[2]);
            Block key(argv[3]);
            SplitedBlock splited_input = split(input);
            SplitedBlock splited_key = split(key);
            SplitedBlock result = LSX(splited_key, splited_input);
            std::cout << concatinate(result).to_string() << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "X") {
            Block input(argv[2]);
            Block key(argv[3]);
            SplitedBlock splited_input = split(input);
            SplitedBlock splited_key = split(key);
            SplitedBlock result = X(splited_key, splited_input);
            std::cout << concatinate(result).to_string() << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "encrypt") {
            std::bitset<256> key(argv[2]);
            Block block(argv[3]);
            SplitedBlock splited_block = split(block);
            SplitedBlock result = encrypt(key, splited_block);
            std::cout << concatinate(result).to_string() << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "decrypt") {
            std::bitset<256> key(argv[2]);
            Block block(argv[3]);
            SplitedBlock splited_block = split(block);
            SplitedBlock result = decrypt(key, splited_block);
            std::cout << concatinate(result).to_string() << std::endl;
            return 0;
        } else {
            std::cout << "Wrong args format!" << std::endl;
            return 0;
        }
    } else if (argc == 3) {
        if (std::string(argv[1]) == "R") {
            Block input(argv[2]);
            SplitedBlock splited_input = split(input);
            SplitedBlock result = R(splited_input);
            std::cout << concatinate(result).to_string() << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "L") {
            Block input(argv[2]);
            SplitedBlock splited_input = split(input);
            SplitedBlock result = L(splited_input);
            std::cout << concatinate(result).to_string() << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "S") {
            Block input(argv[2]);
            SplitedBlock splited_input = split(input);
            SplitedBlock result = S(splited_input);
            std::cout << concatinate(result).to_string() << std::endl;
            return 0;
        } else if (std::string(argv[1]) == "K") {
            std::bitset<256> a(argv[2]);
            std::vector<SplitedBlock> keys = get_keys(a);
            assert(keys.size() == 10);
            for (std::size_t i = 0; i < keys.size(); ++i) {
                std::cout << concatinate(keys[i]).to_string() << std::endl;
            }
            return 0;
        } else {
            std::cout << "Wrong args format!" << std::endl;
            return 0;
        }
    } else if (argc == 2) {
        if (std::string(argv[1]) == "C") {
            auto constants = get_constants();
            for (std::size_t i = 0; i < constants.size(); ++i) {
                std::cout << concatinate(constants[i]).to_string() << std::endl;
            }
            return 0;
        }
    } else if (argc == 1) {
        std::bitset<128> key(std::string(128, '1'));
        std::bitset<128> block(std::string(128, '0'));
        auto splited_block = split(block);
        auto splited_key = split(key);
        std::cout << block.to_string() << std::endl;

        auto lsx = L(S(X(splited_key, splited_block)));
        std::bitset<128> result = concatinate(lsx);
        std::cout << result.to_string() << std::endl;

        auto splited_result = split(result);
        auto input = X(splited_key, S_inverse(L_inverse(splited_result)));
        std::bitset<128> input_block = concatinate(input);
        std::cout << input_block.to_string() << std::endl;
        return 0;
    } else {
        std::cout << "Wrong arguments number!" << std::endl;
        return 0;
    }
}

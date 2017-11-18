#include <iostream>
#include <bitset>
#include <string>
#include <deque>

#include "block.h"
#include "lsx.h"


int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Wrong args number!" << std::endl;
    } else {
        std::bitset<128> a(argv[2]);
        auto _a = get_parts(a);
        std::deque<std::bitset<8>> _res;
        if (std::string(argv[1]) == "R") {
            _res = R(_a);
        } else if (std::string(argv[1]) == "L") {
            _res = L(_a);
        } else {
            std::cout << "Wrong args format!" << std::endl;
        }
        std::cout << concatinate(_res) << std::endl;
    }


/* lsx test:
    std::bitset<128> key(std::string(128, '1'));
    std::bitset<128> block(std::string(128, '0'));
    auto splited_block = get_parts(block);
    auto splited_key = get_parts(key);
    std::cout << block.to_string() << std::endl;

    auto lsx = L(S(X(splited_key, splited_block)));
    std::bitset<128> result = concatinate(lsx);
    std::cout << result.to_string() << std::endl;

    auto splited_result = get_parts(result);
    auto input = X(splited_key, S_inverse(L_inverse(splited_result)));
    std::bitset<128> input_block = concatinate(input);
    std::cout << input_block.to_string() << std::endl;
*/
    return 0;
}

#include <chrono>
#include <cstring>
#include <iostream>
#include <cstdint>
#include <string>
#include <bitset>

#include "data.h"

const std::size_t NUMBER_OF_ROUNDS = 10;
const std::size_t BLOCK_LEN_IN_BYTES = 16;
const std::size_t KEY_LENGTH_IN_BYTES = 32;
const std::size_t NUMBER_OF_ROUNDS_IN_KEY_SCHEDULE = 8;


void block_from_string(const std::string& in_string, std::uint8_t* result, std::size_t size=16) {
    for (std::size_t i = 0; i < size; ++i) {
        result[i] = static_cast<std::uint8_t>(std::bitset<8>(in_string.substr(i * 8, 8)).to_ulong());
    }
}

std::string to_string(const std::uint8_t* in_block, std::size_t size=16) {
    std::string result;
    for (int i = 0; i < size; ++i) {
        result += std::bitset<8>(in_block[i]).to_string();
    }
    return result;
}


static void swap_blocks(std::uint8_t* left, std::uint8_t* right, std::uint8_t* tmp) {
    std::memcpy(tmp, left, BLOCK_LEN_IN_BYTES);
    std::memcpy(left, right, BLOCK_LEN_IN_BYTES);
    std::memcpy(right, tmp, BLOCK_LEN_IN_BYTES);
}


static void apply_S(std::uint8_t* block) {
    for (int byte_index = 0; byte_index < BLOCK_LEN_IN_BYTES; ++byte_index) {
        block[byte_index] = pi[block[byte_index]];
    }
}

static void do_L(const std::uint8_t* input, std::uint8_t* output) {
    for (int byte_index = 0; byte_index < BLOCK_LEN_IN_BYTES; ++byte_index) {
        std::uint8_t component = 0x00;
        for (int addend_index = 0; addend_index < BLOCK_LEN_IN_BYTES; ++addend_index) {
            component ^= multiply_map[L_matrix[addend_index][byte_index]][input[addend_index]];
        }
        output[byte_index] = component;
    }
}

static void do_X(const std::uint8_t* key, const std::uint8_t* input, std::uint8_t* output) {
    for (int i = 0; i < BLOCK_LEN_IN_BYTES; ++i) {
        output[i] = input[i] ^ key[i];
    }
}

static void apply_LSX(const std::uint8_t* key, std::uint8_t* block, std::uint8_t* tmp) {
    do_X(key, block, tmp);
    apply_S(tmp);
    do_L(tmp, block);
}


static void apply_F(
    const std::uint8_t* key, std::uint8_t* left, std::uint8_t* right,
    std::uint8_t* tmp1, std::uint8_t* tmp2
) {
    std::memcpy(tmp1, left, BLOCK_LEN_IN_BYTES);
    apply_LSX(key, tmp1, tmp2);
    do_X(tmp1, right, right);
    swap_blocks(left, right, tmp2);
}

static void do_round_keys(
    const std::uint8_t* key, std::uint8_t* round_keys,
    std::uint8_t* tmp1, std::uint8_t* tmp2
) {
    std::memcpy(round_keys, key, BLOCK_LEN_IN_BYTES * 2);
    for (int i = 1; i <= 4; ++i) {
        std::memcpy(
            &round_keys[BLOCK_LEN_IN_BYTES * (i * 2)],
            &round_keys[BLOCK_LEN_IN_BYTES * ((i - 1) * 2)],
            BLOCK_LEN_IN_BYTES * 2
        );
        for (int j = 8 * (i - 1) + 1; j <= 8 * (i - 1) + 8; ++j) {
            apply_F(
                 round_constants[(j - 1)],
                 &round_keys[BLOCK_LEN_IN_BYTES * (i * 2)],
                 &round_keys[BLOCK_LEN_IN_BYTES * (i * 2 + 1)],
                 tmp1,
                 tmp2
            );
        }
    }
}


static void encrypt(const std::uint8_t* key, std::uint8_t* block) {
    std::uint8_t cache[BLOCK_LEN_IN_BYTES * 2] = {0};
    std::uint8_t round_keys[BLOCK_LEN_IN_BYTES * NUMBER_OF_ROUNDS] = {0};
    do_round_keys(key, round_keys, &cache[0], &cache[BLOCK_LEN_IN_BYTES]);

    // Последний раунд не полный
    for (int round_index = 0; round_index < NUMBER_OF_ROUNDS - 1; ++round_index) {
        apply_LSX(&round_keys[BLOCK_LEN_IN_BYTES * round_index], block, cache);
    }
    do_X(&round_keys[BLOCK_LEN_IN_BYTES * (NUMBER_OF_ROUNDS - 1)], block, block);
}

int main(int argc, char** argv) {
    if (argc == 4) {
        if (std::string(argv[1]) == "encrypt") {
            std::uint8_t key[32] = {0};
            std::uint8_t block[16] = {0};
            block_from_string(std::string(argv[2]), key, 32);
            block_from_string(std::string(argv[3]), block);
            encrypt(key, block);
            std::cout << to_string(block) << std::endl;
            return 0;
        }
    } else if (argc == 2) {
        if (std::string(argv[1]) == "time") {
            std::uint8_t block[BLOCK_LEN_IN_BYTES] = {0};
            std::uint8_t key[BLOCK_LEN_IN_BYTES* 2] = {1};

            auto start = std::chrono::system_clock::now();
            for (std::size_t i = 0; i < 64 * 1024; ++i) {
                encrypt(key, block);
            }
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout << 1 / (diff.count() * 1) << std::endl; // Mb per second
            return 0;
        }
    }
    std::cout << "wrong arguments" << std::endl;
}

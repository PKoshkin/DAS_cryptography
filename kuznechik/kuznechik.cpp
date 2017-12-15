#include <chrono>
#include <cstring>
#include <iostream>
#include <cstdint>
#include <string>
#include <bitset>

#include "data.h"
#include "LS_matrix.h"

const std::size_t NUMBER_OF_ROUNDS = 10;
const std::size_t BLOCK_LEN_IN_BYTES = 16;
const std::size_t KEY_LENGTH_IN_BYTES = 32;
const std::size_t NUMBER_OF_ROUNDS_IN_KEY_SCHEDULE = 8;

typedef std::uint8_t Block[BLOCK_LEN_IN_BYTES];


static void apply_LS(Block block) {
    Block result = {0};
    for (std::uint8_t i = 0; i < BLOCK_LEN_IN_BYTES; ++i) {
        for (std::uint8_t j = 0; j < BLOCK_LEN_IN_BYTES; ++j) {
            result[j] ^= LS_matrix[i][block[i]][j];
        }
    }
    std::memcpy(block, result, BLOCK_LEN_IN_BYTES);
}

static void do_LS(const Block input, Block output) {
    for (int i = 0; i < BLOCK_LEN_IN_BYTES; ++i) {
        output[i] = 0x0;
    }
    for (std::uint8_t i = 0; i < BLOCK_LEN_IN_BYTES; ++i) {
        for (std::uint8_t j = 0; j < BLOCK_LEN_IN_BYTES; ++j) {
            output[j] ^= LS_matrix[i][input[i]][j];
        }
    }
}

static void block_from_string(const std::string& in_string, Block result, std::size_t size=BLOCK_LEN_IN_BYTES) {
    for (std::size_t i = 0; i < size; ++i) {
        result[i] = static_cast<std::uint8_t>(std::bitset<8>(in_string.substr(i * 8, 8)).to_ulong());
    }
}

static std::string to_string(const Block in_block, std::size_t size=BLOCK_LEN_IN_BYTES) {
    std::string result;
    for (int i = 0; i < size; ++i) {
        result += std::bitset<8>(in_block[i]).to_string();
    }
    return result;
}


static void swap_blocks(Block left, Block right, Block tmp) {
    std::memcpy(tmp, left, BLOCK_LEN_IN_BYTES);
    std::memcpy(left, right, BLOCK_LEN_IN_BYTES);
    std::memcpy(right, tmp, BLOCK_LEN_IN_BYTES);
}


static void apply_S(Block block) {
    for (int byte_index = 0; byte_index < BLOCK_LEN_IN_BYTES; ++byte_index) {
        block[byte_index] = pi[block[byte_index]];
    }
}

static void do_L(const Block input, Block output) {
    for (int byte_index = 0; byte_index < BLOCK_LEN_IN_BYTES; ++byte_index) {
        std::uint8_t component = 0x00;
        for (int addend_index = 0; addend_index < BLOCK_LEN_IN_BYTES; ++addend_index) {
            component ^= multiply_map[L_matrix[addend_index][byte_index]][input[addend_index]];
        }
        output[byte_index] = component;
    }
}

static void do_X(const Block key, const Block input, Block output) {
    for (int i = 0; i < BLOCK_LEN_IN_BYTES; ++i) {
        output[i] = input[i] ^ key[i];
    }
}

static void apply_X(const Block key, Block block) {
    for (int i = 0; i < BLOCK_LEN_IN_BYTES; ++i) {
        block[i] ^= key[i];
    }
}

static void apply_LSX(const Block key, Block block) {
    apply_X(key, block);
    apply_LS(block);
}

static void do_LSX(const Block key, Block input, Block output) {
    apply_X(key, input);
    do_LS(input, output);
}

static void apply_F(const Block key, Block left, Block right, Block tmp) {
    std::memcpy(tmp, left, BLOCK_LEN_IN_BYTES);
    apply_LSX(key, tmp);
    apply_X(tmp, right);
    swap_blocks(left, right, tmp);
}

static void do_round_keys(const Block key, std::uint8_t* round_keys, Block tmp) {
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
                 tmp
            );
        }
    }
}


static void apply_encrypt(const std::uint8_t* round_keys, Block block) {
    // Последний раунд не полный
    Block tmp = {0};
    for (int round_index = 0; round_index < NUMBER_OF_ROUNDS - 1; ++round_index) {
        if (round_index % 2 == 0) {
            do_LSX(&round_keys[BLOCK_LEN_IN_BYTES * round_index], block, tmp);
        } else {
            do_LSX(&round_keys[BLOCK_LEN_IN_BYTES * round_index], tmp, block);
        }
    }
    do_X(&round_keys[BLOCK_LEN_IN_BYTES * (NUMBER_OF_ROUNDS - 1)], tmp, block);
}


int main(int argc, char** argv) {
    if (argc == 4) {
        if (std::string(argv[1]) == "encrypt") {
            std::uint8_t key[BLOCK_LEN_IN_BYTES * 2] = {0};
            Block block = {0};
            block_from_string(std::string(argv[2]), key, BLOCK_LEN_IN_BYTES * 2);
            block_from_string(std::string(argv[3]), block);
            Block cache = {0};
            std::uint8_t round_keys[BLOCK_LEN_IN_BYTES * NUMBER_OF_ROUNDS] = {0};
            do_round_keys(key, round_keys, cache);
            apply_encrypt(round_keys, block);
            std::cout << to_string(block) << std::endl;
            return 0;
        }
    } else if (argc == 2) {
        if (std::string(argv[1]) == "time") {
            Block block = {0};
            std::uint8_t key[BLOCK_LEN_IN_BYTES * 2] = {1};
            Block cache = {0};
            std::uint8_t round_keys[BLOCK_LEN_IN_BYTES * NUMBER_OF_ROUNDS] = {0};
            do_round_keys(key, round_keys, cache);

            auto start = std::chrono::system_clock::now();
            for (std::size_t i = 0; i < 64 * 1024; ++i) {
                apply_encrypt(round_keys, block);
            }
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout << 1 / diff.count() << std::endl; // Mb per second
            return 0;
        }
    }
    std::cout << "wrong arguments" << std::endl;
}

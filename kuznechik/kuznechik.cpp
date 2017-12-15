#include <chrono>
#include <cstring>
#include <iostream>
#include <cstdint>
#include <string>
#include <bitset>

#include "data.h"
#include "LS_matrix.h"

const std::size_t ROUNDS_NUMBER = 10;
const std::size_t BLOCK_LEN_IN_BYTES = 16;
const std::size_t KEY_LEN_IN_BYTES = 32;
const std::size_t ROUNDS_IN_KEY_SCHEDULE_NUMBER = 8;

typedef std::uint8_t Block[BLOCK_LEN_IN_BYTES];
typedef std::uint8_t Key[KEY_LEN_IN_BYTES];


static void apply_LS(Block block) {
    Block result = {0};
    for (std::uint8_t i = 0; i < BLOCK_LEN_IN_BYTES; ++i) {
        for (std::uint8_t j = 0; j < BLOCK_LEN_IN_BYTES; ++j) {
            result[j] ^= LS_matrix[i][block[i]][j];
        }
    }
    std::memcpy(block, result, BLOCK_LEN_IN_BYTES);
}

static void block_from_string(const std::string& in_string, Block result, std::size_t size=BLOCK_LEN_IN_BYTES) {
    for (int i = 0; i < size; ++i) {
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

static void apply_X(const Block key, Block block) {
    for (int i = 0; i < BLOCK_LEN_IN_BYTES; ++i) {
        block[i] ^= key[i];
    }
}

static void apply_LSX(const Block key, Block block) {
    apply_X(key, block);
    apply_LS(block);
}

static void apply_F(const Block key, Block left, Block right) {
    Block tmp = {0};
    std::memcpy(tmp, left, BLOCK_LEN_IN_BYTES);
    apply_LSX(key, tmp);
    apply_X(tmp, right);
    swap_blocks(left, right, tmp);
}

static void do_round_keys(const Block key, Block round_keys[ROUNDS_NUMBER]) {
    std::memcpy(round_keys, key, BLOCK_LEN_IN_BYTES * 2);
    for (int i = 1; i <= 4; ++i) {
        std::memcpy(
            round_keys[i * 2],
            round_keys[(i - 1) * 2],
            BLOCK_LEN_IN_BYTES * 2
        );
        for (int j = 8 * (i - 1) + 1; j <= 8 * (i - 1) + 8; ++j) {
            apply_F(
                 round_constants[j - 1],
                 round_keys[i * 2],
                 round_keys[i * 2 + 1]
            );
        }
    }
}

static void do_round_LSX_matricies(
    const Block round_keys[ROUNDS_NUMBER],
    std::uint8_t round_LSX_matricies[ROUNDS_NUMBER - 1][16][256][16]
) {
    for (int i = 0; i < ROUNDS_NUMBER - 1; ++i) {
        for (int j = 0; j < 16; ++j) {
            for (int k = 0; k < 256; ++k) {
                std::memcpy(round_LSX_matricies[i][j][k], LS_matrix[j][k ^ round_keys[i][j]], 16);
            }
        }
    }
}


static void apply_encrypt(const Block round_keys[ROUNDS_NUMBER], Block block) {
    // Последний раунд не полный
    for (int round_index = 0; round_index < ROUNDS_NUMBER - 1; ++round_index) {
        apply_LSX(round_keys[round_index], block);
    }
    apply_X(round_keys[ROUNDS_NUMBER - 1], block);
}


static void new_apply_encrypt(
    const Block round_keys[ROUNDS_NUMBER],
    std::uint8_t round_LSX_matricies[ROUNDS_NUMBER - 1][16][256][16], Block block
) {
    // Последний раунд не полный
    Block result = {0};
    for (int round_index = 0; round_index < ROUNDS_NUMBER - 1; ++round_index) {
        for (std::uint8_t i = 0; i < BLOCK_LEN_IN_BYTES; ++i) {
            for (std::uint8_t j = 0; j < BLOCK_LEN_IN_BYTES; ++j) {
                result[j] ^= round_LSX_matricies[round_index][i][block[i]][j];
            }
        }
    }
    std::memcpy(block, result, BLOCK_LEN_IN_BYTES);
    apply_X(round_keys[ROUNDS_NUMBER - 1], block);
}


int main(int argc, char** argv) {
    if (argc == 4) {
        if (std::string(argv[1]) == "encrypt") {
            Key key = {0};
            Block block = {0};
            block_from_string(std::string(argv[2]), key, KEY_LEN_IN_BYTES);
            block_from_string(std::string(argv[3]), block);
            Block round_keys[ROUNDS_NUMBER] = {0};
            do_round_keys(key, round_keys);
            std::uint8_t round_LSX_matricies[ROUNDS_NUMBER - 1][16][256][16] = {0};
            do_round_LSX_matricies(round_keys, round_LSX_matricies);
            new_apply_encrypt(round_keys, round_LSX_matricies, block);
            std::cout << to_string(block) << std::endl;
            return 0;
        }
    } else if (argc == 2) {
        if (std::string(argv[1]) == "time") {
            Block block = {0};
            Key key = {0};
            Block round_keys[ROUNDS_NUMBER] = {0};
            do_round_keys(key, round_keys);

            std::uint8_t round_LSX_matricies[ROUNDS_NUMBER - 1][16][256][16];
            do_round_LSX_matricies(round_keys, round_LSX_matricies);


            auto start = std::chrono::system_clock::now();
            for (int i = 0; i < 64 * 1024; ++i) {
                
                new_apply_encrypt(round_keys, round_LSX_matricies, block);
            }
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> diff = end - start;
            std::cout << 1 / diff.count() << std::endl; // Mb per second
            return 0;
        }
    }
    std::cout << "wrong arguments" << std::endl;
}

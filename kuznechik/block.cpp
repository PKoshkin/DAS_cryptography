#include "block.h"

SplitedBlock get_parts(const Block& in_block) {
    SplitedBlock result;
    std::string in_string = in_block.to_string();
    for (std::size_t i = 0; i < 16; ++i) {
        // Сначала берем блоки из конца строки. Они соответствуют меньшим разрядам.
        result.emplace_back(in_string.substr(128 - (i + 1) * 8, 8)); 
    }
    assert(result.size() == 16);
    return result;
}

Block concatinate(const SplitedBlock& in_parts) {
    assert(in_parts.size() == 16);
    std::string concatinate_string(in_parts[15].to_string());
    for (int i = 14; i >= 0; --i) {
        // Присоединяем с конца.
        concatinate_string += in_parts[i].to_string();
    }
    return Block(concatinate_string);
}

//
// Created by Thomas Brooks on 5/28/23.
//

#include <bit>
#include <sstream>
#include <iomanip>
#include "sha256.h"

uint32_t sha256::small_sig_0(uint32_t x) {
    return std::rotr(x, 7) ^ std::rotr(x, 18) ^ (x >> 3);
}

uint32_t sha256::small_sig_1(uint32_t x) {
    return std::rotr(x, 17) ^ std::rotr(x, 19) ^ (x >> 10);
}

uint32_t sha256::big_sig_0(uint32_t x) {
    return std::rotr(x, 2) ^ std::rotr(x, 13) ^ std::rotr(x, 22);
}

uint32_t sha256::big_sig_1(uint32_t x) {
    return std::rotr(x, 6) ^ std::rotr(x, 11) ^ std::rotr(x, 25);
}

uint32_t sha256::maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t sha256::ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
}

std::string sha256::pad(const std::string& msg) {
    uint64_t msg_bits = msg.length() * 8;

    uint32_t base_bits_with_buffer = (msg_bits + 8) % sha256::BLOCK_SIZE;
    uint32_t pad_bits_needed;

    if (base_bits_with_buffer > sha256::PAD_LIMIT) {
        pad_bits_needed = sha256::PAD_LIMIT + sha256::BLOCK_SIZE - base_bits_with_buffer;
    } else {
        pad_bits_needed = sha256::PAD_LIMIT - base_bits_with_buffer;
    }

    std::string padding = std::string(1, sha256::PAD_BUFFER) + std::string(pad_bits_needed / 8, sha256::PAD);
    uint32_t shift = sha256::LOG_MAX_MESSAGE_BITS;

    while (shift > 0) {
        shift -= 8;
        padding += static_cast<char>(msg_bits >> shift);
    }

    return msg + padding;
}

std::vector<std::vector<uint32_t>> sha256::parse(const std::string &padded_msg) {
    std::vector<std::vector<uint32_t>> vec;

    // i iterates over 512-bit blocks
    for (uint64_t i = 0; i < padded_msg.length(); i += sha256::BLOCK_SIZE / 8) {
        std::vector<uint32_t> word(sha256::BLOCK_SIZE / sha256::WORD_SIZE);

        // j iterates over 16 32-bit (4-byte) words
        for (uint64_t j = 0; j < sha256::BLOCK_SIZE / sha256::WORD_SIZE; j++) {
            std::string w = padded_msg.substr(i + j * 4, 4);
            word[j] = ((unsigned char) w[0] << 24) |
                    ((unsigned char) w[1] << 16) |
                    ((unsigned char) w[2] << 8) |
                    (unsigned char) w[3];
        }

        vec.push_back(word);
    }

    return vec;
}

sha256::sha256() {
    this->clear_state();
}

sha256::sha256(const std::string &msg) {
    this->consume_clear(msg);
}

sha256* sha256::consume_clear(const std::string &msg) {
    this->clear_state();
    this->consume(msg);
    return this;
}

sha256* sha256::consume(const std::string &msg) {
    std::vector<std::vector<uint32_t>> preprocessed_msg = sha256::parse(sha256::pad(msg));
    uint32_t working_vars[8];

    for (std::vector<uint32_t> &msg_block : preprocessed_msg) {

        // Prepare message schedule for this message block
        uint32_t message_schedule[sha256::LOG_MAX_MESSAGE_BITS];
        for (uint32_t sched_it = 0; sched_it < sha256::LOG_MAX_MESSAGE_BITS; sched_it++) {
            if (sched_it < sha256::BLOCK_SIZE / sha256::WORD_SIZE) {
                message_schedule[sched_it] = msg_block[sched_it];
            } else {
                message_schedule[sched_it] =
                        sha256::small_sig_1(message_schedule[sched_it-2]) +
                        message_schedule[sched_it-7] +
                        sha256::small_sig_0(message_schedule[sched_it-15]) +
                        message_schedule[sched_it-16];
            }
        }

        // Initialize the working variables for this message block
        std::copy_n(this->hash_state, 8, working_vars);

        // Update the working variables
        for (uint32_t t = 0; t < sha256::LOG_MAX_MESSAGE_BITS; t++) {
            uint32_t temp1 =
                    working_vars[7] +
                    sha256::big_sig_1(working_vars[4]) +
                    sha256::ch(working_vars[4], working_vars[5], working_vars[6]) +
                    sha256::HASH_CONSTANTS[t] +
                    message_schedule[t];
            uint32_t temp2 =
                    sha256::big_sig_0(working_vars[0]) +
                    sha256::maj(working_vars[0], working_vars[1], working_vars[2]);

            working_vars[7] = working_vars[6];
            working_vars[6] = working_vars[5];
            working_vars[5] = working_vars[4];
            working_vars[4] = working_vars[3] + temp1;
            working_vars[3] = working_vars[2];
            working_vars[2] = working_vars[1];
            working_vars[1] = working_vars[0];
            working_vars[0] = temp1 + temp2;
        }

        // Update the hash state
        for (uint32_t reset_it = 0; reset_it < 8; reset_it++) {
            this->hash_state[reset_it] = working_vars[reset_it] + this->hash_state[reset_it];
        }
    }

    return this;
}

void sha256::clear_state() {
    std::copy_n(sha256::INITIAL_HASH_STATE, 8, this->hash_state);
}

std::string sha256::digest() {
    std::stringstream stream;

    for (uint32_t state : this->hash_state) {
        stream << std::setfill ('0') << std::setw(sizeof(uint32_t) * 2)
               << std::hex << state;
    }
    return stream.str();
}



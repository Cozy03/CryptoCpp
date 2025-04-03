#include <classical_ciphers/caeser_cipher/caeser_cipher.hpp>
#include <benchmark/benchmark.h>
#include <random>

/**
 * @file caeser_cipher_bench.cpp
 * @brief Google Benchmark-based performance test for Caesar Cipher.
 */

/// Generates a random alphanumeric string of given length
std::string generate_random_text(size_t length) {
    const std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string result;
    result.reserve(length);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, charset.size() - 1);

    for (size_t i = 0; i < length; ++i) {
        result += charset[dist(rng)];
    }
    return result;
}

/// Benchmark Encryption
static void BM_CaesarEncrypt(benchmark::State& state) {
    size_t text_size = state.range(0);
    uint8_t key = 5;
    Plaintext input = generate_random_text(text_size);

    for (auto _ : state) {
        benchmark::DoNotOptimize(caeser_encrypt(input, key));
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(text_size));
}
BENCHMARK(BM_CaesarEncrypt)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);

/// Benchmark Decryption
static void BM_CaesarDecrypt(benchmark::State& state) {
    size_t text_size = state.range(0);
    uint8_t key = 5;
    Plaintext input = generate_random_text(text_size);
    Ciphertext encrypted = caeser_encrypt(input, key);

    for (auto _ : state) {
        benchmark::DoNotOptimize(caeser_decrypt(encrypted, key));
    }
    state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(text_size));
}
BENCHMARK(BM_CaesarDecrypt)->Arg(100)->Arg(1000)->Arg(10000)->Arg(100000);

BENCHMARK_MAIN();

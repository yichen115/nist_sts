#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <openssl/rand.h>

#include "stat_fncs.h"

#define RAND_LEN      (125000)
#define RAND_BIT_LEN  (RAND_LEN * 8)

void gen_rand(BitSequence *rand_bits, int rand_bits_len)
{
    int count = rand_bits_len / 8;
    unsigned char *rand_bytes = (unsigned char *)calloc(count, 1);
    RAND_bytes(rand_bytes, count);
    BytesToBitSequence(rand_bytes, count, rand_bits, rand_bits_len);
    free(rand_bytes);
}

void save_bits_to_file(const char *filename, BitSequence *rand_bits, int rand_bits_len)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    fwrite(rand_bits, sizeof(BitSequence), rand_bits_len, file);
    fclose(file);
    printf("Bits saved to file: %s\n", filename);
}

BitSequence *read_bits_from_file(const char *filename, int rand_bits_len)
{
    BitSequence *rand_bits = (BitSequence *)calloc(rand_bits_len, sizeof(BitSequence));
    if (rand_bits == NULL) {
        printf("Failed to allocate memory.\n");
        return NULL;
    }

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        free(rand_bits);
        return NULL;
    }

    fread(rand_bits, sizeof(BitSequence), rand_bits_len, file);
    fclose(file);
    printf("Bits read from file: %s\n", filename);

    return rand_bits;
}

int main(int argc, char **argv)
{
    int ret = 0;
    clock_t begin = 0, end = 0;
    const char *random_file = argv[1];

    BitSequence *bits_from_file = read_bits_from_file(random_file, RAND_BIT_LEN);

    //1
    begin = clock();
    ret = Frequency(10000, bits_from_file);
    end = clock();
    printf("[log]-------- Frequency costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- Frequency failed\n");
    } else {
        printf("[res]-------- Frequency pass\n");
    }

    //2
    begin = clock();
    ret = BlockFrequency(100, 10000, bits_from_file);
    end = clock();
    printf("[log]-------- BlockFrequency costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- BlockFrequency failed\n");
    } else {
        printf("[res]-------- BlockFrequency pass\n");
    }

    //3
    begin = clock();
    ret = PokerDetect(8, 10000, bits_from_file);
    end = clock();
    printf("[log]-------- PokerDetect costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- PokerDetect failed\n");
    } else {
        printf("[res]-------- PokerDetect pass\n");
    }

    //4
    begin = clock();
    ret = Serial(2, 10000, bits_from_file);
    end = clock();
    printf("[log]-------- Serial costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- Serial failed\n");
    } else {
        printf("[res]-------- Serial pass\n");
    }

    //5
    begin = clock();
    ret = Runs(1000000, bits_from_file);
    end = clock();
    printf("[log]-------- Runs costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- Runs failed\n");
    } else {
        printf("[res]-------- Runs pass\n");
    }

    //6
    begin = clock();
    ret = RunsDistribution(10000, bits_from_file);
    end = clock();
    printf("[log]-------- RunsDistribution costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- RunsDistribution failed\n");
    } else {
        printf("[res]-------- RunsDistribution pass\n");
    }

    //7
    begin = clock();
    ret = LongestRunOfOnes(10000, bits_from_file);
    end = clock();
    printf("[log]-------- LongestRunOfOnes costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- LongestRunOfOnes failed\n");
    } else {
        printf("[res]-------- LongestRunOfOnes pass\n");
    }

    //8
    begin = clock();
    ret = BinaryDerivate(3, 10000, bits_from_file, sizeof(bits_from_file));
    end = clock();
    printf("[log]-------- BinaryDerivate costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- BinaryDerivate failed\n");
    } else {
        printf("[res]-------- BinaryDerivate pass\n");
    }

    //9
    begin = clock();
    ret = SelfCorrelation(8, 10000, bits_from_file);
    end = clock();
    printf("[log]-------- SelfCorrelation costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- SelfCorrelation failed\n");
    } else {
        printf("[res]-------- SelfCorrelation pass\n");
    }

    //10
    begin = clock();
    ret = Rank(10000, bits_from_file);
    end = clock();
    printf("[log]-------- Rank costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- Rank failed\n");
    } else {
        printf("[res]-------- Rank pass\n");
    }

    //11
    begin = clock();
    ret = CumulativeSums(10000, bits_from_file);
    end = clock();
    printf("[log]-------- CumulativeSums costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- CumulativeSums failed\n");
    } else {
        printf("[res]-------- CumulativeSums pass\n");
    }

    //12
    begin = clock();
    ret = ApproximateEntropy(5, 10000, bits_from_file);
    end = clock();
    printf("[log]-------- ApproximateEntropy costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- ApproximateEntropy failed\n");
    } else {
        printf("[res]-------- ApproximateEntropy pass\n");
    }

    //13
    begin = clock();
    ret = LinearComplexity(500, 1000000, bits_from_file);
    end = clock();
    printf("[log]-------- LinearComplexity costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- LinearComplexity failed\n");
    } else {
        printf("[res]-------- LinearComplexity pass\n");
    }

    //14
    begin = clock();
    ret = Universal(1000000, bits_from_file);
    end = clock();
    printf("[log]-------- Universal costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- Universal failed\n");
    } else {
        printf("[res]-------- Universal pass\n");
    }

    //15
    begin = clock();
    ret = DiscreteFourierTransform(10000, bits_from_file);
    end = clock();
    printf("[log]-------- DiscreteFourierTransform costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("[res]-------- DiscreteFourierTransform failed\n");
    } else {
        printf("[res]-------- DiscreteFourierTransform pass\n");
    }

    printf("\n");

    free(bits_from_file);
    return 0;
}
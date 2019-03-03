#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include "prng.h"

#include "stat_fncs.h"

#define RAND_LEN      (125000)
#define RAND_BIT_LEN  (RAND_LEN * 8)

unsigned char compute(unsigned char b, unsigned char factor)
{
    if ((factor & b) == factor) {
        return 0x01;
    } else {
        return 0x00;
    }
}

void gen_rand(BitSequence *rand_bits)
{
    BitSequence *tmp = (BitSequence *)calloc(RAND_BIT_LEN, sizeof(BitSequence));
    unsigned char rand[RAND_LEN] = {0};
    time_t tt = {0};
    int i = 0, j = 0;
    PRNG_CTX ctx = {0};
    PRNG_init(&ctx);
    tt = time(NULL);
    PRNG_seed(&ctx, (unsigned char *) &tt, sizeof(tt));
    PRNG_rand(&ctx, rand, sizeof(rand));
    for (i = 0; i < sizeof(rand); ++i) {
        j = i * 8;
        tmp[j] = (BitSequence) (compute(rand[i], 0x80));
        tmp[j + 1] = (BitSequence) (compute(rand[i], 0x40));
        tmp[j + 2] = (BitSequence) (compute(rand[i], 0x20));
        tmp[j + 3] = (BitSequence) (compute(rand[i], 0x10));
        tmp[j + 4] = (BitSequence) (compute(rand[i], 0x08));
        tmp[j + 5] = (BitSequence) (compute(rand[i], 0x04));
        tmp[j + 6] = (BitSequence) (compute(rand[i], 0x02));
        tmp[j + 7] = (BitSequence) (compute(rand[i], 0x01));
    }
    memcpy(rand_bits, tmp, RAND_BIT_LEN);
}

int main(int argc, char **argv)
{
    int ret = 0;
    BitSequence *rand_bits = (BitSequence *)calloc(RAND_BIT_LEN, sizeof(BitSequence));
    clock_t begin = 0, end = 0;
	unsigned char n = 255;

    gen_rand(rand_bits);

    //1
    begin = clock();
    ret = Frequency(10000, rand_bits);
    end = clock();
    printf("--------------Frequency costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===Frequency failed\n");
    } else {
        printf("Frequency pass\n");
    }

    //2
    begin = clock();
    ret = BlockFrequency(100, 10000, rand_bits);
    end = clock();
    printf("--------------BlockFrequency costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===BlockFrequency failed\n");
    } else {
        printf("BlockFrequency pass\n");
    }

    //3
    begin = clock();
    ret = PokerDetect(8, 10000, rand_bits);
    end = clock();
    printf("--------------PokerDetect costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===PokerDetect failed\n");
    } else {
        printf("PokerDetect pass\n");
    }

    //4
    begin = clock();
    ret = Serial(2, 10000, rand_bits);
    end = clock();
    printf("--------------Serial costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===Serial failed\n");
    } else {
        printf("Serial pass\n");
    }

    //5
    begin = clock();
    ret = Runs(1000000, rand_bits);
    end = clock();
    printf("--------------Runs costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===Runs failed\n");
    } else {
        printf("Runs pass\n");
    }

    //6
    begin = clock();
    ret = RunsDistribution(10000, rand_bits);
    end = clock();
    printf("--------------RunsDistribution costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===RunsDistribution failed\n");
    } else {
        printf("RunsDistribution pass\n");
    }

    //7
    begin = clock();
    ret = LongestRunOfOnes(10000, rand_bits);
    end = clock();
    printf("--------------LongestRunOfOnes costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===LongestRunOfOnes failed\n");
    } else {
        printf("LongestRunOfOnes pass\n");
    }

    //8
    begin = clock();
    ret = BinaryDerivate(3, 10000, rand_bits, sizeof(rand_bits));
    end = clock();
    printf("--------------BinaryDerivate costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===BinaryDerivate failed\n");
    } else {
        printf("BinaryDerivate pass\n");
    }

    //9
    begin = clock();
    ret = SelfCorrelation(8, 10000, rand_bits);
    end = clock();
    printf("--------------SelfCorrelation costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===SelfCorrelation failed\n");
    } else {
        printf("SelfCorrelation pass\n");
    }

    //10
    begin = clock();
    ret = Rank(10000, rand_bits);
    end = clock();
    printf("--------------Rank costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===Rank failed\n");
    } else {
        printf("Rank pass\n");
    }

    //11
    begin = clock();
    ret = CumulativeSums(10000, rand_bits);
    end = clock();
    printf("--------------CumulativeSums costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===CumulativeSums failed\n");
    } else {
        printf("CumulativeSums pass\n");
    }

    //12
    begin = clock();
    ret = ApproximateEntropy(5, 10000, rand_bits);
    end = clock();
    printf("--------------ApproximateEntropy costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===ApproximateEntropy failed\n");
    } else {
        printf("ApproximateEntropy pass\n");
    }

    //13
    begin = clock();
    ret = LinearComplexity(500, 1000000, rand_bits);
    end = clock();
    printf("--------------LinearComplexity costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===LinearComplexity failed\n");
    } else {
        printf("LinearComplexity pass\n");
    }

    //14
    begin = clock();
    ret = Universal(1000000, rand_bits);
    end = clock();
    printf("--------------Universal costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===Universal failed\n");
    } else {
        printf("Universal pass\n");
    }

    //15
    begin = clock();
    ret = DiscreteFourierTransform(10000, rand_bits);
    end = clock();
    printf("--------------DiscreteFourierTransform costs %.3lf ms\n", (double)(end - begin) * 1000 / CLOCKS_PER_SEC);
    if (ret == 0) {
        printf("!===DiscreteFourierTransform failed\n");
    } else {
        printf("DiscreteFourierTransform pass\n");
    }

	getchar();
    return 0;
}
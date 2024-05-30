#include "discounter_hll.hpp"
#include <cmath>
#include <cstring>
#include <iostream>
extern "C"
{
    #include "hash.h"
}

/**
 * Width shoule be power of 2
 * */
DiscounterHLL::DiscounterHLL(unsigned width, int lgn) {
    bt_.lgn = lgn;
    bt_.width = width;
    for (bt_.log2m = 1; (unsigned)(1 << bt_.log2m) <= width; bt_.log2m++);
    bt_.log2m--;
    bt_.alphaMM = getAlphaMM(bt_.log2m, width);
    bt_.num_zero = width;
    bt_.counts = new unsigned char[width]();
    char name[] = "HyperLogLog";
    unsigned long seed = AwareHash((unsigned char*)name, strlen(name), 13091204281, 228204732751, 6620830889);
    srand(time(0));
    seed += rand();
    bt_.hash= GenHashSeed(seed++);
}

DiscounterHLL::~DiscounterHLL() {
    delete [] bt_.counts;
}

void DiscounterHLL::Update(uint64_t* key) {
    //Get hash value of key
    uint32_t hashedValue = MurmurHash2((unsigned char *)(key), bt_.lgn, bt_.hash);
    // std::cout<<hashedValue<<std::endl;
    // j becomes the binary address determined by the first b log2m of x
    // j will be between 0 and 2^log2m
    unsigned j = hashedValue >> (sizeof(unsigned long)*8 - bt_.log2m);
    unsigned r = numberOfLeadingZeros(((hashedValue << bt_.log2m) | (1 << (bt_.log2m - 1))) + 1) + 1;
    if (bt_.counts[j] == 0) {
        bt_.num_zero--;
    }
    if (bt_.counts[j] < r) {
        bt_.counts[j] = r;
    }
}


// uint64_t DiscounterHLL::Query() {
//     double sum = 0;
//     for (unsigned j = 0; j < bt_.width; j++) {
//         int val = bt_.counts[j];
//         sum += 1.0 / (1 << val);
//     }
//     double estimate = bt_.alphaMM * (1 / sum);

//     // Small Range Estimate
//     if (estimate <= (5.0 / 2.0) * bt_.width) {
//         estimate = bt_.width * log(bt_.width*1.0 / bt_.num_zero);
//         return (uint64_t)round(estimate);
//     }
//     //intermediate range - no correction
//     else if (estimate <= 1.0*pow(2, 32)/30) {     
//         return (uint64_t)round(estimate);
//     }
//     //large range correction
//     else {
//         unsigned long pow2 = pow(2, 32);
//         return (uint64_t)round((-1)*pow2*log(1-estimate/pow2));
//     }
//     return 0;
// }


double DiscounterHLL::Query() {
    double sum = 0;
    for (unsigned j = 0; j < bt_.width; j++) {
        int val = bt_.counts[j];
        sum += 1.0 / (1 << val);
    }
    double estimate = bt_.alphaMM * (1 / sum);

    // Small Range Estimate
    if (estimate <= (5.0 / 2.0) * bt_.width) {
        estimate = bt_.width * log(bt_.width*1.0 / bt_.num_zero);
        return estimate;
    }
    //intermediate range - no correction
    else if (estimate <= 1.0*pow(2, 32)/30) {     
        return estimate;
    }
    //large range correction
    else {
        unsigned long pow2 = pow(2, 32);
        return (-1)*pow2*log(1-estimate/pow2);
    }
    return 0;
}

uint64_t DiscounterHLL::TableQuery(int d, double alphaMM) {
    // D("Now query the %d-th table\n", d);
    // double sum = 0;
    // for (unsigned j = 0; j < bt_.width; j++) {
    //     int val = bt_.counts[d][j];
    //     sum += 1.0 / (1 << val);
    // }
    // double estimate = alphaMM * (1 / sum);

    // // Small Range Estimate
    // if (estimate <= (5.0 / 2.0) * bt_.width) {
    //     D("estimate=%lf\tSmall Range Estimate\t zero=%d\n",estimate, bt_.num_zero[d]);
    //     estimate = bt_.width * log(bt_.width*1.0 / bt_.num_zero[d]);
    //     return (uint64_t)round(estimate);
    // }
    // //intermediate range - no correction
    // else if (estimate <= 1.0*pow(2, 32)/30) {     
    //     return (uint64_t)round(estimate);
    // }
    // //large range correction
    // else {
    //     unsigned long pow2 = pow(2, 32);
    //     return (uint64_t)round((-1)*pow2*log(1-estimate/pow2));
    // }
    return 0;
}


/**
 *Get the number of leading zeors
 * */

unsigned char DiscounterHLL::numberOfLeadingZeros(unsigned long value) {

    if (value ==0)
        return 64;
    unsigned char n = 0;
    unsigned x = (unsigned)(value >> 32);
    if (x == 0) {
        n = 32;
        x = (int)value;
    }
    if ((x & 0xFFFF0000) == 0) { 
        n += 16; 
        x = x << 16;
    } 
    if ((x & 0xFF000000) == 0) { 
        n = n +  8; 
        x = x <<  8;
    } 
    if ((x & 0xF0000000) ==0) { 
        n = n +  4; 
        x = x <<  4;
    } 
    if ((x & 0xC0000000) == 0) { 
        n = n +  2;
        x = x <<  2;}
    if ((x & 0x80000000) == 0) {
        n = n +  1;
        x = x <<  1;
    } 
    return n;
}


/**
 *get the constant to correct bias
 * */
double DiscounterHLL::getAlphaMM(int p, unsigned m) {
    switch (p) {
        case 4:
            return 0.673 * m * m;
        case 5:
            return 0.697 * m * m;
        case 6:
            return 0.709 * m * m;
        default:
            return (0.7213 / (1 + 1.079 / m)) * m * m;
    }
}

void DiscounterHLL::Reset() {
    bt_.num_zero = bt_.width;
    bt_.counts = new unsigned char[bt_.width]();
}

void DiscounterHLL::Print(unsigned char* filename) {}

void DiscounterHLL::Read(unsigned char* filename) {}

long long DiscounterHLL::GetCount() {
    return bt_.count;
}

void DiscounterHLL::SetCount(long long val) {
    bt_.count = val;
}

#include "discounter_lc.hpp"
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
extern "C"
{
    #include "bitmap.h"
    #include "hash.h"
}

DiscounterLC::DiscounterLC(int width, int lgn) {
    cm_.width = width;
    cm_.lgn = lgn;
    cm_.count = 0;   

    cm_.counts = new unsigned char [(width + 7) >> 3]();
    cm_.num_zero = width;
    char name[] = "LinearCounting";
    cm_.seed = AwareHash((unsigned char*)name, strlen(name), 13091204281, 228204732751, 6620830889);
    srand(time(0));
    cm_.seed += rand();
}

DiscounterLC::~DiscounterLC() {
    delete [] cm_.counts;
}


void DiscounterLC::Update(uint64_t* key) {
    uint32_t p = MurmurHash2((unsigned char *)(key), cm_.lgn, cm_.seed);

    // std::cout << p % cm_.width << " " << ((uint32_t )p * (unsigned long)cm_.width >> 32) << std::endl;
    // std::cout << p << std::endl;
    p = (uint32_t )p * (unsigned long)cm_.width >> 32;
    // std::cout<<p<<std::endl;
    // std::cout << p << std::endl;
    if(getbit(p, cm_.counts) == 0) {
        cm_.num_zero --;
        // std::cout << p << " " << cm_.num_zero << " " << cm_.width << std::endl;
        setbit(p, cm_.counts);
    }
}

uint64_t DiscounterLC::Query() {
    if(cm_.num_zero == 0) return 1.0 * cm_.width * log(1.0 * cm_.width);
    uint64_t ret = 1.0 * cm_.width * log(1.0 * cm_.width / cm_.num_zero);
    return ret;
}

void DiscounterLC::Reset() {
    cm_.counts = new unsigned char [(cm_.width + 7) >> 3]();
    cm_.num_zero = cm_.width;
}

void DiscounterLC::Print(unsigned char * filename) {
    return;
}

void DiscounterLC::Read(unsigned char * filename) {
    return;
}

long long DiscounterLC::GetCount() {
    return cm_.count;
}

void DiscounterLC::SetCount(long long val) {
    cm_.count = val;
}

int DiscounterLC::getNumZero() {
    return cm_.num_zero;
}

int DiscounterLC::getLgn() {
    return cm_.lgn;
}

void DiscounterLC::getCounts(int * start) {
    for(int i = 0; i < cm_.width; i++) {
        if(getbit(i, cm_.counts) != 0){
            *(start + i) = 1;
        }
    }
}

unsigned long DiscounterLC::getSeed() {
    return cm_.seed;
}

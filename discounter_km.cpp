#include "discounter_km.hpp"
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>

extern "C"
{
    #include "hash.h"
}
DiscounterKM::DiscounterKM(int width, int lgn) {
   
    km_.width = width;
    km_.lgn = lgn;
    km_.counts = new uint32_t [width]();
    km_.index = 0;
    char name[] = "KMinimumValue";
    uint64_t seed = AwareHash((unsigned char*)name, strlen(name), 13091204281, 228204732751, 6620830889);
    srand(time(0));
    seed += rand();
    // std::cout<<seed;
    // km_.hash = GenHashSeed(seed++);
    km_.hash = GenHashSeed(8281037335806428185);
}

DiscounterKM::~DiscounterKM() {
    delete [] km_.counts;
}




/*
 *Sorting while updating, using binary searching has higher throughput
 * */
void DiscounterKM::Update(uint64_t* key) {
    //uint64_t bucket = AwareHash(key, km_.lgn/8, km_.hash[i], km_.scale[i], km_.hardner[i]);
    // uint64_t bucket = MurmurHash64A((unsigned char *)&key, km_.lgn/8, km_.hardner);
    uint32_t bucket = MurmurHash2((unsigned char *)(key), km_.lgn, km_.hash);
    // std::cout<<bucket * 1.0 / UINT32_MAX<<std::endl;
    int l = 0;
    int r = km_.index - 1;
    int m = 0;
    // If kmv is full, skip if element larger than head
    // TODO make bool setting
    if (km_.index >= km_.width && km_.counts[0] <= bucket) {
        return;
    }
    //Just insert if empty
    if (km_.index == 0) {
        km_.counts[km_.index] = bucket;
        km_.index++;
        return;
    }
    //Perform search
    while (1) {
        //Find new middle
        m = (l + r) / 2;
        //Not found, insert
        if (l > r || m >= km_.index) {
            //If kmv is full, shift up
            if (km_.index >= km_.width) {
                memmove(km_.counts, km_.counts+1, m*sizeof(uint32_t));
                //Insert the element
                km_.counts[m] = bucket;
                break;
            } else {
                //Else shift values down to make space
                if (km_.counts[m] > bucket) {
                    m++;
                }
                memmove(km_.counts+m+1, km_.counts+m, (km_.index - m)*sizeof(uint32_t));
                //Insert the element
                km_.counts[m] = bucket;
                km_.index++;
                break;
            }
            break;
        }
        if (km_.counts[m] > bucket) {
            l = m + 1;
            continue;
        } else if (km_.counts[m] < bucket) {
            r = m - 1;
            continue;
        }
        break;
    }
    
}


double DiscounterKM::Query() {
    double ret;
    if (km_.width > km_.index) {
        //burn daylight
        /* 
        if (km_.index[i] > 1) {
            ans[i+1] = (km_.index[i] - 1)*1.0*UINT64_MAX / km_.counts[i][0];
        } else {
            ans[i+1] = km_.index[i]*1.0*UINT64_MAX / km_.counts[i][0];

        }
        */
        //if width > km_.index[i], just return km_.index[i]
        ret = km_.index;
    } else {
        if (km_.width > 1) {
            ret = (km_.width - 1)*1.0/ km_.counts[0]*UINT32_MAX;
        } else {
            ret = km_.width * 1.0 / km_.counts[0]* UINT32_MAX ;
        }
    }
    // std::cout << "[Query] ans["<<i+1<<"]="<<ans[i+1]<<std::endl;
    return ret;
}

void DiscounterKM::Reset() {
    // memset(km_.counts, 0, km_.width * sizeof(uint32_t));
    km_.counts = new uint32_t [km_.width]();
    km_.index = 0;
}

void DiscounterKM::getMax() {
    // for(int i = 0; i < km_.width; i++) {
    //     std::cout<<km_.counts[i]<<", ";
    // }
    std::cout<<km_.counts[0] * 1.0 / UINT32_MAX;
    // std::cout<<std::endl;
}

void DiscounterKM::getCounts() {
    for(int i = 0; i < 2; i++) {
        std::cout<<std::setprecision(10)<<km_.counts[km_.width - i - 1] * 1.0 / UINT32_MAX<<", ";
    }
    // std::cout<<km_.counts[0] * 1.0 / UINT32_MAX;
    // // std::cout<<std::endl;
}

void DiscounterKM::getHash(uint64_t* key, double & hash) {
    uint32_t bucket = MurmurHash2((unsigned char *)(key), km_.lgn, km_.hash);
    // std::cout<<std::setprecision(10)<<bucket * 1.0 /UINT32_MAX<<std::endl;
    hash = bucket * 1.0 /UINT32_MAX;
}

void DiscounterKM::getBucket(uint64_t* key) {
    uint32_t bucket = MurmurHash2((unsigned char *)(key), km_.lgn, km_.hash);
    std::cout<<bucket;
}

void DiscounterKM::Print(unsigned char * filename) {
    return;
}

void DiscounterKM::Read(unsigned char * filename) {
    return;
}


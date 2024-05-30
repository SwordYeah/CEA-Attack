#ifndef DISCOUNTER_KM_H
#define DISCOUNTER_KM_H
#include <cstdint>
#include <vector>
#include "datatypes.hpp"
class DiscounterKM{

    struct KM_type {
        //# of k-array
        // int depth;

        //K value
        int width; 

        //Array table
        uint32_t *counts;
        uint64_t hash, scale, hardner;
        int lgn;
        //length of current k-array
        int index;
    };

public:
    DiscounterKM(int width, int lgn);

    ~DiscounterKM();

    void Update(uint64_t* key);

    double Query();

    void Reset();

    void Print(unsigned char* filename);

    void Read(unsigned char* filename);
    
    void getCounts();

    void getMax();

    void getHash(uint64_t* key, double & hash);

    void getBucket(uint64_t* key);

    int heap_adjust = 0;

private:
    KM_type km_;

};
#endif

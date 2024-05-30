#ifndef DISCOUNTER_LC_H
#define DISCOUNTER_LC_H
#include "datatypes.hpp"
class DiscounterLC{

    struct CM_type {
        //Count total items
        long long count;  

        //# hash table
        int depth;                          
        
        //# counters in each hash table
        int width;                    
        
        //Hash tables
        unsigned char *counts;
 
        //# zeros in each hash table
        int num_zero;                     
        // unsigned *hash, *scale, *hardner;
        unsigned long seed;
        //# bits in key
        int lgn;                           
    };

public:
    DiscounterLC(int width, int lgn);

    ~DiscounterLC();

    void Update(uint64_t* key);

    uint64_t Query();

    void Reset();

    void Print(unsigned char* filename);

    void Read(unsigned char* filename);

    long long GetCount();

    int getNumZero();

    void SetCount(long long val);

    int getLgn();

    void getCounts(int * start);

    unsigned long getSeed();

private:
    CM_type cm_;
};
#endif

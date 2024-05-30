#ifndef DISCOUNTER_HLL_H
#define DISCOUNTER_HLL_H
#include "datatypes.hpp"
class DiscounterHLL{

    struct BITMAP{
        //Count total itmes
        long long count;

        //Count how many 0 in the bitmap
        unsigned num_zero;

        //Length of bitmap
        unsigned width;
        
        //Mumber of bits to use as the basis for the HLL instance, it defines
        //the accuracy of the counter. The larger the log2m the better the accuracy.
        //accuracy = 1.04/sqrt(2^log2m)
        int log2m;
        
        
        //Bitmap tables
        unsigned char *counts;
        
        //# bits in key
        int lgn;

        //Hash related variable
        unsigned hash, scale, hardner;
        
        //Correction constant
        double alphaMM;
    };

public: 
    DiscounterHLL(unsigned width, int lgn);

    ~DiscounterHLL();

    void Update(uint64_t* t);

    double Query();

    void Reset();

    void Print(unsigned char* filename);

    void Read(unsigned char* filename);

    long long GetCount();

    void SetCount(long long val);
private:
    BITMAP bt_;

    double getAlphaMM(int p, unsigned m);

    unsigned char numberOfLeadingZeros(unsigned long value);

    uint64_t TableQuery(int d, double alphaMM);
};
#endif



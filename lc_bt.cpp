#include "discounter_lc.hpp"
#include "adaptor.hpp"
#include <utility>
#include "datatypes.hpp"
#include "util.h"
#include <fstream>
#include <iomanip>
#include <set>
#include <cmath>
#include <algorithm>
#include <random>

/*
该实验为推测Linear Counting算法使用位图大小的代码
*/


uint32_t testHash(uint64_t* key, int len, uint32_t seed ) {
    return MurmurHash2((unsigned char *)(&key), len, seed);
}

int main(int argc, char* argv[]) {

    using namespace std;
    int memory = atoi(argv[1]); //位图大小
    int lgn = 8;
   
    
    uint64_t size = pow(2, 20); //生成随机元素
    uint64_t* start;
    
    start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }
    

    

    uint64_t j = 0, i;
    uint64_t est_before, est_after; 
    int cnt = 0;


    //int num = 8;
    int m,total_num = 0;
    
    int iter = 10;  // 运行次数

    for(i = 0; i < iter; i++) {

        
        
        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);
        

        

        // Create Sketch instance
        j = 0;
        DiscounterLC * lc = new DiscounterLC(memory, lgn);
        // cout<<lc->Query()<<endl;
        cnt = 0;
        lc->Reset();

        while(1) {
            est_before = lc->Query();
            lc->Update(start + j);
            est_after = lc->Query();
            if(est_after > est_before) {
                cnt++;
            }
            if((double)cnt/(j + 1) <=0.632) {     //0.632为数学上m个元素随机插入到大小为m的位图中，非空桶的占比
                m = j + 1;
                break;
            }
            j++;
        }

        total_num += abs(m - memory);
    }

    cout<<(double)total_num/memory/iter*100<<"%"<<endl;  //输出平均误差大小


    delete[] start;
  

}


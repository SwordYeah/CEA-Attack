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
该实验为推测Linear Counting算法使用位图大小的代码，比lc_bt.cpp中增加了一个假设，
即算法使用的位图大小一定为2的指数倍。
*/

int main(int argc, char* argv[]) {

    using namespace std;
    int memory = atoi(argv[1]);
    int lgn = 8;
   
    
    uint64_t size = pow(2, 20); //设置初始集合大小
    uint64_t* start;
    
    start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }
    

    

    int j=0;
    uint64_t est_before, est_after; 
    int cnt = 0;


    int num = 0;
    int m;
    
    int iter = 100;    // 运行次数

    int total = pow(2, 5);  //设置初始时插入sketch中的元素个数

    for(int i = 0; i < iter; i++) {

        
        
        // 使用随机数引擎和 std::random_shuffle 函数对初始集合数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);
        

        

        // Create sketch instance
        j = 0;
        DiscounterLC * lc = new DiscounterLC(memory, lgn);
        // cout<<lc->Query()<<endl;
        cnt = 0;
        lc->Reset();


        while(1) {
            while(j < total) {
                est_before = lc->Query();
                lc->Update(start + j);
                est_after = lc->Query();
                if(est_after > est_before) {
                    cnt++;
                }
                j++;
            }
            if((double)cnt/total <= 0.7) {  //m个元素随机插入到大小为m的位图中，非空桶的理论占比为0.632；2m个元素随机插入时，理论占比为0.787，0.7为两者大约中点位置
                m = total;
                break;
            }
            total = 2 * total;
        }
        

        // cout<<m<<endl;  

        num += abs(m - memory);


        delete lc;
    }


    cout<<(double)num/iter/memory*100<<"%"<<endl;  //平均误差


    delete[] start;
  

}


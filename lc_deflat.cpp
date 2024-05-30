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
该实验为针对Linear Counting算法构造攻击集进行基数缩减攻击的代码
*/

int main(int argc, char* argv[]) {

    using namespace std;
    int memory = atoi(argv[1]);  //位图大小
    int lgn = 8;
   
    
    uint64_t size = pow(2, 20);   //初始集合大小，可修改
    uint64_t* start;
    
    start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }
    

    

    uint64_t j=0;
    uint64_t est_before, est_after; 
    int cnt = 0;


    int num = 0, attack_num = 0;
    int m;
    
    int iter = 10;   //运行次数，可修改

    int deflat_time = atoi(argv[2]);   //需要的攻击集缩减倍数


    for(int i = 0; i < iter; i++) {

        int total = pow(2, 4);
        
        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);

        

        // Create DREX instance
        j = 0;
        DiscounterLC * lc = new DiscounterLC(memory, lgn);
        uint64_t * set = new uint64_t[size];
        uint64_t idx = 0;
        // cout<<lc->Query()<<endl;
        cnt = 0;
        lc->Reset();

        // 推测位图大小
        while(1) {
            while(j < total) {
                est_before = lc->Query();
                lc->Update(start + j);
                est_after = lc->Query();
                if(est_after > est_before) {
                    set[idx++] = start[j];
                    cnt++;
                }
                j++;
            }
            if((double)cnt/total <= 0.7) {
                m = total;
                break;
            }
            total = 2 * total;
        }
        


        lc->Reset();


        for(int i = 0; i < (int)(deflat_time * m * log(m)); i++) {
            lc->Update(start + i);  //插入攻击集
            attack_num = idx;
        }


        // cout<<lc->Query()<<endl;
        num += (double)(deflat_time * m * log(m))/lc->Query();

        delete lc;
    }

    // cout<<deflat_time * m * iter / num<<endl;

    cout<<(double)num/iter<<endl;  //实际得到的平均基数缩减倍数

    


    delete[] start;
  

}


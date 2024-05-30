#include "discounter_hll.hpp"
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

using namespace std;

/*
HyperLogLog基数缩减攻击算法的复现，该代码为“HyperLogLog: Exponentially Bad in Adversarial Settings”
5.2.2小节两种设计中简单版本的实现
*/




int main(int argc, char* argv[]) {
   
    int memory = atoi(argv[1]);
    double bucket_fractor = 0.5;   // 选中的桶的占比，关于该部分见论文”HyperLogLog: Exponentially Bad in Adversarial Settings”5.2节
    uint64_t bucket_num = (uint64_t)(bucket_fractor * memory);
    int lgn = 8;
    
    

    int deflat_time = atoi(argv[2]);  // 预期的基数缩减倍数

    uint64_t need = (uint64_t)(log(2) * deflat_time * memory);  // log2一值和桶的占比相关，选定不同的桶占比，基数估计值就不相同
    cout<<need<<endl;

    int exp = 15;

    while(pow(2, exp) < need * 2){
        exp++;
    }

    uint64_t size = pow(2, exp);
    // cout<<size<<endl;

    uint64_t* start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }

    double alpha_m;
    int bit = 1;
    while((int)(1 << bit) <= memory) {
        bit++;
    } 

    switch(memory) {
        case 16:
            alpha_m = 0.673;
            break;
        case 32:
            alpha_m = 0.697;
            break;
        case 64:
            alpha_m = 0.709;
            break;
        default:
            alpha_m = (0.7213 / (1 + 1.079 / memory));
    }


    double bMax = 0;
    // cout<<alpha_m<<endl;
    bMax = memory * (1 - alpha_m / 5.0) / (1 - pow(2, -(bit + 1)));
    // cout<<fixed<<setprecision(8)<<bMax<<endl;
    if(bucket_num > bMax){
        cout<<"buck_num can't larger than bMax!"<<endl;
        return -1;
    }


    
    uint64_t iter = 10;    // 运行次数


    uint64_t total_est = 0, total_num = 0, cnt = 0;


    double t1, t2, time = 0;


    for(uint64_t k = 0; k < iter; k++) {

        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);

        t1 = now_us();


        // Create DREX instance
        DiscounterHLL * hll = new DiscounterHLL(memory, lgn);

        uint64_t est, est_before, est_after;
        uint64_t * set_a = new uint64_t[size];
        uint64_t idx = 0, j = 0;

        // double real_est = 1.0 * memory * log(1.0 * memory / (memory - bucket_num));
        // cout<<real_est<<endl;

        est = hll->Query();
        while(cnt < bucket_num) {
            hll->Update(start + j);
            j++;
            est_after = hll->Query();
            if(est_after > est) {
                cnt++;
                est = est_after;
            }
        }
        // cout<<cnt<<"  "<<bucket_num<<endl;
        bucket_num = j;

        est_before = est;
        j = 0;
        while(j < size) {
            hll->Update(start + j);
            est_after = hll->Query();
            if(est_after == est_before) {
                set_a[idx++] = start[j];
                if(idx >= need) {
                    break;
                }
            } else {
                hll->Reset();
                for(uint64_t i = 0; i < bucket_num; i++) {
                    hll->Update(start + i);
                }
                est_before = est;
            }
            j++;
        }

        t2 = now_us();

        
        


        time = time + (t2 - t1)/1000000;
        // cout<<(t2 - t1)/1000000<<endl;

        total_num += idx;

        // cout<<"idx: "<<idx<<endl;

        hll->Reset();

        //  将攻击集插入已有mln(m)个元素的非空sketch中
        for(j = 0; j < memory * log(memory); j++) {
            hll->Update(start + j);
        }

        // cout<<hll->Query()<<endl;


        for(j = 0; j < idx; j++) {
            hll->Update(set_a + j);
        }

        // cout<<hll->Query()<<endl;
        total_est += hll->Query();

        delete hll;
        delete[] set_a;
    
    }



    cout<<total_est/iter<<endl;   // 平均基数估计值
    cout<<total_num/iter<<endl;   //  平均攻击集大小
    cout<<(double)time/iter<<endl;   // 平均运行时间


    delete[] start;

}


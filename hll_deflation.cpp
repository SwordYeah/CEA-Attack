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
针对HyperLogLog设计的基数缩减攻击算法，该算法为“HyperLogLog: Exponentially Bad in Adversarial Settings”
5.2.2小节两种设计中简单版本的实现
*/



int main(int argc, char* argv[]) {
   
    int memory = atoi(argv[1]);
    int lgn = 8;

    int deflat_time = atoi(argv[2]);

    uint64_t need = (uint64_t)(2.88 * deflat_time * memory); // 2.88M为HLL桶内值全为2时的基数估计
    

    int exp = 15;

    // 有75%的概率选中元素，因此初始集合大小为所需攻击集大小的4/3
    while(pow(2, exp) < (int)(need / 3.0 * 4) ){
        exp++;
    }

    uint64_t size = pow(2, exp);  // 初始集合大小


    uint64_t total_num = 0, total_est = 0;

    uint64_t* start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }

    double alpha_m;
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

    double factor = alpha_m * memory * memory;

    double t1, t2, time = 0;
    
    uint64_t iter = 10;


    for(uint64_t k = 0; k < iter; k++) {

        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);

        t1 = now_us();

        // Create DREX instance
        DiscounterHLL * hll = new DiscounterHLL(memory, lgn);

        double est, est_now;
        uint64_t * flag = new uint64_t[size];
        uint64_t * set_a = new uint64_t[size];
        uint64_t * set_f = new uint64_t[size];
        std::fill(flag, flag + size, 0);
        uint64_t idx = 0, idx_f = 0, j;
        uint64_t begin, end;
        double value;

        j = 0;
        while(j < size) {
            begin = j;
            est = 0;
            while(est < 2.8 * memory && j < size) {
                hll->Update(start + j);
                j++;
                est = hll->Query();
            }

            if(j >= size) {
                break;
            }

            end = j;
            // cout<<"("<<begin<<", "<<end<<")"<<endl;

            // 筛选能够判断前导零大小的元素
            hll->Reset();
            for(uint64_t i = begin; i < end; i++) {
                for(uint64_t a = begin; a < end; a++) {
                    if(a == i || flag[a] == 1) {
                        continue;
                    }
                    hll->Update(start + a);
                }
                est_now = hll->Query();
                if(est == est_now) {
                    flag[i] = 1;
                    // set_a[idx++] = start[i];
                }
                hll->Reset();
            }

            
            // 选取mln(m)个前导零不大于2的元素
            for(uint64_t i = begin; i < end; i++) {
                if(flag[i] == 1) {
                    continue;
                }
                for(uint64_t a = begin; a < end; a++) {
                    if(a == i || flag[a] == 1) {
                        continue;
                    }
                    hll->Update(start + a);
                }
                est_now = hll->Query();
                if(est_now > 2.5 * memory) {
                    value = -log2(factor/est - factor/est_now + 1.0); // 计算当前元素哈希后的前导零
                    if(value <= 2.0) {
                        set_a[idx++] = start[i];
                        if(idx >= memory * log(memory)) {
                            break;
                        }
                    }
                }
                hll->Reset();
            }

            // 选取初始集合中所有前导零不大于2的元素
            if(idx >= memory * log(memory)) {
                
                j = 0;
                hll->Reset();
                // cout<<idx<<endl;
                for(uint64_t i = 0; i < idx; i++) {
                    hll->Update(set_a + i);
                    // cout<<hll->Query()<<endl;
                }
                est = hll->Query();
                // cout<<est<<endl;

                while(j < size) {
                    hll->Update(start + j);
                    est_now = hll->Query();
                    if(est_now == est) {
                        set_f[idx_f++] = start[j];
                        if(idx_f >= need){
                            break;
                        }
                    } else {
                        hll->Reset();
                        for(uint64_t i = 0; i < idx; i++) {
                            hll->Update(set_a + i);
                        }
                    }
                    j++;
                }
                break;
            }
        }
        
        // uint64_t cnt = 0;
    
        // cout<<"idx_f: "<<idx_f<<endl;

        hll->Reset();

        t2 = now_us();
        time = time + (t2 - t1)/1000000;
        // cout<<(t2 - t1)/1000000<<endl;

        //  将攻击集插入已有mln(m)个元素的非空sketch中
        // for(j = 0; j < memory * log(memory); j++) {
        //     hll->Update(start + j);
        // }

        // cout<<hll->Query()<<endl;


        for(j = 0; j < idx_f; j++) {
            hll->Update(set_f + j);
        }

        // cout<<hll->Query()<<endl;

        total_est += hll->Query();
        total_num += idx_f;


        delete hll;
        delete[] flag;
        delete[] set_a;

    
    }


    cout<<total_est/iter<<endl;   // 平均基数估计值
    cout<<total_num/iter<<endl;   //  平均攻击集大小
    cout<<(double)time/iter<<endl;   // 平均运行时间


    delete[] start;

}


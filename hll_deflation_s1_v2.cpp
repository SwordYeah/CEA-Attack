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
5.2.2小节两种设计中复杂攻击的实现
*/



int main(int argc, char* argv[]) {
   
    int memory = atoi(argv[1]);
    double bucket_fractor = 0.5;   // 选中的桶的占比，关于该部分见论文”HyperLogLog: Exponentially Bad in Adversarial Settings”5.2节
    uint64_t bucket_num = (uint64_t)(bucket_fractor * memory);
    int lgn = 8;
    

    int deflat_time = atoi(argv[2]);  // 预期的基数缩减倍数

    //log2一值和桶的占比相关，因为bucket_fractor为0.5，只有50%概率选中元素，
    // 因此初始集合大小要再乘以2
    uint64_t size = (uint64_t)(2 * log(2) * deflat_time * memory);  
    uint64_t* start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }


    double t1, t2, total_time = 0;
    uint64_t total_est = 0, total_num = 0, cnt = 0;

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
    bMax = 1.0 * memory * (1 - alpha_m / 5.0) / (1 - pow(2, -(bit + 1)));
    // cout<<fixed<<setprecision(8)<<bMax<<endl;
    if(bucket_num > bMax){
        cout<<"buck_num can't larger than bMax!"<<endl;
        return -1;
    }


    
    uint64_t iter = 10;  // 运行次数



    for(uint64_t k = 0; k < iter; k++) {

        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);


        t1 =now_us();

        // Create DREX instance
        DiscounterHLL * hll = new DiscounterHLL(memory, lgn);

        uint64_t est, est_before, est_after;
        uint64_t * set_a = new uint64_t[size];
        uint64_t idx = 0, j;
        uint64_t * start_list = new uint64_t[size];
        uint64_t * now_list = start;
        uint64_t * attack_list = set_a;
        int flag = 0;

        // uint64_t pass = (1.0 - bucket_num * 1.0 / memory)/(bMax - bucket_num) * size;
        // cout<<"pass: "<<pass<<endl;

        int change;
        uint64_t end = size; // 初始数组结束遍历的位置
        
        j = 0;
        cnt = 0;
        est = hll->Query();
        while(cnt < bucket_num) {
            hll->Update(start + j);
            est_after = hll->Query();
            if(est_after > est) {
                cnt++;
                est = est_after;
            }
            j++;
        }
        uint64_t real_bucket_num = j;  //记录达到B个桶需要项目的个数

        for(uint64_t i = 0; i < real_bucket_num; i++) {
            start_list[i] = start[i];
        }

        // cout<<hll->Query()<<endl;


        uint64_t est_bound = 1.0 * memory * log(1.0 * memory / (memory - bMax));
        // cout<<est_bound<<endl;
        // cout<<end<<endl;
        // cout<<j<<endl;

        j = 0;
        est_before = est;
        uint64_t time = 0;
        change = 1;
        while(change == 1) {
            change = 0;
            while(j < end) {
                hll->Update(now_list + j);
                est_after = hll->Query();
                if(est_after == est_before) {
                    attack_list[idx++] = now_list[j];
                } else {
                    change = 1;
                    if(est_after < est_bound) {
                        est_before = est_after;
                        j++;
                        continue;
                    }
                    hll->Reset();
                    for(uint64_t i = 0; i < real_bucket_num; i++) {
                        hll->Update(start_list + i);
                    }
                    est_before = est;
                    time++;
                }
                j++;
            }

            // 把得到的列表作为新的输入
            if(flag == 0) {
                now_list = set_a;
                attack_list = start;
                flag = 1;
            } else {
                now_list = start;
                attack_list = set_a;
                flag = 0;
            }

            end = idx;
            idx = 0;
            hll->Reset();
            
            j = 0;
            for(uint64_t i = 0; i < real_bucket_num; i++) {
                hll->Update(start_list + i);
            }
            est_before = est;
            time++;
            // cout<<time<<endl;
        }


        t2 = now_us();


        total_time = total_time + (t2 - t1)/1000000;
        // cout<<(t2 - t1)/1000000<<endl;
        
        total_num += end;
        // cout<<"idx: "<<end<<endl;

        hll->Reset();

        // 将攻击集插入已有mln(m)个元素的非空sketch中
        for(j = 0; j < memory * log(memory); j++) {
            attack_list[j] = j+1;
            hll->Update(attack_list + j);
        }

        // cout<<hll->Query()<<endl;


        for(j = 0; j < end; j++) {
            hll->Update(now_list + j);
        }

        // cout<<hll->Query()<<endl;
        total_est += hll->Query();



        delete hll;
        delete[] start_list;
        delete[] set_a;

    
    }


    cout<<total_est/iter<<endl;   // 平均基数估计值
    cout<<total_num/iter<<endl;   //  平均攻击集大小
    cout<<(double)total_time/iter<<endl;   // 平均运行时间


    delete[] start;

}


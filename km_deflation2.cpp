#include "discounter_km.hpp"
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
针对K Minimum Values的基数缩减攻击
*/



int main(int argc, char* argv[]) {

    int memory = atoi(argv[1]);
    int lgn = 8;

    int  deflat_time = atoi(argv[2]);  // 攻击集的基数缩减倍数

    // 攻击集所需大小，因为选取哈希值大于0.5的，因此基数估计下界为2(K-1)
    uint64_t total = 2 * deflat_time * (memory - 1);  

    uint64_t size = (uint64_t)(2.1 * total);  // 用于构造攻击集的初始集合大小

    
    // cout<<size<<endl;
    uint64_t* start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }


    int iter = 10;  // 运行次数


    uint64_t idx = 0, idx_f = 0, j;
    

    uint64_t num = 0;


    


    double t1, t2, time = 0;
    // double bound = 2.0  / (memory - 1) * est_real;
    double bound = 4.0; // 在K=3的sketch中对应的基数估计值的上界

    
    for(int k = 0; k < iter; k++) {
        // cout<< k+1<<endl;

        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);
        // Create DREX instance

        t1 = now_us();


        DiscounterKM * km = new DiscounterKM(memory, lgn);
        uint64_t* set_a = new uint64_t[size];
        uint64_t* set_f = new uint64_t[size];
        

        // double t1=0, t2=0;
        idx = 0;
        idx_f = 0;

        // 缩减初始集合大小
        double est_before, est_after;
        est_before = km->Query();
        for(j=0; j < size; j++) {
            km->Update(start + j);
            est_after = km->Query();
            if(est_after > est_before) {
                // cout<<est_after<<"  "<<est_before<<endl;
                set_a[idx++] = start[j];
                est_before = est_after;
            }
        }
        // cout<<idx<<"    "<<int(km->Query())<<endl;
        // cout<<set_a[0]<<endl;
        km->Reset();

        est_before = km->Query();
        for(j = 1; j <= idx; j++) {
            km->Update(set_a + idx - j);
            est_after = km->Query();
            if(est_after > est_before) {
                // cout<<est_after<<"  "<<est_before<<endl;
                set_f[idx_f++] = set_a[idx - j];
                est_before = est_after;
            }
                    
        }

        // cout<<idx_f<<"    "<<int(km->Query())<<endl;
        // cout<<set_f[0]<<endl;
        // km->Reset();


        // for(j = 0; j < idx_f; j++) {
        //     km->Update(set_f + j);
        // }

        // cout<<int(km->Query())<<endl;
        // cout<<endl;


        // 找到哈希值最小的两个元素
        DiscounterKM * km2 = new DiscounterKM(2, lgn);
        uint64_t max1 = 0, max2 = 0;
        est_before = km2->Query();
        for(j = 0; j < idx_f; j++) {
            km2->Update(set_f + j);
            est_after = km2 -> Query();
            if(est_after > est_before) {
                max1 = j;
                est_before = est_after;
            }
        }

        km2->Reset();
        km2->Update(set_f + max1);
        est_before = km2->Query();
        for(j = 0; j < idx_f; j++) {
            km2->Update(set_f + j);
            est_after = km2 -> Query();
            if(est_after > est_before) {
                max2 = j;
                est_before = est_after;
            }
        }

        // cout<<set_f[max1]<<"  "<<set_f[max2]<<endl;
        // km2->getHash(set_f + max1);
        // km2->getHash(set_f + max2);
        // km2->getCounts();
        // cout<<int(km2->Query())<<endl;

        // 找到哈希值不小于0.5的元素加入攻击集
        DiscounterKM * km3 = new DiscounterKM(3, lgn);
        uint64_t* h_list = new uint64_t[total];
        uint64_t idx_h = 0;
        km3->Update(set_f + max1);
        km3->Update(set_f + max2);
        for(j = 0; j < size; j++) {
            km3->Update(start +j);
            est_after = km3->Query();
            if( est_after < bound) {
                // cout<<est_after<<"  "<<est_before<<endl;
                h_list[idx_h++] = start[j];
                if(idx_h >= total) {
                    break;
                }
            }
            km3->Reset();
            km3->Update(set_f + max1);
            km3->Update(set_f + max2);
        }

        // cout<<cnt<<endl;
        // cout<<int(km3->Query())<<endl;


        


    
        t2 = now_us();
        time = time + (t2 - t1)/1000000;


        km->Reset();
        // cout<<idx_h<<endl;
        for(j = 0; j < idx_h; j++) {
            km->Update(h_list + j);
        }

        num += (uint64_t)km->Query();



        delete km;
        delete km2;
        delete km3;
        delete[] h_list;
        delete[] set_a;
        delete[] set_f;

    }

    

    cout<<fixed<<setprecision(8)<<num/iter<<endl;   // 平均基数估计值

    cout<<fixed<<setprecision(8)<<time/iter<<endl;    // 平均运行时间

    delete[] start;

    
}



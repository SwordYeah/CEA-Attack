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
针对K Minimum Values的基数膨胀攻击算法的复现，该代码为
“On the Security of the K Minimum Values (KMV) Sketch ”中3.1小节中描述攻击的复现
*/


int main(int argc, char* argv[]) {
    int memory = atoi(argv[1]);
    int lgn = 8;

    int initial = atoi(argv[2]);

    uint64_t size = initial * memory;  // 初始集合大小

    int iter = 100;  // 算法运行次数

    uint64_t* start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }


    // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列

    
    uint64_t idx = 0, idx_f = 0, j;
    double est_before, est_after;

    uint64_t idx_cnt = 0;
    // uint64_t total_num = 0;

    
    double t1, t2, time = 0;

    for(int k = 0; k < iter; k++) {
        // cout<< k+1<<endl;
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);
        


        t1 = now_us();

        // Create sketch instance
        DiscounterKM * km = new DiscounterKM(memory, lgn);
        uint64_t* set_a = new uint64_t[size];
        uint64_t* set_f = new uint64_t[size];
        

        // Update DREX
        // double t1=0, t2=0;
        idx = 0;
        idx_f = 0;

        // 论文中攻击复现，遍历初始集合，选取增加基数估计值的元素
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

        // 逆序遍历选取出的元素，仍旧选取增加基数估计值的元素加入新的攻击集中
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

        t2 = now_us();
        time = time + (t2 - t1)/1000000;

        idx_cnt += idx_f;
        // km->Reset();


        // for(j = 0; j < idx_f; j++) {
        //     km->Update(set_f + j);
        // }

    //    total_num += (uint64_t)km->Query();



        delete km;
        delete[] set_a;
        delete[] set_f;

    }

    cout<<fixed<<setprecision(8)<<idx_cnt/iter<<endl;    // 构造出的攻击集的平均大小
    // cout<<fixed<<setprecision(8)<<total_num/iter<<endl;
    cout<<fixed<<setprecision(8)<<time/iter<<endl;       //  平均运行时间

    delete[] start;

    
}



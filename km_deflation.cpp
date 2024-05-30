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
论文“On the Security of the K Minimum Values (KMV) Sketch ”中
3.2小节中描述的基数缩减攻击的复现
*/



int main(int argc, char* argv[]) {
    using namespace std;
    int memory = atoi(argv[1]);  // K的取值
    int lgn = 8;

    int multiple = atoi(argv[2]);  // t的取值关于K的倍数
    int deflat_time = atoi(argv[3]);  // 攻击集造成的基数缩减倍数
    uint64_t t = multiple * memory;  
    uint64_t total = (t + memory) * deflat_time; // 攻击集大小
    double fractor = (t - memory * log( (memory + t - 1) * 1.0 / memory ))/ (memory + t); // 每轮次选取的元素占比
    // cout<<fractor<<endl;

    int exp = 15;

    while(pow(2, exp) * fractor < total) {
        exp++;
    }
    uint64_t size = pow(2, exp);  // 初始集合大小
    // cout<<size<<endl;
    uint64_t* start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }





    uint64_t inc, j, reset_cnt = 0;
    uint64_t idx = 0, i, num = 0, total_reset = 0;
    double est, est_after;
    uint64_t real_chg = 0;

    double t1, t2, time = 0;
    j = 0;
    inc = 0;
    uint64_t k,iter = 10;
    
    for(k = 0; k < iter; k++) {
        reset_cnt = 0;
        real_chg = 0;

        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);

        t1 = now_us();

        DiscounterKM * km = new DiscounterKM(memory, lgn);
        uint64_t * set_a = new uint64_t[total];
        uint64_t idx1 = 0, est1, est_after1;

        idx = 0;
        j = 0;
        inc = 0;
        int flag = 0;

        est = km->Query();
        for(i = 0; i < size; i++) {
            j += inc;
            km->Update(start + i);
            est_after = km->Query();
            // 第一次插入元素后基数估计不变时开启计数器
            // 将不改变基数估计的元素加入攻击集
            if(est_after == est) {
                inc = 1;
                set_a[idx++] = start[i];
                if(idx == total) {
                    break;
                }
            }
            est = est_after;
            // 计数器值大于t时重置
            if(j > t) {
                km->Reset();
                j = 0;
                inc = 0;
                est = 0;
                reset_cnt++;
            }
        }
        // cout<<"idx: "<<idx<<", i: "<<i<<endl;
        // cout<<"fraction: "<<(double)idx/i<<endl;

        // cout<<(double)real_chg<<endl;

        // total_reset += reset_cnt;
        // cout<<"reset num: "<<reset_cnt<<"   ";
        // cout<<"i: "<< i<<"   "<<"idx1: "<<idx1<<endl;


        
        

        t2 = now_us();
        time = time + (t2 - t1)/1000000;


        // cout<<"idx: "<<idx<<", i: "<<i<<endl;



        km->Reset();


        for(i = 0; i < idx; i++) {
            km->Update(set_a + i);
        }

        // cout<<"Est: "<<(int)km->Query()<<endl;
        num += (uint64_t)km->Query();


        delete[] set_a;
        delete km;
    }

    cout<<fixed<<setprecision(8)<<num/iter<<endl;   // 平均基数估计值

    cout<<fixed<<setprecision(8)<<time/iter<<endl;  // 平均运行时间

    delete[] start;

    
}



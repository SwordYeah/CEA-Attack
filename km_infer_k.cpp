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
该实验为推测K Minimum Values用于计算基数估计的样本大小K的代码
*/

int main(int argc, char* argv[]) {
    using namespace std;
    int memory = atoi(argv[1]);  //K值大小
    int lgn = 8;

    uint64_t size = pow(2, 20);  //初始集合大小，可修改
    uint64_t* start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }


    // Update DREX
    uint64_t j;
    uint64_t num = 0;
    uint64_t est;

    double t1, t2, time = 0;
    j = 0;
    uint64_t k,iter = 100, k1 = 0; //iter为迭代次数
    
    for(k = 0; k < iter; k++) {
        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);

        t1 = now_us();

        DiscounterKM * km = new DiscounterKM(memory, lgn);

        for(j = 0; j < size; j++) {
            km->Update(start + j);
            
            est = km->Query();
            // cout<<j + 1<<","<<est<<"   ";
            if((j + 1) != est){
                k1 = j + 1;
                break;
            }
        }
        

        t2 = now_us();
        time = time + (t2 - t1)/1000000;

        km->Reset();

        // cout<<k1<<endl;
        num = num +  k1 - memory;

        delete km;
    }

    cout<<fixed<<setprecision(8)<<(double)num/iter/memory * 100<<"%"<<endl;    // 估计值的平均误差

    cout<<fixed<<setprecision(8)<<time/iter<<endl;   // 平均运行时间

    delete[] start;

    
}



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
针对K Minimum Values的基数膨胀攻击算法，利用KM_inflation的代码先减小初始集合大小
*/



struct IndexedValue {
    double value;
    int index;
};


// 定义比较函数，用于排序
bool compareIndexedValue(const IndexedValue& a, const IndexedValue& b) {
    return a.value < b.value;
}


int main(int argc, char* argv[]) {
    int memory = atoi(argv[1]);
    int lgn = 8;

    int initial = atoi(argv[2]);

    uint64_t size = initial * memory;  // 初始集合大小
    int iter = 100;  // 运行次数


    uint64_t* start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }

    // uint64_t num = 0;
    uint64_t idx = 0, idx_f = 0, j;
    uint64_t max1 = 0, max2 = 0;
    double est_before, est_after;


    
    double t1, t2, time = 0;

    for(int k = 0; k < iter; k++) {
        // cout<< k+1<<endl;
        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);
        


        t1 = now_us();

        // Create KMV instance
        DiscounterKM * km = new DiscounterKM(memory, lgn);
        uint64_t* set_a = new uint64_t[size];
        uint64_t* set_f = new uint64_t[size];

        idx = 0;
        idx_f = 0;

        // 先利用km_infaltion中的代码缩减初始集合大小
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

        // 后续和km_inflation2中相同
        DiscounterKM * km2 = new DiscounterKM(2, lgn);
        
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

        // cout<<max1<<"  "<<max2<<endl;
        // km2->getHash(set_f + max1);
        // km2->getHash(set_f + max2);
        // km2->getCounts();
        // cout<<int(km2->Query())<<endl;


        DiscounterKM * km3 = new DiscounterKM(3, lgn);
        int cnt = 0;
        km3->Update(set_f + max1);
        km3->Update(set_f + max2);
        double* h_list = new double[idx_f];
        for(j = 0; j < idx_f; j++) {
            km3->Update(set_f +j);
            est_after = km3->Query();
            h_list[j] = 2.0 / est_after;
            cnt++;
            km3->Reset();
            km3->Update(set_f + max1);
            km3->Update(set_f + max2);
        }
        h_list[max1] = 0;
        h_list[max2] = 0;

        // cout<<cnt<<endl;
        // cout<<int(km3->Query())<<endl;

        

     // 创建一个存储索引和值的向量
        std::vector<IndexedValue> indexedArray(idx_f);
        for (uint64_t i = 0; i < idx_f; ++i) {
            indexedArray[i].value = h_list[i];
            indexedArray[i].index = i;
        }

        // 对 indexedArray 进行排序
        std::sort(indexedArray.begin(), indexedArray.end(), compareIndexedValue);


        t2 = now_us();
        time = time + (t2 - t1)/1000000;


    //     // std::cout << "Sorted values and original indices:" << std::endl;
    //     // for (uint64_t i = 0; i < idx_f; ++i) {
    //     //     std::cout << "Value: " << indexedArray[i].value << ", Original Index: " << indexedArray[i].index << std::endl;
    //     // }


        // km->Reset();
        // // cout<<int(km->Query())<<endl;
        // for(j = 0; j < memory; j++) {
        //     km->Update(set_f + indexedArray[j].index);
        // }

        // cout<<int(km->Query())<<endl;
        // num += (uint64_t)km->Query();

        


        delete km;
        delete km2;
        delete km3;
        delete[] set_a;
        delete[] set_f;
        delete[] h_list;

    }

    
    // cout<<fixed<<(double)num/iter<<endl;
    // cout<<fixed<<setprecision(8)<<num/iter<<endl;
    cout<<fixed<<setprecision(8)<<time/iter<<endl;   // 算法的平均运行时间

    delete[] start;

    
}



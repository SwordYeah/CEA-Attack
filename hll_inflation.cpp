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

struct IndexedValue {
    double value;
    uint64_t index;
};


/*
针对HyperLogLog设计的基数膨胀攻击算法，因为推测桶的个数的算法已经证明在桶的大小达到一定值时，
推测出的大小几乎没有误差，因此下文代码假设已经推测出桶的大小，即将其当做已知条件
*/



int main(int argc, char* argv[]) {
    // pcap traces
   
    int memory = atoi(argv[1]);  //位图大小
    int lgn = 8;
    int initial = atoi(argv[2]);
    
    uint64_t size = initial * memory;   //初始集合大小
    uint64_t* start = new uint64_t[size];
    // 初始化数组，将1到size的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }
    

    // 计算HyperLogLog算法计算公式中的参数alpha_m和公式的常数部分factor
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


    std::vector<IndexedValue> indexedArray(size);


    
    uint64_t iter = 100, total_m = 0;   //iter为运行次数
    double total_num = 0;


    for(uint64_t k = 0; k < iter; k++) {

        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);


        // Create DREX instance
        DiscounterHLL * hll = new DiscounterHLL(memory, lgn);

        double est, est_now, est_before, est_after;
        
        uint64_t * set_a = new uint64_t[size];
        uint64_t * set_f = new uint64_t[size];
        
        uint64_t idx = 0, idx_f = 0, j;
        uint64_t begin, end;
        double value;

        j = 0;
        est = 0;

        // 随机插入2.8m个元素
        while(est < 2.8 * memory) {
            hll->Update(start + j);
            j++;
            est = hll->Query();
        }

        end = j;
        // cout<<end<<endl;

        // 遍历元素，筛选出增加基数估计的加入set_a
        est_before = hll->Query();
        for(; j < size; j++) {
            hll->Update(start + j);
            est_after = hll->Query();
            if(est_after > est_before) {
                // cout<<est_after<<"  "<<est_before<<endl;
                set_a[idx++] = start[j];
                est_before = est_after;
            }
        }

        // cout<<idx<<"    "<<hll->Query()<<endl;
        hll->Reset();

        // 重置后再次插入之前的2.8m个元素
        for(j = 0; j < end; j++) {
            hll->Update(start + j);
        }

        // 反向遍历set_a，筛选出增加基数估计的元素到set_f
        est_before = hll->Query();
        for(j = 1; j <= idx; j++) {
            hll->Update(set_a + idx - j);
            est_after = hll->Query();
            if(est_after > est_before) {
                // cout<<est_after<<"  "<<est_before<<endl;
                set_f[idx_f++] = set_a[idx - j];
                est_before = est_after;
            }
                    
        }

        // cout<<fixed<<idx_f<<"   "<<hll->Query()<<endl; 
        hll->Reset();

        // 把开始的2.8m个元素加入set_f
        for(uint64_t i = 0; i < end; i++) {
            set_f[idx_f++] = start[i];
        }

        // 记录set_f中元素插入到sketch后得到的基数估计值est
        for(j = 0; j < idx_f; j++) {
            hll->Update(set_f + j);
        }
        est = hll->Query();

        uint64_t * flag = new uint64_t[idx_f];
        std::fill(flag, flag + idx_f, 0);

        // 循环遍历set_f,每次插入set_f中除第i个元素之外的所有元素，
        // 与est进行比较，如果相等则把对应flag位置1，表示存在比该元素映射后前导零更大的元素
        hll->Reset();
        for(uint64_t i = 0; i < idx_f; i++) {
            for(uint64_t a = 0; a < idx_f; a++) {
                if(a == i || flag[a] == 1) {
                    continue;
                }
                hll->Update(set_f+ a);
            }
            est_now = hll->Query();
            if(est_now == est) {
                flag[i] = 1;
            }
            hll->Reset();
        }
        
        // uint64_t cnt = 0;
        // hll->Reset();
        // // cout<<hll->Query()<<endl;
        // for(int i =0; i < idx; i++) {
        //     if(indexedArray[i].value >= 5 ) {
        //         cnt++;
        //         hll->Update(start + indexedArray[i].index);
        //     }
        //     // cout<<indexedArray[i].value<<"  ";
        // }
        // cout<<cnt<<endl;

    
        // cout<<"idx: "<<idx<<endl;

        // cout<<log2(size * 1.0 / alpha_m / memory)<<endl;

        // cout<<hll->Query()<<endl;

        uint64_t cnt = 0;
        for(j = 0; j < idx_f; j++) {
            if(flag[j] == 0) {
                hll->Update(set_f + j);
                cnt++;
            }  
        }
        // cout<<cnt<<endl;
        // cout<<fixed<<hll->Query()<<endl;

        total_m +=cnt;
        total_num += hll->Query();

        delete[] set_a;
        delete[] set_f;
        delete hll;
    

    }


    cout<<total_m/iter<<endl;   // 平均攻击集大小
    cout<<fixed<<total_num/iter<<endl;  // 攻击集产生的平均基数估计大小

}


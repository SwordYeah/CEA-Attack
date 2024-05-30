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
该实验为推测HyperLogLog算法使用桶的个数的代码
*/



int main(int argc, char* argv[]) {
   
    int memory = atoi(argv[1]);  //位图大小
    int lgn = 8;
    
    uint64_t size = pow(2, 20);  //初始集合大小，可修改
    uint64_t* start = new uint64_t[size];
    // 初始化数组，将1到100万的数字依次赋值给数组的元素
    for (uint64_t i = 0; i < size; i++) {
        start[i] = i + 1;
    }
    int find_time = 0, num = 0;


    int iter = 10;  //运行次数，可修改


    while(find_time < iter) {
        // 使用随机数引擎和 std::random_shuffle 函数对数组进行随机排列
        random_device rd;
        mt19937 g(rd());
        shuffle(start, start + size, g);


        // Create sketch instance
        DiscounterHLL * hll = new DiscounterHLL(memory, lgn);

        uint64_t est_before, est_after, m;
        double avg_change= 0, change;
        uint64_t j;

        // 先向sketch中插入200个随机元素
        for(j = 0;j < 200; j++) {
            hll->Update(start + j);
        }

        // 计算插入200-400个元素的平均基数估计变化率
        est_before = hll->Query();
        for(;j < 400; j++) {   
            hll->Update(start + j);
            est_after = hll->Query();
            avg_change += double(est_after - est_before)/est_before * 100;
            est_before = est_after;
        }
        avg_change /= 200;

        // 继续插入元素，并计算每次插入后的基数估计变化率
        est_before = hll -> Query();
        while(j < size) {
            hll->Update(start + j);
            est_after = hll->Query();
            change = double(est_after - est_before)/est_before * 100;
            //如果该值小于0，则找到临界点
            if(change < 0) {
                // cout<<"xiaoyu 0"<<endl;
                m = int((double)(est_after)/2.5);
                num = num + abs((int)(m - memory));
                find_time++;
                break;
            } else if(change > 5 * avg_change) {
                //如果该值大于平均变化率的5倍，则找到临界点，5倍为根据实验测试确定的值
                m = int((double)(est_after)/2.5);
                num = num + abs((int)(m - memory));
                find_time++;
                break;
            }
            est_before = est_after;
            j++;

        }
        // if(j == size) {
        //     cout<<"can't find"<<endl;
        // } else {
        //     cout<<m<<endl;
        // }

        delete hll;
    }


    cout<<(double)num/iter/memory * 100<<"%"<<endl; // 平均相对误差

}


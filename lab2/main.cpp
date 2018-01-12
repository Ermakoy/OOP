#include<iostream>
#include<vector>
#include"StatisticMultiSet.h"

using namespace std;

int main() {
    cout << "Lab 02" << endl;
    StatisticMultiSet<int> ms1;
    ms1.addNum(89);
    ms1.addNum(54);
    ms1.addNum(54);
    ms1.addNum(24);
    StatisticMultiSet<int> ms2;
    std::vector<int> somedata = {10, 40, 6, 87};
    ms2.addNum(somedata.begin(), somedata.end());
    StatisticMultiSet<int> ms3;
    ms3.addNum(ms1);
    ms3.addNum(ms2);
    cout << " Min: " << ms3.getMin()
         << " Avg: " << ms3.getAvg()
         << " Max: " << ms3.getMax()
         << endl;
    return 0;
}
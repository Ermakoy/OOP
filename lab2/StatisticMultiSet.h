#pragma once

#include<vector>
#include<list>
#include<fstream>
#include<set>

template<class T>
class StatisticMultiSet {
public:

    StatisticMultiSet() = default;

    ~StatisticMultiSet() = default;

    void addNum(const T &num) {
        data.push_back(num);
        added(num);
    };

    void addNum(const StatisticMultiSet &set) {
        for (T x : set.data) addNum(x);
    };

    void addNum(const char *filename) {
        std::ifstream cin(filename);
        T x;
        while (!cin.eof()) {
            cin >> x;
            addNum(x);
        }
    };
    // Next func in taken from  https://edu.tochlab.net/forum/viewtopic.php?f=4&t=25
    template<class Iter>
    void addNum(Iter begin, Iter end) {
        while (begin != end) {
            data.push_back(*begin);
            added(*begin);
            ++begin;
        }
    };

    T getMin() const {
        return min;
    };

    T getMax() const {
        return max;
    };

    T getAvg() const {
        return avg;
    };

    int getCountUnder(float threshold) const {
        int count = 0;
        for (T x : data) {
            if (x < threshold)count++;
        }
        return count;
    };

    int getCountAbove(float threshold) const {
        int count = 0;
        for (T x : data) {
            if (x > threshold)count++;
        }
        return count;
    };

private:
    std::vector<T> data;
    T max;
    T min;
    double avg;

    void added(const T &num) {
        if (max < num)max = num;
        if (min > num)min = num;
        if (data.size() == 1) {
            max = num;
            min = num;
            avg = num;
        } else avg = (avg * (data.size() - 1) + num) / data.size();
    };
};

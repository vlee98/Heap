#include "heap.hpp"
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;
class Less: public BinaryOperator<int>{
public:
    Less(){};
    int operator()(int left, int right){
        if (left < right){
            return 1;
        }
        else{
            return 0;
        }
    }
};

class Greator: public BinaryOperator<int>{
public:
    Greator(){};
    int operator()(int left, int right){
        if (left > right){
            return 1;
        }
        else{
            return 0;
        }
    }
};


std::vector<double> runningMedian(vector<int> a) {
    BinaryOperator<int>* large = new Greator();
    BinaryOperator<int>* small = new Less();
    Heap<int> maxHeap(large);
    Heap<int> minHeap(small);
    std::vector<double> ret;
    ret.push_back(a[0]);
    if (a.size() > 1){
        if (a[1] > a[0]){
            minHeap.push(a[1]);
            maxHeap.push(a[0]);
        }
        else{
            minHeap.push(a[0]);
            maxHeap.push(a[1]);
        }
        ret.push_back((double)(a[1] + a[0]) / 2);
    }
    for (int i = 2; i < a.size(); ++i){
        int target = a[i];
        if (target > maxHeap.peek() ){
            minHeap.push(target);
            if (minHeap.size() - maxHeap.size() > 1){
                maxHeap.push(minHeap.pop());
            }
        }
        else{
            maxHeap.push(target);
            if (maxHeap.size() - minHeap.size() > 1){
                minHeap.push(maxHeap.pop());
            }
        }
        if (maxHeap.size() > minHeap.size()){
            ret.push_back(maxHeap.peek());
        }
        else if (maxHeap.size() < minHeap.size()){
            ret.push_back(minHeap.peek());
        }
        else{
            ret.push_back((double)(minHeap.peek() + maxHeap.peek()) / 2);
        }
    }
    return ret;
}

int main()
{

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[a_itr] = a_item;
    }
    
    std::cout << std::setprecision(1) << std::fixed;
    vector<double> result = runningMedian(a);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        cout << result[result_itr];

        if (result_itr != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";
    return 0;
}


#ifndef _HEAP_
#define _HEAP_

#include <iostream>
#include <vector>

template <typename T>
class BinaryOperator{
    public:
        BinaryOperator(){};
        virtual int operator()(T left, T right) = 0;
}; 

template <typename T>
int Comparator(T left, T right, BinaryOperator<T>* binaryOP){
    return (*binaryOP)(left,right);
}

template <typename T>
class Heap{
    public:
        Heap(BinaryOperator<T>* binary);
        void push(T value);
        T pop();
        T peek();
        int size(); 
        void toString();
    private:
        int len;
        std::vector<T>* array; 
        BinaryOperator<T> * compare;
};

template <typename T>
Heap<T>::Heap(BinaryOperator<T>* binary){
    compare = binary;
    len = 0;
    array = new std::vector<T>();
}

template <typename T>
int Heap<T>::size(){
    return len;
}   

template <typename T>
void Heap<T>::push(T value){
    array -> emplace_back(value);
    len++;
    int index = len - 1;
    int parent = (int)( (index - 1) / 2);
    while(parent >= 0 && Comparator((*array)[index], (*array)[parent], compare)){
        T temp = (*array)[index];
        (*array)[index] = (*array)[parent];
        (*array)[parent] = temp;
        index = parent;
        parent = (int)((index-1)/2);
    }
}

template <typename T>
void Heap<T>::toString(){
    for (int i = 0; i < len; ++i){
        std::cout << (*array)[i];
    }
    std::cout << std::endl;
}

template <typename T>
T Heap<T>::peek(){
    return (*array)[0];
}

template <typename T>
T Heap<T>::pop(){
    if (len == 0){
        return 1;
    }
    T ret = (*array)[0]; 
    (*array)[0] = array->back();
    array -> pop_back();
    --len;
    int pos = 0;
    while (pos < len){
        int left = pos * 2 + 1;
        int right = pos * 2 + 2;
        int target;
        if (right > len && left > len){
            break;
        }
        if (right > len){
            target = left;
        }
        else{
            if (Comparator((*array)[left], (*array)[right], compare)){
                target = left;
            }
            else{
                target = right;
            }
        }
        if (Comparator((*array)[target],(*array)[pos],compare)){
            T temp = (*array)[pos];
            (*array)[pos] = (*array)[target];
            (*array)[target] = temp;
            pos = target;
        }
        else{
            break;
        }
    }
    return ret;
}

#endif

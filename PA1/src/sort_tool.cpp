// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2016/02/25 Chih-Ming Chang]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<cstdlib>
#include<ctime>

// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int key, i;
    for (int j = 1; j < data.size(); j++) {
        key = data.at(j);
        i = j - 1;
        while(i >= 0 && data.at(i) > key) {
            data.at(i + 1) = data.at(i);
            i = i - 1;
        }
        data.at(i + 1) = key;
     }
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    SortSubVector(data, 0, data.size() - 1);
}

// Sort subvector
void SortTool::SortSubVector(vector<int>& data, int low, int high) {
    // Function : Sort subvector
    // TODO : Please complete SortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    if (high > low) {      
        int middle = (high + low) / 2;
        SortSubVector(data, low, middle);
        SortSubVector(data, middle + 1, high);
        Merge(data, low, middle, middle + 1, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    vector<int> vl, vr;
    vl.assign(data.begin() + low, data.begin() + middle1 + 1);
    vr.assign(data.begin() + middle2, data.begin() + high + 1);
    int i = 0, j = 0;
    for (int n = low; n <= high; n++) {
        if (i != middle1 - low + 1 && j != high -middle2 +1) {
            if (vl.at(i) < vr.at(j)) {
                data.at(n) = vl.at(i);
                i++;
                continue;
            }
            else {
                data.at(n) = vr.at(j);
                j++;
                continue;
            }
        }
        if (j == high -middle2 +1) {
            data.at(n) = vl.at(i);
            i++;
            continue;
        }
        if (i == middle1 - low + 1) {
            data.at(n) = vr.at(j);
            j++;
            continue;
        }
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data) {
    // Function : Quick sort
    // TODO : Please complete quick sort code here
    Random_Quick(data, 0, data.size() - 1);
}

void SortTool::Random_Quick(vector<int>& data, int p, int r) {
    if (r > p) {
        int q = Random_Partition(data, p, r);;
        Random_Quick(data, p, q - 1);
        Random_Quick(data, q + 1, r);
    }
}

int SortTool::Partition(vector<int>& data, int p, int r) {
    int pivot = data.at(r);
    int i = p - 1;
    for(int j = p; j < r; j++) {
        if (data.at(j) <= pivot) {
           i = i + 1;
           int temp = data.at(i);
           data.at(i) = data.at(j);
           data.at(j) = temp;
        }
    }
    int temp = data.at(i + 1);
    data.at(i + 1) = data.at(r);
    data.at(r) = temp;
    return i + 1;
}

int SortTool::Random_Partition(vector<int>& data, int p, int r) {
    srand(time(NULL));
    int i = rand()%(r - p + 1) + p;
    int temp = data.at(r);
    data.at(r) = data.at(i);
    data.at(i) = temp;
    return Partition(data, p, r);
}

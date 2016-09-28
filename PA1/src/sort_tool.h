// **************************************************************************
//  File       [sort_tool.h]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The header file for the SortTool Class]
//  Modify     [2016/02/25 Chih-Ming Chang]
// **************************************************************************

#ifndef _SORT_TOOL_H
#define _SORT_TOOL_H

#include<vector>
using namespace std;

class SortTool {
    public:
        
                    SortTool(); // constructor
        void        InsertionSort(vector<int>&); // sort data using insertion sort
        void        MergeSort(vector<int>&); // sort data using merge sort
        void        QuickSort(vector<int>&); // sort data using heap sort
    private:

        void        SortSubVector(vector<int>&, int, int); // sort subvector
        void        Merge(vector<int>&, int, int, int, int); // merge two sorted subvector
        void        Random_Quick(vector<int>&, int, int);
        int         Partition(vector<int>&, int, int);        
        int         Random_Partition(vector<int>&, int, int);
};

#endif

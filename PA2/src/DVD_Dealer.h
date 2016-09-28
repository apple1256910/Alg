// **************************************************************************
//  File       [DVD_Dealer.h]
//  Author     [Chih-Ming Chang]
//  Synopsis   [The header file for the DVD_Dealer Class]
//  Modify     [2016/03/15 Chih-Ming Chang]
// **************************************************************************

#ifndef _DVD_DEALER_H
#define _DVD_DEALER_H

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>

using namespace std;

int Greedy(int, int, int, vector<int>);

int DynamicProgramming(int, int, int, vector<int>);
/*
void QuickSort(vector<int>&, vector<int>&);

void Random_Quick(vector<int>&, int, int, vector<int>&);

int Partition(vector<int>&, int, int, vector<int>&);

int Random_Partition(vector<int>&, int, int, vector<int>&);

*/

bool firstCompare(const pair<int, int>&, const pair<int, int>&);

bool secondCompare(const pair<int, int>&, const pair<int, int>&);

#endif

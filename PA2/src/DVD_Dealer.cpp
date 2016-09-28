// **************************************************************************
//  File       [DVD_Dealer.cpp]
//  Author     [Chih-Ming Chang]
//  Synopsis   [The implementation of the DVD_Dealer Class]
//  Modify     [2016/03/15 Chih-Ming Chang]
// **************************************************************************

#include "DVD_Dealer.h"
#include <algorithm>

bool firstCompare(const pair<int, int>& first, const pair<int, int>& second) {
        return first.first < second.first;
}

bool secondCompare(const pair<int, int>& first, const pair<int, int>& second) {
        return first.second < second.second;
}

int Greedy(int Number_of_Songs, int Number_of_DVDs, int DVD_Constraint_Time, vector <int> songs){
	
	cout << 1 << endl;
	//TODO implement Greedy algorithm code here
        vector<pair<int, int> > songs_cpy;
        for(int i = 0; i < songs.size() - 1; i++)
            songs_cpy.push_back(make_pair(songs.at(i + 1), i + 1));
        //sorted by songs time
        stable_sort(songs_cpy.begin(), songs_cpy.end(), firstCompare);
        int number_of_select = 0;
        for( ; number_of_select < songs_cpy.size(); ++ number_of_select) 
        {
            int j = 0;
            //sorted by index
            stable_sort(songs_cpy.begin(), songs_cpy.begin() + number_of_select + 1, secondCompare);
            for(int i = 0; i < Number_of_DVDs; i++)
                for(int rest_time = DVD_Constraint_Time; j <= number_of_select ; ++j)
                {
                    if(rest_time - (songs_cpy.at(j)).first < 0) 
                        break;
                    rest_time -= (songs_cpy.at(j)).first;
                }
            --j;
            if(j != number_of_select)
                break;
        }
        return number_of_select;
}

int*** create_3D_Array(int a, int b, int c) {
	int*** A = new int**[a];
	for(int i = 0; i < a; ++i)
        {
	    A[i] = new int*[b];
            for(int j = 0; j < b; ++j)
		A[i][j] = new int[c];
	}
	for(int i = 0; i < a; ++i)
	    for(int j = 0; j < b; ++j)
		for(int k = 0; k < c; ++k) 
                {
                    if(i == 0 || j == 0)
                        A[i][j][k] = 0;
		    else
		        A[i][j][k] = -1;
                }
	return A;
}

int DP(int i, int j, int k, vector<int>& s, int*** F, int T) { 
       //have solved
	if(F[i][j][k] != -1)
            return F[i][j][k];
       //haven't solved
        //don't have space and another DVD to store the song
        if(j == 1 && k < s.at(i))
            F[i][j][k] = DP(i-1, j, k, s, F, T);
        //have space to store the song
        if(k >= s.at(i)) 
            F[i][j][k] = max(DP(i-1, j, k-s.at(i), s, F, T) + 1, DP(i-1, j, k, s, F, T));
         //don't have space to store the song
          //the song bigger than the DVD
        else if(s.at(i) > T)
            F[i][j][k] = DP(i-1, j, k, s, F, T);
        else
            F[i][j][k] = max(DP(i, j-1, T, s, F, T), DP(i-1, j, k, s, F, T));
        return F[i][j][k];
}

int DynamicProgramming(int Number_of_Songs, int Number_of_DVDs, int DVD_Constraint_Time, vector <int> songs){
	cout << 2 << endl;
	//TODO implement Dynamic Programming algorithm code here
        int*** F = create_3D_Array(Number_of_Songs + 1, Number_of_DVDs + 1, DVD_Constraint_Time + 1);
        DP(Number_of_Songs, Number_of_DVDs, DVD_Constraint_Time, songs, F, DVD_Constraint_Time);
        return F[Number_of_Songs][Number_of_DVDs][DVD_Constraint_Time];
}

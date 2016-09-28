// **************************************************************************
//  File       [main.cpp]
//  Author     [Chih-Ming Chang]
//  Synopsis   [The main file]
//  Modify     [2016/03/15 Chih-Ming Chang]
// **************************************************************************

#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include "../lib/tm_usage.h"
#include "DVD_Dealer.h"

using namespace std;

void help_message() {
    cout << "usage: DVD_Dealer -[GD|DP] <input_file> <output_file>" << endl;
    cout << "options:" << endl;
    cout << "   GD  - Greedy" << endl;
    cout << "   DP  - Dynamic Programming" << endl;
}

int main(int argc, char* argv[])
{
	int max_songs = 0;
	
    if(argc != 4) {
       help_message();
       return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    //////////// read the input file /////////////

    ifstream fin(argv[2]);
    if(!fin.is_open()){
        cout<<"Cannot open input file \""<<argv[2]<<"\"!!"<<endl;
        return false;
    }
	int Number_of_Songs, Number_of_DVDs, DVD_Constraint_Time;
	
	fin >> Number_of_Songs >> Number_of_DVDs >> DVD_Constraint_Time;
	
	vector <int> songs(Number_of_Songs+1);
	
	////// be careful! song number 1 is stored at song[1] //////
	for ( int i=1;i<=Number_of_Songs;++i ){
		fin >> songs[i];
	}

    //////////// find the Maximum songs /////////////
    tmusg.periodStart();

    if(strcmp(argv[1], "-GD") == 0) {
        // greedy
        max_songs = Greedy(Number_of_Songs, Number_of_DVDs, DVD_Constraint_Time, songs);
    }
    else if(strcmp(argv[1], "-DP") == 0) {
        // dynamic programming
        max_songs = DynamicProgramming(Number_of_Songs, Number_of_DVDs, DVD_Constraint_Time, songs);
    }
    else {
        help_message();
        return 0;
    }

    tmusg.getPeriodUsage(stat);

    //////////// write the output file ///////////

    // Place print the following message in the output file
    ofstream fout(argv[3]);
	
	fout << max_songs << endl;
    
    fout.close();

    cout <<"# run time = " << (stat.uTime + stat.sTime) / 1000000.0 << " sec" << endl;
    cout <<"# memory =" << stat.vmPeak / 1000.0 << " MB" << endl;


    return 0;
}


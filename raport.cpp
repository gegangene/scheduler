//
// Created by Bartłomiej Pruszczyk on 21/01/2024.
//

#include <fstream>
#include <vector>
#include <iostream>
#include "raport.h"

using namespace std;


bool newComeVisualiseReport(vector<int> tab[], int &tact, fstream &fOutput)
{
	string processes;
	bool gained_=false;
	for(int i=0; i<tab[0].size(); ++i)
	{
		if(tab[2][i]==tact)
		{
			gained_=true;
			processes+=to_string(tab[0][i])+"  ";
		}
	}
	if(gained_)
	{
		fOutput<<"\n"<<tact<<"\tgained new processes: "<<processes;
	}
	return gained_;
}

void ageing(vector<int> tab[], fstream &fOutput)
{

}

void mainReport(vector<int> tab[], float avg, fstream &fOutput)
{
	fOutput<<"average waiting time: "<<avg<<"\n\n";
	// tab : {so-called number of process : tacts : tactOfBeginning}
	fOutput<<"tact\tPID\twaited for ... tacts\n--------------------------------------";
	int tact=0;
	for(int i=0; i</*sum*/tab[0].size(); ++i)
	{
		bool showed_=false;
		for(int ii=0; ii<tab[1][i]; ++ii)
		{
			string tactVisual=newComeVisualiseReport(tab,tact,fOutput)?"":to_string(tact);
			if(!showed_)
			{
				fOutput<<"\n"<<tactVisual<<"\t"<<tab[0][i]<<"\t"<<tact-tab[2][i];
				showed_=true;
			}
			tact++;
		}
	}
}


void generateReport(vector<int> tab[], float avg)
{
	fstream fOutput("../output.txt",ios::out);
	mainReport(tab,avg,fOutput);
}
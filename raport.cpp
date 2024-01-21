//
// Created by Bartłomiej Pruszczyk on 21/01/2024.
//

#include <fstream>
#include <vector>
#include <iostream>
#include "raport.h"
#include "miscMultialgFuns.h"

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

void ageing(vector<int> tab[], int &tact, fstream &fOutput)
{
	string mess;
	bool gained_=false;
	for(int i=0; i<tab[0].size(); ++i)
	{
		if(tab[2][i]==tact)
		{
			gained_=true;
			mess+="["+to_string(tab[0][i])+"|"+to_string(tab[1][i])+"]  ";
		}
	}
	if(gained_)
	{
		fOutput<<"\n"<<tact<<"\tprocesses with increased priority [ID|newPriority]: "<<mess;
	}
}

void mainReport(vector<int> tab[], float avg, fstream &fOutput)
{
	fOutput<<"average waiting time: "<<avg<<"\n\n";
	// tab : {so-called number of process : tacts : tactOfBeginning}
	fOutput<<"tact\tPID\t\twaiting time\n-------------------------------";
	int tact=0;
	for(int i=0; i</*sum*/tab[0].size(); ++i)
	{
		bool showed_=false;
		for(int ii=0; ii<tab[1][i]; ++ii)
		{
			if(!showed_)
			{
				fOutput<<"\n"<<tact<<"\t\t"<<tab[0][i]<<"\t\t"<<tact-tab[2][i];
				showed_=true;
			}
			tact++;
		}
	}
	fOutput<<"\n\nimportant changes during the operation of the simulation:\nTact:	What happened:\n------------------------------------------------------------";
	for(int i=0; i<vecSum(tab[0]); ++i)
	{
		newComeVisualiseReport(tab,i,fOutput);
	}
}

void mainReport(vector<int> tab[], float avg, fstream &fOutput, vector<int> priorityChanges[])
{
	fOutput<<"average waiting time: "<<avg<<"\n\n";
	// tab : {so-called number of process : tacts : tactOfBeginning}
	fOutput<<"tact\tPID\t\twaiting time\tpriority:\n--------------------------------------------";
	int tact=0;
	for(int i=0; i</*sum*/tab[0].size(); ++i)
	{
		bool showed_=false;
		for(int ii=0; ii<tab[1][i]; ++ii)
		{
			if(!showed_)
			{
				fOutput<<"\n"<<tact<<"\t\t"<<tab[0][i]<<"\t\t"<<tact-tab[2][i]<<"\t\t\t\t"<<tab[3][i];
				showed_=true;
			}
			tact++;
		}
	}

	fOutput<<"\n\nimportant changes during the operation of the simulation:\nTact:	What happened:\n------------------------------------------------------------";
	for(int i=0; i<vecSum(tab[0]); ++i)
	{
		newComeVisualiseReport(tab,i,fOutput);
		ageing(priorityChanges, i, fOutput);
	}
}


void generateReport(vector<int> tab[], float avg)
{
	fstream fOutput("../output.txt",ios::out);
	mainReport(tab,avg,fOutput);
}

void generateReport(vector<int> tab[], float avg, vector<int> priorityChanges[])
{
	fstream fOutput("../output.txt",ios::out);
	mainReport(tab,avg,fOutput,priorityChanges);
}
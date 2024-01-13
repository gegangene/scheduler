//
// Created by Bartłomiej Pruszczyk on 13/01/2024.
//

#include <vector>
#include <iostream>
#include "visualisation.h"

using namespace std;

bool newComeVisualise(vector<int> tab[], int &tact)
{
	string processes;
	bool gained_=false;
	for(int i=0; i<tab[0].size(); ++i)
	{
		if(tab[2][i]==tact)
		{
			gained_=true;
			processes+='P'+to_string(tab[0][i])+"  ";
		}
	}
	if(gained_)
	{
		cout<<"\n"<<tact<<"\tgained new processes: "<<processes;
	}
	return gained_;
}

void visualisation(vector<int> tab[], float avg)
{
	cout<<"average waiting time: "<<avg<<"\n\n";
	cout<<"visualisation of algorithm:\n";
	// tab : {so-called number of process : tacts : tactOfBeginning}
	cout<<"tact\tid\twaited for ... tacts\n--------------------------------------";
	int tact=0;
	for(int i=0; i</*sum*/tab[0].size(); ++i)
	{
		bool showed_=false;
		for(int ii=0; ii<tab[1][i]; ++ii)
		{
			string tactVisual=newComeVisualise(tab,tact)?"":to_string(tact);
			if(!showed_)
			{
				cout<<"\n"<<tactVisual<<"\t'P"<<tab[0][i]<<"'\t"<<tact-tab[2][i];
				showed_=true;
				wait();
			}
			tact++;
		}
	}
}

void wait()
{
	for(long i=INT_MIN/3;i<0; ++i);
}
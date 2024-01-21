//
// Created by Bartłomiej Pruszczyk on 13/01/2024.
//

#include <vector>
#include <iostream>
#include "visualisation.h"
#include "raport.h"

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
		wait(1);
	}
	return gained_;
}

void visualisation(vector<int> tab[], float avg)
{
	int tact=0;
	cout<<"visualisation of algorithm:\n";
	// tab : {so-called number of process : tacts : tactOfBeginning}
	cout<<"tact (starting tact)\t\t\t\t(ending tact):\n--------------------------------------";
	for(int i=0; i</*sum*/tab[0].size(); ++i)
	{
		bool showed_=false;
		bool gainedNew_=false;
		for(int ii=0; ii<tab[1][i]; ++ii)
		{
			if(newComeVisualise(tab,tact)&&!gainedNew_)
				gainedNew_=true;
			if(!showed_)
			{
				string afterGained=gainedNew_?"\n":"";
				cout<<afterGained;
				cout<<"\n"<<tact<<"\t|-------------------------------|\n";
					  "|          PID: xxxx            |\n"
					  "|        Arr. tact: xxxx        |\n"
					  "|       Waited for: xxxx        |\n"
					  "|     Process duration: xx      |\n"
					  "|-------------------------------|\n"
					  "|         Priority: x           |\n"
					  "|-------------------------------|";
				size_t spacesNo=15-to_string(tab[0][i]).size();
				string spacesStr=string(spacesNo,' ');
				cout<<"\t|           PID: "<<tab[0][i]<<spacesStr<<"|\n";
				cout<<"\t|-------------------------------|\n";
				spacesNo=11-to_string(tab[2][i]).size();
				spacesStr=string(spacesNo,' ');
				cout<<"\t|         Arr. tact: "<<tab[2][i]<<spacesStr<<"|\n";
				spacesNo=11-to_string(tact-tab[2][i]).size();
				spacesStr=string(spacesNo,' ');
				cout<<"\t|        Waited for: "<<tact-tab[2][i]<<spacesStr<<"|\n";
				spacesNo=8-to_string(tab[1][i]).size();
				spacesStr=string(spacesNo,' ');
				cout<<"\t|     Process duration: "<<tab[1][i]<<spacesStr<<"|\n";
				cout<<"\t|-------------------------------|\t"<<tact+tab[1][i]<<"\n";
				showed_=true;
//				wait(tab[1][i]);
			}
			tact++;
		}
	}
	cout<<"\n\naverage waiting time: "<<avg;
	generateReport(tab, avg);
}

void wait(int givenInt)
{
	for(long i=LONG_MIN/100000000000*givenInt;i<0; ++i);
}
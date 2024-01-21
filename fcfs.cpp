//
// Created by Bartłomiej Pruszczyk on 13/01/2024.
//

#include <vector>
#include "miscMultialgFuns.h"
#include "visualisation.h"
#include "fcfs.h"

void fcfs(std::vector<int> tab[])
{
	sortVec(tab,0,4);
	int time=0;
	// {waitingTime}
	std::vector<int> timeTab;
	// {id : tacts : arriving}
	std::vector<int> toDraw[3];
	for(std::size_t i=0; i<tab[0].size(); ++i)
	{
		timeTab.push_back(time-tab[0][i]);
		time+=tab[1][i];
	}
	toDraw[0]=tab[2];
	toDraw[1]=tab[1];
	toDraw[2]=tab[0];
	visualisation(toDraw,avg(timeTab));
}
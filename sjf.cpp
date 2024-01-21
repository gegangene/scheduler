//
// Created by Bartłomiej Pruszczyk on 13/01/2024.
//

#include <vector>
#include "miscMultialgFuns.h"
#include "visualisation.h"
#include "sjf.h"

void sjf(std::vector<int> tab[])
{
	// array of processes currently available to put on processor.
	// **use only when sorted!**
	// {id : tacts : arriving}
	std::vector<int> currentlyAvailable[3];
	// {waitingTime}
	std::vector<int> timeTab;
	// array for "drawing" - visualisation function
	// {id : tacts : arriving}
	std::vector<int> toDraw[3];

	// tacts needed to complete all processes
	int tacts=vecSum(tab[1]);

	// processor busy status indicator
	bool busy_=false;
	// tacts lasts to end current process
	int toEndCurrent=0;

	// for every tact, check what's going on in there
	for(int i=0; i<tacts; ++i)
	{
		for(std::size_t ii=0; ii<tab[0].size(); ++ii)
		{
			// loading processes gained in current tact
			if(i==tab[0][ii])
			{
				currentlyAvailable[0].push_back(tab[2][ii]);
				currentlyAvailable[1].push_back(tab[1][ii]);
				currentlyAvailable[2].push_back(tab[0][ii]);

			}
		}

		// sorting available processes by tacts
		sortVec(currentlyAvailable,1,3);

		//loading process on processor
		if(!busy_)
		{
			busy_=true;
			toDraw[0].push_back(currentlyAvailable[0][0]);
			toDraw[1].push_back(currentlyAvailable[1][0]);
			toDraw[2].push_back(currentlyAvailable[2][0]);
			timeTab.push_back(i-currentlyAvailable[2][0]);
			toEndCurrent=currentlyAvailable[1][0]-1;
			currentlyAvailable[0].erase(currentlyAvailable[0].begin());
			currentlyAvailable[1].erase(currentlyAvailable[1].begin());
			currentlyAvailable[2].erase(currentlyAvailable[2].begin());
		}

		else
		{
			if(toEndCurrent==0)
			{
				busy_=false;
			}
			--toEndCurrent;
		}
	}

	visualisation(toDraw,avg(timeTab));
}

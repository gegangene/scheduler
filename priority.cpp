//
// Created by Bartłomiej Pruszczyk on 13/01/2024.
//

#include <vector>
#include "miscMultialgFuns.h"
#include "visualisation.h"
#include "priority.h"

void priority(std::vector<int> tab[])
{
	// array of processes currently available to put on processor.
	// **use only when sorted!**
	// {id : tacts : arriving : priority}
	std::vector<int> currentlyAvailable[4];

	// vector for waiting times
	// {waitingTime}
	std::vector<int> timeTab;
	// array for "drawing" - visualisation function
	// {id : tacts : arriving : priority}
	std::vector<int> toDraw[4];
	// array for priority changes
	// {id : newPriority : tact}
	std::vector<int> priorityChanges[3];

	// tacts needed to complete all processes
	int tacts=vecSum(tab[1]);

	// processor busy status indicator
	bool busy_=false;
	// tacts lasts to end current process
	int toEndCurrent=0;

	// for every tact, check what's going on in there
	for(int i=0; i<tacts; ++i)
	{
		// increasing priority for old processess every tab[4][0] tacts
		for(int ii=0; ii<currentlyAvailable[0].size(); ++ii)
		{
			if((i-currentlyAvailable[2][ii])%tab[4][0]==0 && i!=0)
			{
				if(currentlyAvailable[3][ii]>0)
				{
					currentlyAvailable[3][ii]--;
					//cout<<"increased priority of process no "<<currentlyAvailable[0][ii]<<" at tact "<<i<<". current priority: "<<currentlyAvailable[3][ii]<<"\n";
					priorityChanges[0].push_back(currentlyAvailable[0][ii]);
					priorityChanges[1].push_back(currentlyAvailable[3][ii]);
					priorityChanges[2].push_back(i);
				}
			}
		}

		for(size_t ii=0; ii<tab[0].size(); ++ii)
		{
			// loading processes gained in current tact
			if(i==tab[0][ii])
			{
				currentlyAvailable[0].push_back(tab[2][ii]);
				currentlyAvailable[1].push_back(tab[1][ii]);
				currentlyAvailable[2].push_back(tab[0][ii]);
				currentlyAvailable[3].push_back(tab[3][ii]);
			}
		}

		// sorting available processes by tacts and then priorities (which correspondents as prioritizing processes priorities)
		sortVec(currentlyAvailable,1,4);
		sortVec(currentlyAvailable,3,4);

		//loading process on processor
		if(!busy_)
		{
			busy_=true;
			for(int ii=0; ii<4; ii++)
			{
				toDraw[ii].push_back(currentlyAvailable[ii][0]);
			}
			timeTab.push_back(i-currentlyAvailable[2][0]);
			toEndCurrent=currentlyAvailable[1][0]-1;
			for(auto &ii: currentlyAvailable)
			{
				ii.erase(ii.begin());
			}
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
	visualisation(toDraw,avg(timeTab),priorityChanges);
}
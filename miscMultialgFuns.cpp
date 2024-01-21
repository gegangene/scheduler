//
// Created by Bartłomiej Pruszczyk on 13/01/2024.
//

#include <vector>
#include "miscMultialgFuns.h"

int vecSum(std::vector<int> &tab)
{
	int sum=0;
	for(auto &i: tab)
		sum+=i;
	return sum;
}

float avg(std::vector<int> &tab)
{
	return static_cast<float>(vecSum(tab))/static_cast<float>(tab.size());
}

void sortVec(std::vector<int> tab[], char row, char noOfRows)
{
	for(std::size_t ipre=1; ipre<tab[0].size(); ++ipre)
		for(std::size_t i=1; i<tab[0].size(); ++i)
		{
			int temp[noOfRows];
			if(tab[row][i-1]>tab[row][i])
			{
				for(int ii=0; ii<noOfRows; ++ii)
				{
					temp[ii]=tab[ii][i-1];
					tab[ii][i-1]=tab[ii][i];
					tab[ii][i]=temp[ii];
				}
			}
		}
}
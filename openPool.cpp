//
// Created by Bartłomiej Pruszczyk on 21/01/2024.
//

#include <vector>
#include "openPool.h"
#include "miscMultialgFuns.h"
#include <iostream>

void processAdd(std::vector<int> tab[])
{
	std::cout<<"Your actual range of tacts: 0-"<<vecSum(tab[1])<<". On which you want your process to be added?\n>> ";
	int onTact;
	std::cin>>onTact;
	std::cout<<"Put duration time of your process\n>> ";
	int tacts;
	std::cin>>tacts;
	std::cout<<"Put priority of your process (0 - greatest; 255 - lowest)\n>> ";
	int prior;
	std::cin>>prior;
	tab[0].push_back(onTact);
	tab[1].push_back(tacts);
	tab[2].push_back(tab[2][tab[2].size()-1]+1);
	tab[3].push_back(prior);
	std::cin.ignore();
}
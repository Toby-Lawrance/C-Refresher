#pragma once

#include <iostream>
#include <vector>

//Pine Tree
void PrintATree(int height)
{
	/*
	 * Print a Pine tree in the form
	 *         *
	 *		  ***
	 *		 *****
	 *		*******
	 *	   *********
	 *	       |
	 *
	 * With a total height of height
	 *
	 * Bonus exercise, decorate the tree with other characters that look nice
	 */
}

void RemoveDuplicates()
{
	std::vector<int> values{ 1,2,2,3,5,7,1,2,6,23,7,2,1,1,5,5,3,2,7,8,9,5,3,5,4,5,7,33,12,145,122,22,12,1 };

	//Print out the contents of the collection above such that each number only appears once.
	//Bonus, print them out in order
}


void PrepareExercises()
{
	std::cout << "Enter tree height: ";
	int height = 1;
	std::cin >> height;
	PrintATree(height);

	std::cout << std::endl << std::endl;

	RemoveDuplicates();
}
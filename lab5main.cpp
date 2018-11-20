/*
 * lab5main.cpp
 *
 *  Created on: Nov 14, 2018
 *      Author: patrickshannon
 */

#include "makeSeuss.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){
	srand(time(0));
	cout << "make Seuss called" << endl;
	//makeSeuss Seuss1 = makeSeuss("DrSeuss.txt", "run1.txt", true, true);
	makeSeuss Seuss2 = makeSeuss("DrSeuss.txt", "run2.txt", true, false);
	//makeSeuss Seuss3 = makeSeuss("DrSeuss.txt", "run3.txt", false, true);
	makeSeuss Seuss4 = makeSeuss("DrSeuss.txt", "run4.txt", false, false);



	return 0;
}



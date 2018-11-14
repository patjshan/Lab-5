/*
 * Node.cpp
 *
 *  Created on: Nov 8, 2018
 *      Author: patrickshannon
 */

#include "hashNode.hpp"


hashNode::hashNode(){
	valuesSize = 0;
	currSize = 0;
	keyword = "";
	values = NULL;
	searched = false;
}

hashNode::hashNode(string s){
	keyword = s;
	valuesSize = 100;
	currSize = 0;
	values = new string[valuesSize];
	searched = false;

}

hashNode::hashNode(string s, string v){
	keyword = s;
	valuesSize = 100;
	currSize = 1;
	values = new string[valuesSize];
	values[0] = v;
	searched = false;

}

void hashNode::addValue(string v){
	int t = 0;
	while(values[t] != ""){
		t++;
	}
	values[t] = v;

}

void hashNode::dblArray(){
	int nwvaluesSize = 2 * valuesSize;
	string *dblarr = new string[nwvaluesSize];
	string *tmparr = values;
	values = dblarr;

	for(int i = 0; i < valuesSize; i++){
		addValue(tmparr[i]);
	}
	valuesSize = nwvaluesSize;

	delete [] tmparr;
}

string hashNode::getRandValue(){
	if(values[0] == ""){
		string empty = "";
		return empty;
	}
	else{
		int rvals = rand() % valuesSize - 1;
		while(values[rvals] == "null"){
			rvals = rand() % valuesSize - 1;
		}
		return values[rvals];
	}
}



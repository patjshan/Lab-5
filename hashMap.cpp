/*
 * hashMap.hpp
 *
 *  Created on: Nov 12, 2018
 *      Author: patrickshannon
 */

#include "hashMap.hpp"

hashMap::hashMap(bool hash1, bool coll1){
	mapSize = 137;
	map = new hashNode*[mapSize]{NULL};
	h1 = hash1;
	c1 = coll1;
	numKeys = 0;
	collisionct1 = 0;
	collisionct2 = 0;
	first = "";

}


void hashMap::addKeyValue(string k, string v){


}

int hashMap::calcHash(string k){
	int strhsh = 0;
	for(int i = 0; i < k.length(); i++){
		strhsh += int(k[i]);
		strhsh = strhsh % mapSize;
	}
	return strhsh;
}

int hashMap::calcHash2(string k){
	int strhsh = 0;
	for(int i = 0; i < k.length(); i++){
		strhsh = int(k[i]) * 7;
		strhsh = strhsh % mapSize;
	}
	return strhsh;

}
int hashMap::getIndex(string k){
	int tmp = calcHash(k);
	reHash();
	return (tmp);
}

void hashMap::reHash(){


}

int hashMap::collHash1(int h, int i , string k){

}

int hashMap::collHash2(int h, int i, string k){

}

int hashMap::findKey(string k){

}

void hashMap::getClosestPrime(){


}

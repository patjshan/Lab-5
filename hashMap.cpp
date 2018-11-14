/*
 * hashMap.hpp
 *
 *  Created on: Nov 12, 2018
 *      Author: patrickshannon
 */

#include "hashMap.hpp"

hashMap::hashMap(bool hash1, bool coll1){ // initializes hashMap properties
	mapSize = 137;
	cout << "calling hashNode array constructor" << endl;
	map = new hashNode*[mapSize];
	h1 = hash1;
	c1 = coll1;
	numKeys = 0;
	collisionct1 = 0;
	collisionct2 = 0;
	first = "";

}


void hashMap::addKeyValue(string k, string v){ // checks the hash value and adds the key
	//value pair if the index is unoccupied, if it is occupied the collision handling
	//methods are called
	int index;
	if (h1){
		cout << "call calc-hash" << endl;
		index = calcHash(k);
		cout << "out of calc-hash : "<< index << endl;
	}
	else{
		index = calcHash2(k);
	}
	bool inserted = false;
	int colls = 0;;

	cout << "in while insertion" << endl;

	while(!inserted){
		if(map[index] == NULL){ // add the hashNode with key value pair to the hashMap
			cout << "found NULL index" << endl;
			map[index] = new hashNode(k , v);
			inserted = true;
			numKeys ++;
			cout << "added" << endl;
		}
		else if (map[index]->keyword == k){ // if the key already exists add the value to the values list
			map[index]->addValue(v);
			inserted = true;
		}
		else if (map[index]->keyword != k && colls < 1){ // if the index already has a different key word add one to the collision counters
			collisionct1 ++;
			colls++;
		}
		else if (colls == 1){ // if there is one collision, use the appropriate collision handler
			if (c1){
			index = collHash1(index);
			}
			else{
				index = collHash2(colls, index);
			}
		}
		else{ // each time there is a collision past the first add one to collision tracker 2 and colls
			collisionct2 ++;
			colls++;
			if (c1){
				index = collHash1(index);
			}
			else{
				index = collHash2(colls, index);
			}
		}
	}
	cout << "out of while insert" << endl;
	cout << numKeys << endl;

	if (numKeys * 100 / mapSize >= 70){
		reHash();
	}
	cout << "done with addkey" << endl;

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
	int nwSize = getClosestPrime();
	hashNode ** tmp = map;
	map = new hashNode*[nwSize];
	int i  = 0;
	while(i < mapSize){
		int length = tmp[i]->valuesSize;
		for(int j = 0; j < length; j++){
			addKeyValue(tmp[i]->keyword, tmp[i]->values[j]);
		}
	}

	for(int j = 0; j < mapSize; j++){
		delete [] tmp[j];
	}
	delete[] tmp;
	mapSize = nwSize;
}

int hashMap::collHash1(int i){ //linear probing
	return (i + 1) % mapSize;


}

int hashMap::collHash2(int h, int i){ // quadratic probing
	return (i + h * h) % mapSize;
}

int hashMap::findKey(string k){
	int index;
	if(h1){
		index = calcHash(k);
	}
	else{
		index = calcHash2(k);
	}
	bool found = false;
	int ct = 0;
	while(!found){
		if( map[index] == NULL){ // if the loop comes upon an empty slot, that means that key word was never inserted
			index = -1;
			found = true;
		}
		else if (map[index]->keyword == k){ // if key matches k then return the index of k
			found = true;
		}
		else{ // if there is a different key in that index follow the collision handling methods
			ct ++ ;
			if(c1){
				index = collHash1(index);
			}
			else{
				index = collHash2(ct, index);
			}
		}
	}
	return index;

}

int hashMap::getClosestPrime(){
	int k;
	int tmp = mapSize * 2;
	k = tmp / 6;
	bool prime = true;
	for(int j = 2; j < tmp / 2; j++){
		if(tmp % j == 0){
			prime = false;
			break;
		}
	}
	while(!prime){
		k ++;
		for(int j = 2; j < tmp / 2; j++){
			if(tmp % j == 0){
				prime = false;
				break;
			}
		}
	}
	return 6 * k + 1;

}

void hashMap::printMap(){
	for(int n = 0; n < mapSize; n++){
		if(map[n] == NULL){
			cout << "NULL" << endl;
		}
		else{
			cout << map[n]->keyword << ": " << endl;
			for(int j = 0; j < map[n]->values->length(); j++){
				cout << map[n]->values[j];
			}
			cout << endl;
		}
	}
}


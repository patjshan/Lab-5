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
	for(int i = 0; i < mapSize; i++){
		map[i] = NULL;
	}
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
	cout << k << " : " << v << endl;
	if (h1){ // hash the key to get the intended index
		cout << "call calc-hash" << endl;
		index = calcHash(k);
		cout << "out of calc-hash : "<< index << endl;
	}
	else{
		index = calcHash2(k);
	}
	bool inserted = false; // flag to tell whether the value has been inserted
	int colls = 0;

	cout << "in while insertion" << endl;

	while(!inserted){
		//cout<<  "in while : "<< index <<endl;
		if(map[index] == NULL){ // add the hashNode with key value pair to the hashMap
			cout << "found NULL index" << endl;
			map[index] = new hashNode(k , v);
			inserted = true;
			numKeys ++;
			cout << "added" << endl;
		}
		else if (map[index]->keyword == k){ // if the key already exists add the value to the values list
			//cout << "ahh" << endl;
			map[index]->addValue(v);
			cout << "added stuff" << endl;
			inserted = true;
		}
		else if (map[index]->keyword != k && colls < 1){ // if the index already has a different key word add one to the collision counters
			//cout << "ahhhh" << endl;
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
	cout << numKeys << " : numKeys" << endl;

	if (numKeys * 100 / mapSize >= 70){
		cout << "calling rehash" << endl;
		reHash();
	}
	cout << "done with addKey" << endl;

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
	int tmp = 0;
	if(h1){
		tmp = calcHash(k);
	}
	else{
		tmp = calcHash2(k);
	}
	bool found = false;
	int colls = 0;
	cout << "get index while" << endl;
	while(!found){
		if (map[tmp]->keyword ==  k){
					found = true;
		}
		else if (c1){
			colls++;
			tmp = collHash1(tmp);
		}
		else{
			colls ++;
			tmp = collHash2(colls, tmp);
			cout << tmp << endl;
			cout << colls << endl;
		}
	}
	cout << "done with get index" << endl;
	return tmp;
}

void hashMap::reHash(){
	cout << "in reHash" << endl;
	int nwSize = getClosestPrime();
	hashNode ** tmp = map;
	map = new hashNode*[nwSize];
	for(int n = 0; n < nwSize; n++){
		map[n] = NULL;
	}
	int tmpSize = mapSize;
	mapSize = nwSize;
	int i  = 0;
	cout << "entering while for rehash" << endl;
	while(i < tmpSize){
		if(tmp[i] == NULL){
		}
		else{
			int length = tmp[i]->valuesSize;
			for(int j = 0; j < length; j++){
				if(tmp[i]->values[j] == ""){

				}
				else{
				addKeyValue(tmp[i]->keyword, tmp[i]->values[j]);
				}
			}
		}
		i++;
	}
	cout << "done with while for rehash" << endl;

	for(int j = 0; j < tmpSize; j++){
		delete tmp[j];
	}
	delete[] tmp;
	cout << "done with reHash : " << mapSize << endl;
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
	cout << "in get closest prime" << endl;
	int k;
	int tmp = mapSize * 2;
	cout << "made tmp" << endl;
	k = tmp / 6;
	bool prime = true;
	for(int j = 2; j < tmp / 2; j++){
		if(6*k + 1 % j == 0){
			prime = false;
			break;
		}
	}
	cout << "checked prime" << endl;
	while(!prime){
		k ++;
		for(int j = 2; j < tmp / 2; j++){
			if(6*k + 1 % j == 0){
				prime = false;
				break;
			}
		}
	}
	cout << "done with getclosestprime" << endl;
	return (6 * k + 1);

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


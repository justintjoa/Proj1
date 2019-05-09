#include "StringHashes.h"
#include "HashSet.h"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

void HashSet::insert(const std::string& value) {
	//cout << "hash Designed" << endl;
	//cout << nitems << endl;
	//cout << nslots << endl;
	string* newstring;
	newstring = new string;
	*newstring = value;
	uint64_t input;
	input = (*strfn).hash(value);
	uint64_t index;
	index = (*intfn).hash(input);
	//cout << index << endl;
	//cout << slots[index] << endl;
	if ((slots[index]) == NULL) {
		//cout << "about to add" << endl;
		(slots[index]) = newstring;
		//cout << "added fine" << endl;
	}
	else {
		//cout << "doubled" << endl;
		input = (*strfn2).hash(value);
		int index;
        index = (*intfn).hash(input);
		while((slots[index]) != NULL) {
			index++;
			if (index >= nslots) {
				index = 0; 
			}
		}
		(slots[index]) = newstring;
		//cout << *(slots[index]) << endl;
		//cout << "doubled fine" << endl;

	}
	//cout << "veg" << endl;
	nitems++;
	rehash();
}

bool HashSet::lookup(const std::string& value) const {
	//cout << "hash look" << endl;
		uint64_t input;
        input = (*strfn).hash(value);
        int index;
        index = (*intfn).hash(input);
        if (slots[index] != NULL) {
       	 	if ((*(slots[index])) == value) {
        		return true;
			}
		}
        int i;
        i = 0;
        input = (*strfn2).hash(value);
        index = (*intfn).hash(input);
	     while((i < nslots)) {
                        //cout << "its fine" << endl;
	       			if (index >= nslots) {
                               // cout << "manny" << endl;
						index = 0;
                 	}
                 	if (slots[index] != NULL) {
                 		if ((*(slots[index])) == value) {
				//cout << "sugar" << endl;
							return true;
                 		}
				
					}
			//cout << "cans" << endl;
					index++;
                	i++;
					if (index >= nslots) {
						index = 0;
					}
		}		
		//cout << "track" << endl;
        return false;	
	
}

HashSet::HashSet() {
	//cout << "hash create" << endl;
	nitems = 0;
	nslots = 200;
	intfn = new DivisionHash(11, nslots);
	strfn = new JenkinsHash();
	strfn2 = new PearsonHash();
	slots = new string*[nslots];
	for (int i = 0; i < nslots; i++) {
		//(slots[i]) = new string;		
		(slots[i]) = NULL;
	}
}

void HashSet::rehash() {
	//cout << "hash rehash" << endl;


	if (nitems == nslots) {
			string** p1; 
            p1 = slots;
            int newsize;
            newsize = nslots*2;
            string** p2; 
            p2 = new string*[newsize];
            for (int i = 0; i < newsize; i++) {
                   // p2[i] = new string;
                    (p2[i]) = NULL;
            }
			slots = p2; 
            int oldsize;
			oldsize = nslots;
			nslots = newsize;
			delete intfn;
			intfn = new DivisionHash(11, nslots);
			for (int i = 0; i < oldsize; i++) {
                if (p1[i] != NULL) {
                	 insert(*(p1[i]));
                }
            }   
            for (int i = 0; i < oldsize; i++) {
                if (p1[i] != NULL) {
                      delete (p1[i]);
                }
            }   
            delete[] p1; 
	}   
	
}

HashSet::~HashSet() {
	//cout << "delete hash" << endl;
	delete intfn;
	delete strfn;
	delete strfn2;
	for (int i = 0; i < nslots; i++) {
               if (slots[i] != NULL) {
                      delete (slots[i]);
               }
    }   
    delete [] slots;
}


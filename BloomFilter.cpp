#include "IntegerHashes.h"
#include "StringHashes.h"
#include "BloomFilter.h"
#include <cstdint>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;

BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn) {
	//cout << intfn << endl;
	//cout << "initiate" << endl;
	this->k = k;
	this->m = m;
	if (strcmp(strfn.c_str(), "jenkins") == 0) {
		this->strfn = new JenkinsHash();
	}
	if (strcmp(strfn.c_str(), "pearson")  == 0) {
		this->strfn = new PearsonHash();
	}
	this->intfns = new IntegerHash*[k];
	string a;
	a = "";
	for (unsigned int i = 0; i < intfn.length(); i++) {
		if (intfn[i] == ',') {
			a = "";
			continue;
		}
		if (intfn[i] == ' ') {
			continue;
		}
		else {
			a += intfn[i];
			if (strcmp(a.c_str(), "division") == 0) {
              			for (int i = 0; i < k; i++) {  
							(this->intfns)[i] = new DivisionHash(i, m);
        				}
			}
        		if (strcmp(a.c_str(), "reciprocal") == 0) {
        			  for (int i = 0; i < k; i++) {
                                        (this->intfns)[i] = new ReciprocalHash(i, m);
                       }
			}
        		if (strcmp(a.c_str(), "squareroot") == 0) {
				  for (int i = 0; i < k; i++) {
                                        (this->intfns)[i] = new SquareRootHash(i, m);
                  }	
			}

		}
	}	
	(this->bits) = new uint64_t[m];
	for (int i = 0; i < m; i++) {
		bits[i] = 0; 
	}
	//int rem;
	//rem = 64 - m;
	//int top;
	//top = 64;  //set every other bit to 1 that is not the first k
	//for (int i = 0; i < rem; i++) {
	//	int target;
	//	target = *bits;
	//	target = target + pow(2,top);
	//	*bits = target;
	//	top--;
	//}
}

BloomFilter::~BloomFilter() {
	//cout << "about to delete bloom" << endl;
	delete strfn;
	for (int i = 0; i < k; i++) {
		delete intfns[i];
	}
	delete [] intfns;
	delete [] bits;
}

void BloomFilter::insert(const std::string& value) {
	//cout << "lm" << endl;
	//cout << k << endl;
	uint64_t input;
	input = strfn -> hash(value);
	//std::cout<<input<<std::endl;
	for (int i = 0; i < k; i++) {
		uint64_t entry;
		entry = intfns[i] -> hash(input);
		//std::cout<<entry<<std::endl;
		//if (entry < 64) {
			bits[entry] = 1;
		//}
		////else {
			//cout << "too big" << endl;
		//}
	}
	//cout << input << endl;
}

bool BloomFilter::lookup(const std::string& value) const {
	//cout << "lemon" << endl;
	uint64_t input;
    input = (*(strfn)).hash(value);
	for (int i = 0; i < k; i++) {
				uint64_t standard;
                standard = (*(intfns[i])).hash(input);
                if (bits[standard] == 1) {
                	continue;
                }
                else {
                	return false;
                }
     }
		return true;
}

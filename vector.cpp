#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <vector>
#include <list>
#include<time.h>
using namespace std;
using std::vector;
using std::cout;
using std::endl;
using std::list;
int main(){
	vector<int> a;
	for (int i = 0; i < 10; ++i){
		a.push_back(i);
	}
	vector< vector<int>> b;
	b.push_back(a);
	b.push_back(a);
	b.push_back(a);
	b.push_back(a);
	b.push_back(a);
	for (int i = 0; i < b[0].size(); ++i){
		cout<<b[0].begin().[i] <<endl;
	}
}
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
struct Pokeparada{ //estructura
	int id;
	int cluster;
	int beneficios;
};
void imprimirvector(vector<Pokeparada> a){
	for (int j = 0; j < a.size(); j++) {								// imprime arreglo de struct pokeparada con id, cluster al que pertenece y beneficios
		cout<<"La pokepara numero "<<a[j].id<<endl;
		cout<<"Pertenece al cluster "<< a[j].cluster<<endl;
		cout<<"Tiene unos beneficios de "<<a[j].beneficios<<endl;
		cout<<"----------------------------------"<<endl;
	}
}
vector<int> eliminarnodo(vector<int>b, int id){
	for (int i = 0; i < b.size(); i++){
		if(b[i]==id){
			b.erase(b.begin()+i);
			break;
		}
	}
	return b;
}
int idmenorvalor(vector<int> a, int nodoactual, double matrix[5][5]){
	double nodomenor;
	int valor;
	valor=matrix[nodoactual][a[0]];
	nodomenor=a[0];
	if(a.size()>1){
		for (int i = 1; i < a.size(); ++i)	{
			if(valor>matrix[nodoactual][a[i]]){
				valor=matrix[nodoactual][a[i]];
				nodomenor=a[i];
			}
		}
		return nodomenor;
	}else{
		return nodomenor;
	}
}
int nodomenorvaor(vector<int> a,int idmenor){
	for (int i = 0; i <a.size() ; ++i){
		if(a[i]==idmenor){
			return i;
		}
	}
}
vector<int> greedy(vector<int> a, int nodoinicio,double matrix[5][5]){
	vector<int> ids;
	for (int i = 0; i < a.size(); ++i){
		ids.push_back(i);
	}
	vector<int> solucion;
	int idactual,next;
	idactual=nodoinicio;
	solucion.push_back(idactual);
	ids=eliminarnodo(ids,idactual);
	while(ids.size()!=0){
		idactual=idmenorvalor(ids,idactual,matrix);
		next=nodomenorvaor(ids,idactual);
		solucion.push_back(ids[next]);
		ids.erase(ids.begin()+next);
	}
	solucion.push_back(nodoinicio);
	return solucion;

}
int main(int argc, char* argv[]){
	vector<int> a;
	a.push_back(0);
	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	double matrix[5][5]={
		0,2,3,5,1,
		2,0,4,2,1,
		3,4,0,5,6,
		5,2,5,0,2,
		1,1,6,2,0
	};
	vector<int> solucion=greedy(a,atoi(argv[1]) ,matrix);
	for (int i = 0; i < solucion.size(); ++i){
		cout<<solucion[i]<<" ";
	}
	cout<<endl;

}
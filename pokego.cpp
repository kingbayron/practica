#include <iostream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <vector>
#include <list>
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
int main(int argc, char* argv[]){ 
	for (int i = 1; i < argc; i++){										// for lectura multiples archivos tsp
		cout<<"Se esta estudiando el archivo "<<argv[i]<< endl;			// archivo que e leera en ese omento
		string linea,arbol;													// string para lectura archivo
		int nodos;														// numero de nodos
		int clusters;													// numero de clusters
		char linea1[100];												// arreglo de caracteres para el uso de tokenizar
		int id;															// id del nodo
		int clust;														// cluster al que pertenece el nodo
		int pokeparada;													// beneficios de la pokeparada
		char *ptr;														// ptr para tokenizar
		int x;															// coordenada x para costo de viaje entre nodos
		int y;															// coordenada y para costo de viaje entre nodos
		double costo;													// costo de viaje entre nodos
		ifstream archivo;												// creacion de archivo
		archivo.open(argv[i],ios::in);									// apertura de archivo
		getline(archivo,linea);											// obtencion linea del archivo
		strcpy(linea1,linea.c_str());									// pasar string a arreglo de caracteres
		ptr = strtok(linea1," ");										//  tokenizar arreglo de caracteres
		while(ptr != NULL){		
			if(strcmp(ptr,"Nodes")==0){
				ptr = strtok(NULL, " ");
				nodos=atoi(ptr);										// ingreso numero de nodos a la variable
				cout<<"Existen este nuemro de nodos "<<nodos<<endl;
			}
			ptr = strtok(NULL, " ");
		}
		getline(archivo,linea);											//obtencion nueva linea de archivo
		strcpy(linea1,linea.c_str());
		ptr = strtok(linea1," ");
		while(ptr != NULL){
			if(strcmp(ptr,"Clusters")==0){
				ptr = strtok(NULL, " ");
				clusters=atoi(ptr);										//ingreso numero de cluster a variable
				cout<<"Existen este nuemro de clusters "<<clusters<<endl;
			}
			ptr = strtok(NULL, " ");
		}
		cout<<"----------------------"<<endl;
		double precios[nodos][nodos];									// matriz de precios de viajar de un nodo a otro
		Pokeparada pokeparadas[nodos];									// arreglo de Struct Pokeparada
		for (int i = 0; i < nodos; i++) {								// ingreso Struct a Arreglo "pokeparada"
			getline(archivo,linea);
			strcpy(linea1,linea.c_str());
			ptr = strtok(linea1," ");
			ptr = strtok(NULL, " ");
			id=atoi(ptr);												// id struct
			ptr = strtok(NULL, " ");
			clust=atoi(ptr);											// cluster struc
			ptr = strtok(NULL, " ");
			pokeparada=atoi(ptr);
			Pokeparada a;												// beneficios Struct
			a.id=id;													//ingreso de variables a struct
			a.cluster=clust;
			a.beneficios=pokeparada;
			pokeparadas[i]=a;											// ingreso struct a Arreglo de struct
		}
		for (int j = 0; j < nodos; j++) {								// imprime arreglo de struct pokeparada con id, cluster al que pertenece y beneficios
			cout<<"La pokepara numero "<<pokeparadas[j].id<<endl;
			cout<<"Pertenece al cluster "<< pokeparadas[j].cluster<<endl;
			cout<<"Tiene unos beneficios de "<<pokeparadas[j].beneficios<<endl;
			cout<<"----------------------------------"<<endl;
		}
		while(!archivo.eof()){											// lectura de archivpo para obtencion de costos deviaje entre nodos
			getline(archivo,linea);
			if(linea.empty()){
				break;
			}
			strcpy(linea1,linea.c_str());
			ptr = strtok(linea1," ");
			ptr = strtok(NULL, " ");
			x=atoi(ptr);												// obtencion coordenada x (nodo partida)
			ptr = strtok(NULL, " ");
			y=atoi(ptr);												// obtencion coordenada y (nodo llegada)
			ptr = strtok(NULL, " ");
			costo=atof(ptr);											// obtencion costo viaje
			precios[x][y]=costo;										// ingreso costo a la matriz con x,y /partida, llegada
			precios[y][x]=costo;										// ingreso costo a matriz con y, x / llegada, partida
		}
		for (int i = 0; i < nodos; i++) {								// imprimir matriz de costos
			precios[i][i]=0;
			for (int j = 0; j < nodos; j++) {
				cout<<precios[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<"\nFunciono\n"<<endl;
	}
	return 0;
}

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
struct Pokeparada{ 														//estructura
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
double costoviaje(vector<Pokeparada> a,vector< vector<double>> matrix){ //calcula costo de un vector de estructura sumando el valor de un punto a otro
	double costo;														
	int anterior,siguiente;
	anterior=a[0].id;													//primer nodo del tour
	for (int i = 1; i < a.size(); ++i){									// evalua los costos desde el primer nodo con el segundo, el segundo con el tercero....y n-1 con n
		siguiente=a[i].id;												//asignacion de siguiente (sigueitne nodo a anterior )
		costo=costo+matrix[anterior][siguiente];						//suma de costos
		anterior=siguiente;												//nodo sigueinte pasa a ser anterior 
	}
	return costo;
}
void imprimirsolucion(vector<Pokeparada> a){							// imprime id de vector de struct
	for (int i = 0; i < a.size(); ++i){
		cout<<a[i].id<<" ";
	}
	cout<<endl;
}
vector<Pokeparada> eliminarnodo(vector<Pokeparada>b, int id){			//elimina nodo de un vector de struct
	for (int i = 0; i < b.size(); i++){									//busca id que se desea eleminar
		if(b[i].id==id){
			b.erase(b.begin()+i);										//elimina nodo 
			break;
		}
	}
	return b;
}
int idmenorvalor(vector<Pokeparada> a, int nodoactual,vector< vector<double>> matrix){		//busca el nodo con menor costo desde nodo actual 
	double nodomenor;
	int valor;
	valor=matrix[nodoactual][a[0].id];														// costo desde nodo actual al primer nodo de vector de struct(primer nodo de os nodos que van quedando)
	nodomenor=a[0].id;																		//nodo menor va a ser en un principio el primer nodo del vector de struct(nodos que van quedando)
	if(a.size()>1){																			// si exsiste mas de un nodo se busca el que tiene menor costo sino seria el nodo que queda
		for (int i = 1; i < a.size(); ++i)	{												// se evalua el nodo con menor costo desde nodo actual al nodo i
			if(valor>matrix[nodoactual][a[i].id]){											// si valor es mayor que el costo desde nodo actual al nodo i 
				valor=matrix[nodoactual][a[i].id];											// valor pasa a ser el costo desde el nodo actual al nodo i 
				nodomenor=a[i].id;															// y nodo menor pasa a ser el nodo i
			}
		}
		return nodomenor;																	//retorna el id del nodo menor
	}else{
		return nodomenor;
	}
}
int nodomenorvaor(vector<Pokeparada> a,int idmenor){										// busca la posicion en el vector de struct donde se encuentra el id 										
	for (int i = 0; i <a.size() ; ++i){
		if(a[i].id==idmenor){
			return i;																		// retorna la posicion del nodo con id(idmenor) del vector
		}
	}
}
vector<Pokeparada> greedy(vector<Pokeparada> a, int nodoinicio,vector< vector<double>> matrix){ // algoritmo para una primera aproximacion del problema
	vector<Pokeparada> ids=a;																	// copia de vector de struct
	vector<Pokeparada> solucion;																// solucion de greedy, inicia vacia
	int idactual,next;	
	idactual=nodoinicio;																		// id actual es igual al nodo que se entrega en el programa, desde donde se parte
	solucion.push_back(a[idactual]);															// se le agrega a solicon el nodo de partida
	ids=eliminarnodo(ids,idactual);																// se elimina de ids el nodo de partida
	while(ids.size()!=0){																		// mientras el vector de struct tenga nodos se precede al algoritmo
		idactual=idmenorvalor(ids,idactual,matrix);												// se busca el nodo(id) con menor distancia desde id actual
		next=nodomenorvaor(ids,idactual);														// se busca la posicion del nodo/ id con menor costo desde id actual
		solucion.push_back(ids[next]);															// se agrega a solucion el nodo que esta en la posicion con menor costo
		ids.erase(ids.begin()+next);															// se elimina de ids(la copia de vectores) el nodo recien agregado a la solucion
	}
	solucion.push_back(a[nodoinicio]);															// se agrega el nodo inicial a solucion para terminar el recorrido
	return solucion;																			//retorna solucion

}
int main(int argc, char* argv[]){									
		cout<<"Se esta estudiando el archivo "<<argv[1]<< endl;			// archivo que e leera en ese omento
		string linea,arbol;												// string para lectura archivo
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
		archivo.open(argv[1],ios::in);									// apertura de archivo
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
		double precios[493][493];									// matriz de precios de viajar de un nodo a otro
		vector<Pokeparada> pokeparadas;									// vector de Struct Pokeparada
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
			pokeparadas.push_back(a);									// ingreso struct a vector de struct
		}
		vector< vector<double>> vecotorcosotos;							//vector de vectores de double
    	vector<double> precio;											//vector de double
		imprimirvector(pokeparadas);
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
		for (int i = 0; i < nodos; ++i){								// algoritmo para psar de matriz a vector de vectores de double
			for (int j = 0; j < nodos; ++j){
				precio.push_back(precios[i][j]);						// ingreso de valores a vector de double
			}
			vecotorcosotos.push_back(precio);							// ingreso de vector de double a vector
			precio.erase(precio.begin(),precio.begin()+precio.size());	// borrado de vector de double para reiniciar ingreso
		}
		cout<<"\nSolucion algoritmo greedy vecino mas cercano\n"<<endl;
		vector<Pokeparada> solucion=greedy(pokeparadas,atoi(argv[2]) ,vecotorcosotos);// busqueda de primera solucion con algoritmo greddy
		cout<<"\nCosto del viaje\n"<<endl;
		costo=costoviaje(solucion,vecotorcosotos);						// calculo de costo de viaje de la solucion
		cout<<costo<<endl;
		return 0;
	}

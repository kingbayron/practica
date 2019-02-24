#include <iostream>
#include <fstream>
#include <stdbool.h>
#include <utility>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <vector>
#include <map>
#include<cmath>
#include <cstdlib>
#include <ctime>
#include<sys/stat.h>
using namespace std;
using std::vector;
using std::map;
using std::cout;
using std::endl;
unsigned t0,t1;
typedef pair<int, vector<int> > par;
typedef pair<int, int > parint;
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
int idmenorvalor2(vector<int> a, int nodoactual,vector< vector<double>> matrix){		//busca el nodo con menor costo desde nodo actual 
	double nodomenor;
	int valor;
	valor=matrix[nodoactual][a[0]];														// costo desde nodo actual al primer nodo de vector de struct(primer nodo de os nodos que van quedando)
	nodomenor=a[0];																		//nodo menor va a ser en un principio el primer nodo del vector de struct(nodos que van quedando)
	if(a.size()>1){																			// si exsiste mas de un nodo se busca el que tiene menor costo sino seria el nodo que queda
		for (int i = 1; i < a.size(); ++i)	{												// se evalua el nodo con menor costo desde nodo actual al nodo i
			if(valor>matrix[nodoactual][a[i]]){											// si valor es mayor que el costo desde nodo actual al nodo i 
				valor=matrix[nodoactual][a[i]];											// valor pasa a ser el costo desde el nodo actual al nodo i 
				nodomenor=a[i];															// y nodo menor pasa a ser el nodo i
			}
		}
		return nodomenor;																	//retorna el id del nodo menor
	}else{
		return nodomenor;
	}
}
int aidi(vector<int> a, int id){
	for (int i = 0; i < a.size(); ++i){
		if(id==a[i]){
			return i;
		}
	}
}
int nodomenorvaor2(vector<int> a,int idmenor){										// busca la posicion en el vector de struct donde se encuentra el id 										
	for (int i = 0; i <a.size() ; ++i){
		if(a[i]==idmenor){
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
vector<int> greddy2(vector<int>a,int nodoinicio,vector< vector<double>> matrix){
	vector<int> aux=a;
	aux.erase(aux.begin()+(aux.size()-1));
	vector<int>solucion;
	int idactual,next;
	idactual=nodoinicio;
	solucion.push_back(idactual);
	aux.erase(aux.begin()+idactual);
	while(aux.size()!=0){																		// mientras el vector de struct tenga nodos se precede al algoritmo
		idactual=idmenorvalor2(aux,idactual,matrix);												// se busca el nodo(id) con menor distancia desde id actual
		next=nodomenorvaor2(aux,idactual);														// se busca la posicion del nodo/ id con menor costo desde id actual
		solucion.push_back(aux[next]);															// se agrega a solucion el nodo que esta en la posicion con menor costo
		aux.erase(aux.begin()+next);															// se elimina de ids(la copia de vectores) el nodo recien agregado a la solucion
	}
	solucion.push_back(a[nodoinicio]);															// se agrega el nodo inicial a solucion para terminar el recorrido
	return solucion;
}
void printVec(vector<int> vect){
    ///imprime vector
	for(int i = 0; i < vect.size(); i++)
		cout<<vect[i]<<" ";
	cout<<endl;
}

void printVect(vector<double> vect){
    ///imprime vector
	for(int i = 0; i < vect.size(); i++)
		cout<<vect[i]<<" ";
	cout<<endl;
}
vector<int> shuffle(vector<int> a) {
	vector<int> vect=a;
	int inicio, fin;
	inicio = 1+rand()%(a.size()-2);
	fin = 1+rand()%(a.size()-2);
    //cout<<inicio<<" "<<fin<<endl;
	swap(vect[inicio],vect[fin]);
	//printVec(vect);
	return vect;
}

bool metropolis(int fx, int fx1, double T){
    /**
    * Calcula el valor de la distribución de boltzman
    * para obtener el resultado del paso de metropolis.
    */
	double boltzman;
	boltzman = exp(-1*(fx1-fx)/T);
	if(boltzman < rand()/RAND_MAX)
		return false;
	return true;
}
double calculaValor(vector<int> vect,vector<vector<double> > ciudades){
	if(vect.size()==0){
		return 0;
	}
	double costo;														
	int anterior,siguiente;
	anterior=vect[0];													//primer nodo del tour
	for (int i = 1; i < vect.size(); ++i){									// evalua los costos desde el primer nodo con el segundo, el segundo con el tercero....y n-1 con n
		siguiente=vect[i];												//asignacion de siguiente (sigueitne nodo a anterior )
		costo=costo+ciudades[anterior][siguiente];						//suma de costos
		anterior=siguiente;												//nodo sigueinte pasa a ser anterior 
	}
	return costo;
}
void escribirfile(ofstream &outputFile,vector<int> vect,vector<vector<double> > a){
	for(int i = 0; i < vect.size(); i++)
		outputFile<<vect[i]<<" ";
	outputFile<<endl;
	outputFile<<"Costo Solucion: "<<calculaValor(vect,a)<<endl;
	outputFile<<"La solucion tiene un largo de: "<<vect.size()<<endl;
}

vector<int> simulated(vector<int> vect,double Temp,double converg,vector<vector<double> > ciudades){
	vector<int> probable,actual;
	double T=Temp;
	double v_cong=converg;
	int v_actual,v_probable;
    //Obtenemos una solución inicial
	probable=shuffle(vect);
	actual=probable;
	v_actual=calculaValor(actual,ciudades);
	do{
        //Obtenemos una nueva solucion aleatoria
		probable=actual;
		probable=shuffle(probable);
        //Obtenemos el costo de la solucion candidato
		v_probable = calculaValor(probable,ciudades);
		if(v_actual > v_probable){
			actual=probable;
			v_actual = v_probable;
			probable=actual;
		}
		else if(metropolis(v_actual,v_probable,T)){
			actual=probable;
			v_actual = v_probable;
			probable=actual;
		}
        //Disminuimos T
		T=T*0.99;
	}while(T>v_cong);
	return actual;
}
vector<int> realsimu(vector<int> vect,double Temp,double converg,vector<vector<double> > ciudades){
	vector<int> actual,probable,inicio;
	actual=vect;
	inicio=actual;
	probable=actual;
	double v_actual,v_probable;
	int T=Temp;
	v_probable=calculaValor(actual,ciudades);
	for (int i = 0; i < 10; ++i){
		actual=simulated(actual,Temp,converg,ciudades);
		v_actual=calculaValor(actual,ciudades);
		if(v_actual<v_probable){
			probable=actual;
			v_probable=v_actual;
		}
		actual=vect;
		T=Temp;
	}
	return probable;

}
vector<int> structaint(vector<Pokeparada> a){
	vector<int> b;
	for (int i = 0; i < a.size(); ++i){
		b.push_back(a[i].id);
	}
	return b;
}
vector<double> costosprom(vector<vector<double> > a,int b){
	double costoprom;
	vector<double> cost;
	for (int i = 0; i < a.size(); ++i){
		for (int j = 0; j < a.size(); ++j){
			costoprom=costoprom+a[i][j];
		}
		costoprom=(costoprom/(a.size()-1));
		cost.push_back(costoprom);
	}
	cost[b]=0;
	return cost;
}
int idcostopromayor(vector<double> a){
	double b=0;
	int id;
	for (int i = 0; i < a.size(); ++i){
		if(a[i]>b){
			b=a[i];
			id=i;
		}
	}
	return id;
}

map<int,vector<int> > cluster(int numcluster,vector<Pokeparada> b){
	map<int, vector<int> > clusters;
	vector<int> a;
	for (int i = 0; i < numcluster; ++i){
		clusters.insert(par(i,a));
	}
	for (int i = 0; i < b.size() ; ++i){
		clusters[b[i].cluster].push_back(b[i].id);
	}
	return clusters;

}
map<int,int> mapaverif(int numcluster){
	map<int,int> a;
	for (int i = 0; i < numcluster; ++i){
		a.insert(parint(i,0));
	}
	return a;
}
map<int,int> clustervisitado(int id, map<int,int> b){
	map<int,int> a=b;
	if(a[id]==0){
		a[id]=1;
	}
	return a;
}
bool verificacionclusters(map<int,int>a){
	int b=0;
	for (int i = 0; i < a.size(); ++i){
		if(a[i]==1){
			b=b+1;
		}
		if(b==a.size()){
			return true;
		}
	}
	return false;
}
int valorenmapa(int a,map<int,vector<int> > b){
	map<int, vector<int> >::iterator p = b.begin();
		while (p != b.end() ){
			for (int i = 0; i < p->second.size(); ++i){
				if(p->second[i]==a){
					return p->first;
				}
			}
			p++;
		}
}
bool recorridocontodoslosclusters(vector<int> a, map<int,vector<int> > b, map<int,int>c){
	map<int,int> mapa=c;
	for (int i = 0; i < a.size(); ++i){
		mapa=clustervisitado(valorenmapa(a[i],b),mapa);
		if(verificacionclusters(mapa)==1){
			return true;
		}
	}
	if(verificacionclusters(mapa)==1){
		return true;
	}else{
		return false;
	}
}
vector<int> complementosol(vector<int>solucion,vector<int>complemento){
	if(solucion.size()==0){
		return complemento;
	}else{
		vector<int> a=complemento;
		vector <int> b=solucion;
		b.erase(b.begin()+(b.size()-1));
		for (int i =(b.size()-1); i >= 0; --i){
			a[b[i]]=-1;
		}
		for (int i = a.size()-1; i >= 0; --i){
			if(a[i]==-1){
				a.erase(a.begin()+i);
			}
		}
		return a;
	}
	
}
string fecha(){
	time_t now=time(0);
	tm *time=localtime(&now);
	string dia =to_string(time->tm_mday);
	string mes = to_string(time->tm_mon+1);
	string year= to_string(time->tm_year+1900);
	string hour= to_string(time->tm_hour);
	string min= to_string(time->tm_min);
	string seg= to_string(time->tm_sec);
	string fecha=dia+"M"+mes+"Y"+year+"_H"+hour+"M"+min+"S"+seg;
	return fecha;

}
void crearGML(vector<int>nuevasolucion,vector<int>complementosolucion ,char*a,int nodos){
	ofstream Graphics(strcat(a,"/Grafico.gml"));
	if (!Graphics.is_open()) { // check for successful opening
		cout << "Output file could not be opened Terminating" << endl;
		exit(-1);
	}
	Graphics << "graph [ hierarchic 1 directed 1" << endl;

	for ( int j = 0; j < complementosolucion.size(); j++){

		Graphics << "node [ id " << complementosolucion[j]<< " "
		<< "graphics [ x " << rand()%nodos * 10 << " "
		<< "y " << rand()%nodos * 10 << " "
		<< "w 11  h 11 type \"roundrectangle\"] LabelGraphics"
		<< " " << "[text " << " " << "\"" << complementosolucion[j]
		<< "\"" << " " << "fontSize 7 ] ]" << endl;

	}
	if(nuevasolucion.size()!=0){
		Graphics << "node [ id " << nuevasolucion[0] << " "
		<< "graphics [ x " << rand()%nodos * 10 << " "
		<< "y " << rand()%nodos * 10  << " "
		<< "w 11  h 11 type \"triangle\" fill  \"#008080\"] LabelGraphics"
		<< " " << "[text " << " " << "\""
		<< nuevasolucion[0] << "\"" << " " << "fontSize 7 ] ]" << endl;
		for (int i = 1; i < nuevasolucion.size()-1; i++){
			Graphics << "node [ id " << nuevasolucion[i] << " "
			<< "graphics [ x " << rand()%nodos * 10 << " "
			<< "y " << rand()%nodos * 10  << " "
			<< "w 11  h 11 type \"triangle\" fill  \"#FF6600\"] LabelGraphics"
			<< " " << "[text " << " " << "\""
			<< nuevasolucion[i] << "\"" << " " << "fontSize 7 ] ]" << endl;
		}

		for (int l = 1; l < nuevasolucion.size(); ++l)
		{
			Graphics << "edge [ source " << " " << nuevasolucion[l-1];

			Graphics << " " << "target" << " "
			<< nuevasolucion[l] << " " << "graphics [ fill \""
			<< "#5E5E5E" << "\" targetArrow \"standard\" ] ]"
			<< endl;
		}
	}
	Graphics << "]" << endl;
	Graphics.close();
}
void imprimierbeneficios(vector<Pokeparada>a,vector<int>b,ofstream &outputFile){
	int beneficios=0;
	for (int i = 0; i < b.size(); ++i){
		beneficios=beneficios+a[b[i]].beneficios;
	}
	outputFile<<"El camino tiene unos beneficios de: "<<beneficios<<endl;
}

int main(int argc, char* argv[]){
		t0=clock();
		char str[100];
		char str1[100];
		strcpy(str,argv[1]);
		strcat(str,"_");
		strcat(str,argv[2]);
		strcat(str,"_");
		strcat(str,argv[3]);
		strcat(str,"D");
		strcat(str,fecha().c_str());
		cout<<fecha()<<endl;
		mkdir(str,0777);
		strcpy(str1,str);
		ofstream outputFile(strcat(str,"/Soluciones.txt"));		
		if (!outputFile.is_open()) { // check for successful opening
			cout << "Outneeeeeelile could not be opened Terminating" << endl;
		}
		outputFile<<"Se esta estudiando el archivo "<<argv[1]<< endl;			// archivo que e leera en ese omento
		outputFile<<"Partiendo del nodo: "<< argv[2]<<endl;
		outputFile<<"Con un presupuesto maximo de: "<<argv[3]<<endl;
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
				clusters=atoi(ptr)+1;										//ingreso numero de cluster a variable
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
		map<int,vector<int> > mapaclusters = cluster(clusters,pokeparadas);
		map<int,int> mapaverificacion=mapaverif(clusters);

		map<int, vector<int> >::iterator p = mapaclusters.begin();
		while (p != mapaclusters.end() )
		{
			cout << setw(10) << p->first << setw(10); 
			for (int i = 0; i < p->second.size(); ++i){
				cout<<p->second[i]<<" ";
			};
			cout<<endl;
			p++;
		}

		cout << "........................\n";
		cout<<"\nSolucion algoritmo greedy vecino mas cercano\n"<<endl;
		vector<Pokeparada> solucion=greedy(pokeparadas,atoi(argv[2]) ,vecotorcosotos);// busqueda de primera solucion con algoritmo greddy
		imprimirsolucion(solucion);
		cout<<"\nCosto del viaje\n"<<endl;
		costo=costoviaje(solucion,vecotorcosotos);						// calculo de costo de viaje de la solucion
		cout<<costo<<endl;
		cout<<"La solucion tiene un largo de: "<<solucion.size()<<endl;
		cout<<"---------------------------"<<endl;
		vector<int> nuevasolucion=structaint(solucion);
		vector<int> complementosolucion=structaint(pokeparadas);
		bool verdad=recorridocontodoslosclusters(nuevasolucion,mapaclusters,mapaverificacion);
		double T = 3906290;
    //v_cong es el valor de congelacion, que marca
    //el final del algoritmo
		double v_cong = 0.05;
		if(costo<atof(argv[3])){
			t1=clock();
			double time = (double(t1-t0)/CLOCKS_PER_SEC);
			cout << "Execution Time: " << time << endl;
			exit(-1);
		}
		nuevasolucion=realsimu(nuevasolucion,T,v_cong,vecotorcosotos);
		//double v_probable=calculaValor(nuevasolucion,vecotorcosotos);
		double nuevocosto=calculaValor(nuevasolucion,vecotorcosotos);
		cout<<"solucion simulated aneling"<<endl;
		printVec(nuevasolucion);
		escribirfile(outputFile,nuevasolucion,vecotorcosotos);
		imprimierbeneficios(pokeparadas,nuevasolucion,outputFile);
		cout<<"Costo solucion: "<<nuevocosto<<endl;
		cout<<"---------------------------"<<endl;
		verdad=recorridocontodoslosclusters(nuevasolucion,mapaclusters,mapaverificacion);
		vector<double> costospromedios=costosprom(vecotorcosotos,atoi(argv[2]));
		while(nuevocosto>atof(argv[3])){
			if(nuevasolucion.size()-1==mapaverificacion.size()){
				outputFile<<"\nNo existe solucion con el costo de viaje pedido"<<endl;
				nuevasolucion.erase(nuevasolucion.begin(),nuevasolucion.begin()+nuevasolucion.size());
				escribirfile(outputFile,nuevasolucion,vecotorcosotos);
				imprimierbeneficios(pokeparadas,nuevasolucion,outputFile);
				break;
			}
			int idcos=idcostopromayor(costospromedios);
			int aidis=aidi(nuevasolucion,idcos);
			vector <int> aux=nuevasolucion;
			nuevasolucion.erase(nuevasolucion.begin()+aidis);
			verdad=recorridocontodoslosclusters(nuevasolucion,mapaclusters,mapaverificacion);
			while(verdad==0){
				nuevasolucion=aux;
				costospromedios[idcos]=0;
				idcos=idcostopromayor(costospromedios);
				aidis=aidi(nuevasolucion,idcos);
				aux=nuevasolucion;
				nuevasolucion.erase(nuevasolucion.begin()+aidis);
				verdad=recorridocontodoslosclusters(nuevasolucion,mapaclusters,mapaverificacion);
				if(nuevasolucion.size()-1==mapaverificacion.size()){
					outputFile<<"No existe solucion con el costo de viaje pedido"<<endl;
					nuevasolucion.erase(nuevasolucion.begin(),nuevasolucion.begin()+nuevasolucion.size());	
					escribirfile(outputFile,nuevasolucion,vecotorcosotos);
					imprimierbeneficios(pokeparadas,nuevasolucion,outputFile);
				}
			}
			if(verdad==1){
				cout<<"recorre todos los clusters"<<endl;
				cout<<"---------------------------"<<endl;
			}
			costospromedios[idcos]=0;
			nuevasolucion=greddy2(nuevasolucion,atoi(argv[2]) ,vecotorcosotos);
			nuevasolucion=realsimu(nuevasolucion,T,v_cong,vecotorcosotos);
			printVec(nuevasolucion);
			escribirfile(outputFile,nuevasolucion,vecotorcosotos);
			imprimierbeneficios(pokeparadas,nuevasolucion,outputFile);
			nuevocosto=calculaValor(nuevasolucion,vecotorcosotos);
			cout<<"costo del camino "<<nuevocosto<<endl;
			cout<<"La solucion tiene un largo de: "<<nuevasolucion.size()<<endl;

		}
		cout<<"---------------------------"<<endl;
		cout<<"La solucion optima es: ";
		printVec(nuevasolucion);
		escribirfile(outputFile,nuevasolucion,vecotorcosotos);
		imprimierbeneficios(pokeparadas,nuevasolucion,outputFile);
		nuevocosto=calculaValor(nuevasolucion,vecotorcosotos);
		cout<<"Con el siguiente costo en distancia: "<<nuevocosto<<endl;
		printVec(complementosolucion);
		//verdad=recorridocontodoslosclusters(nuevasolucion,mapaclusters,mapaverificacion);
		
		complementosolucion=complementosol(nuevasolucion,complementosolucion);
		int aux1=0;
		while(aux1==0){
			crearGML(nuevasolucion,complementosolucion,str1,nodos);	
			aux1++;
		}
		
		t1=clock();
		double time = (double(t1-t0)/CLOCKS_PER_SEC);
		cout << "Execution Time: " << time <<" Segundos"<< endl;
		outputFile<<"Execution Time: " << time <<" Segundos"<< endl;
		outputFile.close();
		return 0;
	}
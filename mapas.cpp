#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <iomanip>
#include <vector>

using namespace std;
using std::vector;
/*----------------------------------------*/
typedef pair<int, vector<int> > venta_dia;

int main()
{
  cout << "\nUna simple prueba de map\n";
  cout << "........................\n";
  map<int, vector<int> > semana;
  vector<int> a;
  a.push_back(1);
  a.push_back(2);
  a.push_back(3);
  a.push_back(4);
  vector<int> b;
  b.push_back(5);
  b.push_back(6);
  b.push_back(7);
  b.push_back(8);
  semana.insert( venta_dia(0, a) );
  semana.insert( venta_dia(1, a) );
  double total = 0;
  semana[0].push_back(10);
  map<int, vector<int> >::iterator p = semana.begin();
  while (p != semana.end() )
  {
    cout << setw(10) << p->first << setw(10); 
    for (int i = 0; i < p->second.size(); ++i){
    	cout<<p->second[i]<<" ";
    };
    cout<<endl;
    p++;
  }

  cout << "........................\n";
  //cout << setw(10) << "total:" << setw(12) << total << endl;

  
  return 0;
}
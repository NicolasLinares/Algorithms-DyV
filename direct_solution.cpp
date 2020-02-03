#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
using namespace std;


string cadena; 
string conjuntoS;

list<int> solucionDirecta(int p, int num){
	
	int posicion = p; // posición en la cadenaC
	string subcadena="";

	list<int> listaIndices;
	
	//definimos un array para que no escoja caracteres ya usados del conjuntoS	
	int contador = 0; //contador para la subcadena (máximo 3)
	 
	bool letrasUsadas[5];
	for(int o = 0; o < 5; o++) letrasUsadas[o] = false;

	for(int i = p; i <= num; i++){

		bool encontrado = false;
		int j= 0;
		while( j < 5 and !encontrado){
			if(cadena[i] == conjuntoS[j] ) {
				//compara si se repite un elemento en la subcadena
				if(!letrasUsadas[j]){
					subcadena += conjuntoS[j];
					letrasUsadas[j] = true;
					encontrado = true;
				}else{
					
	
					unsigned int k=0;  
					int cont=0;
					
					//recorremos la subcadena que se va formando al haber encontrado coincidencias,
					//como la letra se marca como usada en letrasUsadas[]  entonces 
					// debe buscar donde se encuentra la repetición de esa letra para quedarse con la nueva subcadena 
					//válida -> ab a : ba ; abb : b.
	
					while(subcadena[k] != conjuntoS[j]){
						//ponemos a falso las letras que quitamos de la subcadena
						int t=0;
						while(subcadena[k] != conjuntoS[t]) t++; //buscamos la que es del conjunto para ponerla a falso
						letrasUsadas[t] = false;
						cont++; 
						k++;
					}
					
					letrasUsadas[j] = true;//volvemos a ponerla a true para el caso en el que borramos la misma letra que acabamos de añadir
					subcadena = subcadena.substr(cont + 1) + conjuntoS[j];
					contador = subcadena.size() - 1; //porque después se cuenta  en la línea 65 (contador++)
					encontrado = true;
				}
			}
			j++;
		}
		

		if (encontrado) contador++;
		else {
			//reseteamos la búsqueda de la subcadena porque no se ha encontrado
			contador = 0;
			subcadena ="";
			for(int o = 0; o < 5; o++) letrasUsadas[o] = false;
		}
		
		if (contador == 3){
			//reseteamos porque hemos encontrado la subcadena correcta
			contador = 0;
			for(int o = 0; o < 5; o++) letrasUsadas[o] = false;
			listaIndices.push_back(posicion - 2); 
			subcadena ="";
		}
		posicion++;
	}

	return listaIndices;
}

int main(void){
	int niteraciones; // número de cadenas que analizamos
	cin >> niteraciones;
	int l=0; 
	while(l<niteraciones){
		
		int numElementos; // número de elementos de la cadenaC
		
		cin >> numElementos;
		cin >> cadena;
		cin >> conjuntoS;
		
		cout << "La cadena C generada es: " << cadena << endl;
		cout << "El conjunto S utilizado es: [" << conjuntoS[0] << ", " << conjuntoS[1] << ", " << conjuntoS[2] << ", " << conjuntoS[3] << ", " << conjuntoS[4] << "] " << endl;
		
		list<int> resultado =  solucionDirecta(0, numElementos -1);
		//RESULTADOS:
		int aciertos=0;
		list<int>::iterator it = resultado.begin();
		while(it != resultado.end()){
			aciertos++;
			cout << "[" <<  *it << "] ";
			it++;
			if (it == resultado.end()) cout << endl;
		}
		
		
		cout<< "Aciertos: " << aciertos <<endl;
		cout << endl;
		l++; 
	}
}

#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;

string cadena; 
string conjuntoS;
const int PEQUENIO = 5000;

bool pertenece(int i){
	int j=0;
	while(j<5){
		if(cadena[i] == conjuntoS[j]) return true;
		j++;
	}
	return false;
}

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
					contador = subcadena.size() - 1; //porque después se cuenta  en la línea 73 (contador++)
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


//CASOS CONFLICTIVOS EN COMBINAR
//~ s1              s2
//~ ...bc|a.....  -> bca suma 1 cadena m�s
//~ ...bc|ab.....  -> bca suma 1 cadena m�s
//~ ...bc|abc....  -> bca suma 1 cadena m�s y rompemos abc
//~ ...abcbc|abca...  -> bca suma 1 cadena m�s y rompemos abc, lee bca y sigue rompiendo...
//~ ...bc|abcabXcabc...  -> bca, bca y cuando llega a la X para
//~ ...ac|abcabXcabc...  -> no forma subcadena en medio y se queda igual
//~ ...Xbcabc|abcabcX...  -> busca hacia la izquierda el l�mite X y hacia la derecha el l�mite X

list<int> combinar(int p, int q, int n, list<int> s1, list<int> s2){ //p: posicion inicial de la cadena;  q: posicion final de la cadena; n: mitad de la cadena; s1: subcadena izquierda; s2: subcadena derecha;
	
	//listas vacías por no haber encontrado nada, solo comprobamos los 2 últimos de s1 y los 2 primeros de s2
	if (s1.empty() and s2.empty()) {
		return solucionDirecta(n-1, n+3);
	}else {

		//vamos a buscar los candidatos posibles entre las dos partes
	
		//LIMITE IZQUIERDO
		int izq;
		if (s1.empty()) izq = n -2; // solo nos fijamos en los dos últimos del s1
		else{
			izq = n; //izquierdo comienza a buscar desde el extremo derecho del s1
			while(pertenece(izq) and izq>=p) izq--; //buscamos el limite izquierdo en s1 de letras seguidas que pertenecen al subconjunto
		}
		
		//LIMITE DERECHO
		int der=n+1;
		while(pertenece(der) and der<=q) der++; //buscamos el limite derecho en s2 de letras seguidas que pertenecen al subconjunto
	
		//borrar las posiciones de las cadenas
		if(izq == p) {
			list<int> aux1;
			s1 =aux1;
		}else if (!s1.empty()){
			list<int>::iterator it = s1.begin();
			while(it != s1.end() and *it < izq) it++;  //buscamos un elemento que sea mayor que i. Una vez											
			s1.erase(it , s1.end());				//encontrado, borramos desde ese elemento al final
		}
		
		if(der == q) {
			list<int> aux2;
			s2 =aux2;
		}else if (!s2.empty()){						
			list<int>::iterator it = s2.begin();					
			while(it != s2.end() and *it < der) it++;		//buscamos un elemento que sea mayor que d. Una vez
			s2.erase(s2.begin(), it);					//encontrado borramos desde el principio hasta el elemento encontrado
		}
	
		//concatenar(s1, unir, s2)
		list<int> unir = solucionDirecta(izq, der);
		s1.merge(unir);
		s1.merge(s2);	
		return s1;
	}
}


list<int> divideyvenceras(int p, int q){
	int tam = q - p + 1;
	
	//¿Es suficientemente pequeño?
	if (tam <= PEQUENIO){
			return solucionDirecta(p, q);
			
	} else {
		//DIVIDIR
		int n = (q + p)/2;
		
		//RESOLVER Y COMBINAR
		return combinar(p,q,n, divideyvenceras(p, n), divideyvenceras(n+1, q));
	}

}

int main(){
	
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
		list<int> resultado = divideyvenceras(0, numElementos-1);
	
	
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



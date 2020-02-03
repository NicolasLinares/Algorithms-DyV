#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <time.h>
using namespace std;

int numElementos;  // nº de elementos de la cadena
int nlineas;
int n, m;
int caso;

string generarCadena(int n){
	string resultado;
	for(int i=0; i< n ; i++){		
		int numero = rand() % (122-97+1) + 97; 		
		resultado += (char) numero;
	}
	return resultado;
	
}

string generarCadenaSin(int n, string evitar){
	string resultado;
	int i = 0;
	while(i < n){		
		int numero = rand() % (122-97+1) + 97;
		int j = 0;
		bool encontrado = false;
		while(j<5  && !encontrado){
			if(numero == evitar[j]){ 
				encontrado = true;					
			}
			j++;
		}
		if (encontrado == false){
			 resultado += (char) numero;
			 i++;
		}
	}
	return resultado;
	
}

string generarConjunto(){
	bool abecedario[25];
	for(int o = 0; o < 25; o++) abecedario[o] = false;
	
	string resultado;
	int i=0;
	while(i < 5){
		
		int numero = rand() % (122-97+1) + 97; 	
		if(!abecedario[numero % 25]){
			resultado += (char) numero;
			abecedario[numero % 25] = true;
			i++;
		}
	}
	return resultado;
	
}

int main(void){
	srand (time(NULL));
	
	ofstream ficheroSalida;
	ficheroSalida.open ("fichero.txt");
	
	
	cout <<"Numero de cadenas: " ;
	cin >> nlineas;
	cout <<"Rango de caracteres en las cadenas N M: " ;
	cin >> n >> m;
    cout << "1 Mejor caso, 2 Peor caso, 3 Aleatorio :";
    cin >> caso;
	ficheroSalida << nlineas << endl;
	switch(caso){
		
		// No hay ninguna coincidencia con el conjunto S
		
		case 1:{
			for(int i =0;i<nlineas;i++){
				
				int numElementos = rand() % (m-n+1) + n; 	
				ficheroSalida << numElementos << endl;

				string conjunto = generarConjunto();
		
				ficheroSalida << generarCadenaSin(numElementos, conjunto) << endl;
				ficheroSalida << conjunto << endl;
			}
			break;
		}
		
		// Solo hay subcadenas del conjunto S
		case 2:{
			for(int i =0;i<nlineas;i++){
				
				int numElementos = rand() % (m-n+1) + n; 
				 	
				ficheroSalida << numElementos << endl;

				string conjunto = generarConjunto();
				for(int c =0; c<numElementos ; c++){
					if( c % 3 == 0) ficheroSalida << conjunto[4];
					if( c % 3 == 1) ficheroSalida << conjunto[3];
					if( c % 3 == 2) ficheroSalida << conjunto[2];
				}
		
				ficheroSalida << endl;
				ficheroSalida << conjunto << endl;
			}
			break;
		
		}
		
		// Caso aleatorio 
		case 3:{
			for(int i =0;i<nlineas;i++){
				
				int numElementos = rand() % (m-n+1) + n; 	
				ficheroSalida << numElementos << endl;
				
				ficheroSalida << generarCadena(numElementos) << endl;
				ficheroSalida << generarConjunto() << endl;
			}
			break;
		}
	
	
	
	}
	cout << "Fichero generado." << endl;
	
	ficheroSalida.close();
}

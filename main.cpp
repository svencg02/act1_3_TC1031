// =================================================================
//
// File: main.cpp
// Author: Sven Chavez Garcia
// Date: 11/09/22
//
// =================================================================
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <time.h>
#include <string.h>
#include <iomanip>
#include <cstdlib>
#include "insertion.h"

int main(int argc, char* argv[]) {
	std::ifstream entrada;
	std::ofstream salida;
	entrada.open(argv[1], std::ios::in);
	salida.open(argv[2], std::ios::out); // se abren los archivos correspondientes de entrada y salida 

	if (argc != 3){
		return -1; // se checa el numero de argumentos que se mandan a la app
	}

	else if (entrada.fail() || salida.fail()){
		std::cout << "no se pudo abrir alguno de los textos...";
		return -1;
	} // se checa que se hayan abierto correctamente los archivos 


	int n; //numero de elementos a leer
	
	std::string prefix; // prefix para hacer el filtrado de barcos

	entrada >> n; // asignacion de numero de elementos a leer 
	entrada >> prefix; // asignacion del prefix

	struct barcos // estructura para almacenar diferentes tipos de datos
	{
		std::string fecha_s, hora, puerto, clave; // los strings
		int dia, mes, valor; // los enteros para ordenar
	};

	std::vector <barcos> arr_barcos; // verctor de estructura barco 
	int cont = 0; // contador para recorrer el vector 

	for (int i=0; i < n; i++){
		barcos barco; // se crea un auxiliar de barco para evaluar si cumple con el prefix y ordenarlo por fecha
		entrada >> barco.fecha_s >> barco.hora >> barco.puerto >> barco.clave; // se asignan los elementos del barco 
		
		std::size_t found = barco.clave.rfind(prefix); // se busca si cumple con el prefix 
		if (found != string::npos){ // si se cumple la condicion del prefix 
			barco.dia = stoi(barco.fecha_s.substr(0, barco.fecha_s.find("-"))); //  se convierte el string del dia en entero
			barco.mes = stoi(barco.fecha_s.substr(3, barco.fecha_s.find("-"))); // se convierte el string del mes en entero
			barco.valor = (barco.mes * 100) + barco.dia; // se multiplica el mes para que tenga un valor mas alto que el dia 
			arr_barcos.push_back(barco); // se agrega al vector de barcos con el prefix
		}
	};

	insertionSort(arr_barcos); // se hace el ordenamiento a traves de insertion pero solo por el mes y el dia no por la hora 

	for (int i = 0; i < arr_barcos.size(); i++){
		salida << arr_barcos[i].fecha_s << " " << arr_barcos[i].hora << " " << arr_barcos[i].puerto << " " << arr_barcos[i].clave << endl;
	} // se escribe en el archivo de salida

	entrada.close();
	salida.close(); // se cierran los archivos

	return 0;
}
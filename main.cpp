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
	salida.open(argv[2], std::ios::out);

	if (argc != 3){
		return -1;
	}

	else if (entrada.fail() || salida.fail()){
		std::cout << "no se pudo abrir alguno de los textos...";
		return -1;
	}

	int n;
	
	std::string prefix;

	entrada >> n;
	entrada >> prefix;

	struct barcos
	{
		std::string fecha_s, hora, puerto, clave;
		int dia, mes, valor; 
	};

	std::vector <barcos> arr_barcos;
	int cont = 0;

	for (int i=0; i < n; i++){
		barcos barco;
		entrada >> barco.fecha_s >> barco.hora >> barco.puerto >> barco.clave;
		
		std::size_t found = barco.clave.rfind(prefix);
		if (found != string::npos){
			barco.dia = stoi(barco.fecha_s.substr(0, barco.fecha_s.find("-")));
			barco.mes = stoi(barco.fecha_s.substr(3, barco.fecha_s.find("-")));
			barco.valor = barco.mes * barco.dia;
			arr_barcos[cont] = barco; 
		}
	};

	insertionSort(arr_barcos);

	for (int i = 0; i < arr_barcos.size(); i++){
		salida << arr_barcos[i].fecha_s << " " << arr_barcos[i].hora << " " << arr_barcos[i].puerto << " " << arr_barcos[i].clave << endl;
	}

	entrada.close();
	salida.close();

	return 0;
}
#include <iostream>

using namespace std;

class DFSdata{
public:
	bool visitado;
	int low;
	int num;
	int anterior;
	bool marcado;
	int label;
	
	DFSdata(){
		visitado = false;
		anterior = -1;
		marcado = false;
		low = -1;
		num = -1;
		label = -1;
	}
};

class MinimumData{
public:
	int d;
	int anterior;
	char cor;
	
	MinimumData(){
		d = 1000000000;
		anterior = -1;
		cor = 'B';
	}
};

class Coloracao{
public:
	int cor;
	
	Coloracao(){
		cor = 0;
	}
};

class DataVertice{
public:
	int id;
	double x;
	double y;
	double consumidores;
	double demanda;
	double cargaTrabalho;
	double fuga;
	
	DataVertice(){
		x = -1;
		y = -1;
		consumidores = -1;
	    demanda = -1;
	    cargaTrabalho = -1;
	    fuga = -1;
	}
};

class Regioes {
	DataVertice* vSubRegioes;
	
};

class InfoSubReg {
public:
	int qntReg;
	double lambdaConsumidores;
	double lambdaDemanda;
	double lambdaCargaTrabalho;
	double betaConsumidores;
	double betaDemanda;
	double betaCargaTrabalho;
	
	InfoSubReg(){
		qntReg = -1;
		lambdaConsumidores = -1;
		lambdaDemanda = -1;
		lambdaCargaTrabalho = -1;
		betaConsumidores = -1;
		betaDemanda = -1;
		betaCargaTrabalho = -1;
	}
};

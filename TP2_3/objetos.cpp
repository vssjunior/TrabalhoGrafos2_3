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
	bool adicionado;
	
	DataVertice(){
		x = -1;
		y = -1;
		consumidores = -1;
	    demanda = -1;
	    cargaTrabalho = -1;
	    fuga = -1;
	    adicionado = false;
	}
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


class SubRegioes {
public:
	DataVertice** vertices;
	int tam;
	int capacidade;
	int media;
	double fuga;
	double betaConsumidores;
	double betaDemanda;
	double betaCargaTrabalho;
	int quantidadeDeVertices;
	
	SubRegioes(){
		this->capacidade  = 0;
		this->tam = 0;
	}
	
	SubRegioes(int capacidade){
		this->capacidade  = capacidade;
		vertices = new DataVertice*[capacidade];
		for(int i=0; i<capacidade; i++){
			vertices[i] = new DataVertice;
		}
		tam = 0;
	}
	
	void calcularFuga(InfoSubReg info){
		double auxConsumidores, auxDemanda, auxCargaTrabalho;
		
		for(int i = 0; i < quantidadeDeVertices; i++){
			auxConsumidores += (vertices[i]->consumidores - info.betaConsumidores) ;
			auxDemanda += (vertices[i]->demanda - info.betaDemanda);
			auxCargaTrabalho += (vertices[i]->cargaTrabalho - info.betaCargaTrabalho);
		}
		
		betaConsumidores = auxConsumidores;
		betaDemanda = auxDemanda;
		betaCargaTrabalho = auxCargaTrabalho;
		
		auxConsumidores = (auxConsumidores > 0) ? auxConsumidores : auxConsumidores*(-1);
		auxDemanda = (auxDemanda > 0) ? auxDemanda : auxDemanda*(-1);
		auxCargaTrabalho = (auxCargaTrabalho > 0) ? auxCargaTrabalho : auxCargaTrabalho*(-1);
		
		auxConsumidores /= quantidadeDeVertices;
		auxDemanda /= quantidadeDeVertices;
		auxCargaTrabalho /= quantidadeDeVertices;
		
		fuga = auxConsumidores + auxDemanda + auxCargaTrabalho;
	}
	
	double calcularFuga(InfoSubReg info, DataVertice* vertice){
		double auxConsumidores, auxDemanda, auxCargaTrabalho;
		
		auxConsumidores = (vertice->consumidores - info.betaConsumidores) + betaConsumidores;
		auxDemanda = (vertice->demanda - info.betaDemanda) + betaDemanda;
		auxCargaTrabalho = (vertice->cargaTrabalho - info.betaCargaTrabalho) + betaCargaTrabalho;
		
		auxConsumidores = (auxConsumidores > 0) ? auxConsumidores : auxConsumidores*(-1);
		auxDemanda = (auxDemanda > 0) ? auxDemanda : auxDemanda*(-1);
		auxCargaTrabalho = (auxCargaTrabalho > 0) ? auxCargaTrabalho : auxCargaTrabalho*(-1);
		
		return (auxConsumidores + auxDemanda + auxCargaTrabalho);
	}
};

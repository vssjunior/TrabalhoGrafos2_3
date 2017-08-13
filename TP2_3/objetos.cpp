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
	int cor;
	int id;
	double x;
	double y;
	double consumidores;
	double demanda;
	double cargaTrabalho;
	double fuga;
	bool adicionado;
	
	DataVertice(){
		cor = -1;
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
	double fugaConsumidores;
	double fugaDemanda;
	double fugaCargaTrabalho;
	double mediaConsumidores;
	double mediaDemanda;
	double mediaCargaTrabalho;
	double taxaConsumidores;
	double taxaDemanda;
	double taxaCargaTrabalho;
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
		quantidadeDeVertices = 0;
	}
	
	void calcularFuga(InfoSubReg info){
		double auxConsumidores, auxDemanda, auxCargaTrabalho;
		
		auxConsumidores = 0;
		auxDemanda = 0;
		auxCargaTrabalho = 0;
		
		for(int i = 0; i < quantidadeDeVertices; i++){
			auxConsumidores += (vertices[i]->consumidores) ;
			auxDemanda += (vertices[i]->demanda);
			auxCargaTrabalho += (vertices[i]->cargaTrabalho);
		}
		
		/*
		auxConsumidores /= quantidadeDeVertices;
		auxDemanda /= quantidadeDeVertices;
		auxCargaTrabalho /= quantidadeDeVertices;
		*/
		
		mediaConsumidores = auxConsumidores;
		mediaDemanda = auxDemanda;
		mediaCargaTrabalho = auxCargaTrabalho;
		
		fugaConsumidores = auxConsumidores - info.betaConsumidores;
		fugaDemanda = auxDemanda - info.betaDemanda;
		fugaCargaTrabalho = auxCargaTrabalho - info.betaCargaTrabalho;
		
		fugaConsumidores *= (fugaConsumidores > 0) ? (1) : (-1);
		fugaDemanda *= (fugaDemanda > 0) ? (1) : (-1);
		fugaCargaTrabalho *= (fugaCargaTrabalho > 0) ? (1) : (-1);
		
		fuga = fugaConsumidores + fugaDemanda + fugaCargaTrabalho;
	}
	
	double calcularFuga(InfoSubReg info, DataVertice* vertice){
		double auxConsumidores, auxDemanda, auxCargaTrabalho;
		
		auxConsumidores = vertice->consumidores;
		auxDemanda = vertice->demanda;
		auxCargaTrabalho = vertice->cargaTrabalho;
		
		for(int i = 0; i < quantidadeDeVertices; i++){
			auxConsumidores += (vertices[i]->consumidores) ;
			auxDemanda += (vertices[i]->demanda);
			auxCargaTrabalho += (vertices[i]->cargaTrabalho);
		}
		
		/*
		auxConsumidores /= (quantidadeDeVertices + 1);
		auxDemanda /= (quantidadeDeVertices + 1);
		auxCargaTrabalho /= (quantidadeDeVertices + 1);
		*/
		
		auxConsumidores -= info.betaConsumidores;
		auxDemanda -= info.betaDemanda;
		auxCargaTrabalho -= info.betaCargaTrabalho;
		
		auxConsumidores *= (auxConsumidores > 0) ? (1) : (-1);
		auxDemanda *= (auxDemanda > 0) ? (1) : (-1);
		auxCargaTrabalho *= (auxCargaTrabalho > 0) ? (1) : (-1);
		
		return (auxConsumidores + auxDemanda + auxCargaTrabalho);
	}
	
	void calcularTaxasLambda(InfoSubReg info) {
		taxaConsumidores = mediaConsumidores/info.betaConsumidores;
		taxaDemanda = mediaDemanda/info.betaDemanda;
		taxaCargaTrabalho = mediaCargaTrabalho/info.betaCargaTrabalho;
	}
};

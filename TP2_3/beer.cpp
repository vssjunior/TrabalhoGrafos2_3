#include <iostream>
#include <fstream>
#include "grafos.cpp"
#include "objetos.cpp"
#include <list>

using namespace std;

void montarSubRegiao(Grafo* grafo, DataVertice* vertices, InfoSubReg infoSubReg, list<DataVertice> **subReg, double mediaConsumidor, double mediaDemanda, double mediaCargaTrabalho){
	double mediaInferiorConsumidores = mediaConsumidor - infoSubReg.lambdaConsumidores;
	double mediaSuperiorConsumidores = mediaConsumidor + infoSubReg.lambdaConsumidores;
	double mediaInferiorDemanda = mediaDemanda - infoSubReg.lambdaDemanda;
	double mediaSuperiorDemanda = mediaDemanda + infoSubReg.lambdaDemanda;
	double mediaInferiorCargaTrabalho = mediaCargaTrabalho - infoSubReg.lambdaCargaTrabalho;
	double mediaSuperiorCargaTrabalho = mediaCargaTrabalho + infoSubReg.lambdaCargaTrabalho;
	
	for(int i = 0; i < grafo -> getQuantVertices(); i++){
		if(vertices[i].consumidores - mediaInferiorConsumidores and vertices[i].consumidores < mediaSuperiorConsumidores
			and vertices[i].demanda > mediaInferiorDemanda) {
			
		}
	}
	
	
	
	
}

int main(){
	Grafo* grafo;
	
	int tam, arestas, u, v, qnt_subReg;
	//string nomeArq = (argv[1]);
	//nomeArq += ".txt";
	ifstream arq("instance.input");
	
	arq >> tam;
	grafo = new ListaDeAdjacencia(false);
	grafo -> adicionarVertices(tam);
	
	DataVertice* vertices = new DataVertice[tam];
	
	for(int i=0; i<tam; i++){
		arq >> vertices[i].id;
		arq >> vertices[i].x;
		arq >> vertices[i].y;
		arq >> vertices[i].consumidores;
		arq >> vertices[i].demanda;
		arq >> vertices[i].cargaTrabalho;
	}
	
	arq >> arestas;
	
	for(int i=0; i<arestas; i++){
		arq >> u;
		arq >> v;
		try{
			grafo -> adicionarAresta(u, v, 1);
		}
		catch(EdgeInsertionException e){
		}
	}
		
	arq >> qnt_subReg;
	
	InfoSubReg infoSubReg;

	arq >> infoSubReg.qntReg;
	arq >> infoSubReg.lambdaConsumidores;
	arq >> infoSubReg.lambdaDemanda;
	arq >> infoSubReg.lambdaCargaTrabalho;
	
	arq.close();
	
	double somaConsu = 0;
	double somaDeman = 0;
	double somaCTrab = 0;
	
	for(int i = 0; i < tam; i++){
		somaConsu += vertices[i].consumidores;
		somaDeman += vertices[i].demanda;
		somaCTrab += vertices[i].cargaTrabalho;
	}
	
	infoSubReg.betaConsumidores = somaConsu/tam;
	infoSubReg.betaDemanda = somaDeman/tam;
	infoSubReg.betaCargaTrabalho = somaCTrab/tam;
	
	double auxConsumidores, auxDemanda, auxCargaTrabalho;
	
	for(int i=0; i<tam; i++){
		auxConsumidores = abs(vertices[i].consumidores
	cout << infoSubReg.betaConsumidores << "consumidor\n";
	cout << infoSubReg.betaDemanda << "demanda\n";
	cout << infoSubReg.betaCargaTrabalho << "carga\n";
	
	list<DataVertice> **subReg = new list<DataVertice>*[infoSubReg.qntReg];	
	for(int i=0; i<infoSubReg.qntReg; i++){
		subReg[i] = new list<DataVertice>;
	}
	
	montarSubRegiao(grafo, vertices, infoSubReg, subReg, infoSubReg.betaConsumidores, infoSubReg.betaDemanda, infoSubReg.betaCargaTrabalho);
	return 0;
}

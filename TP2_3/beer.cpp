#include <iostream>
#include <fstream>
#include "grafos.cpp"
#include "objetos.cpp"

using namespace std;

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
	
	int aux;
	for(int i=0; i<tam; i++){
		arq >> aux;
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
	
	return 0;
}

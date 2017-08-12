#include <iostream>
#include <fstream>
#include "grafos.cpp"
#include "objetos.cpp"
#include <list>

using namespace std;

void quickSort(DataVertice** vertices , int left, int right) {
      int i = left, j = right;
      DataVertice* tmp;
      double pivot = vertices[(left + right) / 2]->fuga;
	  
      while (i <= j) {
            while (vertices[i]->fuga < pivot)
                  i++;
            while (vertices[j]->fuga > pivot)
                  j--;
                  
            if (i <= j) {
                  tmp = vertices[i];
                  vertices[i] = vertices[j];
                  vertices[j] = tmp;
                  i++;
                  j--;
            }
      };
	  
      if (left < j)
            quickSort(vertices, left, j);
      if (i < right)
            quickSort(vertices, i, right);
}

void insertionSort(SubRegioes **subReg, int n)
{
   int i, j;
   double key;
   for (i = 1; i < n; i++)
   {
       key = subReg[i]->fuga;
       j = i-1;
 
       
       while (j >= 0 && subReg[j]->fuga > key)
       {
		   SubRegioes* aux = subReg[j+1];
           subReg[j+1] = subReg[j];
           subReg[j] = aux;
           j = j-1;
       }
       //subReg[j+1].fuga = key;
   }
}

void montarSubRegiao(Grafo* grafo, DataVertice** vertices, InfoSubReg infoSubReg, SubRegioes **subReg, double mediaConsumidor, double mediaDemanda, double mediaCargaTrabalho, int qntSubRegiao){
	for(int i=0; i<qntSubRegiao; i++){
		
		subReg[i]->vertices[0] = vertices[i];
		subReg[i]->quantidadeDeVertices++;
		subReg[i]->calcularFuga(infoSubReg);
	}
	
	int aux = qntSubRegiao-1;
	double menorFuga = (vertices[grafo->getQuantVertices()-1]->fuga)+1;
	double fugaAchada;
	int menorFugaVertice;
	bool achou = false, acabou = false;
	while(aux >= 0){
		for(int i=0; i < subReg[aux]->quantidadeDeVertices; i++){
			List vizinhos = grafo -> getVizinhos(vertices[i]->id);

			for(int i = 0; i < vizinhos.size(); i++){  
				int v = vizinhos.get(i).getVerticeAlvo();
				fugaAchada = subReg[aux]->calcularFuga(infoSubReg, vertices[v]);
				if(fugaAchada < menorFuga and !vertices[v]->adicionado){
					menorFuga = fugaAchada;
					menorFugaVertice = v;
					achou = true;
					acabou = true;
				}
				else {
					acabou = false;
				}
			}
		}
		if(achou){
			subReg[aux]->vertices[subReg[aux]->quantidadeDeVertices-1] = vertices[menorFugaVertice];
			subReg[aux]->quantidadeDeVertices ++;
			subReg[aux]->calcularFuga(infoSubReg);
			insertionSort(subReg, aux);
		}
		if(!acabou){
			aux--;
		}
		
		menorFuga = (vertices[grafo->getQuantVertices()-1]->fuga)+1;
		achou = false;
		acabou = false;
	}
	
	
	for(int i=0; i<qntSubRegiao; i++){
		
		cout << subReg[i] -> quantidadeDeVertices << "\n";
	}
	
	/*bool adicionou = false;
	int j = 0;
	double mediaInferiorConsumidores = mediaConsumidor - infoSubReg.lambdaConsumidores;
	double mediaSuperiorConsumidores = mediaConsumidor + infoSubReg.lambdaConsumidores;
	double mediaInferiorDemanda = mediaDemanda - infoSubReg.lambdaDemanda;
	double mediaSuperiorDemanda = mediaDemanda + infoSubReg.lambdaDemanda;
	double mediaInferiorCargaTrabalho = mediaCargaTrabalho - infoSubReg.lambdaCargaTrabalho;
	double mediaSuperiorCargaTrabalho = mediaCargaTrabalho + infoSubReg.lambdaCargaTrabalho;
	
	double mediaTotal = (mediaConsumidor + mediaDemanda + mediaCargaTrabalho) / 3;
	double mediaTotalInf = (mediaInferiorConsumidores + mediaInferiorDemanda + mediaInferiorCargaTrabalho) / 3;
	double mediaTotalSup = (mediaSuperiorConsumidores + mediaSuperiorDemanda + mediaSuperiorCargaTrabalho) / 3;
	
	for(int i = 0; i < grafo -> getQuantVertices(); i++){
		vertices[i].media = (vertices[i].consumidores + vertices[i].demanda + vertices[i].cargaTrabalho) / 3;
		if(vertices[i].media > mediaTotalInf and vertices[i].media < mediaTotalSup){
			while(!adicionou and j<qntSubRegiao){
				if(subReg[j]!=NULL){
					subReg[j] = new DataVertice;
					subReg[0][j] = vertices[i];
					adicionou = true;
				}
				else 
				j++;
			}
		}
	}*/
}

int main(){
	
	Grafo* grafo;
	
	int tam, arestas, u, v;
	//string nomeArq = (argv[1]);
	//nomeArq += ".txt";
	ifstream arq("instance.input");
	
	arq >> tam;
	grafo = new ListaDeAdjacencia(false);
	grafo -> adicionarVertices(tam);
	
	DataVertice** vertices = new DataVertice*[tam];
	for(int i=0; i<tam; i++){
		vertices[i] = new DataVertice;
		arq >> vertices[i]->id;
		arq >> vertices[i]->x;
		arq >> vertices[i]->y;
		arq >> vertices[i]->consumidores;
		arq >> vertices[i]->demanda;
		arq >> vertices[i]->cargaTrabalho;
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
	
	//arq >> qnt_subReg;
	
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
		somaConsu += vertices[i]->consumidores;
		somaDeman += vertices[i]->demanda;
		somaCTrab += vertices[i]->cargaTrabalho;
	}
	
	infoSubReg.betaConsumidores = (somaConsu/tam);
	infoSubReg.betaDemanda = (somaDeman/tam);
	infoSubReg.betaCargaTrabalho = (somaCTrab/tam);
	
	
	double auxConsumidores, auxDemanda, auxCargaTrabalho;
	
	
	for(int i=0; i<tam; i++){
		auxConsumidores = (vertices[i]->consumidores - infoSubReg.betaConsumidores) ;
		auxDemanda = (vertices[i]->demanda - infoSubReg.betaDemanda);
		auxCargaTrabalho = (vertices[i]->cargaTrabalho - infoSubReg.betaCargaTrabalho);
		
		auxConsumidores = (auxConsumidores > 0) ? auxConsumidores : auxConsumidores*(-1);
		auxDemanda = (auxDemanda > 0) ? auxDemanda : auxDemanda*(-1);
		auxCargaTrabalho = (auxCargaTrabalho > 0) ? auxCargaTrabalho : auxCargaTrabalho*(-1);
		
		vertices[i]->fuga = auxConsumidores + auxDemanda + auxCargaTrabalho;
	}
		
	//cout  << endl;
	quickSort(vertices, 0, tam-1);
	
	
	//cout << infoSubReg.betaConsumidores << "consumidor\n";
	//cout << infoSubReg.betaDemanda << "demanda\n";
	//cout << infoSubReg.betaCargaTrabalho << "carga\n";
	
	SubRegioes **subReg = new SubRegioes*[infoSubReg.qntReg];	
	for(int i=0; i<infoSubReg.qntReg; i++){
		subReg[i] = new SubRegioes(tam);
	}
	
	/*for(int i=0; i < tam; i++){
		cout << vertices[i]->fuga << " " << vertices[i]->id << "\n";
	}*/
	montarSubRegiao(grafo, vertices, infoSubReg, subReg, infoSubReg.betaConsumidores, infoSubReg.betaDemanda, infoSubReg.betaCargaTrabalho, infoSubReg.qntReg);
	return 0;
}

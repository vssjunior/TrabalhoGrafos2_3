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
	cout << "Chamou insert\n";
   int i, j;
   for (i = 1; i <= n; i++)
   {
       j = i;
 
       cout << subReg[j-1]->fuga << " <-------> " << subReg[j]->fuga << endl;
       while (j > 0 && subReg[j-1]->fuga > subReg[j]->fuga)
       {
		   SubRegioes* aux = subReg[j];
           subReg[j] = subReg[j-1];
           subReg[j-1] = aux;
           j--;
       }
   }
}

void montarSubRegiao(Grafo* grafo, DataVertice** vertices, InfoSubReg infoSubReg, SubRegioes **subReg){
	for(int i=0; i<infoSubReg.qntReg; i++){
		
		subReg[i]->vertices[0] = vertices[i];
		vertices[i]->adicionado = true;
		subReg[i]->fuga = vertices[i]->fuga;
		subReg[i]->quantidadeDeVertices++;
		//cout << "subReg[" << i <<"]->vertices[0] = " << vertices[i]->id <<";\n"; 
	}
	
	int aux = infoSubReg.qntReg -1, pos;
	double menorFuga = 1000000;
	double fugaAchada;
	int menorFugaVertice;
	bool achou = false, acabou = false;
	
	while(aux >= 0){
		for(int i = 0; i < subReg[aux]->quantidadeDeVertices; i++){
			List vizinhos = grafo -> getVizinhos(subReg[aux]->vertices[i]->id);

			for(int j = 0; j < vizinhos.size(); j++){  
				int v = vizinhos.get(j).getVerticeAlvo();
				cout << subReg[aux]->vertices[i]->id << " -> " << v << "    aux: " << aux <<"\n";
				
				for(int k = 0; k < grafo->getQuantVertices(); k++){
					if(vertices[k]->id == v){
						pos = k;
					}
				}
				
				fugaAchada = subReg[aux]->calcularFuga(infoSubReg, vertices[pos]);
				cout << "Fuga Achada: " << fugaAchada << "\n";
				if(fugaAchada < menorFuga and !vertices[pos]->adicionado){
					menorFuga = fugaAchada;
					menorFugaVertice = pos;
					achou = true;
					acabou = true;
				}
			}
		}
		cout << "Menor fuga Vertice: " << menorFugaVertice << "\n";
		if(achou){
			subReg[aux]->vertices[subReg[aux]->quantidadeDeVertices] = vertices[menorFugaVertice];
			vertices[menorFugaVertice]->adicionado = true;
			subReg[aux]->quantidadeDeVertices ++;
			subReg[aux]->calcularFuga(infoSubReg);
			insertionSort(subReg, aux);
			for(int i=0; i<3; i++){
				cout << subReg[i]->fuga << "  " << i << "  ";
			} cout << "\n";
		}
		//cout << subReg[aux] -> quantidadeDeVertices << "aux->" <<aux << "\n";
		if(!acabou){
			aux--;
		}
		
		menorFuga = 1000000;
		achou = false;
		acabou = false;
		
		
	}
	
	
	for(int i=0; i<infoSubReg.qntReg; i++){
		subReg[i] -> calcularTaxasLambda(infoSubReg);
		cout << "\nQuantidade de pontos de referência: ";
		cout << subReg[i] -> quantidadeDeVertices << "\n";
		cout << "Valor das Fugas dos valores esperados:\n";
		cout << subReg[i] -> fugaConsumidores << "\n";
		cout << subReg[i] -> fugaDemanda << "\n";
		cout << subReg[i] -> fugaCargaTrabalho << "\n";
		cout << "Os 3 lamdas:\n";
		cout << "Lambda Consumidores:      " << subReg[i] -> taxaConsumidores << endl;
		cout << "Lambda Demanda:           " << subReg[i] -> taxaDemanda << endl;
		cout << "Lambda Carga de trabalho: " << subReg[i] -> taxaCargaTrabalho << endl << endl;
	}
	
	cout << "\n" <<infoSubReg.betaConsumidores << "\n";
	cout << infoSubReg.betaDemanda << "\n";
	cout << infoSubReg.betaCargaTrabalho << "\n";
	
	
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
	ifstream arq("instances/n500-m1479-k15-2.input");
	
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
	
	infoSubReg.betaConsumidores = (somaConsu/infoSubReg.qntReg);
	infoSubReg.betaDemanda = (somaDeman/infoSubReg.qntReg);
	infoSubReg.betaCargaTrabalho = (somaCTrab/infoSubReg.qntReg);
	
	
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
	
	
//	cout << infoSubReg.betaConsumidores << "consumidor\n";
	//cout << infoSubReg.betaDemanda << "demanda\n";
	//cout << infoSubReg.betaCargaTrabalho << "carga\n";
	
	/*56.05consumidor
	  201.95demanda
	  201.5carga*/

	
	SubRegioes **subReg = new SubRegioes*[infoSubReg.qntReg];	
	for(int i=0; i<infoSubReg.qntReg; i++){
		subReg[i] = new SubRegioes(tam);
	}
	
	for(int i=0; i < tam; i++){
		cout << vertices[i]->fuga << " " << vertices[i]->id << "\n";
	}
	montarSubRegiao(grafo, vertices, infoSubReg, subReg);
	return 0;
}

//============================================================================
// Name        : main.cpp
// Author      : Igor
// Version     : 0.0.0.1
// Description : Dynamic Ant Programming in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
using namespace std;

#define MAX_ELEMENTOS 100

/* Definição das estruturas de dados */

enum tp_no {START=-1, TERMINAL=1, NAO_TERMINAL=2};
enum tp_terminais { T_X, T_CT };
enum tp_nao_terminais { T_SOMA, T_SUB, T_MUL, T_DIV, T_SEN, T_COS};
char aridade_nao_terminais[] = {2, 2, 2, 2, 1, 1};

typedef struct{
	tp_no tipo;
	char valor;
	char aridade;
}type_no;

typedef struct{
	type_no caminho[MAX_ELEMENTOS];
	int tamanho;
	float fitness;
}type_ant;

/**/

/* Variáveis */

type_ant * formigas;
type_no elementos[MAX_ELEMENTOS]; //Elementos da iteração corrente
double feromonios[MAX_ELEMENTOS][(MAX_ELEMENTOS*2)+1]; //+1 para o nó Start

int m_iteracoes; //Número de iterações do algoritmo
int m_n_ants;    //Número de formigas
int m_elementos; //Número corrente de nós
float m_alpha;   //Fator de importância do histórico de feromônios
float m_beta;    //Fator de importância da heurística
float m_rho;     //Taxa de evaporação dos feromônios
float m_tal_min; //Valor mínimo de feromônio em uma aresta
float m_tal_ins; //Valor de feromônio atribuído a uma linha/coluna inseridos

float probabilidades[MAX_ELEMENTOS]; //Probabilidade de cada elemento ser escolhido
char  visitados[MAX_ELEMENTOS];

/**/

/* Protótipos das funções */

void  ObtemParametros(int argc, char * argv[]);
void  InicializaFeromonios();
void  ConstroiCaminho(int id_formiga);
float CalculaProbabilidade(int i, int j);
float AvaliaPrograma(int * programa, int ** dados);
void  AtualizaFeromonios();
void  DeletaNos();
void  InsereNos(int iteracao);

/* */

int main(int argc, char * argv[]) {

	/* Inicialização */
	ObtemParametros(argc, argv);
	InicializaFeromonios();
	InsereNos(0);

	int count = 1, i;

	/* Critério de parada */
	while(count <= m_iteracoes){

		/* Constrói o caminho para cada formiga */
		for(i=0; i< m_n_ants;i++){
			ConstroiCaminho(i);
		}

		AtualizaFeromonios();
		DeletaNos();
		InsereNos(count);

		count++;
	}

	return 0;
}

/* Implementação das funções */

void  ObtemParametros(int argc, char * argv[]){

	m_iteracoes = 100;
	m_n_ants  = 100;
	m_alpha   = 0.9f;
	m_beta    = 0.1f;
	m_rho     = 0.0f;
	m_tal_min = 0.0f;

	//Nota: interessante para incentivar escolhas de novos caminhos
	m_tal_ins = 0.2f;

    formigas = (type_ant *) malloc(m_n_ants * sizeof(type_ant));
}

void InicializaFeromonios(){

	int i,j;
	for(i=0;i<MAX_ELEMENTOS;i++){
		for(j=0;j<2*MAX_ELEMENTOS;j++){
			feromonios[i][j] = m_tal_min;
		}
	}
}

void ConstroiCaminho(int id){

	int i,j;

	for(i=0;i<m_elementos;i++){
		probabilidades[i] = 0.0f;
		visitados[i] = 0;
	}

	formigas[id].tamanho = 0;
	formigas[id].caminho[0].tipo = START;


}

float CalculaProbabilidade(int i, int j){

	return 0;
}

void AtualizaFeromonios(){

}

void InsereNos(int iteracao){

}

void DeletaNos(){

}


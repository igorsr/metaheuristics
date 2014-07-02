//============================================================================
// Name        : main.cpp
// Author      : Igor
// Version     : 0.0.0.1
// Description : Dynamic Ant Programming in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#define MAX_ELEMENTOS 200

/* Definição das estruturas de dados */

enum tp_no {TERMINAL=1, NAO_TERMINAL=2};
enum tp_terminais { T_X, T_CT };
enum tp_nao_terminais { T_SOMA, T_SUB, T_MUL, T_DIV, T_SEN, T_COS};
char aridade_nao_terminais[] = {2, 2, 2, 2, 1, 1};

typedef struct{
	tp_no tipo;
	char valor;
	char aridade;
}No;

/* Variáveis */

No elementos[MAX_ELEMENTOS]; //Elementos da iteração corrente
double feromonios[MAX_ELEMENTOS][MAX_ELEMENTOS*2];

int m_n_ants;   //Número de formigasFelipe
float m_alpha;  //Fator de importância do histórico de feromônios
float m_beta;   //Fator de importância da heurística
float m_rho;    //Taxa de evaporação dos feromônios
float probabilidades[MAX_ELEMENTOS]; //Probabilidade de cada elemento ser escolhido

/**/

/* Protótipos das funções */

float CalculaProbabilidade(int i, int j);
float AvaliaPrograma(int * programa, int ** dados);

/* */


int main(int argc, char * argv[]) {
	cout << "!!!Hello World!!!" << endl;
	return 0;
}

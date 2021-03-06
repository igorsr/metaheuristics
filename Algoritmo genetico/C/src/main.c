/*
 * main.c
 *
 * Author: igorsr
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GEN_SIZE 8
#define POP_SIZE 50
#define TOURNAMENT_SIZE 2
#define P_CROSSOVER 0.8
#define P_MUTATION 0.05
#define GENERATIONS 100
#define ELISTIST_SIZE 1

typedef struct{
	char genotype[GEN_SIZE];
	float fitness;
}individual;

individual pop[POP_SIZE];

void initialize_population(individual * pop){

	int i,j;
	for(i=0; i< POP_SIZE;i++){
		for(j=0;j<GEN_SIZE;j++){
			pop[i].genotype[j] = rand() % 2;
		}
	}
}

/*
 * Simply gets the string's integer value
 *
 */
float fitness_function(individual * p){

	float sum=0;
	int i, n=1;
	for(i=GEN_SIZE-1; i>=0; i--, n=n<<1){
		sum+=(int)p->genotype[i] * n;
	}
	return sum;
}

void evaluation(individual *pop){

	int i;
	for(i=0; i< POP_SIZE; i++){
		pop[i].fitness = fitness_function(&pop[i]);
	}
}

/*
 * Tournament selection
 */
int selection(int competitor, individual * pop){

	int i, winner = competitor;
	int partner;

	for(i=0; i< TOURNAMENT_SIZE; i++){

		partner = rand() % POP_SIZE;

		if(pop[partner].fitness > pop[winner].fitness){
			winner = partner;
		}

	}

	return winner;
}

/*
 * Single point crossover
 * */
void recombination(individual parents[2], individual offspring[2]){

	int i;

	float random = (float)rand()/RAND_MAX;

	if(random <= (float)P_CROSSOVER){

		int point = rand() % GEN_SIZE;

		for(i=0; i <= point;i++){
			offspring[0].genotype[i] = parents[0].genotype[i];
			offspring[1].genotype[i] = parents[1].genotype[i];
		}

		for(i=point+1; i <GEN_SIZE;i++){
			offspring[0].genotype[i] = parents[1].genotype[i];
			offspring[1].genotype[i] = parents[0].genotype[i];
		}
	}
	else{
		for(i=0; i < GEN_SIZE;i++){
			offspring[0].genotype[i] = parents[0].genotype[i];
			offspring[1].genotype[i] = parents[1].genotype[i];
		}
	}
}

/*
  Bit-flip mutation
 * */
void mutation(individual *p){

	int i;
	for(i=0;i< GEN_SIZE; i++){

		float random = (float)rand()/RAND_MAX;

		if(random < (float)P_MUTATION){
			p->genotype[i] = ((int)p->genotype[i] + 1) % 2;
		}
	}
}


int compare_individuals(const void* a, const void* b){

	individual* p1 = (individual*)a;
	individual* p2 = (individual*)b;

    return p1->fitness < p2->fitness;
}

void sort(individual * pop){	
	qsort(pop, POP_SIZE, sizeof(individual), (int(*)(const void*, const void*))compare_individuals);
}


void population_replacement(individual *pop, individual * newPop){
	
	sort(pop);
	sort(newPop);

	//keeps elitist individuals
	int j = 0, l, i;
	for(i = ELISTIST_SIZE; i < POP_SIZE;i++,j++){

		for(l=0;l<GEN_SIZE;l++){
			pop[i].genotype[l] = newPop[j].genotype[l];
		}

		pop[i].fitness = newPop[j].fitness;
	 }
}

void add_individual(individual *pop, individual *p, int index){

	int j;
	for(j=0;j<GEN_SIZE;j++){
		pop[index].genotype[j] = p->genotype[j];
	}
}

void create_new_population(individual * pop, individual * newPop){

	int i;

	for(i=0;i<POP_SIZE-1;i++) {

		individual parents[2], offspring[2];

		parents[0] = pop[selection(i, pop)];
		parents[1] = pop[selection(i+1, pop)];

		recombination(parents, offspring);

		mutation(&offspring[0]);
		mutation(&offspring[1]);

		add_individual(newPop, &offspring[0],i);
		add_individual(newPop, &offspring[1],i+1);

		i++;
	 }
}


void print_population(individual * pop){

	int i,j;

	for(i=0;i<POP_SIZE;i++){
		for(j=0;j<GEN_SIZE;j++)
			printf("%d",pop[i].genotype[j]);
		printf("==> %f\n", pop[i].fitness);
	}
}

void print_best(individual * pop){
	
	float best;

	#ifdef ELITIST_SIZE 
   	if(ELITIST_SIZE>0){	

	if(pop[0].fitness > pop[ELITIST_SIZE].fitness){
		best =  pop[0].fitness;
	}
	else{
		best =  pop[ELITIST_SIZE].fitness;	
	}

	}
	#else
		best =  pop[0].fitness;
	#endif

	printf("Best: %f\n", best);
	

}


int main(int argc, char **argv){

	individual pop[POP_SIZE], newPop[POP_SIZE];
	int generation=1;

	initialize_population(pop);
	evaluation(pop);
	sort(pop);

	while(generation <= GENERATIONS){

		printf("-------------------------------------\n");
		printf("Generation %d:\n", generation);
		
		print_best(pop);
		//print_population(pop);

		create_new_population(pop, newPop);
		evaluation(newPop);
		population_replacement(pop, newPop);

		generation++;
	}

	return 0;
}

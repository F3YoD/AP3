#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arbresynt.h"
#include "divers.h"



int main(int argc, char ** argv){

	TArbreSynt Arbre = ConsBinaire('+', ConsConstante(1), ConsFonction('s', ConsFonction('l', ConsBinaire('*', ConsConstante(10), ConsVariable()))));
	TArbreSynt a1 = CreeArbreAlea(1000);
	double res = Evaluation(Arbre, 1);
	printf("l'arbre vaut : %lf\n", res);
	
	printf("l'arbre alea vaut : %lf\n", Evaluation(a1, 1));
	
	LibererArbreSynt(Arbre);

	// ================== TEST ==================== //

	//VerificationMemoire(&NbPointeursNonLiberer, &NombreOctetsAlloués);
	//printf("nbre pt non libere: %d \nnombre d'octet alloues : %d\n", NbPointeursNonLiberer, NombreOctetsAlloués);

	getchar();
	return 0;
}

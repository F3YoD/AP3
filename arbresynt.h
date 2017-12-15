#ifndef _ARBRESYNT_
#define _ARBRESYNT_

#include "divers.h"
#include "string.h"

#include <time.h>
#include <math.h>
#include <stdbool.h>

typedef enum {Variable, Constante, Fonction, Binaire}TNature;

typedef struct NoeudSynt {
	struct NoeudSynt * FG, *FD;
	double ValConst;
	char OperOuFonction;
	TNature Nature;
}TNoeudSynt, *TArbreSynt;


TArbreSynt ConsVariable();

TArbreSynt ConsConstante(double pConstante);

TArbreSynt ConsFonction(char nom, TArbreSynt pFG);

TArbreSynt ConsBinaire(char op, TArbreSynt pFG, TArbreSynt pFD);

TNature Nature(TArbreSynt pA);

TArbreSynt FG(TArbreSynt pA);

TArbreSynt FD(TArbreSynt pA);

double GetConstante(TArbreSynt pA);

double Evaluation(TArbreSynt, double);

char GetOperOuFonction(TArbreSynt pA);

void LibererArbreSynt(TArbreSynt pA);

char *ArbreEnChaine(TArbreSynt pA);

TArbreSynt CreeArbreAlea(int h);

int ArbreSyntEgaux(TArbreSynt, TArbreSynt);

#endif

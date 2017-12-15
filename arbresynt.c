#include <stdio.h>
#include <stdlib.h>

#include "arbresynt.h"


TArbreSynt ConsVariable(){
	//
	TArbreSynt Res = (TArbreSynt)malloc(sizeof(TNoeudSynt));
	Res->Nature = Variable;
	return Res;
}

TArbreSynt ConsConstante(double pConstante){
	//
	TArbreSynt Res = (TArbreSynt)malloc(sizeof(TNoeudSynt));
	Res->Nature = Constante;
	Res->ValConst = pConstante;
	return Res;
}

TArbreSynt ConsFonction(char nom, TArbreSynt pFG){
	//
	TArbreSynt Res = (TArbreSynt)malloc(sizeof(TNoeudSynt));
	Res->Nature = Fonction;
	Res->OperOuFonction = nom;
	Res->FG = pFG;
	return Res;
}

TArbreSynt ConsBinaire(char op, TArbreSynt pFG, TArbreSynt pFD){
	//
	TArbreSynt Res = (TArbreSynt)malloc(sizeof(TNoeudSynt));
	Res->Nature = Binaire;
	Res->OperOuFonction = op;
	Res->FG = pFG;
	Res->FD = pFD;
	return Res;
}

TNature Nature(TArbreSynt pA){
	return pA->Nature;
}

TArbreSynt FG(TArbreSynt pA){
	return pA->FG;
}

TArbreSynt FD(TArbreSynt pA){
	return pA->FD;
}

double GetConstante(TArbreSynt pA){
	return pA->ValConst;
}

char GetOperOuFonction(TArbreSynt pA){
	printf("%c\n", pA->OperOuFonction);
	return pA->OperOuFonction;
}

void LibererArbreSynt(TArbreSynt pA){
	switch (pA->Nature){
	case Variable:
		free(pA);
		break;
	case Constante:
		free(pA);
		break;
	case Fonction:
		LibererArbreSynt(pA->FG);
		free(pA);
		break;
	case Binaire:
		LibererArbreSynt(pA->FG);
		LibererArbreSynt(pA->FD);
		free(pA);
		break;
	}
}

double Evaluation(TArbreSynt pA, double pX){
	double Arg;
	switch (Nature(pA)){
		case Constante:
			return GetConstante(pA);
			break;
		case Variable:
			return pX;
			break;
		case Fonction:
			Arg = Evaluation(FG(pA), pX);
			switch (GetOperOuFonction(pA)){
			case 'c':
				return cos(Arg);
				break;
			case 's':
				return sin(Arg);
				break;
			case 'r':
				return sqrt(Arg);
				break;
			case 't':
				return tan(Arg);
				break;
			case 'l':
				return log(Arg);
				break;
			default:
				AfficherMessage("erreur", true);
				break;
			}
		case Binaire:
			switch (GetOperOuFonction(pA)){
			case '*':
				return Evaluation(FG(pA), pX) * Evaluation(FD(pA), pX);
			case '+':
				return Evaluation(FG(pA), pX) + Evaluation(FD(pA), pX);
			case '-':
				return Evaluation(FG(pA), pX) - Evaluation(FD(pA), pX);
			case '/':
				if (GetConstante(FD(pA)) == 0)
					AfficherMessage("erreur", true);
				return Evaluation(FG(pA), pX) / Evaluation(FD(pA), pX);
			default:
				AfficherMessage("erreur", true);
				return EXIT_FAILURE;
			}
	
		default:
			AfficherMessage("erreur ", true);
			break;
	}
}

char *ArbreEnChaine(TArbreSynt pA){
	//
	char *chaine;
	char *fg;
	char *fd;
	char bin[2];
	switch (Nature(pA)){
	case Constante:
		chaine = malloc(100 * sizeof(char));
		snprintf(chaine, 100, "%lf", GetConstante(pA));
		return (char*)chaine;
		break;
	case Variable:
		return (char*)"x";
		break;
	case Binaire:
		fg = (char*)ArbreEnChaine(FG(pA));
		fd = (char*)ArbreEnChaine(FD(pA));
		bin[0] = GetOperOuFonction(pA);
		bin[1] = '\0';

		if (Nature(FG(pA)) == Binaire){
			int taille = strlen(fg) + strlen(fd) + strlen(bin) + 2;
			char *chainefg = (char*)malloc(taille * sizeof(char));
			snprintf(chainefg, taille, "(%s)", fg);
		}
		else if (Nature(FD(pA)) == Binaire){
			int taille = strlen(fg) + strlen(fd) + strlen(bin) + 2;
			char *chainefd = (char*)malloc(taille * sizeof(char));
			snprintf(chainefd, taille, "(%s)", fd);
		}
		
		int Taille = strlen(fg) + strlen(fd) + strlen(bin) + 2;
		char *maChaine = (char*)malloc(Taille * sizeof(char));
		snprintf(maChaine, Taille, "%s%s%s", fg, bin, fd);
		return maChaine;
	}
}

TArbreSynt CreeArbreAlea(int h){
	/// local
	int h2 = 1 + rand()%(h-1);
	char op[4] = {'+','-','*','/'};
	char fonc[5] = {'c', 's', 't', 'l', 'm'};

	if(h == 1){
		if(rand()%2) return ConsVariable();
		return ConsConstante(1 + rand()%50);	
	}else{
		if(rand()%2){
			return ConsFonction(fonc[rand()%5],CreeArbreAlea(h - 1));
		}else{
			if(rand()%2){
				return ConsBinaire(op[rand()%4],
					CreeArbreAlea(h - 1),
					CreeArbreAlea(h2)
				);
			}else{
				
				return ConsBinaire(op[rand()%4],
					CreeArbreAlea(h2),
					CreeArbreAlea(h - 1)
				);
			}
		}
	}
}

int ArbreSyntEgaux(TArbreSynt pA1, TArbreSynt pA2){
// role : retourne 1 si pA1 == pA2 sinon retourne 0
	if(Nature(pA1) != Nature(pA2)) return 0;
	switch(Nature(pA1)){
		case Variable: return 1;
		case Constante: return (GetConstante(pA1) == GetConstante(pA2));
		case Fonction:
			if(GetOperOuFonction(pA1) != GetOperOuFonction(pA2))
				return 0;
			return ArbreSyntEgaux(FG(pA1), FG(pA2));
		case Binaire:
			return GetOperOuFonction(pA1) == GetOperOuFonction(pA2) &&
				ArbreSyntEgaux(FG(pA1), FG(pA2)) && 
				ArbreSyntEgaux(FD(pA1), FD(pA2));
		default: return 0; 	
	}
}

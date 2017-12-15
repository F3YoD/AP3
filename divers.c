#include <stdio.h>
#include <stdlib.h>

#include "divers.h"

void AfficherMessage(char * pMsg, bool pB){
	//
	printf("%s\n", pMsg);
	if (pB){
		printf("Execution Interrompu\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
}

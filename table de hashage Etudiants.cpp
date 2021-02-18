#include <stdio.h>
#include <stdlib.h>
#include <String.h>

/*creer une liste chainée des Etudians.*/


//un element de la liste
typedef struct etudiant {
	char* CNE; //string
	char* nom; //string
	char* prenom; //string
	char* filiere; //string
	float moyennes[8]; //numbers table
	
	//pointeur vers element suivant
	etudiant *suivant;
} Etudiant;

//structure de controle
/*
	pour quoi stcture avec une seule variable puisque on peut la declarer directement ?
	oui, on peut faire ça mais je prefere d'utiliser un structure pour avoir l'oportunté d'ajouter quelque d'autre chose
	par exemple une variable contenant le nombre des éléments de la liste ...
*/
typedef struct liste{
	Etudiant *premier; //the door of the list hhh
} Liste;


Liste * initialisation();
void initialiserEtudiant(Etudiant *etudiant);
Etudiant * creationEtudiant(char* CNE, char* nom, char* prenom, char*filiere, float* moyennes);
void insertionDebut(Liste *liste, Etudiant *nouveauEtudiant);
void insertionApres(Liste *liste, Etudiant *nouveauEtudiant, Etudiant *precedent);
void suppressionDernier(Liste *liste);
void suppressionEtudiant(Liste *liste, Etudiant *etudiantAsupp, Etudiant *precedent);
void afficherEtudiant(Etudiant *etudiant);
void afficherList(Liste* liste);
int tailleListe(Liste *liste);


unsigned int hachage(char* chaine, int tailleTable);
Etudiant  rechercheTableHachage(Etudiant tableEtudiants[], int tailleTable, char* nom );
//  *********************** main app ***********************

int main(){
	/*
	Liste *liste1 = initialisation();
	float etudiant1Moyennes[8] = {15,12,16.5,9,18,14,17,20};
	Etudiant *etudiant1 = creationEtudiant("1", "Ahmed", "Lamin", "BDCC1", etudiant1Moyennes);
	
	float etudiant2Moyennes[8] = {8,20,16.5,9,18,14,17,20};
	Etudiant *etudiant2 = creationEtudiant("2", "Essadeq", "Lamin", "BDCC1", etudiant2Moyennes);
	
	float etudiant3Moyennes[8] = {14,48,16.5,9,18,14,17,20};
	Etudiant *etudiant3 = creationEtudiant("3", "Mouaad", "Lamin", "BDCC1", etudiant3Moyennes);
	
	float etudiant4Moyennes[8] = {11.25,12,16.5,9,18,14,17,20};
	Etudiant *etudiant4 = creationEtudiant("4", "Rharib", "Lamin", "BDCC1", etudiant4Moyennes);
	
	float etudiant44Moyennes[8] = {4.4,4,4.4,4,4,4,4,4};
	Etudiant *etudiant44 = creationEtudiant("444444", "ELRAB3A", "Raeef", "BDCC1", etudiant44Moyennes);
	
	insertionDebut(liste1, etudiant1);
	insertionDebut(liste1, etudiant2);
	insertionDebut(liste1, etudiant3);
	insertionDebut(liste1, etudiant4);
	
	insertionApres(liste1, etudiant44, etudiant4);
	
	suppressionEtudiant(liste1, etudiant2, etudiant3); // suppremer etudiant2
	
	//suppressionDernier(liste1);
	
	printf("\n taille de liste (sans l'element d'initialisation) = %d \n",tailleListe(liste1));
	
	afficherList(liste1);
	*/
	
	int tailleTable = 14; 
	Etudiant  tableEtudiants[tailleTable];
	
	float etudiant44Moyennes[8] = {4.4,4,4.4,4,4,4,4,4};
	Etudiant *etudiant44 = creationEtudiant("444444", "ELRAB3A", "Raeef", "BDCC1", etudiant44Moyennes);
	
	printf("%d \n",hachage(etudiant44->nom, tailleTable));
	int indice = hachage(etudiant44->nom, tailleTable);
	tableEtudiants[indice] = *etudiant44;
	
	Etudiant etud = rechercheTableHachage(tableEtudiants, 14, "ELRAB3A");
	printf("%s \n", etud.prenom);
	
	return 0;
}

//  *********************** end main app *********************


//  *********************** hachage *********************

unsigned int hachage(char* chaine, int tailleTable){
	unsigned int nombre = 0;
	for(int i=0; i<strlen(chaine); i++){
		nombre = nombre*7+(int)chaine[i];
	}
	nombre %=tailleTable; // toujour un nombre entre 0 et (tailleTable-1)
	return nombre;
	
	/*
	Grâce à cette fonction de hachage, vous savez donc dans quelle case
	de votre tableau vous devez placer vos données.
	*/
}


Etudiant  rechercheTableHachage(Etudiant tableEtudiants[], int tailleTable, char* nom ){
	unsigned int indice = hachage(nom, tailleTable);
	Etudiant etud = (Etudiant)tableEtudiants[indice];
	return etud;
}

//  *********************** start Liste Chainée *********************

//fonction d'initialisation
Liste * initialisation(){
	Liste *liste = (Liste *)malloc(sizeof(*liste));
	Etudiant *etudiant = (Etudiant *)malloc(sizeof(*etudiant));
	
	if(liste == NULL || etudiant == NULL){
		exit(EXIT_FAILURE);
	}
	
	initialiserEtudiant(etudiant);
	etudiant->suivant = NULL;
	
	//element porte
	liste->premier = etudiant;
	
	return liste;
}

void initialiserEtudiant(Etudiant *etudiant){
	etudiant->CNE = NULL;
	etudiant->nom = NULL;
	etudiant->prenom = NULL;
	etudiant->filiere = NULL;
	
	for(int i=0; i<8; i++){
		etudiant->moyennes[i] = 0;
	}
	
}

Etudiant * creationEtudiant(char* CNE, char* nom, char* prenom, char* filiere, float* moyennes2){
	Etudiant *etudiant = (Etudiant *)malloc(sizeof(*etudiant));
	etudiant->CNE = CNE;
	etudiant->nom = nom;
	etudiant->prenom = prenom;
	etudiant->filiere = filiere;
	
	for(int i=0; i<8; i++){
		etudiant->moyennes[i] = moyennes2[i];
	}
	
	return etudiant;
}

void insertionDebut(Liste *liste, Etudiant *nouveauEtudiant){
	if(liste == NULL || nouveauEtudiant == NULL){
		exit(EXIT_FAILURE);
	}
	
	//ajouter le nouveau element au début de liste
	nouveauEtudiant->suivant = liste->premier;
	liste->premier = nouveauEtudiant;
	
}

void insertionApres(Liste *liste, Etudiant *nouveauEtudiant, Etudiant *precedent){
	if(liste == NULL || nouveauEtudiant == NULL || precedent == NULL){
		exit(EXIT_FAILURE);
	}
	
	//ajouter le nouveau element 
	nouveauEtudiant->suivant = precedent->suivant;
	precedent->suivant = nouveauEtudiant;
	
}

void suppressionDernier(Liste *liste){
	if(liste == NULL){
		exit(EXIT_FAILURE);
	}
	
	if(liste->premier != NULL){
		//verifons qu'il ya au moins un element dans la liste
		Etudiant *etudiantAsupp =  liste->premier;
		liste->premier = liste->premier->suivant;
		free(etudiantAsupp);
	}
}

void suppressionEtudiant(Liste *liste, Etudiant *etudiantAsupp, Etudiant *precedent){
	if(liste == NULL || etudiantAsupp == NULL || precedent == NULL){
		exit(EXIT_FAILURE);
	}
	
	if(liste->premier != NULL){
		//verifons qu'il ya au moins un element dans la liste
		precedent->suivant = etudiantAsupp->suivant;
		free(etudiantAsupp);
	}
}

void afficherEtudiant(Etudiant *etudiant){
	
	if(etudiant == NULL){
		exit(EXIT_FAILURE);
	}
	printf("\n==========================================================\n");
	printf("| %s | %s | %s | %s |\n",  etudiant->CNE, etudiant->nom, etudiant->prenom, etudiant->filiere);
	printf("\n");
	printf("Notes : ");
	for(int i=0; i<8; i++){
		printf("%.2f ", etudiant->moyennes[i]);
	}
	printf("\n==========================================================\n");
	printf("\n\n\n");
}

void afficherList(Liste* liste){
	if(liste == NULL){
		exit(EXIT_FAILURE);
	}
	
	Etudiant *etudiantActuel = liste->premier;
	
	while(etudiantActuel != NULL){
		afficherEtudiant(etudiantActuel);
		etudiantActuel = etudiantActuel->suivant;
	}
}

int tailleListe(Liste *liste){
	int counter = 0;
	if(liste == NULL ){
		exit(EXIT_FAILURE);
	}
	Etudiant *etudiantActuel = liste->premier;
	
	while(etudiantActuel != NULL){
		counter++;
		etudiantActuel = etudiantActuel->suivant;	
	}
	return counter-1;
}


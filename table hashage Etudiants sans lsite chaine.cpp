/* ce programme est pour but d'utiliser un table de hashage pour sauvgarder une listes des etudiant*/
#include <stdio.h>
#include <stdlib.h>
#include <String.h>

/*structure Etudiant */
typedef struct{
	char* CNE; //string
	char* nom; //string
	char* prenom; //string
	char* filiere; //string
	float moyennes[8]; //numbers table
} Etudiant;

//representer la table de hachage par une structure.
typedef struct{
	Etudiant** etudiants; //tableau des pointeurs.
	int count; //nombre des elements
	int size; //taille du table
}HashTable;

/*prototypes */
HashTable* creer_table(int size);
unsigned int hachage(char* chaine, int tailleTable);
void insererEtudiant(HashTable * table, Etudiant * etudiant);
Etudiant * rechercherEudiant(HashTable *table, char* CNE );
void supprimerEtudiant(HashTable *table, char* CNE );
Etudiant * creationEtudiant(char* CNE, char* nom, char* prenom, char* filiere, float* moyennes2);
void afficherEtudiant(Etudiant *etudiant);
void freeEtudiant(Etudiant* etudiant);
void freeTable(HashTable *table);
int isEtudiantExiste(HashTable *table, char* CNE);
void afficherTable(HashTable *table);

/************************************************************** Start Main App */
int main(){
	
	//creation du hash table
	HashTable * tableHachage = creer_table(12); //était 5
	
	float notes_etudiant1[8] = {12,20,15.32,10,14,15,18};
	Etudiant * etudiant1 = creationEtudiant("AA241", "ELAAMIRI", "Essadeq", "BDCC", notes_etudiant1 );//
	//collision :  AA141 et  UU478 tableSize = 5/11 et facteur = 7
	
	float notes_etudiant2[8]  = {12,20,19,8.6,12.5,15,20};
	Etudiant * etudiant2 = creationEtudiant("UU478", "AALAMI", "GHAYA", "BDCC", notes_etudiant2 );
	
	float notes_etudiant3[8]  = {12.5,20,15.32,9.8,14,15,17};
	Etudiant * etudiant3 = creationEtudiant("B1415", "Layla", "TAMIN", "BDCC", notes_etudiant3 );
	
	float notes_etudiant4[8]  = {13,20,12,9.8,14,15,17};
	Etudiant * etudiant4 = creationEtudiant("14B15", "Layla2", "ARATYM", "BDCC", notes_etudiant4 );
	
	float notes_etudiant5[8]  = {13,20,12,9.8,14,15,17};
	Etudiant * etudiant5 = creationEtudiant("6655pp", "Zaryty", "ARATYM", "BDCC", notes_etudiant4 );
	
	float notes_etudiant6[8]  = {13,20,12,9.8,14,15,17};
	Etudiant * etudiant6 = creationEtudiant("oo1478", "Tayori", "ARATYM", "BDCC", notes_etudiant4 );
	
	//inserer au table
	insererEtudiant(tableHachage, etudiant1);
	insererEtudiant(tableHachage, etudiant2);
	insererEtudiant(tableHachage, etudiant3);
	insererEtudiant(tableHachage, etudiant4);
	insererEtudiant(tableHachage, etudiant5);
	insererEtudiant(tableHachage, etudiant6);
	
	//chercher etudiant
	isEtudiantExiste(tableHachage, "14B15");
	
	printf("count : %d\n", tableHachage->count);
	
	afficherTable(tableHachage);

	return 0;
}
/************************************************************** End Main App */

HashTable* creer_table(int size){
	HashTable *table = (HashTable*)malloc(sizeof(*table));
	table->size = size;
	table->count = 0;
	table->etudiants = (Etudiant**)malloc(table->size*sizeof(Etudiant*));
	for(int i=0; i < (table->size); i++){
		table->etudiants[i] = NULL;
	}
	return table;
}


unsigned int hachage(char* chaine, int tailleTable){
	/*
	cette fonction reçoit une chaine de charachère, et la taille du table dans lequel on va faire le stockage
	puis transformer la chaine à un entier non signée  entre 0 et (tailleTable-1)
	*/
	unsigned int nombre = 0;
	for(int i=0; i<strlen(chaine); i++){
		nombre = nombre*7+(int)chaine[i]; 
		/*
		on multiplie chaque par 7 pour faire difference 
		entre les mots de même lettres et avec une autre  
		permutation ex :"ABC" et "BAC"
		*/
	}
	nombre %=tailleTable; // toujour un nombre entre 0 et (tailleTable-1)
	
	return nombre;
	
	/*
	Grâce à cette fonction de hachage, vous savez donc dans quelle case
	de votre tableau vous devez placer vos données.
	*/
}

void insererEtudiant(HashTable * table, Etudiant * etudiant){
	unsigned int indice = hachage(etudiant->CNE, table->size);
	Etudiant *etudiant1 = (Etudiant *)table->etudiants[indice];
	if(etudiant1 != NULL){
		if(strcmp(etudiant1->CNE, etudiant->CNE) == 0){
			printf("\n Erreur d'insertion: il existe une entree avec le meme key! \n [index: %d][etudiant : %s]\n updated to : [etudiant : %s]\n\n",indice, etudiant1->CNE, etudiant->CNE);
			table->etudiants[indice] = etudiant;
			return;
		}
		else{
			printf("\n il ya une collistion! [index: %d][etudiant: %s][etudiant: %s]\n",indice, etudiant1->CNE, etudiant->CNE);
			return;
		}
	}
	if(table->count == table->size){
		printf("\n Erreur d'insertion: la table et plienne! ");
		return;
	}
	table->etudiants[indice] = etudiant;
	table->count +=1;
	printf("\n Insertion avec succes [etudiant: %s]!\n",etudiant->CNE);
}

Etudiant * rechercherEudiant(HashTable *table, char* CNE ){
	
	unsigned int indice = hachage(CNE, table->size); // transformer le nom au indice 
	Etudiant * etudiant = (Etudiant *)table->etudiants[indice];
	if(etudiant != NULL){
		if(strcmp(etudiant->CNE, CNE) == 0){
			return etudiant;
		}
	}
	
	return NULL;
}

int isEtudiantExiste(HashTable *table, char* CNE){
	
	if(rechercherEudiant(table, CNE) == NULL){
		printf("\n Etudiant [%s] n'existe pas ! \n ", CNE);
		return 0;
	}
	printf("\n Etudiant [%s] existe ! \n ", CNE);
	return 1;
}

void supprimerEtudiant(HashTable *table, char* CNE ){
	
	unsigned int indice = hachage(CNE, table->size); // transformer le nom au indice 
	Etudiant * etudiant = (Etudiant *)table->etudiants[indice];
	freeEtudiant(etudiant);
	table->etudiants[indice] = NULL;
}

void afficherTable(HashTable *table){
	for(int i=0; i<table->size; i++){
		Etudiant * Curretudiant = table->etudiants[i];
		if(Curretudiant != NULL){
			afficherEtudiant(Curretudiant);
		}
	}
}

Etudiant * creationEtudiant(char* CNE, char* nom, char* prenom, char* filiere, float* moyennes2){
	/*
		recoit les données ,
		crée l'etudiant
		return un pointeur vers lui
	*/
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

void freeEtudiant(Etudiant* etudiant){
	free(etudiant);
}
void freeTable(HashTable *table){
	 // Frees the table
    for (int i=0; i<table->size; i++) {
        Etudiant* etudiant = table->etudiants[i];
        if (etudiant != NULL)
            freeEtudiant(etudiant);
    }
 
    free(table->etudiants);
    free(table);
}

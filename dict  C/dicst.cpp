#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define WORD_NBR 15

//int compareTwoWords(char *word1, char *word2)
int compareTwoWords(char *word1, char *word2);

int main(){
	
	//char words1[WORD_NBR][5] = {"dEer", "dzer", "dzer", "dBZr", "dzzq"};
	char words1[WORD_NBR][5] = {"darn", "dona", "dorm", "dram", "mano", "mora", "morn", "nard", "noma", "norm", "orad", "rand", "road", "roam", "roan"};

	char words[WORD_NBR][5];
	char temp[5];
	
	//to lowercase
	for(int i=0; i<WORD_NBR; i++){
		strcpy(words[i], strlwr(words1[i]));
	}
	
	
	for(int i=0; i<WORD_NBR; i++){
		for(int j=0; j<WORD_NBR; j++){
			if(compareTwoWords(words[i], words[j]) == -1){
				strcpy(temp, words[i]);
				strcpy(words[i], words[j]);
				strcpy(words[j], temp);
			}
		}
	}

	
	//showing
	printf("\n\n----------------\n");
	for(int i=0; i<WORD_NBR; i++){
		printf("%s \n", words[i]);
	}
	
	return 0;
}

int compareTwoWords(char *word1, char *word2){
	//if the word1 is less than word2 returns -1
	//if the word2 is less then word1 returns 1
	// if the words are the same returns 0;
	
	char s1[5], s2[5];
	int k=0; 	//compteur
	int nbr=5; //nombre de charactères
	
	//to lowercase
	strcpy(s1, strlwr(word1));
	strcpy(s2, strlwr(word2));
	
	if((int)s1[k] != (int)s2[k]){
		if((int)s1[k] < (int)s2[k]){
			return -1;
		}
		else if((int)s1[k] > (int)s2[k]){
			return 1;
		}
		
	}
	else{
		do{
			k++;
			if((int)s1[k] < (int)s2[k]){
				return -1;
			}
			else if((int)s1[k] > (int)s2[k]){
				return 1;
			}
			
		}
		while((k<nbr) && (s1[k] == s2[k]));
	}
	
	return 0;
}

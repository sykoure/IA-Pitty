#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUMBER_LIGNE 151
#define PI 3.141592

//Structure du tableau contenant les données pour la BDA iris
typedef struct iris iris;
struct iris
{
    int sepal_length;
    int sepal_width;
    int petal_length;
    int petal_width;
    char species[20];
};


//Declaration des fonctions
void loadData(char *flower,int cellule);

//Lecture de la base de données iris
void loadData(char *flower,int cellule){

    //Initialisation
    FILE* file;
    char ligne[NUMBER_LIGNE];
    char *pointeur_chaine;
    int numligne;
    int sepal_length;
    int sepal_width;
    int petal_length;
    int petal_width;
    char species[10];
    iris iris[NUMBER_LIGNE];
    
    numligne = 1;    

    //Ouverture du fichier csv
    file = fopen("iris.csv","rt");
    if(file == NULL){
        printf("Ouverture impossible");
        exit(1);
    }

    //Lecture du fichier csv
    while(fgets(ligne,151,file) != NULL){
        printf("\n %d : ",numligne);
        numligne++;
        pointeur_chaine = strtok (ligne,",");


        //sepal_length
        if(sscanf(pointeur_chaine,"%d",&sepal_length) !=1){
            puts("\n issue with the value 1");
            sepal_length = -1;
        }
        pointeur_chaine = strtok(NULL,",");

        //sepal_width
        if(sscanf(pointeur_chaine,"%d",&sepal_width) !=1){
            puts("\n issue with the value 2");
            sepal_width = -1;
        }
        pointeur_chaine = strtok(NULL,",");

        //petal_length
        if(sscanf(pointeur_chaine,"%d",&petal_length) !=1){
            puts("\n issue with the value 3");
            petal_length = -1;
        }
        pointeur_chaine = strtok(NULL,",");

        //petal_width
        if(sscanf(pointeur_chaine,"%d",&petal_width) !=1){
            puts("\n issue with the value 4");
            petal_width = -1;
        }
        pointeur_chaine = strtok(NULL,",");

        //Species
        if(sscanf(pointeur_chaine,"%s",iris[numligne-1].species) !=1){
            puts("\n issue with the value 5");
            species[0] = 0;
        }


        //Affichage (Surement utile pour un futur traitement)
        printf("\n\t cellule 1 : %d",sepal_length);
        printf("\n\t cellule 2 : %d",sepal_width);
        printf("\n\t cellule 3 : %d",petal_length);
        printf("\n\t cellule 4 : %d",petal_width);
        printf("\n\t cellule 5 : %s",iris[numligne-1].species);

        iris[numligne-1].sepal_length = sepal_length;
        iris[numligne-1].sepal_width = sepal_width;
        iris[numligne-1].petal_length = petal_length;
        iris[numligne-1].petal_width = petal_width;
    }
	printf("\n");
    fclose(file);

    //Avoir la moyenne en fonction du type de fleur
    int i = 0;
    float moyenne_flower = 0;    
    for(i = 0;i < NUMBER_LIGNE;i++){
        if(strcmp(iris[i].species,flower) == 0){
			switch(cellule){
				case 0 :
            		moyenne_flower = moyenne_flower + iris[i].sepal_length;
					break;
				case 1 :
            		moyenne_flower = moyenne_flower + iris[i].sepal_width;
					break;
				case 2 :
            		moyenne_flower = moyenne_flower + iris[i].petal_length;
					break;
				case 3 : 
            		moyenne_flower = moyenne_flower + iris[i].petal_width;
					break;
			}
        }
    }
    moyenne_flower = moyenne_flower / NUMBER_LIGNE;

    //Avoir l'écart type en fonction du type de fleur
    float variance = 0;
	float ecart;
    for(i = 0;i < NUMBER_LIGNE;i++){
        if(strcmp(iris[i].species,flower) == 0){
			switch(cellule){
				case 0 :
            		variance = variance + (iris[i].sepal_length-moyenne_flower)*(iris[i].sepal_length-moyenne_flower);
					break;
				case 1 :
            		variance = variance + (iris[i].sepal_width-moyenne_flower)*(iris[i].sepal_width-moyenne_flower);
					break;
				case 2 :
            		variance = variance + (iris[i].petal_length-moyenne_flower)*(iris[i].petal_length-moyenne_flower);
					break;
				case 3 : 
            		variance = variance + (iris[i].petal_width-moyenne_flower)*(iris[i].petal_width-moyenne_flower);
					break;
			}
        }
    }
	variance = variance/ NUMBER_LIGNE;
	ecart = sqrt(variance);
	printf("moyenne = %f et ecart type = %f\n",moyenne_flower,ecart);


	//Calcul de la gaussienne
	FILE* fichier = NULL;

	fichier = fopen("data/C1-X1.csv","w");

	int j = 0;
	float gaussienne = 0;

	for(j = 0;j < NUMBER_LIGNE;j = j++){
        if(strcmp(iris[j].species,flower) == 0){
			gaussienne = ( 1./(ecart*sqrt(2.*PI))*exp(-pow(j-moyenne_flower,2.)/(2.*pow(ecart,2.))));
			fprintf(fichier,"%f\n", gaussienne);
		}
		else{
			fprintf(fichier,"0\n");
		}
	}

	fclose(fichier);			
}

int main(){
	loadData("setosa",0);
    return 0;
}

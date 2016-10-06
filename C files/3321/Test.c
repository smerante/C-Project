#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct VectorPair{
	char word1[20],word2[20];
	float similarity;
};

//global variables too big to fit on stack
struct VectorPair vectorPairs[1000000]; //object for each pair of words
int numVectors = 0,numPairs = 0; 
int i=0,counter = 0; // i -> words, counter -> vectors
int j,k; //for computing all possible pairs of cosine sims
char string[100000][20];	//lots of possible words
float vectors[100000][100],temp = 0; //lost of possible vectors
	
int cmpSimfunc (const void * a, const void * b)
{
	const struct VectorPair *va = (struct VectorPair *)a;
	const struct VectorPair *vb = (struct VectorPair *)b;
	//sort it in decreasing order
	if(va->similarity < vb->similarity)
	{
		return 1;
	}
	else if(va->similarity>vb->similarity)
		return -1;
	else
		return 0;
}

float dotProductFunc(float vector1[],float vector2[]){
	int i = 0;
	float product = 0;
	for(i=0;i<numVectors;i++){
		product +=  vector1[i]*vector2[i];
	}
	return product;
}
float powerOf2(float vector1[]){
	return dotProductFunc(vector1,vector1);
}

float cosineSimilarity(float vector1[],float vector2[]){
	float magnitiude = 0,dotProduct = 0;
	dotProduct = dotProductFunc(vector1,vector2);
	magnitiude  = sqrt(powerOf2(vector1))*sqrt(powerOf2(vector2));
	return dotProduct/magnitiude;
}

main(int argc, char *argv[])
{
	i=0,counter = 0;
	FILE *file;
	file = fopen(argv[1],"r");
	while(!feof(file))
	{
				if(fscanf(file,"%f",&temp) == 1){
					vectors[i-1][counter] = temp;
					counter++;
				}else{
					fscanf(file,"%s",string[i]);
					i++;
					numVectors = counter;
					counter = 0;
				}
	}
	fclose(file);
	numPairs = 0;
	for(j=0;j<=i-2;j++)
	{
		for(k=j+1;k<=i-1;k++){
		strcpy(vectorPairs[numPairs].word1,string[j]);
		strcpy(vectorPairs[numPairs].word2,string[k]);
		vectorPairs[numPairs].similarity = cosineSimilarity(vectors[j],vectors[k]);
		numPairs++;
		}
	}

   qsort(vectorPairs, numPairs, sizeof(struct VectorPair), cmpSimfunc);
   int n = 0;
   printf("%s %s %s %.6f " ,argv[1],vectorPairs[0].word1 ,vectorPairs[0].word2,vectorPairs[0].similarity); 
   printf("%s %s %.6f " ,vectorPairs[1].word1 ,vectorPairs[1].word2,vectorPairs[1].similarity); 
   printf("%s %s %.6f\n" ,vectorPairs[2].word1 ,vectorPairs[2].word2,vectorPairs[2].similarity); 
}                     
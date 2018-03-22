#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int comparisons = 0;

//Algoritmo do maternal
int linearSearch(int x, int * vet, int n){
  if(x<0) return -1;
  if(!vet || n<=0) return -1;
  for(int i = 0;i<n;i++){
    comparisons++;
    if(vet[i]==x)return i;
  }
  return -1;
}

//Algoritmo do wikipedia
int binarySearch(int x, int * vet, int l, int h){
  if (x<0) return -1;
  if(h>=l){
    comparisons++;
    int pivot = (h + l)/2;
    if(vet[pivot]==x){
      return pivot;
    }
    else{
      if(vet[pivot]>x) return binarySearch(x,vet,l,pivot-1);
      else if(vet[pivot]<x) return binarySearch(x,vet,pivot+1,h);
    }
  }
  return -1;
}


//Nao era nem pra isso existir mas ok
int bogoSearch(int x, int *vet, int n){
  if(x<0) return -1;
  int pos = rand() % n; //posicao aleatoria no vetor
  int aux[n]; //vetor auxiliar para verificar se a comparacao ja foi feita anteriormente
  int count = 0; //numero de comparacoes
  while(count<n){
    if(aux[pos] != 1){ //se eu ainda nao comparei com esse numero
      comparisons++;
      if(vet[pos] == x){
        return pos;
      }
      else{
        aux[pos]= 1; //marca que já passou
      }
    }
    count++;
    pos = rand() % n; //escolhe uma nova posicao
  }
  return -1;
}

//FUNÇÕES AUXILIARES PQ NINGUEM EH DE FERRO
int * buildVector(char * fileName){
  FILE * fp;
  fp = fopen(fileName, "rt");
  if(!fp) exit(1);

  int amount, number, *vector, reader;

  reader = fscanf(fp,"%d",&amount);
  reader = fscanf(fp,"%d",&amount);
  vector = malloc(sizeof(int)*amount);

  int i = 0;
  while(reader != EOF){
    reader = fscanf(fp,"%d",&number);
    vector[i] = number;
    i++;
  }
  fclose(fp);
  return vector;
}

void printVector(int * vector, int size){
  int i = 0;
  while(i<size){
    printf("%d\n",vector[i]);
    i++;
  }
}

int main(int argc, char*argv[]){
  srand(time(NULL));

  int *vet = buildVector(argv[1]);
  int n, x;
  int linear, binaria, isthisyourcard;
  FILE * fp;
  fp = fopen(argv[1],"rt");
  if(!fp) exit(1);

  fscanf(fp,"%d", &x);
  fscanf(fp,"%d", &n);
  fclose(fp);
  //Uncomment for debugging
  //printVector(vet, n);

  printf("Buscando %d...\n",x);

  linear = linearSearch(x, vet, n);
  if(linear>=0) printf("A busca linear encontrou o elemento na posicao %d!\n", linear);
  else printf("A busca linear nao encontrou o elemento\n");
  printf("A busca linear realizou %d comparacoes\n\n",comparisons);
  comparisons = 0;

  binaria = binarySearch(x, vet, 0, n-1);
  if(binaria>=0) printf("A busca binaria encontrou o elemento na posicao %d!\n", binaria);
  else printf("A busca binaria nao encontrou o elemento\n");
  printf("A busca binaria realizou %d comparacoes\n\n",comparisons);
  comparisons = 0;

  isthisyourcard = bogoSearch(x, vet, n);
  if(isthisyourcard<0) printf("A busca bogo nao encontrou o elemento\n");
  else printf("A busca bogo encontrou o elemento na posicao %d!\n",isthisyourcard);
  printf("A busca bogo realizou %d comparacoes\n",comparisons);

  printf("\nPrograma terminado.Byebye!\n");
  free(vet);
  return 1;

}

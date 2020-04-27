#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>


int numofelements;//noof elements in file
int *numbers; //array read from file
int i,j,k,length1,length2;

//function that reads the elements from input file
void readFile(){
FILE * f;
f=fopen("input.txt","r");
 if (f!=NULL){
  while(!feof(f)){
   fscanf(f,"%d",&numofelements);
   fscanf(f,"\n");
   numbers=(int*)malloc(numofelements*sizeof(int));
   for(i=0;i<numofelements;i++)
      fscanf(f,"%d ",&numbers[i]);  
}
}}

//function that merges 2 sorted arrays
void merge(int first, int mid, int last)
{
length1= mid-first+1;//no of elements
length2= last-mid;//mid not included
int left[length1]; //initializing size of first subarray
int right[length2]; //initializing size of second subarray

 for(i=0;i<length1; i++)
  left[i]=numbers[first+i];

 for(i=0;i<length2;i++)
  right[i]=numbers[mid+i+1];


left[length1]=999999; //last element tends to infinity
right[length2]=999999; //last element tends to infinity
i=0;
j=0;

for(k=first;k<=last;k++){
 if(left[i]<=right[j]){
  numbers[k]=left[i];
  i++;                }

 else {
  numbers[k]=right[j];
  j++;
       }
}}


//function that splits an array into 2 subarrays then calls the merge function to merge the 2 subarrays
void* mergeSort(void* args){
int* index= (int*)args;
int first=index[0]; //takes first index
int last=index[1]; //takes last index

pthread_t thread1,thread2;

if(first<last)
{  int mid=(last+first)/2;
int index1[2]= {first,mid};
int index2[2]= {mid+1,last};
pthread_create(&thread1,NULL,mergeSort,(void*)index1); //array of first and last elements bec it doesnt take 2 parameters
pthread_create(&thread2,NULL,mergeSort,(void*)index2);

pthread_join(thread1, NULL);
pthread_join(thread2, NULL);

merge(first, mid, last);
}}


int main(){
  
readFile();
int size[2]={0,numofelements-1}; //give the size array the start and end
mergeSort((void*)size); //calls the mergeSort fn and then gives it the size array

printf("Array after sorting:\n"); 
for(i=0;i<numofelements;i++)
 printf("%d ",numbers[i]);


return 0;
}



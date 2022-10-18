#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>
#include<omp.h>
/*
unsigned long read_cycles(){
unsigned long cycles;
asm volatile ("rdcycle %0":"=r"(cycles));
return cycles;
}
*/
           
#define v 1024
#define e 32208
#define m 0
//#define r 93

#define r v/(omp_get_max_threads())

unsigned start,end;
int j,i,iter;

int k;
int p;

int main()
{

int *vec = (int*)malloc( sizeof(int)*v);
//int vec[v];
//int maski[v];//={1,1,1,1}; //mask for 4x4 with 1 initialised indicated none of them are visited
//int disti[v];//={-1,-1,-1,-1}; //-1 is thought of infinity
//int mat_rp[v+1];//={0,0,1,2,4}; //row pointer in CSR of 4x4 adjacency
//int col[e];//={0,0,1,2};//column index in CSR of 4x4
int flag;
int *maski = (int*)malloc( sizeof(int)*v);
int *disti = (int*)malloc( sizeof(int)*v);
int *mat_rp = (int*)malloc( sizeof(int)*(v+1));
int *col = (int*)malloc( sizeof(int)*e);

  FILE *fp;
  
  fp = fopen("1M.index", "r"); // read mode

   if (fp == NULL)
   {
      printf("Error while opening the file.\n");
     }
 
   for(int i = 0; i< e ; i++){
     fscanf(fp,"%d\n",&col[i]);
   }

   fclose(fp);
   fp = fopen("1M.off", "r"); // read mode

   if (fp == NULL)
   {
      printf("Error while opening the file.\n");
     }
 
 for(int i = 0; i< (v+1) ; i++){
  fscanf(fp,"%d\n",&mat_rp[i]);
}
// for(int i = 0; i< 4 ; i++){
//  printf("mat: %d\n",col[i]);
//}

//

for(int i = 0; i< v ; i++){
   disti[i]=-1;
   maski[i]=1;
   vec[i]=0;
   //active[i]=0;
   //countmask[i]=0;
   //count[i]=0;
}
int count_in=0;
int count_mask=0;;


iter=0;

disti[m]=0; //distance of source is made 0
maski[m]=0; //source is already visited hence mask of source is made 0
vec[m]=1; //source node is made 1.
/*
for(i=0;i<93;i++){ // this is for 4 rows of adjacency matrix, change accordingly

rw=mat_rp[i+1]-mat_rp[i]; // calculate row weight
printf("row weight for row %d is %d\n",i,rw);//point=mat_rp[i]; //get the value pointer
}*/

//p=0;
int c;
double s,stop;
int g=0;





#pragma omp parallel  
{
int a,b,id,nthrds;
id=omp_get_thread_num();
//printf("hi i am thread=%d\n",id);

int z,y,ci,point,rw,iter_;
int *active = (int*)malloc( sizeof(int)*(r));

//int *vector = (int*)malloc( sizeof(int)*(v));
int *mask = (int*)malloc( sizeof(int)*(r));
int *dist = (int*)malloc( sizeof(int)*(r));
//int mask[r];
//int dist[r];

int start;
//int mask[r];
//int dist[r];
iter_=0;
a=id*r;
b=(id+1)*r;

//int mat[r+1];
int *mat = (int*)malloc( sizeof(int)*(r+1));
for(z=0;z<(r+1);z++){
mat[z]=mat_rp[z+a];
}

int no_elements=mat[r]-mat[0];
//int col_ind[no_elements];
int *col_ind = (int*)malloc( sizeof(int)*(no_elements));
start=mat[0];

for(z=0;z<no_elements;z++){
col_ind[z]=col[start+z];
}

for(z=a;z<b;z++){
mask[z-a]=maski[z];
dist[z-a]=disti[z];
}

#pragma omp barrier
s=omp_get_wtime();


times:
/*
for (z=0;z<v;z++){ 
vector[z]=vec[z]; 
}
*/
for(z=a;z<b;z++){ 
rw=mat[(z+1)-a]-mat[z-a]; 
point=mat[z-a]; 

for(y=0;y<rw;y++){
ci=col_ind[(point+y)-start]; 
if(mask[z-a]&vec[ci]){
dist[z-a]=iter_+1; 
active[z-a]=1;
}
}

                   if(active[z-a]){ 
                                 mask[z-a]=0;            
                      }

}

//iter_++;

#pragma omp barrier
for (z=a;z<b;z++){ 
vec[z]=active[z-a]; 
active[z-a]=0;
}

#pragma omp barrier

iter_++;
if(iter_<12){
goto times;
}
else
{
stop=omp_get_wtime();
//#pragma omp critical
{
for(z=a;z<b;z++) 
{
disti[z]=dist[z-a];
} 
}
}
//stop=omp_get_wtime();
free(active);
free(mask);
//free(vector);
free(dist);
free(mat);
free(col_ind);
}
//c=r;
//printf("r is %d",c);

//end=read_cycles();

//printf("number of iteration is%d\n",c);
int nc=0;
for(i=0;i<v;i++)
{//i=1000;
if(disti[i]==10)
nc++;
}
printf("num of 7 is:%d\n",nc); //display cost of traversal to each vertex
   for(i=0;i<10;i++)
   { 
    printf("Distance is %d\n",disti[i]);
   }
printf("No of time: %f by %d\n",stop-s,omp_get_max_threads());
//for(i=0;i<iter;i++){
//printf("total count inside of %d:is %d\n",i,c_iter[i]);
//printf("total count inside of %d:is %d\n",i,m_iter[i]);
//}
free(disti);
free(maski);
free(vec);
free(mat_rp);
free(col);

return 0;
}



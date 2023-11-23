#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int n;
long long int initmem;
long long int s;

long long int** matrixcreate()
{
    int i,j;

    long long int** matrix = (long long int**)malloc(n*sizeof(long long int*));

    for(i=0 ; i<n ; i++)
    {
      matrix[i]=(long long int*)malloc(n*sizeof(long long int));
    }

    for(i=0 ; i<n ; i++)
    {
      for (j=0 ; j<n ; j++)
      {
        struct timeval start;
        gettimeofday(&start, NULL);

        srand((unsigned) start.tv_usec);

        long long int num=rand();

        matrix[i][j]=num;
      }
    }

    return matrix;
}

void transpose(long long int** matrix)
{
    int i,j;

    for(i=0 ; i<n ; i++)
    {
      for (j=i+1 ; j<n ; j++) 
      {
        long long int temp=matrix[i][j];

        matrix[i][j]=matrix[j][i];
        matrix[j][i]=temp;
      }
    }
}

void trans1 ()
{
  struct rusage usage;

  long long int** matrix1;
  matrix1=matrixcreate();

  long long int** matrix2;
  matrix2=matrixcreate();

  long long int** matrix3;
  matrix3=matrixcreate();

  long long int** matrix4;
  matrix4=matrixcreate();

  long long int** matrix5;
  matrix5=matrixcreate();

  for(int i=0 ; i<10 ; i++)
  {
    transpose(matrix1);
    transpose(matrix2);
    transpose(matrix3);
    transpose(matrix4);
    transpose(matrix5);

    getrusage(RUSAGE_SELF, &usage);
    long long int mem=usage.ru_maxrss;
    long long int pagefaults=usage.ru_minflt;

    printf("Memory = %lld + %lld , Page faults = %lld\n",initmem,mem-initmem,pagefaults-s);
  }
}

void trans2 ()
{
  for(int i=0 ; i<10 ; i++)
  {
    struct rusage usage;

    long long int** matrix1;
    matrix1=matrixcreate();

    long long int** matrix2;
    matrix2=matrixcreate();

    long long int** matrix3;
    matrix3=matrixcreate();

    long long int** matrix4;
    matrix4=matrixcreate();

    long long int** matrix5;
    matrix5=matrixcreate();

    transpose(matrix1);
    transpose(matrix2);
    transpose(matrix3);
    transpose(matrix4);
    transpose(matrix5);

    getrusage(RUSAGE_SELF, &usage);
    long long int mem=usage.ru_maxrss;
    long long int pagefaults=usage.ru_minflt;

    printf("Memory = %lld + %lld , Page faults = %lld\n",initmem,mem-initmem,pagefaults-s);
  }
}

int main() 
{
  struct rusage usage;
  struct timeval start,end;

  long long int e;
  long long int m2;

  getrusage(RUSAGE_SELF,&usage);

  s= usage.ru_minflt;
  initmem = usage.ru_maxrss;

  printf("Enter n value: ");
  scanf("%d", &n);

  printf("Enter Choice\n");
  printf("Memory Allocated once-1\n");
  printf("Memory Allocated each time-2\n");

  int choice;
  scanf("%d", &choice);

  if(choice==1) trans1();
  else trans2();

  return 0;
}
#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main()

  {

    const int size = 25600;

    double sinTable[size];



    SimRoiStart();

    #pragma omp parallel for

    for(int n=0; n<size; ++n)

      sinTable[n] = n;

    SimRoiEnd();

        return 0;

}

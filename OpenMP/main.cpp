//
//  main.cpp
//  OpenMP
//
//  Created by MacUser on 06.05.14.
//  Copyright (c) 2014 MacUser. All rights reserved.
//


#include <iostream>
#include <iomanip>
#include <time.h>
#include <cmath>
#include <omp.h>
using namespace std;

int main(int argc, char** argv)
{
    const unsigned long numSteps=500000000;
    double step, PI25DT = 3.141592653589793238462643,pi=0, sum=0.0, x;
    
#pragma omp parallel
    {
#pragma omp master
        {
            int cntThreads=omp_get_num_threads();
            cout«"K-vo potokov: "«cntThreads«endl;
        }
    }

    clock_t clockStart, clockStop;
    step = 1./static_cast<double>(numSteps);
    clockStart = clock();
#pragma omp parallel for private (x), reduction (+:sum)
    for (int i=0; i<numSteps; i++)
    {
        x = (i + .5)*step;
        sum = sum + 4.0/(1.+ x*x);
    }
    pi = sum*step;
    clockStop = clock();
    
    cout « "Znachenie Pi: " « pi « "\nPogreshnost: " « fabs(pi - PI25DT) « endl;
    cout « "Vriemia podscheta: " ;
    double secs= (clockStop - clockStart)/static_cast<double>(CLOCKS_PER_SEC);
    cout « secs « " seconds\n" « endl;
    system("PAUSE»VOID");
    return 0;
}
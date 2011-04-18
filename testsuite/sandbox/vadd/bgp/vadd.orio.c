#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

double getClock()
{
    struct timezone tzp;
    struct timeval tp;
    gettimeofday (&tp, &tzp);
    return (tp.tv_sec + tp.tv_usec*1.0e-6);
}

int main(int argc, char *argv[])
{
    double *y;
    double *x1;
    double *x2;
    double *x3;

#pragma disjoint (*x1,*x2,*x3,*y) 

    int n = N;
    {
        int i1;
        y = (double*) malloc((n) * sizeof(double));
        x1 = (double*) malloc((n) * sizeof(double));
        x2 = (double*) malloc((n) * sizeof(double));
        x3 = (double*) malloc((n) * sizeof(double));
        for (i1=0; i1<n; i1++) {
            x1[i1] = (i1+1) % 4 + 1;
            x2[i1] = (i1+5) % 10 + 1;
            x3[i1] = (i1+3) % 6 + 1;
            y[i1] = 0;
        }
    }

    double orio_t_start, orio_t_end, orio_t_total=0;
    int orio_i;
    int reps = REPS;
#ifdef TEST
    reps = 1;
#endif

    orio_t_start = getClock(); 
    for (orio_i=0; orio_i<reps; orio_i++)
    {
	int i;

	if (n <= 65) {
	    // parallelize=False, ufactor=3
	    if ((((int)(x1)|(int)(x2)|(int)(x3)|(int)(y)) & 0xF) == 0) {
		__alignx(16,x1); 
		__alignx(16,x2); 
		__alignx(16,x3); 
		__alignx(16,y); 
		for (i=0; i<=n-3; i=i+3) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		}
		for (; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    } else {
		for (i=0; i<=n-3; i=i+3) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		}
		for (; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    }
#ifdef ORIO_SEQ
	} else if (n <= 810) {
	    // parallelize=False, ufactor=10
	    if ((((int)(x1)|(int)(x2)|(int)(x3)|(int)(y)) & 0xF) == 0) {
		__alignx(16,x1); 
		__alignx(16,x2); 
		__alignx(16,x3); 
		__alignx(16,y); 
		for (i=0; i<=n-10; i=i+10) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		}
		for (; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    } else {
		for (i=0; i<=n-10; i=i+10) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		}
		for (; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    }
	} else if (n <= 131250) {
	    // parallelize=False, ufactor=20
	    if ((((int)(x1)|(int)(x2)|(int)(x3)|(int)(y)) & 0xF) == 0) {
		__alignx(16,x1); 
		__alignx(16,x2); 
		__alignx(16,x3); 
		__alignx(16,y); 
		for (i=0; i<=n-20; i=i+20) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		    y[(i+10)]=x1[(i+10)]+x2[(i+10)]+x3[(i+10)];
		    y[(i+11)]=x1[(i+11)]+x2[(i+11)]+x3[(i+11)];
		    y[(i+12)]=x1[(i+12)]+x2[(i+12)]+x3[(i+12)];
		    y[(i+13)]=x1[(i+13)]+x2[(i+13)]+x3[(i+13)];
		    y[(i+14)]=x1[(i+14)]+x2[(i+14)]+x3[(i+14)];
		    y[(i+15)]=x1[(i+15)]+x2[(i+15)]+x3[(i+15)];
		    y[(i+16)]=x1[(i+16)]+x2[(i+16)]+x3[(i+16)];
		    y[(i+17)]=x1[(i+17)]+x2[(i+17)]+x3[(i+17)];
		    y[(i+18)]=x1[(i+18)]+x2[(i+18)]+x3[(i+18)];
		    y[(i+19)]=x1[(i+19)]+x2[(i+19)]+x3[(i+19)];
		}
		for (; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    } else {
		for (i=0; i<=n-20; i=i+20) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		    y[(i+10)]=x1[(i+10)]+x2[(i+10)]+x3[(i+10)];
		    y[(i+11)]=x1[(i+11)]+x2[(i+11)]+x3[(i+11)];
		    y[(i+12)]=x1[(i+12)]+x2[(i+12)]+x3[(i+12)];
		    y[(i+13)]=x1[(i+13)]+x2[(i+13)]+x3[(i+13)];
		    y[(i+14)]=x1[(i+14)]+x2[(i+14)]+x3[(i+14)];
		    y[(i+15)]=x1[(i+15)]+x2[(i+15)]+x3[(i+15)];
		    y[(i+16)]=x1[(i+16)]+x2[(i+16)]+x3[(i+16)];
		    y[(i+17)]=x1[(i+17)]+x2[(i+17)]+x3[(i+17)];
		    y[(i+18)]=x1[(i+18)]+x2[(i+18)]+x3[(i+18)];
		    y[(i+19)]=x1[(i+19)]+x2[(i+19)]+x3[(i+19)];
		}
		for (; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    }
	} else {
	    // parallelize=False, ufactor=16
	    if ((((int)(x1)|(int)(x2)|(int)(x3)|(int)(y)) & 0xF) == 0) {
		__alignx(16,x1); 
		__alignx(16,x2); 
		__alignx(16,x3); 
		__alignx(16,y); 
		for (i=0; i<=n-16; i=i+16) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		    y[(i+10)]=x1[(i+10)]+x2[(i+10)]+x3[(i+10)];
		    y[(i+11)]=x1[(i+11)]+x2[(i+11)]+x3[(i+11)];
		    y[(i+12)]=x1[(i+12)]+x2[(i+12)]+x3[(i+12)];
		    y[(i+13)]=x1[(i+13)]+x2[(i+13)]+x3[(i+13)];
		    y[(i+14)]=x1[(i+14)]+x2[(i+14)]+x3[(i+14)];
		    y[(i+15)]=x1[(i+15)]+x2[(i+15)]+x3[(i+15)];
		}
		for (; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    } else {
		for (i=0; i<=n-16; i=i+16) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		    y[(i+10)]=x1[(i+10)]+x2[(i+10)]+x3[(i+10)];
		    y[(i+11)]=x1[(i+11)]+x2[(i+11)]+x3[(i+11)];
		    y[(i+12)]=x1[(i+12)]+x2[(i+12)]+x3[(i+12)];
		    y[(i+13)]=x1[(i+13)]+x2[(i+13)]+x3[(i+13)];
		    y[(i+14)]=x1[(i+14)]+x2[(i+14)]+x3[(i+14)];
		    y[(i+15)]=x1[(i+15)]+x2[(i+15)]+x3[(i+15)];
		}
		for (; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    } 
	}
#elif ORIO_PAR
	} else if (n <= 835) {
	    // parallelize=False, ufactor=10
	    if ((((int)(x1)|(int)(x2)|(int)(x3)|(int)(y)) & 0xF) == 0) {
		__alignx(16,x1); 
		__alignx(16,x2); 
		__alignx(16,x3); 
		__alignx(16,y); 
		for (i=0; i<=n-10; i=i+10) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		}
		for (; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    } else {
		for (i=0; i<=n-10; i=i+10) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		}
		for (; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    }
        } else if (n <= 132500) {
	    // parallelize=True, ufactor=20
	    if ((((int)(x1)|(int)(x2)|(int)(x3)|(int)(y)) & 0xF) == 0) {
		__alignx(16,x1); 
		__alignx(16,x2); 
		__alignx(16,x3); 
		__alignx(16,y); 
#pragma omp parallel for
		for (i=0; i<=n-20; i=i+20) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		    y[(i+10)]=x1[(i+10)]+x2[(i+10)]+x3[(i+10)];
		    y[(i+11)]=x1[(i+11)]+x2[(i+11)]+x3[(i+11)];
		    y[(i+12)]=x1[(i+12)]+x2[(i+12)]+x3[(i+12)];
		    y[(i+13)]=x1[(i+13)]+x2[(i+13)]+x3[(i+13)];
		    y[(i+14)]=x1[(i+14)]+x2[(i+14)]+x3[(i+14)];
		    y[(i+15)]=x1[(i+15)]+x2[(i+15)]+x3[(i+15)];
		    y[(i+16)]=x1[(i+16)]+x2[(i+16)]+x3[(i+16)];
		    y[(i+17)]=x1[(i+17)]+x2[(i+17)]+x3[(i+17)];
		    y[(i+18)]=x1[(i+18)]+x2[(i+18)]+x3[(i+18)];
		    y[(i+19)]=x1[(i+19)]+x2[(i+19)]+x3[(i+19)];
		}
		for (i=n-((n-1)%20)-1; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    } else {
#pragma omp parallel for
		for (i=0; i<=n-20; i=i+20) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		    y[(i+10)]=x1[(i+10)]+x2[(i+10)]+x3[(i+10)];
		    y[(i+11)]=x1[(i+11)]+x2[(i+11)]+x3[(i+11)];
		    y[(i+12)]=x1[(i+12)]+x2[(i+12)]+x3[(i+12)];
		    y[(i+13)]=x1[(i+13)]+x2[(i+13)]+x3[(i+13)];
		    y[(i+14)]=x1[(i+14)]+x2[(i+14)]+x3[(i+14)];
		    y[(i+15)]=x1[(i+15)]+x2[(i+15)]+x3[(i+15)];
		    y[(i+16)]=x1[(i+16)]+x2[(i+16)]+x3[(i+16)];
		    y[(i+17)]=x1[(i+17)]+x2[(i+17)]+x3[(i+17)];
		    y[(i+18)]=x1[(i+18)]+x2[(i+18)]+x3[(i+18)];
		    y[(i+19)]=x1[(i+19)]+x2[(i+19)]+x3[(i+19)];
		}
		for (i=n-((n-1)%20)-1; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    }
	} else {
	    // parallelize=True, ufactor=12
	    if ((((int)(x1)|(int)(x2)|(int)(x3)|(int)(y)) & 0xF) == 0) {
		__alignx(16,x1); 
		__alignx(16,x2); 
		__alignx(16,x3); 
		__alignx(16,y); 
#pragma omp parallel for
		for (i=0; i<=n-12; i=i+12) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		    y[(i+10)]=x1[(i+10)]+x2[(i+10)]+x3[(i+10)];
		    y[(i+11)]=x1[(i+11)]+x2[(i+11)]+x3[(i+11)];
		}
		for (i=n-((n-1)%12)-1; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    } else {
#pragma omp parallel for
		for (i=0; i<=n-12; i=i+12) {
		    y[i]=x1[i]+x2[i]+x3[i];
		    y[(i+1)]=x1[(i+1)]+x2[(i+1)]+x3[(i+1)];
		    y[(i+2)]=x1[(i+2)]+x2[(i+2)]+x3[(i+2)];
		    y[(i+3)]=x1[(i+3)]+x2[(i+3)]+x3[(i+3)];
		    y[(i+4)]=x1[(i+4)]+x2[(i+4)]+x3[(i+4)];
		    y[(i+5)]=x1[(i+5)]+x2[(i+5)]+x3[(i+5)];
		    y[(i+6)]=x1[(i+6)]+x2[(i+6)]+x3[(i+6)];
		    y[(i+7)]=x1[(i+7)]+x2[(i+7)]+x3[(i+7)];
		    y[(i+8)]=x1[(i+8)]+x2[(i+8)]+x3[(i+8)];
		    y[(i+9)]=x1[(i+9)]+x2[(i+9)]+x3[(i+9)];
		    y[(i+10)]=x1[(i+10)]+x2[(i+10)]+x3[(i+10)];
		    y[(i+11)]=x1[(i+11)]+x2[(i+11)]+x3[(i+11)];
		}
		for (i=n-((n-1)%12)-1; i<=n-1; i=i+1) 
		    y[i]=x1[i]+x2[i]+x3[i];
	    } 
	}
#else
	printf("error\n");
	exit(1);
#endif

    }
    orio_t_end = getClock();
    orio_t_total = orio_t_end - orio_t_start;

    orio_t_total = orio_t_total / REPS; 
    double mflops = (8.0*N)/(orio_t_total*1000000);

#ifdef TEST
    {
	int i;
	for (i=0; i<=n-1; i++) {
	    if (i%10 == 0)
		printf("\n");
	    printf("%f ",y[i]);
	}
    }
#else
    printf("%f\t%f\n", orio_t_total, mflops);
#endif

    return y[0];
}


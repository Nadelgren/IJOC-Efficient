#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include<time.h>

/* File created by Nathan Adelgren, Graduate Assisistant at Clemson University on 6/22/2014 as part of doctoral research
under the advisement of Drs. Pietro Belotti and Akshay Gupte. The goal of this program is to generate data that approximates
the integer feasible solutions that might be discovered during a BB solution of a BOMILP.*/

static FILE *seeds;
static FILE *data;

double a = 0;
double b = 0;
double c = 0;
double d = 0;
int n = 0;
int m = 0;
int p = 0;
int q = 0;

void main(int argc, char *argv[])
{
/*	seeds = fopen("seeds.txt", "a+");*/
	seeds = fopen( argv[1], "r" );
	data = fopen("input_data.txt", "w");
	
	int intvar = 0, cntr = 1;
	if (sscanf (argv[2], "%i", &intvar)!=1) { printf ("error - not an integer"); exit(0); }
	
	char line[1000000];
	char *ptr;
	
	fgets(line,1000000,seeds);
/*	printf("%s\n",line);*/
	
    	int seed = strtol(line, &ptr, 10);
/*    	printf("the seed is %d\n",seed);*/
    	
    	while(intvar > cntr)
    	{
    		fgets(line,1000000,seeds);
    		seed = strtol(line, &ptr, 10);
/*    		printf("the seed is %d\n",seed);*/
    		cntr++;
    	}
/*    	exit(0);*/
	
/*	int seed = intvar;//time(NULL);*/
	srand48(seed);
  	srand(seed);
  	
/*  	fprintf(seeds,"%d\n",seed);*/
  	
	//srand(72); //started w 65 and 6 then 71 and 12
	//srand48(13);

	double k = 1.;//MAX_ITER;
	int i = 0;
	int counter = 0;
	int max_counter = strtol(argv[4], &ptr, 10);
	double mu = atof(argv[3]);

	while (counter < max_counter)
    	{
		n = round(1+(rand() % 100)/20.);
		//printf("n: %d\n",n);
		m = n;
		double points[2*n];
		a =(floor (drand48() * 1.0e9)) / 1.0e8;
		b = (10.5-a)*(10.5-a)/5.;
		points[0] = a;
		points[1] = b;
		//printf("first point is: (%lf,%lf)\n",points[0],points[1]);
		int j = 2*n;
		int xyz;
		//printf("a: %lf\n",a);
		if(n > 1)
		{
			for(xyz = 2; xyz < 2*n; xyz += 2)
			{	//printf("xyz: %d\n",xyz);
				if(xyz == 2) points[2] = a + .15*drand48();
				else points[xyz] = points[xyz-2]+.15*drand48();
			}
			points[2*n-1] = (10.5-points[2*n-2])*(10.5-points[2*n-2])/5.;
			for(xyz = 2; xyz < 2*n-2; xyz += 2)
			{
				points[xyz+1] = (10.5-points[xyz])*(10.5-points[xyz])/5.;
/*				double prev_slope = -15;*/
/*				double slope_to_end = (points[2*n-1]-points[xyz-1])/(points[2*n-2]-points[xyz-2]);*/
/*				if(xyz > 2) prev_slope = (points[xyz-1]-points[xyz-3])/(points[xyz-2]-points[xyz-4]);*/
/*				//printf("prev slope: %lf\n",prev_slope);*/
/*				points[xyz+1] = fmax(prev_slope*(points[xyz]-points[xyz-2])+points[xyz-1],points[2*n-1])+(fmin(points[xyz-1],slope_to_end*(points[xyz]-points[2*n-2])+points[2*n-1])-fmax(prev_slope*(points[xyz]-points[xyz-2])+points[xyz-1],points[2*n-1]))*drand48()/2.; */
			}
			for(xyz = 0; xyz < 2*n; xyz += 2)
			{
				points[xyz] = points[xyz] + (5 - k);
				points[xyz+1] = points[xyz+1]  - k;
			}
		}
		else
		{
			points[0] = points[0] + (5 - k);
			points[1] = points[1]  - k;
		}
		if (m == 1)
		{
			//insert(1,points[0],points[1],0,0,0.,&tree);
			counter++;
			//printf("The generated point is: %lf,%lf \n",points[0],points[1]);
			//fprintf(fp,"plot(%lf,%lf,'o');\n",points[0],points[1]);
			fprintf(data,"1 %lf %lf 0 0 0.0\n",points[0],points[1]);
		}
		else
		{
			int r;
			for (r = 0; r < 2*m-2; r = r+2)
			{
				//insert(2,points[r],points[r+1],points[r+2],points[r+3],(points[r+3]-points[r+1])/(points[r+2]-points[r]),&tree);
				counter++;
				//printf("The %d generated segment is: %lf,%lf to %lf,%lf \n",r/2+1,points[r],points[r+1],points[r+2],points[r+3]);
				//fprintf(fp,"plot([%lf,%lf],[%lf,%lf],'-o');\n",points[r],points[r+2],points[r+1],points[r+3]);
				fprintf(data,"2 %lf %lf %lf %lf %lf\n",points[r],points[r+1],points[r+2],points[r+3],(points[r+3]-points[r+1])/(points[r+2]-points[r]));
				if (m == 2) break;
			}
		}
		k = k + 10./(max_counter);
		//printf("k: %.16lf\n",k);
		i++;
    	}
    	fclose(seeds);
	fclose(data);
}

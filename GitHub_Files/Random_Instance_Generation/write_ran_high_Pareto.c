#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

FILE *testp1;
FILE *testp2;

/*******************************************************************/
/*		VARIABLES								               */
/*******************************************************************/

int nd, nf, i, j;
double cur;

/******************************************************************/

int min(int x, int y)
{
  return ((x < y) ? x : y);
}

int max(int x, int y)
{
  return ((x > y) ? x : y);
}

int main(int argc, char **argv)
{

	char line[10000];
	int iter_cnt = 0, num_nodes = 0, num_edges = 0;
	
	int N = atoi(argv[1]);
	
	//printf("starting main\n");
	//printf("file to be read is %s\n",argv[1]);
  	
    	if (( testp1 = fopen("testp1.lp","w"))==NULL)
    	{
    		printf("error, exitting\n");
      		exit(1);
    	}
    	if (( testp2 = fopen("testp2.lp","w"))==NULL)
    	{
    		printf("error, exitting\n");
      		exit(1);
    	}
    	
    	fprintf(testp1,"Maximize\n  obj: ");
    	fprintf(testp2,"Maximize\n  obj: ");
    	
	fprintf(testp1,"y1 + 0y2 + 0y3");
	fprintf(testp2,"0y1 + y2 + 0y3");
	
	fprintf(testp1,"\nSubject To\n");
	fprintf(testp2,"\nSubject To\n");

	int constr_counter = 0;
	double x_val1 = 0., x_val2 = 0., y_val1 = 0., y_val2 = 0., slope = 0.;
	
	y_val1 = sqrt(N*N - x_val1*x_val1);
	
	x_val2 =  ((double) N)/(atoi(argv[2]));
	
	y_val2 = sqrt(N*N - x_val2*x_val2);
	
	slope = (y_val2-y_val1)/(x_val2-x_val1);
	
	fprintf(testp1," C%d: y2 + %lfy1 <= %lf\n",constr_counter,-slope,y_val1-x_val1*slope);
	fprintf(testp2," C%d: y2 + %lfy1 <= %lf\n",constr_counter,-slope,y_val1-x_val1*slope);
	constr_counter++;

	for(i=1;i<atoi(argv[2]);i++)
	{
		x_val1 = x_val2;
		y_val1 = y_val2;
		
		x_val2 += ((double) N)/(atoi(argv[2]));
		y_val2 = sqrt(N*N - x_val2*x_val2);
		
		slope = (y_val2-y_val1)/(x_val2-x_val1);
		
		if(slope == slope)
		{
			fprintf(testp1," C%d: y2 + %lfy1 <= %lf\n",constr_counter,-slope,y_val1-x_val1*slope);
			fprintf(testp2," C%d: y2 + %lfy1 <= %lf\n",constr_counter,-slope,y_val1-x_val1*slope);
		}
		constr_counter++;
	}
	
	fprintf(testp1," C%d: y1 - .1y3 <= .025\n",constr_counter);
	fprintf(testp2," C%d: y1 - .1y3 <= .025\n",constr_counter);
	constr_counter++;
	
	fprintf(testp1," C%d: -y1 + .1y3 <= .025\n",constr_counter);
	fprintf(testp2," C%d: -y1 + .1y3 <= .025\n",constr_counter);
	constr_counter++;
	
	fprintf(testp1," C%d: -y1 <= 0\n",constr_counter);
	fprintf(testp2," C%d: -y1 <= 0\n",constr_counter);
	fprintf(testp1," C%d: -y2 <= 0\n",constr_counter+1);
	fprintf(testp2," C%d: -y2 <= 0\n",constr_counter+1);
	
	fprintf(testp1,"General\n");
	fprintf(testp2,"General\n");
	
	fprintf(testp1," y3\n");
	fprintf(testp2," y3\n");
	
	fprintf(testp1,"End\n");
	fprintf(testp2,"End\n");
	
	fclose(testp1);
	fclose(testp2);

}






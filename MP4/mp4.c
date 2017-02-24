/*
 *  A program that prints out the roots of a polynomial using Halley's method
 *  takes a polynomial input from a file, and print out the roots found on console
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double abs_double(double y)
{
    return y >= 0 ? y : -y;      // the abs value of y
}

double fx_val(double a, double b, double c, double d, double e, double x)
{
    return (a*x*x*x*x + b*x*x*x + c*x*x + d*x + e);     // return f(x)
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{
    return (a*4*x*x*x + b*3*x*x + c*2*x + d);       // return f'(x)
}

double fx_ddval(double a, double b, double c, double d, double e, double x)
{
    return (a*12*x*x + b*6*x + c*2);        // return f''(x)
}


double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    double fx, dfx, ddfx, ret;          // find  the Halley's Xn+1
    fx = fx_val(a,b,c,d,e,x);
    dfx = fx_dval(a,b,c,d,e,x);
    ddfx = fx_dval(a,b,c,d,e,x);
    ret = x - ((2* fx * dfx) / (2* dfx * dfx - fx * ddfx));
    return ret;
}

int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
    int isPosNow, isPosLast;
    int countl, countr;
    double temp;
    countl = 0;
    countr = 0;
                                    // count the # of sign changes p(x + l)
    isPosLast = a > 0 ? 1 : 0;      // 0 if negative, 1 if positive
    temp = 4*a*l + b;
    isPosNow = temp > 0 ? 1 : 0;
    if (isPosNow != isPosLast) countl++;
    isPosLast = isPosNow;

    temp = 6*a*l*l + 3*b*l + c;
    isPosNow = temp > 0 ? 1 : 0;
    if (isPosNow != isPosLast) countl++;
    isPosLast = isPosNow;

    temp = fx_dval(a,b,c,d,e,l);
    isPosNow = temp > 0 ? 1 : 0;
    if (isPosNow != isPosLast) countl++;
    isPosLast = isPosNow;

    temp = fx_val(a,b,c,d,e,l);
    isPosNow = temp > 0 ? 1 : 0;
    if (isPosNow != isPosLast) countl++;
    isPosLast = isPosNow;
                                    // count the # of sign changes p(x + r)
    isPosLast = a > 0 ? 1 : 0;
    temp = 4*a*r + b;
    isPosNow = temp > 0 ? 1 : 0;
    if (isPosNow != isPosLast) countl++;
    isPosLast = isPosNow;

    temp = 6*a*r*r + 3*b*r + c;
    isPosNow = temp > 0 ? 1 : 0;
    if (isPosNow != isPosLast) countl++;
    isPosLast = isPosNow;

    temp = fx_dval(a,b,c,d,e,r);
    isPosNow = temp > 0 ? 1 : 0;
    if (isPosNow != isPosLast) countl++;
    isPosLast = isPosNow;

    temp = fx_val(a,b,c,d,e,r);
    isPosNow = temp > 0 ? 1 : 0;
    if (isPosNow != isPosLast) countl++;

    return abs(countl - countr);
}

int main(int argc, char **argv)
{
	double a, b, c, d, e, l, r;
	FILE *in;

	if (argv[1] == NULL) {
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &a);
	fscanf(in, "%lf", &b);
	fscanf(in, "%lf", &c);
	fscanf(in, "%lf", &d);
	fscanf(in, "%lf", &e);
	fscanf(in, "%lf", &l);
	fscanf(in, "%lf", &r);
    
    double x, root, temp;
    int i;
    x = l;
    if (rootbound(a,b,c,d,e,r,l) == 0)          // step 1
    {
        printf("The polynomial has no roots in the given interval.\n");
        return 0;
    }
    while (x <= r)                              // step 2
    {
        root = newrfind_halley(a,b,c,d,e,x);
       for (i = 0; i < 10000; i++)
       {
           temp = newrfind_halley(a,b,c,d,e,root);
           if (abs_double(temp - root) <= 0.000001)
           {
               printf("Root found: %lf\n", temp);
               root = temp;
               break;
           }
           root = temp;
           if (i == 9999) printf("No roots found.\n");
       }
        x += 0.5;
    }
    
    
    fclose(in);
    
    return 0;
}

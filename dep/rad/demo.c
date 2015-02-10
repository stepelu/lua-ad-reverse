/* Simple test program for the RAD package. */

/* Compute f(n,x) = the product of x[0], x[1], ..., x[n-1] */
/* and the gradient of f for two x values, and print the result. */

#include "rad.h"
#include <stdio.h>

static const int Nmax = 40;	/* for simplicity */

 double
f(int n, double *x, double *g)
{
	ADvar rv, v[Nmax];
	int i;

	if (n > Nmax) {
		fprintf(stderr, "Botch: n = %d > Nmax = %d\n", n, Nmax);
		return 0;
		}

	/* Initialize independent active variables, v */

	for(i = 0; i < n; i++)
		v[i] = x[i];

	/* Compute the function (in rv = return value). */

	rv = v[0];
	for(i = 1; i < n; i++)
		rv *= v[i];

	/* Compute the gradient and return the results. */

	ADcontext::Gradcomp();

	for(i = 0; i < n; i++)
		g[i] = v[i].adj();

	return rv.val();
	}

 static double
rel_error(double a, double b) /* Relative error, for comparing results */
{
	double e, t;

	if ((e = a - b) < 0)
		e = -e;
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;
	if (a < b)
		a = b;
	if (a <= 0)
		a = 1;
	return e / a;
	}

 static double
maxrel_error(int n, double *a, double *b)
{
	double e, t;
	int i;

	e = 0;
	for(i = 0; i < n; i++)
		if (e < (t = rel_error(a[i], b[i])))
			e = t;
	return e;
	}

 static void
test(int n, double *x)
{
	double f1, fe, g[Nmax], ge[Nmax];
	int i;
	static int ntest;

	/* First compute in fe and ge the function and gradient */
	/* values we expect from f()... */

	fe = 1;
	for(i = 0; i < n; i++)
		fe *= x[i];
	for(i = 0; i < n; i++)
		ge[i] = fe/x[i];

	/* Now see how well f() works. */

	f1 = f(n, x, g);
	printf("\nTest %d (n = %d): f = %g with rel. error = %.2g\n",
		++ntest, n, f1, rel_error(f1,fe));

	printf("max. rel. error in gradient (g) = %.2g\n", maxrel_error(n,g,ge));
	}

 int
main(void)
{
	double x[Nmax];
	int i, n;

	for(i = 0; i < Nmax; i++)
		x[i] = i + 1;

	for(n = 10; n <= Nmax; n += 10) {

		x[0] = 1;
		test(n,x);

		x[0] = 2;
		test(n,x);
		}

	return 0;
	}

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#ifdef bi
int method = 2;
#else
int method = 1;
#endif

int key_help = 0;
int key_test_root = 0;
int key_test_int = 0;
int key_iter = 0;
int key_points = 0;
int key_int = 0;

double point12, point13, point23;
double eps1 = 0.000001, eps2 = 0.000001;

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double df1(double x);
extern double df2(double x);
extern double df3(double x);
extern double ddf1(double x);
extern double ddf2(double x);
extern double ddf3(double x);

double f4(double x) {
	return 3 * x * x * x;
}

double df4(double x) {
	return 9 * x * x;
}

double ddf4(double x) {
	return 18 * x;
}

double f5(double x) {
	return x * x;
}

double df5(double x) {
	return 2 * x;
}

double ddf5(double x) {
	return 2;
}

double f6(double x) {
	return x;
}

double df6(double x) {
	return 1;
}

double ddf6(double x) {
	return 0; 
}

double root_newton(double (*f)(double x), double (*df)(double x), double (*ddf)(double x), double (*g)(double x), double (*dg)(double x), double (*ddg)(double x), double a, double b, double eps1) {
	double d;
	double x = (a + b) / 2;
	if ((df(x) - dg(x)) * (ddf(x) - ddg(x)) > 0)
		d = b;
	else
		d = a;

	double h = (f(d) - g(d)) / (df(d) - dg(d));
	int iter = 0;
	while (fabs(h) >= eps1 / 2.0) {
		++iter;
		h = (f(d) - g(d)) / (df(d) - dg(d));
		d -= h;
	}

	if (key_iter)
		printf("amount of iterations: %d\n", iter);
	if (key_points)
		printf("abscissa is %lf\n", d);
	return d;
}

double root_bisection(double (*f)(double x), double (*g)(double x), double a, double b, double eps1) {
	double c;
	int iter = 0;
	while (fabs(b - a) >= eps1 / 2.0) {
		++iter;
		c = (a + b) / 2;
		double res = f(c) - g(c);
		if (fabs(res) < eps1 / 2.0)
			break;
		else if (res * (f(a) - g(a)) < 0)
			b = c;
		else
			a = c;
	}

	if (key_iter)
		printf("amount of iterations: %d\n", iter);
	if (key_points)
		printf("abscissa is %lf\n", c);

	return c;
}

double root(double (*f)(double x), double (*df)(double x), double (*ddf)(double x), double (*g)(double x), double (*dg)(double x), double (*ddg)(double x), double a, double b, double eps1) {
	if (method == 1)
		return root_newton(f, df, ddf, g, dg, ddg, a, b, eps1);
	if (method == 2) 
		return root_bisection(f, g, a, b, eps1);
	return 0.0;
}

double calc(double (*f)(double x), double a, double b) {
	return (b - a) / 6.0 * (f(a) + f(b) + 4.0 * f((a + b) / 2.0));
}

double integral(double (*f)(double x), double a, double b, double eps2) {
	if (a > b) {
		double t = b;
		b = a;
		a = t;
	}
	int iter = 4;

	double ans_prev = DBL_MAX;
	double ans = 0.0;
	while (fabs(ans - ans_prev) / 15.0 >= eps2) {
		ans_prev = ans;
		ans = 0.0;
		double step = (b - a) / iter;
		for (int i = 0; i < iter; ++i) {
			ans += calc(f, a + i * step, a + (i + 1) * step);
		}
		iter *= 2;
	}

	if (key_iter)
		printf("iterations for integral: %d\n", iter);
	if (key_int)
		printf("integral is: %lf\n", ans);
	return ans;
}

void print_help(void) {
	printf("\t-help\t\tshows all valid keys\n");
    printf("\t-test_root\ttest root function\n");
    printf("\t-test_int\ttest integral function\n");
    printf("\t-iterations\tprint the amount of iterations\n");
    printf("\t-points\t\tprint abscissa\n");
    printf("\t-int\t\tprint integrals\n");
}

int main(int argc, char* argv[]) {
	for (int i = 0; i < argc; ++i) {
		if (!strcmp(argv[i], "-help"))
			key_help = 1;
		else if (!strcmp(argv[i], "-test_root"))
			key_test_root = 1;
		else if (!strcmp(argv[i], "-test_int"))
			key_test_int = 1;
		else if (!strcmp(argv[i], "-iterations"))
			key_iter = 1;
		else if (!strcmp(argv[i], "-points"))
			key_points = 1;
		else if (!strcmp(argv[i], "-int"))
			key_int = 1;
	}

	if (key_help) {
		print_help();
		return 0;
	}

	if (key_test_int || key_test_root) {
		key_iter = key_points = key_int = 1;
		double (*f[]) (double) = {f1, f2, f3, f4, f5, f6};
        double (*df[]) (double) = {df1, df2, df3, df4, df5, df6};
        double (*ddf[]) (double) = {ddf1, ddf2, ddf3, ddf4, ddf5, ddf6};
		if (key_test_root) {
			double at, bt, epst;
			int n, m;
			printf("root of f_n = f_m on [a; b] with eps precision\ninput a b eps n (from 1 to 6) m (from 1 to 6):\n");
            scanf("%lf %lf %lf %d %d", &at, &bt, &epst, &n, &m);
            root(f[n - 1], df[n - 1], ddf[n - 1], f[m - 1], df[m - 1], ddf[m - 1], at, bt, epst);
		}

		if (key_test_int) {
			printf("integral of f_n on [a; b] with eps precision\ninput a b eps n (from 1 to 6):\n");
			double at, bt, epst;
			int n;
            scanf("%lf %lf %lf %d", &at, &bt, &epst, &n);
            integral(f[n - 1], at, bt, epst);
		}

		return 0;
	}

	printf("root for f1 = f2\n");
	point12 = root(f1, df1, ddf1, f2, df2, ddf2, 4.0, 6.0, eps1);
	printf("%lf %lf", point12, f1(point12));
	printf("\n");
	printf("root for f1 = f3\n");
	point13 = root(f1, df1, ddf1, f3, df3, ddf3, 1.0, 2.0, eps1);
	printf("%lf %lf", point13, f1(point13));
	printf("\n");
	printf("root for f2 = f3\n");
	point23 = root(f2, df2, ddf2, f3, df3, ddf3, 4.0, 5.0, eps1);
	printf("%lf %lf", point23, f2(point23));
	printf("\n");

	double int1, int2, int3;
	int1 = integral(f1, point12, point13, eps2);
	int2 = integral(f2, point12, point23, eps2);
	int3 = integral(f3, point13, point23, eps2);
	//printf("%lf\n%lf\n%lf\n", int1, int2, int3);
	printf("S = %lf\n", int1 - int2 - int3);
	return 0;
}
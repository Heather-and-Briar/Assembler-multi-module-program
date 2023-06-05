#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

double f1(double x);
double f2(double x);
double f3(double x);

double f1test(double x);
double f2test(double x);
double f3test(double x);

double f1p(double x);
double f2p(double x);
double f3p(double x);

double f1testp(double x);
double f2testp(double x);
double f3testp(double x);

extern int iter;

double integral(double (*f)(double x), double a, double b, double eps);

#endif // FUNCTIONS_H_INCLUDED

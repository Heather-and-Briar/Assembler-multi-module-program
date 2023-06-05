#include "functions.h"

int iter = 0;

#ifndef CHORDS      /* BISECTION method */
double root(double (*f)(double x), double (*g)(double x), double a, double b, double eps);

double root(double (*f)(double x), double (*g)(double x), double a, double b, double eps) {
    if ((f(a) - g(a)) >= 0 && (f(a) - g(a)) <= 0)                             //  F(a) == 0
        return a;
    if ((f(b) - g(b)) >= 0 && (f(b) - g(b)) <= 0)                             //  F(b) == 0
        return b;
    double l = b - a;
    double c = a;
    while (l > eps) {
        iter++;
        l /= 2;
        c = a + l;                                      //  c = (a+b) / 2
        if ((f(a) - g(a))*(f(c) - g(c)) < 0) {          //  F(a)*F(c) < 0
            b = c;
        } else if ((f(b) - g(b))*(f(c) - g(c)) < 0){    //  F(b)*F(c) < 0
            a = c;
        } else {                                        //  F(c) == 0
            return c;
        }

    }
    return c;
}

#else               /* method of CHORDS */
double root(double (*f)(double x), double (*g)(double x), double (*fp)(double x), double (*gp)(double x), double a, double b, double eps);

double root(double (*f)(double x), double (*g)(double x), double (*fp)(double x), double (*gp)(double x), double a, double b, double eps) {
    if ((f(a) - g(a)) >= 0 && (f(a) - g(a)) <= 0)                               //  F(a) == 0
        return a;
    if ((f(b) - g(b)) >= 0 && (f(b) - g(b)) <= 0)                               //  F(b) == 0
        return b;

    int flag = 0;

    //  F'(x)<0 => F(x) is decresing => F(a) > F(b)
    //  F'(x)>0 => F(x) is incresing => F(a) < F(b)
    if ((f(a) - g(a)) > (f(b) - g(b)))  //  F(a) > F(b)
        flag++;

    //  F''(x)<0 => F'(x) is decresing => F'(a) > F'(b)
    //  F''(x)>0 => F'(x) is incresing => F'(a) < F'(b)
    if ((fp(a) - gp(a)) > (fp(b) - gp(b)))       //  F'(a) > F'(b)
        flag++;

    if (flag == 1) {                        // F'(x)*F''(x) < 0 => approach from right
        double c = a;
        while (1) {
            iter++;
            c = (a*(f(b) - g(b)) - b*(f(a) - g(a))) / (f(b) - g(b) - f(a) + g(a));  //  c = (a*F(b) - b*F(a)) / (F(b) - F(a));
            if ((f(c-eps) - g(c-eps)) * (f(c) - g(c)) <= 0)
                return c;
            b = c;
        }
    } else {    // if ((flag == 0) || (flag == 2)) F'(x)*F''(x) > 0 => approach from left
        double c = a;
        while (1) {
            iter++;
            c = (a*(f(b) - g(b)) - b*(f(a) - g(a))) / (f(b) - g(b) - f(a) + g(a));  //  c = (a*F(b) - b*F(a)) / (F(b) - F(a));
            if ((f(c) - g(c)) * (f(c+eps) - g(c+eps)) <= 0)
                return c;
            a = c;
        }
    }
}

#endif

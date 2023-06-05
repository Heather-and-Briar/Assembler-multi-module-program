#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

static void wrong_num(int exp) {
  printf("Wrong number of arguments: %d arguments expected\n", exp);
  exit(-1);
}

#ifndef CHORDS      /* BISECTION method */
double root(double (*f)(double x), double (*g)(double x), double a, double b, double eps);

int main(int argc, char **argv) {
    double eps1 = 0.00001;
    double eps2 = 0.00001;
  
    if(argc == 1) {

        double x1 = root(f1, f3, -1.9, -1.7, eps1);
        double x2 = root(f2, f3, -1, 1, eps1);
        double x3 = root(f1, f2, -0.5, 1.5, eps1);

        double J1 = integral(f1, x1, x3, eps2);
        double J2 = integral(f2, x2, x3, eps2);
        double J3 = integral(f3, x1, x2, eps2);
        printf("%f\n", J1 - J2 - J3);
        return 0;
    }

    if (!strncmp(argv[1], "--help", sizeof("--help")) || !strncmp(argv[1], "-h", sizeof("-h"))) {
        if (argc != 2)
            wrong_num(0);
        printf( "COMMANDS:\n"
                "   'without input'                        calculate integral of functions f1, f2, f3\n"
                "   --root (-r)                            intersection points of functions f1, f2, f3\n"
                "       default: bisection method; key -DCHORDS: method of chords\n"
                "   --iterations (-i)                      number of iterations to calculate intersection points\n"
                "   --test-root (-R) F1:F2:A:B:E:R         intersection points of functions f1test, f2test, f3test\n"
                "       F1 anf F2 - numbers of functions; A, B, E - parameters for root(); R - correct answer\n"
                "   --test-integral (-I) F:A:B:E:R         calculate integral of functions f1test, f2test, f3test\n"
                "       F1 - number of function; A, B, E - parameters for integral(); R - correct answer\n");
        return 0;
    }

    if (!strncmp(argv[1], "--root", sizeof("--root")) || !strncmp(argv[1], "-r", sizeof("-r"))) {
        if (argc != 2)
            wrong_num(0);
        double x = root(f1, f3, -1.9, -1.7, eps1);
        printf("Intersection point of f1 and f3 is %f\n", x);
        x = root(f2, f3, -1, 1, eps1);
        printf("Intersection point of f2 and f3 is %lf\n", x);
        x = root(f1, f2, -0.5, 1.5, eps1);
        printf("Intersection point of f1 and f2 is %lf\n", x);
        return 0;
    }

    if (!strncmp(argv[1], "--iterations", sizeof("--iterations")) || !strncmp(argv[1], "-i", sizeof("-i"))) {
        if (argc != 2)
            wrong_num(0);
        root(f1, f3, -1.9, -1.7, eps1);
        printf("Number of iterations to find the intersection point of f1 and f3 is %d\n", iter);
        root(f2, f3, -1, 1, eps1);
        printf("Number of iterations to find the intersection point of f2 and f3 is %d\n", iter);
        root(f1, f2, -0.5, 1.5, eps1);
        printf("Number of iterations to find the intersection point of f1 and f2 is %d\n", iter);
        return 0;
    }

    if (!strncmp(argv[1], "--test-root", sizeof("--test-root")) || !strncmp(argv[1], "-R", sizeof("-R"))) {
        if (argc != 3)
            wrong_num(1);
        
        int f_1, f_2;
        double a, b, e, r;
        sscanf(argv[2], "%d:%d:%lf:%lf:%lf:%lf", &f_1, &f_2, &a, &b, &e, &r);
      
        if (f_1 + f_2 == 3) {           //  (f_1 == 1) && (f_2 == 2) || (f_1 == 2) && (f_2 == 1)
            double x = root(f1test, f2test, a, b, e);
            double mistake = fabs(r - x);
            printf("%f %f %f\n", x, mistake, mistake / r);
        } else if (f_1 + f_2 == 4) {    //  (f_1 == 1) && (f_2 == 3) || (f_1 == 3) && (f_2 == 1)
            double x = root(f1test, f3test, a, b, e);
            double mistake = fabs(r - x);
            printf("%f %f %f\n", x, mistake, mistake / r);
        } else {                        //  (f_1 == 2) && (f_2 == 3) || (f_1 == 3) && (f_2 == 2)
            double x = root(f2test, f3test, a, b, e);
            double mistake = fabs(r - x);
            printf("%f %f %f\n", x, mistake, mistake / r);
        }

        return 0;
    }

    if (!strncmp(argv[1], "--test-integral", sizeof("--test-integral")) || !strncmp(argv[1], "-I", sizeof("-I"))) {
        if (argc != 3)
            wrong_num(1);
        
        int func;
        double a, b, e, r;
        sscanf(argv[2], "%d:%lf:%lf:%lf:%lf", &func, &a, &b, &e, &r);

        if (func == 1) {
            double I = integral(f1test, a, b, e);
            double mistake = fabs(r - I);
            printf("%f %f %f\n", I, mistake, mistake / r);
        } else if (func == 2) {
            double I = integral(f2test, a, b, e);
            double mistake = fabs(r - I);
            printf("%f %f %f\n", I, mistake, mistake / r);
        } else {  //  func == 3
            double I = integral(f3test, a, b, e);
            double mistake = fabs(r - I);
            printf("%f %f %f\n", I, mistake, mistake / r);
        }

        return 0;
    }
  
    printf("Unknown command\n");
    return -1;
}

#else               /* method of CHORDS */
double root(double (*f)(double x), double (*g)(double x), double (*fp)(double x), double (*gp)(double x), double a, double b, double eps);

int main(int argc, char **argv) {
    double eps1 = 0.00001;
    double eps2 = 0.00001;
  
    if(argc == 1) {
        double x1 = root(f1, f3, f1p, f3p, -1.9, -1.7, eps1);
        double x2 = root(f2, f3, f2p, f3p, -1, 1, eps1);
        double x3 = root(f1, f2, f1p, f2p, -0.5, 1.5, eps1);

        double J1 = integral(f1, x1, x3, eps2);
        double J2 = integral(f2, x2, x3, eps2);
        double J3 = integral(f3, x1, x2, eps2);
        printf("%f\n", J1 - J2 - J3);
        return 0;
    }

    if (!strncmp(argv[1], "--help", sizeof("--help")) || !strncmp(argv[1], "-h", sizeof("-h"))) {
        if (argc != 2)
            wrong_num(0);
        printf( "COMMANDS:\n"
                "   'without input'                        calculate integral of functions f1, f2, f3\n"
                "   --root (-r)                            intersection points of functions f1, f2, f3\n"
                "       default: bisection method; key -DCHORDS: method of chords\n"
                "   --iterations (-i)                      number of iterations to calculate intersection points\n"
                "   --test-root (-R) F1:F2:A:B:E:R         intersection points of functions f1test, f2test, f3test\n"
                "       F1 anf F2 - numbers of functions; A, B, E - parameters for root(); R - correct answer\n"
                "   --test-integral (-I) F:A:B:E:R         calculate integral of functions f1test, f2test, f3test\n"
                "       F1 - number of function; A, B, E - parameters for integral(); R - correct answer\n");
        return 0;
    }

    if (!strncmp(argv[1], "--root", sizeof("--root")) || !strncmp(argv[1], "-r", sizeof("-r"))) {
        if (argc != 2)
            wrong_num(0);
        double x = root(f1, f3, f1p, f3p, -1.9, -1.7, eps1);
        printf("Intersection point of f1 and f3 is %f\n", x);
        x = root(f2, f3, f2p, f3p, -1, 1, eps1);
        printf("Intersection point of f2 and f3 is %lf\n", x);
        x = root(f1, f2, f1p, f2p, -0.5, 1.5, eps1);
        printf("Intersection point of f1 and f2 is %lf\n", x);
        return 0;
    }

    if (!strncmp(argv[1], "--iterations", sizeof("--iterations")) || !strncmp(argv[1], "-i", sizeof("-i"))) {
        if (argc != 2)
            wrong_num(0);
        root(f1, f3, f1p, f3p, -1.9, -1.7, eps1);
        printf("Number of iterations to find the intersection point of f1 and f3 is %d\n", iter);
        root(f2, f3, f2p, f3p, -1, 1, eps1);
        printf("Number of iterations to find the intersection point of f2 and f3 is %d\n", iter);
        root(f1, f2, f1p, f2p, -0.5, 1.5, eps1);
        printf("Number of iterations to find the intersection point of f1 and f2 is %d\n", iter);
        return 0;
    }

    if (!strncmp(argv[1], "--test-root", sizeof("--test-root")) || !strncmp(argv[1], "-R", sizeof("-R"))) {
        if (argc != 3)
            wrong_num(1);
        
        int f_1, f_2;
        double a, b, e, r;
        sscanf(argv[2], "%d:%d:%lf:%lf:%lf:%lf", &f_1, &f_2, &a, &b, &e, &r);
      
        if (f_1 + f_2 == 3) {           //  (f_1 == 1) && (f_2 == 2) || (f_1 == 2) && (f_2 == 1)
            double x = root(f1test, f2test, f1testp, f2testp, a, b, e);
            double mistake = fabs(r - x);
            printf("%f %f %f\n", x, mistake, mistake / r);
        } else if (f_1 + f_2 == 4) {    //  (f_1 == 1) && (f_2 == 3) || (f_1 == 3) && (f_2 == 1)
            double x = root(f1test, f3test, f1testp, f3testp, a, b, e);
            double mistake = fabs(r - x);
            printf("%f %f %f\n", x, mistake, mistake / r);
        } else {                        //  (f_1 == 2) && (f_2 == 3) || (f_1 == 3) && (f_2 == 2)
            double x = root(f2test, f3test, f2testp, f3testp, a, b, e);
            double mistake = fabs(r - x);
            printf("%f %f %f\n", x, mistake, mistake / r);
        }

        return 0;
    }

    if (!strncmp(argv[1], "--test-integral", sizeof("--test-integral")) || !strncmp(argv[1], "-I", sizeof("-I"))) {
        if (argc != 3)
            wrong_num(1);
        
        int func;
        double a, b, e, r;
        sscanf(argv[2], "%d:%lf:%lf:%lf:%lf", &func, &a, &b, &e, &r);

        if (func == 1) {
            double I = integral(f1test, a, b, e);
            double mistake = fabs(r - I);
            printf("%f %f %f\n", I, mistake, mistake / r);
        } else if (func == 2) {
            double I = integral(f2test, a, b, e);
            double mistake = fabs(r - I);
            printf("%f %f %f\n", I, mistake, mistake / r);
        } else {  //  func == 3
            double I = integral(f3test, a, b, e);
            double mistake = fabs(r - I);
            printf("%f %f %f\n", I, mistake, mistake / r);
        }

        return 0;
    }
  
    printf("Unknown command\n");
    return -1;
}

#endif

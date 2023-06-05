#include "functions.h"

//#ifndef RECTANGLE
double integral(double (*f)(double x), double a, double b, double eps) {   /*  method of THRAPEZOIDS */
    /* I = h * (0.5*f(x0) + f(x1) + f(x2) + ... + f(xn-1) + 0.5*f(xn)), x0 = a, xn = b, xi = a + i*h, h = (b-a)/2
    outer = 0.5(f(x0) + f(xn)), inner = f(x1) + ... + f(xn-1)
    I = h * (outer + inner) */

    double inner, outer, I_n, I_2n;
    int n = 20;
    double h = (b - a)/n;
    double xi = a;

    outer = (f(a) + f(b)) / 2;
    inner = 0;
    for(int i = 1; i <= n - 1; i++) {
        xi += h;
        inner += f(xi);                     //  xi = a + i*h
    }
    I_n = (inner + outer) * h;

    /* we don't need to calculate 0.5(f(x0) + f(xn)) and f(x2) + f(x4) + ... + f(xn-2)
    because this summes are saved in the outer and inner */

    /* in I_n we save I from the previous step
    in I_2n we sum current I */
    while (1) {
        n *= 2;
        h /= 2;
        xi = a + h;

        for(int i = 1; i <= n - 1; i+=2){
            inner += f(xi);
            xi += 2 * h;
        }
        I_2n = (inner + outer) * h;
        if ((I_2n - I_n) < 3*eps)      //  I_2n is always greater then I_n, so we don't need to use fabs()
            return I_2n;
        else
            I_n = I_2n;
    }
}

//#else
//#include <math.h>
//double integral(double (*f)(double x), double a, double b, double eps) {   /*  method of RECTANGLES */
    // I = h * (f(x0) + f(x1) + .. + f(xn-1)), x0 = a, xi = a + (i + 0.5)*h, h = (b-a)/2

//    double I_n = 0;
//    int n = 20;
//    double h = (b - a)/n;
//    double xi = a + h / 2;

//    for (int i = 0; i < n; i++) {
//        I_n += f(xi);           //  xi = a + (i + 0.5) * h
//        xi += h;
//    }
//    I_n *= h;

//    double I_2n;

    /* in I_n we save I from the previous step
    in I_2n we sum current I */
//    while (1) {
//        n *= 2;
//        h /= 2;
//        I_2n = 0;
//        xi = a + h / 2;
//        for (int i = 0; i < n; i++) {
//            I_2n += f(xi);
//            xi += h;
//        }
//        I_2n *= h;
//        if (fabs(I_n - I_2n) < 3*eps)
//            return I_2n;
//        else
//            I_n = I_2n;
//    }
//}
//#endif

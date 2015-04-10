/* Test problem definitions */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

# include "global.h"
# include "rand.h"

/*  Test problem SCH1
    # of real variables = 1
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void sch1 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    obj[0] = pow(xreal[0],2.0);
    obj[1] = pow((xreal[0]-2.0),2.0);
    return;
}

/*  Test problem SCH2
    # of real variables = 1
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void sch2 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    if (xreal[0]<=1.0)
    {
        obj[0] = -xreal[0];
        obj[1] = pow((xreal[0]-5.0),2.0);
        return;
    }
    if (xreal[0]<=3.0)
    {
        obj[0] = xreal[0]-2.0;
        obj[1] = pow((xreal[0]-5.0),2.0);
        return;
    }
    if (xreal[0]<=4.0)
    {
        obj[0] = 4.0-xreal[0];
        obj[1] = pow((xreal[0]-5.0),2.0);
        return;
    }
    obj[0] = xreal[0]-4.0;
    obj[1] = pow((xreal[0]-5.0),2.0);
    return;
}

/*  Test problem FON
    # of real variables = n
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void fon (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double s1, s2;
    int i;
    s1 = s2 = 0.0;
    for (i=0; i<nreal; i++)
    {
        s1 += pow((xreal[i]-(1.0/sqrt((double)nreal))),2.0);
        s2 += pow((xreal[i]+(1.0/sqrt((double)nreal))),2.0);
    }
    obj[0] = 1.0 - exp(-s1);
    obj[1] = 1.0 - exp(-s2);
    return;
}

/*  Test problem KUR
    # of real variables = 3
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void kur (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    int i;
    double res1, res2;
    res1 = -0.2*sqrt((xreal[0]*xreal[0]) + (xreal[1]*xreal[1]));
    res2 = -0.2*sqrt((xreal[1]*xreal[1]) + (xreal[2]*xreal[2]));
    obj[0] = -10.0*( exp(res1) + exp(res2));
    obj[1] = 0.0;
    for (i=0; i<3; i++)
    {
        obj[1] += pow(fabs(xreal[i]),0.8) + 5.0*sin(pow(xreal[i],3.0));
    }
    return;
}

/*  Test problem POL
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void pol (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double a1, a2, b1, b2;
    a1 = 0.5*sin(1.0) - 2.0*cos(1.0) + sin(2.0) - 1.5*cos(2.0);
    a2 = 1.5*sin(1.0) - cos(1.0) + 2.0*sin(2.0) - 0.5*cos(2.0);
    b1 = 0.5*sin(xreal[0]) - 2.0*cos(xreal[0]) + sin(xreal[1]) - 1.5*cos(xreal[1]);
    b2 = 1.5*sin(xreal[0]) - cos(xreal[0]) + 2.0*sin(xreal[1]) - 0.5*cos(xreal[1]);
    obj[0] = 1.0 + pow((a1-b1),2.0) + pow((a2-b2),2.0);
    obj[1] = pow((xreal[0]+3.0),2.0) + pow((xreal[1]+1.0),2.0);
    return;
}

/*  Test problem VNT
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 3
    # of constraints = 0
    */
void vnt (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    obj[0] = 0.5*(xreal[0]*xreal[0] + xreal[1]*xreal[1]) + sin(xreal[0]*xreal[0] + xreal[1]*xreal[1]);
    obj[1] = (pow((3.0*xreal[0] - 2.0*xreal[1] + 4.0),2.0))/8.0 + (pow((xreal[0]-xreal[1]+1.0),2.0))/27.0 + 15.0;
    obj[2] = 1.0/(xreal[0]*xreal[0] + xreal[1]*xreal[1] + 1.0) - 1.1*exp(-(xreal[0]*xreal[0] + xreal[1]*xreal[1]));
    return;
}

/*  Test problem ZDT1
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void zdt1 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double f1, f2, g, h;
    int i;
    f1 = xreal[0];
    g = 0.0;
    for (i=1; i<30; i++)
    {
        g += xreal[i];
    }
    g = 9.0*g/29.0;
    g += 1.0;
    h = 1.0 - sqrt(f1/g);
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;
}

/*  Test problem ZDT2
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void zdt2 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double f1, f2, g, h;
    int i;
    f1 = xreal[0];
    g = 0.0;
    for (i=1; i<30; i++)
    {
        g += xreal[i];
    }
    g = 9.0*g/29.0;
    g += 1.0;
    h = 1.0 - pow((f1/g),2.0);
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;
}

/*  Test problem ZDT3
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void zdt3 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double f1, f2, g, h;
    int i;
    f1 = xreal[0];
    g = 0.0;
    for (i=1; i<30; i++)
    {
        g += xreal[i];
    }
    g = 9.0*g/29.0;
    g += 1.0;
    h = 1.0 - sqrt(f1/g) - (f1/g)*sin(10.0*PI*f1);
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;
}

/*  Test problem ZDT4
    # of real variables = 10
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void zdt4 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double f1, f2, g, h;
    int i;
    f1 = xreal[0];
    g = 0.0;
    for (i=1; i<10; i++)
    {
        g += xreal[i]*xreal[i] - 10.0*cos(4.0*PI*xreal[i]);
    }
    g += 91.0;
    h = 1.0 - sqrt(f1/g);
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;
}

/*  Test problem ZDT5
    # of real variables = 0
    # of bin variables = 11
    # of bits for binvar1 = 30
    # of bits for binvar2-11 = 5
    # of objectives = 2
    # of constraints = 0
    */
void zdt5 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    int i, j;
    int u[11];
    int v[11];
    double f1, f2, g, h;
    for (i=0; i<11; i++)
    {
        u[i] = 0;
    }
    for (j=0; j<30; j++)
    {
        if (gene[0][j] == 1)
        {
            u[0]++;
        }
    }
    for (i=1; i<11; i++)
    {
        for (j=0; j<4; j++)
        {
            if (gene[i][j] == 1)
            {
                u[i]++;
            }
        }
    }
    f1 = 1.0 + u[0];
    for (i=1; i<11; i++)
    {
        if (u[i] < 5)
        {
            v[i] = 2 + u[i];
        }
        else
        {
            v[i] = 1;
        }
    }
    g = 0;
    for (i=1; i<11; i++)
    {
        g += v[i];
    }
    h = 1.0/f1;
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;
}

/*  Test problem ZDT6
    # of real variables = 10
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void zdt6 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double f1, f2, g, h;
    int i;
    f1 = 1.0 - (exp(-4.0*xreal[0]))*pow((sin(6.0*PI*xreal[0])),6.0);
    g = 0.0;
    for (i=1; i<10; i++)
    {
        g += xreal[i];
    }
    g = g/9.0;
    g = pow(g,0.25);
    g = 1.0 + 9.0*g;
    h = 1.0 - pow((f1/g),2.0);
    f2 = g*h;
    obj[0] = f1;
    obj[1] = f2;
    return;
}

/*  Test problem BNH
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 2
    */
void bnh (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    obj[0] = 4.0*(xreal[0]*xreal[0] + xreal[1]*xreal[1]);
    obj[1] = pow((xreal[0]-5.0),2.0) + pow((xreal[1]-5.0),2.0);
    constr[0] = 1.0 - (pow((xreal[0]-5.0),2.0) + xreal[1]*xreal[1])/25.0;
    constr[1] = (pow((xreal[0]-8.0),2.0) + pow((xreal[1]+3.0),2.0))/7.7 - 1.0;
    return;
}

/*  Test problem OSY
    # of real variables = 6
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 6
    */
void osy (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    obj[0] = -(25.0*pow((xreal[0]-2.0),2.0) + pow((xreal[1]-2.0),2.0) + pow((xreal[2]-1.0),2.0) + pow((xreal[3]-4.0),2.0) + pow((xreal[4]-1.0),2.0));
    obj[1] = xreal[0]*xreal[0] +  xreal[1]*xreal[1] + xreal[2]*xreal[2] + xreal[3]*xreal[3] + xreal[4]*xreal[4] + xreal[5]*xreal[5];
    constr[0] = (xreal[0]+xreal[1])/2.0 - 1.0;
    constr[1] = 1.0 - (xreal[0]+xreal[1])/6.0;
    constr[2] = 1.0 - xreal[1]/2.0 + xreal[0]/2.0;
    constr[3] = 1.0 - xreal[0]/2.0 + 3.0*xreal[1]/2.0;
    constr[4] = 1.0 - (pow((xreal[2]-3.0),2.0))/4.0 - xreal[3]/4.0;
    constr[5] = (pow((xreal[4]-3.0),2.0))/4.0 + xreal[5]/4.0 - 1.0;
    return;
}

/*  Test problem SRN
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 2
    */
void srn (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    obj[0] = 2.0 + pow((xreal[0]-2.0),2.0) + pow((xreal[1]-1.0),2.0);
    obj[1] = 9.0*xreal[0] - pow((xreal[1]-1.0),2.0);
    constr[0] = 1.0 - (pow(xreal[0],2.0) + pow(xreal[1],2.0))/225.0;
    constr[1] = 3.0*xreal[1]/10.0 - xreal[0]/10.0 - 1.0;
    return;
}

/*  Test problem TNK
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 2
    */
void tnk (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    obj[0] = xreal[0];
    obj[1] = xreal[1];
    if (xreal[1] == 0.0)
    {
        constr[0] = -1.0;
    }
    else
    {
        constr[0] = xreal[0]*xreal[0] + xreal[1]*xreal[1] - 0.1*cos(16.0*atan(xreal[0]/xreal[1])) - 1.0;
    }
    constr[1] = 1.0 - 2.0*pow((xreal[0]-0.5),2.0) + 2.0*pow((xreal[1]-0.5),2.0);
    return;
}

/*  Test problem CTP1
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 2
    */
void ctp1 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double g;
    g = 1.0 + xreal[1];
    obj[0] = xreal[0];
    obj[1] = g*exp(-obj[0]/g);
    constr[0] = obj[1]/(0.858*exp(-0.541*obj[0]))-1.0;
    constr[1] = obj[1]/(0.728*exp(-0.295*obj[0]))-1.0;
    return;
}

/*  Test problem CTP2
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp2 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double g;
    double theta, a, b, c, d, e;
    double exp1, exp2;
    theta = -0.2*PI;
    a = 0.2;
    b = 10.0;
    c = 1.0;
    d = 6.0;
    e = 1.0;
    g = 1.0 + xreal[1];
    obj[0] = xreal[0];
    obj[1] = g*(1.0  - sqrt(obj[0]/g));
    exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
    exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
    exp2 = b*PI*pow(exp2,c);
    exp2 = fabs(sin(exp2));
    exp2 = a*pow(exp2,d);
    constr[0] = exp1/exp2 - 1.0;
    return;
}

/*  Test problem CTP3
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp3 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double g;
    double theta, a, b, c, d, e;
    double exp1, exp2;
    theta = -0.2*PI;
    a = 0.1;
    b = 10.0;
    c = 1.0;
    d = 0.5;
    e = 1.0;
    g = 1.0 + xreal[1];
    obj[0] = xreal[0];
    obj[1] = g*(1.0  - sqrt(obj[0]/g));
    exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
    exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
    exp2 = b*PI*pow(exp2,c);
    exp2 = fabs(sin(exp2));
    exp2 = a*pow(exp2,d);
    constr[0] = exp1/exp2 - 1.0;
    return;
}

/*  Test problem CTP4
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp4 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double g;
    double theta, a, b, c, d, e;
    double exp1, exp2;
    theta = -0.2*PI;
    a = 0.75;
    b = 10.0;
    c = 1.0;
    d = 0.5;
    e = 1.0;
    g = 1.0 + xreal[1];
    obj[0] = xreal[0];
    obj[1] = g*(1.0  - sqrt(obj[0]/g));
    exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
    exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
    exp2 = b*PI*pow(exp2,c);
    exp2 = fabs(sin(exp2));
    exp2 = a*pow(exp2,d);
    constr[0] = exp1/exp2 - 1.0;
    return;
}

/*  Test problem CTP5
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp5 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double g;
    double theta, a, b, c, d, e;
    double exp1, exp2;
    theta = -0.2*PI;
    a = 0.1;
    b = 10.0;
    c = 2.0;
    d = 0.5;
    e = 1.0;
    g = 1.0 + xreal[1];
    obj[0] = xreal[0];
    obj[1] = g*(1.0  - sqrt(obj[0]/g));
    exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
    exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
    exp2 = b*PI*pow(exp2,c);
    exp2 = fabs(sin(exp2));
    exp2 = a*pow(exp2,d);
    constr[0] = exp1/exp2 - 1.0;
    return;
}

/*  Test problem CTP6
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp6 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double g;
    double theta, a, b, c, d, e;
    double exp1, exp2;
    theta = 0.1*PI;
    a = 40.0;
    b = 0.5;
    c = 1.0;
    d = 2.0;
    e = -2.0;
    g = 1.0 + xreal[1];
    obj[0] = xreal[0];
    obj[1] = g*(1.0  - sqrt(obj[0]/g));
    exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
    exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
    exp2 = b*PI*pow(exp2,c);
    exp2 = fabs(sin(exp2));
    exp2 = a*pow(exp2,d);
    constr[0] = exp1/exp2 - 1.0;
    return;
}

/*  Test problem CTP7
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 1
    */
void ctp7 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double g;
    double theta, a, b, c, d, e;
    double exp1, exp2;
    theta = -0.05*PI;
    a = 40.0;
    b = 5.0;
    c = 1.0;
    d = 6.0;
    e = 0.0;
    g = 1.0 + xreal[1];
    obj[0] = xreal[0];
    obj[1] = g*(1.0  - sqrt(obj[0]/g));
    exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
    exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
    exp2 = b*PI*pow(exp2,c);
    exp2 = fabs(sin(exp2));
    exp2 = a*pow(exp2,d);
    constr[0] = exp1/exp2 - 1.0;
    return;
}

/*  Test problem CTP8
    # of real variables = 2
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 2
    */
void ctp8 (double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double g;
    double theta, a, b, c, d, e;
    double exp1, exp2;
    g = 1.0 + xreal[1];
    obj[0] = xreal[0];
    obj[1] = g*(1.0  - sqrt(obj[0]/g));
    theta = 0.1*PI;
    a = 40.0;
    b = 0.5;
    c = 1.0;
    d = 2.0;
    e = -2.0;
    exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
    exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
    exp2 = b*PI*pow(exp2,c);
    exp2 = fabs(sin(exp2));
    exp2 = a*pow(exp2,d);
    constr[0] = exp1/exp2 - 1.0;
    theta = -0.05*PI;
    a = 40.0;
    b = 2.0;
    c = 1.0;
    d = 6.0;
    e = 0.0;
    exp1 = (obj[1]-e)*cos(theta) - obj[0]*sin(theta);
    exp2 = (obj[1]-e)*sin(theta) + obj[0]*cos(theta);
    exp2 = b*PI*pow(exp2,c);
    exp2 = fabs(sin(exp2));
    exp2 = a*pow(exp2,d);
    constr[1] = exp1/exp2 - 1.0;
    return;
}

/*  Test problem CEC09 Unconstrained Problem 1
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void cec09unprob1(double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double sum1 = 0.0;
    double sum2 = 0.0;
    int j;
    int J1size = 0;
    int J2size = 0;

    /* Sumatoria para F1 */
    for (j = 3; j <= nreal; j += 2) {
        ++J1size;
        double xj = xreal[j-1];
        double x1 = xreal[0];
        double aux = xj - sin(6.0 * PI * x1 + (j * PI) / nreal);
        sum1 += aux * aux;
    }

    /* Sumatoria para F2 */
    for (j = 2; j <= nreal; j += 2) {
        ++J2size;
        double xj = xreal[j-1];
        double x1 = xreal[0];
        double aux = xj - sin(6.0 * PI * x1 + (j * PI) / nreal);
        sum2 += aux * aux;
    }

    /* Cálculo de F1 y F2 */
    obj[0] = xreal[0] + (2.0 / J1size) * sum1;
    obj[1] = 1.0 - sqrt(xreal[0]) + (2.0 / J2size) * sum2;

    return;
}

/*  Test problem CEC09 Unconstrained Problem 2
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void cec09unprob2(double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double sum1 = 0.0;
    double sum2 = 0.0;
    int j;
    int J1size = 0;
    int J2size = 0;

    /* Sumatoria para F1 */
    for (j = 3; j <= nreal; j += 2) {
        ++J1size;
        double xj = xreal[j-1];
        double x1 = xreal[0];
        double y = xj - (0.3*x1*x1 * cos(24.0*PI*x1 + (4.0*j*PI) / nreal) + 0.6*x1) * cos(6.0*PI*x1 + (j*PI) / nreal);
        sum1 += y * y;
    }

    /* Sumatoria para F2 */
    for (j = 2; j <= nreal; j += 2) {
        ++J2size;
        double xj = xreal[j-1];
        double x1 = xreal[0];
        double y = xj - (0.3*x1*x1 * cos(24.0*PI*x1 + (4.0*j*PI) / nreal) + 0.6*x1) * sin(6.0*PI*x1 + (j*PI) / nreal);
        sum2 += y * y;
    }

    obj[0] = xreal[0] + (2.0 / J1size) * sum1;
    obj[1] = 1 - sqrt(xreal[0]) + (2.0 / J2size) * sum2;

    return;
}

/*  Test problem CEC09 Unconstrained Problem 3
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void cec09unprob3(double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double sum1 = 0.0;
    double sum2 = 0.0;
    double prod1 = 1.0;
    double prod2 = 1.0;
    int j;
    int J1size = 0;
    int J2size = 0;

    /* Sumatoria y producto para F1 */
    for (j = 3; j <= nreal; j += 2) {
        ++J1size;
        double xj = xreal[j-1];
        double x1 = xreal[0];
        double yj = xj - pow(x1, 0.5 * (1.0 + ((3.0 * (j - 2.0)) / (nreal - 2.0))));
        sum1 += yj * yj;
        prod1 *= cos((20.0 * yj * PI) / sqrt(j));
    }

    /* Sumatoria y producto para F2 */
    for (j = 2; j <= nreal; j += 2) {
        ++J2size;
        double xj = xreal[j-1];
        double x1 = xreal[0];
        double yj = xj - pow(x1, 0.5 * (1.0 + ((3.0 * (j - 2.0)) / (nreal - 2.0))));
        sum2 += yj * yj;
        prod2 *= cos((20.0 * yj * PI) / sqrt(j));
    }

    obj[0] = xreal[0] + (2.0 / J1size) * (4.0 * sum1 - 2.0 * prod1 + 2.0);
    obj[1] = 1.0 - sqrt(xreal[0]) + (2.0 / J2size) * (4.0 * sum2 - 2.0 * prod2 + 2.0);

    return;
}

/*  Test problem CEC09 Unconstrained Problem 4
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void cec09unprob4(double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    double sum1 = 0.0;
    double sum2 = 0.0;
    int j;
    int J1size = 0;
    int J2size = 0;

    /* Sumatoria para F1 */
    for (j = 3; j <= nreal; j += 2) {
        ++J1size;
        double xj = xreal[j-1];
        double x1 = xreal[0];
        double yj = xj - sin(6.0 * PI * x1 + (j * PI) / nreal);
        sum1 += fabs(yj) / (1 + exp(2.0 * fabs(yj)));
    }

    /* Sumatoria y producto para F2 */
    for (j = 2; j <= nreal; j += 2) {
        ++J2size;
        double xj = xreal[j-1];
        double x1 = xreal[0];
        double yj = xj - sin(6.0 * PI * x1 + (j * PI) / nreal);
        sum1 += fabs(yj) / (1 + exp(2.0 * fabs(yj)));
    }

    obj[0] = xreal[0] + (2.0 / J1size) * sum1;
    obj[1] = 1.0 - pow(xreal[0], 2) + (2.0 / J2size) * sum2;

    return;
}

/*  Test problem CEC09 Unconstrained Problem 5
    # of real variables = 30
    # of bin variables = 0
    # of objectives = 2
    # of constraints = 0
    */
void cec09unprob5(double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    const int N = 10;
    const double epsilon = 0.1;
    double sum1 = 0.0;
    double sum2 = 0.0;
    double aux;
    int j;
    int J1size = 0;
    int J2size = 0;

    /* Sumatoria para F1 */
    for (j = 3; j <= nreal; j += 2) {
        ++J1size;
        double xj = xreal[j-1];
        double x1 = xreal[0];
        double yj = xj - sin(6.0 * PI * x1 + (j * PI) / nreal);
        double h = 2.0 * yj * yj - cos(4.0 * PI * yj) + 1.0;
        sum1 += h;
    }

    /* Sumatoria para F2 */
    for (j = 2; j <= nreal; j += 2) {
        ++J2size;
        double xj = xreal[j-1];
        double x1 = xreal[0];
        double yj = xj - sin(6.0 * PI * x1 + (j * PI) / nreal);
        double h = 2.0 * yj * yj - cos(4.0 * PI * yj) + 1.0;
        sum2 += h;
    }

    aux = (1.0 / (2.0 * N) + epsilon) * fabs(sin(2.0 * N * PI * xreal[0]));
    obj[0] = xreal[0] + aux + (2.0 / J1size) * sum1;
    obj[1] = 1.0 - xreal[0] + aux + (2.0 / J2size) * sum2;

    return;
}

/*  Test problem DTLZ1
    # of real variables = n
    # of bin variables = 0
    # of objectives = m
    # of constraints = 0
    */
void dtlz1(double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    int i, j, k;
    double g = 0;
    
    /* Calcular g(x) */
    for (i=nobj-1; i < nreal; i++)
    {
        double h = (xreal[i] - 0.5);
        g += h*h - cos(20*PI*h);
    }
    
    k = nreal - nobj + 1;
    g = 100 * (k + g);
    
    /* Calcular F(x) */
    for (i=0; i < nobj; i++)
    {
        obj[i] = 0.5 * (1 + g);
        
        for (j=0; j < nobj - i - 1; j++)
            obj[i] *= xreal[j];
        
        if (i != 0)
        {
            j = nobj - i - 1;
            obj[i] *= 1 - xreal[j];            
        }
    }
    
    return;
}

/*  Test problem DTLZ2
    # of real variables = n
    # of bin variables = 0
    # of objectives = m
    # of constraints = 0
    */
void dtlz2(double *xreal, double *xbin, int **gene, double *obj, double *constr)
{
    int i, j;
    double g = 0;
    
    /* Calcular g(x) */
    for (i=nobj-1; i < nreal; i++)
    {
        double h = (xreal[i] - 0.5);
        g += h*h;
    }
    
    /* Calcular F(x) */
    for (i=0; i < nobj; i++)
    {
        obj[i] = 0.5 * (1 + g);
        
        for (j=0; j < nobj - i - 1; j++)
            obj[i] *= cos(xreal[j] * PI * 0.5);
        
        if (i != 0)
        {
            j = nobj - i - 1;
            obj[i] *= sin(xreal[j] * PI * 0.5);
        }
    }
    
    return;
}

char problem_name[100];
int problem_count = 31;
char *problems[] = {"sch1", "sch2", "fon", "kur", "pol", "vnt",
                    "zdt1", "zdt2", "zdt3", "zdt4", "zdt5", "zdt6",
                    "bnh", "osy", "srn", "tnk", "ctp1", "ctp2",
                    "ctp3", "ctp4", "ctp5", "ctp6", "ctp7", "ctp8",
                    "cec09unprob1", "cec09unprob2", "cec09unprob3",
                    "cec09unprob4", "cec09unprob5", "dtlz1", "dtlz2"};

/* Routine to return the pointer to the evaluation function according to the problem name */
test_problem get_problem_function(char *problem_name)
{
    int i;
    test_problem functions[] = {sch1, sch2, fon, kur, pol, vnt,
                                zdt1, zdt2, zdt3, zdt4, zdt5, zdt6,
                                bnh, osy, srn, tnk, ctp1, ctp2,
                                ctp3, ctp4, ctp5, ctp6, ctp7, ctp8,
				cec09unprob1, cec09unprob2, cec09unprob3,
				cec09unprob4, cec09unprob5, dtlz1, dtlz2};

    for (i=0; i < problem_count; i++)
    {
        if (strcmp(problems[i], problem_name) == 0)
            return functions[i];
    }

    printf("\n Problem read is: %s", problem_name);
    printf("\n Wrong problem name entered, hence exiting \n");
    exit (1);
}

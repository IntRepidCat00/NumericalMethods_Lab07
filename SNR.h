#ifndef LAB07_SNR_H
#define LAB07_SNR_H

#include <iostream>
#include <cmath>

class SNR
{
private:
    double X{0};
    double Y{0};
    double eps{10e-3};
public:
    void print();
    double funcPhi1(double p);
    double funcPhi2(double p);
    double funcF1(double x, double y);
    double funcF2(double x, double y);
    double funcF1DerivByX(double x, double y);
    double funcF1DerivByY(double x, double y);
    double funcF2DerivByX(double x, double y);
    double funcF2DerivByY(double x, double y);
    double funcPhi1DerivByX(double x);
    double funcPhi1DerivByY(double y);
    double funcPhi2DerivByX(double x);
    double funcPhi2DerivByY(double y);
    double calcJacobian(double x, double y);
    double calcDeltaX(double x, double y);
    double calcDeltaY(double x, double y);
    void iterationMethod();
    void NewtonMethod();
};


#endif //LAB07_SNR_H

#include "SNR.h"

void SNR::print()
{
  std::string divideLine(80, '-');
  std::cout << divideLine << std::endl;
  std::cout << "sin(x + 2) - y = 1.5" << std::endl;
  std::cout << "x + cos(y - 2) = 0.5" << std::endl;
  std::cout << divideLine << std::endl;
}

double SNR::funcPhi1(double p)
{
  return sin(p + 2) - 1.5;
}

double SNR::funcPhi2(double p)
{
  return 0.5 - cos(p-2);
}

double SNR::funcF1(double x, double y)
{
  return sin(x+2) - y - 1.5;
}

double SNR::funcF2(double x, double y)
{
  return x + cos(y-2) - 0.5;
}

double SNR::funcF1DerivByX(double x, double y)
{
  return cos(x+2);
}

double SNR::funcF1DerivByY(double x, double y)
{
  return -1;
}

double SNR::funcF2DerivByX(double x, double y)
{
  return 1;
}

double SNR::funcF2DerivByY(double x, double y)
{
  return -sin(y-2);
}

double SNR::funcPhi1DerivByX(double x)
{
  return cos(x+2);
}

double SNR::funcPhi1DerivByY(double y)
{
  return 0;
}

double SNR::funcPhi2DerivByX(double x)
{
  return 0;
}

double SNR::funcPhi2DerivByY(double y)
{
  return sin(y-2);
}

double SNR::calcJacobian(double x, double y)
{
  double Jacobian{0};

  Jacobian += funcF1DerivByX(x, y) * funcF2DerivByY(x, y);
  Jacobian -= funcF2DerivByX(x, y) * funcF1DerivByY(x, y);

  return Jacobian;
}

double SNR::calcDeltaX(double x, double y)
{
  double deltaX{0};
  std::cout << "Jacobian = " <<  calcJacobian(x, y) << std::endl;
  if(calcJacobian(x, y) != 0)
  {
    deltaX += funcF1(x, y) * funcF2DerivByY(x, y);
    deltaX -= funcF2(x, y) * funcF1DerivByY(x, y);
    deltaX /= -calcJacobian(x, y);
    std::cout << "Delta X = " << deltaX << std::endl;
    return deltaX;
  } else
  {
    std::cout << "Jacobian = 0. Cannot calc delta X" << std::endl;
    return 0;
  }
}

double SNR::calcDeltaY(double x, double y)
{
  double deltaY{0};
  std::cout << "Jacobian = " <<  calcJacobian(x, y) << std::endl;
  if(calcJacobian(x, y) != 0)
  {
    deltaY += funcF1DerivByX(x, y) * funcF2(x, y);
    deltaY -= funcF2DerivByX(x, y) * funcF1(x, y);
    deltaY /= -calcJacobian(x, y);
    std::cout << "Delta Y = " << deltaY << std::endl;
    return deltaY;
  } else
  {
    std::cout << "Jacobian = 0. Cannot calc delta Y" << std::endl;
    return 0;
  }
}

void SNR::iterationMethod()
{
  std::string divideLine(80, '-');
  std::cout << "------------------- Iterations Method ------------------------------------------" << std::endl;
  double xn{0}, yn{1};

  double xdif = fabs(funcPhi1DerivByX(xn)) + fabs(funcPhi2DerivByX(xn));
  double ydif = fabs(funcPhi1DerivByY(yn)) + fabs(funcPhi2DerivByY(yn));

  if(xdif < 1 && ydif < 1)
  {
    std::cout << "=The process is convergent=" << std::endl;
  } else
  {
    std::cout << "~The process could be not convergent~" << std::endl;
  }

  double xprev, yprev;

  std::cout << divideLine << std::endl;
  std::cout << "0) X = " << xn << " | Y = " << yn << " | Eps = " << eps << std::endl;

  int iter = 0;
  do
  {
    iter++;
    xprev = xn;
    yprev = yn;

    xn = funcPhi2(yprev);
    yn = funcPhi1(xprev);

    std::cout << iter << ") X = " << xn << " | Y = " << yn << " | Diff = " << fabs(xn - xprev) + fabs(yn - yprev)
    << std::endl;
  }while(fabs(xn - xprev) + fabs(yn - yprev) > eps);
  std::cout << divideLine << std::endl;

  X = xn;
  Y = yn;
}

void SNR::NewtonMethod()
{
  std::string divideLine(80, '-');
  std::cout << "------------------- Newton Method ----------------------------------------------" << std::endl;
  double xn{0}, yn{1};

  double xdif = fabs(funcPhi1DerivByX(xn)) + fabs(funcPhi2DerivByX(xn));
  double ydif = fabs(funcPhi1DerivByY(yn)) + fabs(funcPhi2DerivByY(yn));

  if(xdif < 1 && ydif < 1)
  {
    std::cout << "=The process is convergent=" << std::endl;
  } else
  {
    std::cout << "~The process could be not convergent~" << std::endl;
  }

  double xprev, yprev;

  std::cout << divideLine << std::endl;
  std::cout << "0) X = " << xn << " | Y = " << yn << " | Eps = " << eps << std::endl;

  int iter = 0;
  do
  {
    iter++;
    xprev = xn;
    yprev = yn;

    xn = xprev + calcDeltaX(xprev, yprev);
    yn = yprev + calcDeltaY(xprev, yprev);

    std::cout << iter << ") X = " << xn << " | Y = " << yn << " | Diff = " << fabs(xn - xprev) + fabs(yn - yprev)
              << std::endl;
  }while(fabs(xn - xprev) + fabs(yn - yprev) > eps);
  std::cout << divideLine << std::endl;

  X = xn;
  Y = yn;
}
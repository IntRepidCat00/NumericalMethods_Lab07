#include <iostream>
#include "SNR.h"

int main()
{
  SNR *mySystem = new SNR;
  SNR *mySystem2 = new SNR;
  mySystem->print();
  mySystem->iterationMethod();
  mySystem2->NewtonMethod();

  delete mySystem;
  delete mySystem2;
  return 0;
}

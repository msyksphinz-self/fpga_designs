#include "qbit.hpp"

int main ()
{
  Qbits qbits;
  qbits.AddQbit();
  qbits.AddQbit();

#ifdef C_SIMULATION
  printf("qbit = %x\n", qbits.Measure());
#endif // C_SIMULATION

}

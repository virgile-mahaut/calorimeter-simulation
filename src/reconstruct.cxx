#include <cmath>
#include "TRandom3.h"

#include "Event.h"

using namespace std;

/**
 * @brief This function generates the reconstructed parameters.
 * @details The reconstructed energy `eReco` is obtained by smearing the true value `eTrue`. 
 * A random generator is used to draw a random value with +/- 0.5 GeV areound the true value.
 * @param[in] event Event object.
 */
void reconstruct(Event& event)
{
  TRandom3 *rand = new TRandom3(0);
  float e = event.eTrue(); // get true energy
  float eReso = 0.1 * sqrt(e); // compute resolution
  float eSmeared = rand->Gaus(e, eReso); // smear with a gaussian distribution
  event.seteReco(eSmeared); // set the reconstructed energy
  event.seteRecoBias(eSmeared + 0.1); // set the biased reconstructed energy
  delete rand;
}

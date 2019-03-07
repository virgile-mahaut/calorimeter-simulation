#include <cmath>
#include "TRandom3.h"

#include "Event.h"

using namespace std;

void reconstruct(Event& event)
{
  TRandom3 *rand = new TRandom3(0);
  rand->SetSeed(0);
  float e = event.eTrue(); // get true energy
  float eReso = 0.1 * sqrt(e); // compute resolution
  float eSmeared = e + eReso * (rand->Rndm() - 0.5); // smear with a flat distribution
  event.seteReco(eSmeared); // set the reconstructed energy
  delete rand;
}

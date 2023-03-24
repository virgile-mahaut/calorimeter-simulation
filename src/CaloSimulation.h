#ifndef CaloSimulation_h
#define CaloSimulation_h

/**
 * CaloSimulation
 * Implements the simulation of the calorimter.
 */

#include "CellAddress.h"
#include "CaloCell.h"
#include <vector>
#include <map>

class CaloSimulation
{
public:
  CaloSimulation();

  // Add the calorimeter cells to the vector of cell caldata.
  void CalorimeterData(std::vector<CaloCell>& caldata) const;

  // Simulate a hadronic shower of a given energy, starting from the impact point (x,y)
  // of the electron at the front end of the calorimeter.
  // if f=0, this corresponds to an electromagnetic shower
  void SimulateHadShower(float f, float x, float y, float energy);

  // Print all the cells.
  friend std::ostream& operator<<(std::ostream& os, const CaloSimulation& cs)
  {
    std::vector<CaloCell> caldata;
    cs.CalorimeterData(caldata);
    for (long unsigned int i=0; i<caldata.size(); i++)
    {
      os << caldata.at(i).address() << ", " << caldata.at(i).energy() << "\n";
    }
  return os;
  }

private:
  std::vector<CaloCell> m_caldata; // vector of all cells in the computation
};

#endif

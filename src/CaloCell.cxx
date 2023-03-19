#include "CaloCell.h"
#include "TRandom.h"
#include "CaloConstants.h"
using namespace CalConst;

//______________________________________________________________________________
CaloCell::CaloCell()
{
}

//______________________________________________________________________________
CaloCell::CaloCell(const CellAddress& ca, float energy)
{
  gRandom->SetSeed(0);
  m_energy = energy;
  m_energy_rec = gRandom->Gaus(energy, 0.1 * sqrt(energy));
  m_address = ca;
}

//______________________________________________________________________________
float CaloCell::energy() const
{
  return m_energy;
}

//______________________________________________________________________________
float CaloCell::energy_rec() const
{
  return m_energy_rec;
}

//______________________________________________________________________________
CellAddress CaloCell::address() const
{
  return m_address;
}

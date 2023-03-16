#include "CellAddress.h"
#include "CaloGeometry.h"
#include "CaloConstants.h"
#include <iostream>
using namespace CalConst;
using namespace std;

//______________________________________________________________________________
CaloGeometry::CaloGeometry()
{
}

//______________________________________________________________________________
bool CaloGeometry::IsInside(double xyz[3], CellAddress& cellAddress)
{
  if ((-1 < xyz[0] && xyz[0] < NbCellsInXY)
   && (-1 < xyz[1] && xyz[1] < NbCellsInXY)
   && (-1 < xyz[2] && xyz[2] < NbLayers))
  {
    cellAddress = CellAddress(xyz[0], xyz[1], xyz[2]);
    return true;
  }
  return false;
}

//______________________________________________________________________________
double CaloGeometry::xCentre(const CellAddress& cellAddress)
{
  return cellAddress.ix();
}

//______________________________________________________________________________
double CaloGeometry::yCentre(const CellAddress& cellAddress)
{
  return cellAddress.iy();
}
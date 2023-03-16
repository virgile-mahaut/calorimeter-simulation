#include "CaloConstants.h"
#include "CellAddress.h"
using namespace CalConst;

//______________________________________________________________________________
CellAddress::CellAddress()
{
  m_ix = -1;
  m_iy = -1;
  m_layer = -1;
}

//______________________________________________________________________________
CellAddress::CellAddress(int ix, int iy, int layer)
{
  m_ix = ix;
  m_iy = iy;
  m_layer = layer;
}

//______________________________________________________________________________
bool CellAddress::IsValid() const
{
  return (-1 < m_ix && m_ix < NbCellsInXY)
      && (-1 < m_iy && m_iy < NbCellsInXY)
      && (-1 < m_layer && m_layer < NbLayers);
}

//______________________________________________________________________________
int CellAddress::ix() const
{
  return m_ix;
}

//______________________________________________________________________________
int CellAddress::iy() const
{
  return m_iy;
}

//______________________________________________________________________________
int CellAddress::layer() const
{
  return m_layer;
}
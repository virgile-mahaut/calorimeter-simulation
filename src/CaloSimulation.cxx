#include "CaloSimulation.h"
#include "CaloConstants.h"
#include "TF1.h"
#include "TF2.h"
using namespace CalConst;

//______________________________________________________________________________
CaloSimulation::CaloSimulation()
{
}

//______________________________________________________________________________
void CaloSimulation::CalorimeterData(std::vector<CaloCell>& caldata) const
{
  caldata = m_caldata;
}

//______________________________________________________________________________
void CaloSimulation::SimulateShower(float x, float y, float energy)
{
  m_caldata.clear();
  float XY_inc = (XYMax - XYMin) / float(NbCellsInXY);
  float Z_inc = (ZMax - ZMin) / float(NbLayers);
  TF1 fl("fl",
         "[0] * [1] * pow([1] * x, [2] - 1) * exp(- [1] * x)/ [3]",
         0, 100);
  fl.FixParameter(0, energy); // E0
  fl.FixParameter(1, EM_b); // b
  fl.FixParameter(2, EM_a); // a
  fl.FixParameter(3, EM_Gamma_a); // Gamma(a)
  TF2 ft("ft",
         "[0]*exp((-pow(x - [1], 2) - pow(y - [2], 2))/(2 * pow([3], 2)))/(2. * TMath::Pi() * pow([3], 2))",
         -200,200,-200,200);
  ft.FixParameter(1, x); // front end impact parameter
  ft.FixParameter(2, y);
  ft.FixParameter(3, EM_Rm); // Molière radius
.vscode/settings.json
  // compute longitudinal development of energy loss
  for (int l=0; l < NbLayers; ++l){
    float E_layer = fl.Integral(l * Z_inc / X0, (l + 1) * Z_inc / X0);
    ft.SetParameter(0, E_layer);
    // compute the transverse development of energy loss
    for (int ix=0; ix < NbCellsInXY; ++ix){
      for (int iy=0; iy < NbCellsInXY; ++iy){
        float E_cell = ft.Integral(XYMin + ix * XY_inc, XYMin + (ix + 1) * XY_inc,
                                   XYMin + iy * XY_inc, XYMin + (iy + 1) * XY_inc);
        CellAddress cell_address(ix, iy, l);
        CaloCell calo_cell(cell_address, E_cell);
        m_caldata.push_back(calo_cell);
      }
    }
  }
}
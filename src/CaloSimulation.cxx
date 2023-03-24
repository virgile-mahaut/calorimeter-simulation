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
void CaloSimulation::SimulateHadShower(float f, float x, float y, float energy)
{
  m_caldata.clear();
  float XY_inc = (XYMax - XYMin) / float(NbCellsInXY);
  float Z_inc = (ZMax - ZMin) / float(NbLayers);
  TF1 fl_em("fl_em",
         "[0] * [1] * pow([1] * x, [2] - 1) * exp(- [1] * x)/ [3]",
         0, 100);
  fl_em.FixParameter(0, energy); // E0
  fl_em.FixParameter(1, EM_b); // b
  fl_em.FixParameter(2, EM_a); // a
  fl_em.FixParameter(3, EM_Gamma_a); // Gamma(a)
  TF1 fl_ha("fl_ha",
         "[0] * [1] * pow([1] * x, [2] - 1) * exp(- [1] * x)/ [3]",
         0, 100);
  fl_ha.FixParameter(0, energy); // E0
  fl_ha.FixParameter(1, HA_b); // b
  fl_ha.FixParameter(2, HA_a); // a
  fl_ha.FixParameter(3, HA_Gamma_a); // Gamma(a)
  TF2 ft_em("ft_em",
         "[0]*exp((-pow(x - [1], 2) - pow(y - [2], 2))/(2 * pow([3], 2)))/(2. * TMath::Pi() * pow([3], 2))",
         -200,200,-200,200);
  ft_em.FixParameter(1, x); // front end impact parameter
  ft_em.FixParameter(2, y);
  ft_em.FixParameter(3, EM_Rm); // Molière radius
  TF2 ft_ha("ft_ha",
         "[0]*exp((-pow(x - [1], 2) - pow(y - [2], 2))/(2 * pow([3], 2)))/(2. * TMath::Pi() * pow([3], 2))",
         -200,200,-200,200);
  ft_ha.FixParameter(1, x); // front end impact parameter
  ft_ha.FixParameter(2, y);
  ft_ha.FixParameter(3, HA_Rm); // Molière radius
  // compute longitudinal development of energy loss
  for (int l=0; l < NbLayers; ++l){
    float E_layer_em = (1 - f) * fl_em.Integral(l * Z_inc / X0, (l + 1) * Z_inc / X0);
    ft_em.SetParameter(0, E_layer_em);
    float E_layer_ha = f * fl_ha.Integral(l * Z_inc / L, (l + 1) * Z_inc / L);
    ft_ha.SetParameter(0, E_layer_ha);
    // compute the transverse development of energy loss
    for (int ix=0; ix < NbCellsInXY; ++ix){
      for (int iy=0; iy < NbCellsInXY; ++iy){
        float E_cell = ft_em.Integral(XYMin + ix * XY_inc, XYMin + (ix + 1) * XY_inc,
                                      XYMin + iy * XY_inc, XYMin + (iy + 1) * XY_inc)
                     + ft_ha.Integral(XYMin + ix * XY_inc, XYMin + (ix + 1) * XY_inc,
                                      XYMin + iy * XY_inc, XYMin + (iy + 1) * XY_inc);
        CellAddress cell_address(ix, iy, l);
        CaloCell calo_cell(cell_address, E_cell);
        m_caldata.push_back(calo_cell);
      }
    }
  }
}
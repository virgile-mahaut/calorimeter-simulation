#include <cmath>
#include "TMath.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TF1.h"
#include "TH1F.h"

#include "Event.h"
#include "CaloConstants.h"
#include "CaloGeometry.h"
using namespace CalConst;
using namespace std;

TF1* fit(float E_layer, float posReco)
{
  TF1 *gauss_fun = new TF1("fgauss", "[0] * TMath::Gaus(x, [1], [2], 1)", XYMin, XYMax);
  gauss_fun->SetParameter(0, E_layer);
  gauss_fun->SetParameter(1, posReco);
  gauss_fun->SetParameter(2, Rm);
  gauss_fun->SetParName(0, "E_layer");
  gauss_fun->SetParName(1, "posReco");
  gauss_fun->SetParName(2, "Sigma");

  return gauss_fun;
}

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

  TH1F hx("hx","Gaussian x",NbCellsInXY, XYMin, XYMax);
  TH1F hy("hy","Gaussian y",NbCellsInXY, XYMin, XYMax);
  std::vector<CaloCell> caldata = event.calData();
  float maxE = -1;
  float max_index = -1;
  float E_layer = 0;
  for (long unsigned int i=0; i<caldata.size(); i++) // treat all the cells
  {
    if (caldata.at(i).energy_rec() > maxE){ // cell with maximum value
      maxE = caldata.at(i).energy_rec();
      max_index = i;
    }
    E_layer += caldata.at(i).energy_rec();
    hx.AddBinContent(caldata.at(i).address().ix() + 1, caldata.at(i).energy_rec());
    hy.AddBinContent(caldata.at(i).address().iy() + 1, caldata.at(i).energy_rec());
  }
  TF1 *fun_gauss_x = fit(E_layer, CaloGeometry::xCentre(caldata.at(max_index).address()));
  TF1 *fun_gauss_y = fit(E_layer, CaloGeometry::yCentre(caldata.at(max_index).address()));
  hx.Fit(fun_gauss_x, "Q");
  hy.Fit(fun_gauss_y, "Q");
  float xReco = fun_gauss_x->GetParameter("posReco");
  float yReco = fun_gauss_y->GetParameter("posReco");
  if (event.eventNumber()==0){
    TCanvas *cx = new TCanvas("cx");
    hx.Draw();
    cx->Update();
    cx->Write();
    TCanvas *cy = new TCanvas("cy");
    hy.Draw();
    cy->Update();
    cy->Write();
  }
  event.setxReco(xReco);
  event.setyReco(yReco);
}

void reconstruct_barycentre(Event& event)
{
  TRandom3 *rand = new TRandom3(0);
  float e = event.eTrue(); // get true energy
  float eReso = 0.1 * sqrt(e); // compute resolution
  float eSmeared = rand->Gaus(e, eReso); // smear with a gaussian distribution
  event.seteReco(eSmeared); // set the reconstructed energy
  event.seteRecoBias(eSmeared + 0.1); // set the biased reconstructed energy
  delete rand;

  TH1F hx("hx","Gaussian x",NbCellsInXY, XYMin, XYMax);
  TH1F hy("hy","Gaussian y",NbCellsInXY, XYMin, XYMax);
  std::vector<CaloCell> caldata = event.calData();
  float xReco = 0;
  float yReco = 0;
  float E_tot = 0;
  for (long unsigned int i=0; i<caldata.size(); i++)
  {
    E_tot += caldata.at(i).energy_rec();
    xReco += CaloGeometry::xCentre(caldata.at(i).address()) * caldata.at(i).energy_rec();
    yReco += CaloGeometry::yCentre(caldata.at(i).address()) * caldata.at(i).energy_rec();
  }
  xReco /= E_tot;
  yReco /= E_tot;
  event.setxRecoBar(xReco);
  event.setyRecoBar(yReco);
}

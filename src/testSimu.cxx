#include "CaloSimulation.h"
#include "CaloConstants.h"

// #include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TFile.h"
using namespace CalConst;
using namespace std;


/**
 * @brief displays histograms for the longitudinal and transversal developments after calling 
 * SimulateHadShower(f=0) (purely electromagnetic)
 * 
 */
void testSimu()
{
  TH1F *hlong = new TH1F("hlong", "test longitudinal",
                      NbLayers, ZMin, ZMax);
                   
  TH2F *htrans = new TH2F("htrans", "test transverse", 
                      NbCellsInXY, XYMin, XYMax,
                      NbCellsInXY, XYMin, XYMax);
  CaloSimulation calo_sim; // call to simulate shower
  calo_sim.SimulateHadShower(0., 0., 0., 50.);
  std::vector<CaloCell> caldata;
  calo_sim.CalorimeterData(caldata);
  for (long unsigned int i=0; i<caldata.size(); i++){
    CaloCell calo_cell = caldata.at(i);
    CellAddress cell_address = calo_cell.address();
    hlong->AddBinContent(cell_address.layer() + 1, calo_cell.energy());
    if (cell_address.layer() == 0){
      htrans->SetBinContent(cell_address.ix() + 1, cell_address.iy() + 1, calo_cell.energy());
    }
  }
}

/**
 * @brief displays histograms for the longitudinal and transversal developments after calling 
 * SimulateHadShower(f=1) (purely hadronic)
 * 
 */
void testHadSimu()
{
  TH1F *hlong_had = new TH1F("hlong_had", "test longitudinal (hadronic)",
                      NbLayers, ZMin, ZMax);
                   
  TH2F *htrans_had = new TH2F("htrans_had", "test transverse (hadronic)", 
                      NbCellsInXY, XYMin, XYMax,
                      NbCellsInXY, XYMin, XYMax);
  CaloSimulation calo_sim; // call to simulate shower
  
  // fraction of the purely hadronic component
  // if set to zero, should yield the same result as testSimu()
  float f = 1.;
  calo_sim.SimulateHadShower(f, 0., 0., 50.);
  std::vector<CaloCell> caldata;
  calo_sim.CalorimeterData(caldata);
  for (long unsigned int i=0; i<caldata.size(); i++){
    CaloCell calo_cell = caldata.at(i);
    CellAddress cell_address = calo_cell.address();
    hlong_had->AddBinContent(cell_address.layer() + 1, calo_cell.energy());
    if (cell_address.layer() == 0){
      htrans_had->SetBinContent(cell_address.ix() + 1, cell_address.iy() + 1, calo_cell.energy());
    }
  }
}

/**
 * @brief Computes efficiency and rejection between electromagnetic and purely hadronic showers
 * as functions of the cut (in cm)
 * 
 */
void display_rejection_efficiency()
{
  TF1 fl_em("fl_em",
            "[0] * [1] * pow([1] * x / [4], [2] - 1) * exp(- [1] * x / [4])/ ([3] * [4])",
            0, 100);
  fl_em.FixParameter(0, 50.); // E0
  fl_em.FixParameter(1, EM_b); // b
  fl_em.FixParameter(2, EM_a); // a
  fl_em.FixParameter(3, EM_Gamma_a); // Gamma(a)
  fl_em.FixParameter(4, X0);
  fl_em.SetTitle("longitudinal development function (EM)");
  TF1 fl_ha("fl_ha",
            "[0] * [1] * pow([1] * x / [4], [2] - 1) * exp(- [1] * x / [4])/ ([3] * [4])",
            0, 100);
  fl_ha.FixParameter(0, 50.); // E0
  fl_ha.FixParameter(1, HA_b); // b
  fl_ha.FixParameter(2, HA_a); // a
  fl_ha.FixParameter(3, HA_Gamma_a); // Gamma(a)
  fl_ha.FixParameter(4, L);
  fl_ha.SetTitle("longitudinal development function (hadronic)");
  TF1 ft_em_x("ft_em_x",
         "[0]*exp((-pow(x - [1], 2))/(2 * pow([2], 2)))/(sqrt(2. * TMath::Pi() * pow([2], 2)))",
         -200,200);
  ft_em_x.FixParameter(0, 50.);
  ft_em_x.FixParameter(1, 0.); // front end impact parameter
  ft_em_x.FixParameter(2, EM_Rm); // Molière radius
  ft_em_x.SetTitle("transversal development function x (EM)");
  TF1 ft_ha_x("ft_ha_x",
         "[0]*exp((-pow(x - [1], 2))/(2 * pow([2], 2)))/(sqrt(2. * TMath::Pi() * pow([2], 2)))",
         -200,200);
  ft_ha_x.FixParameter(0, 50.); 
  ft_ha_x.FixParameter(1, 0.); // front end impact parameter
  ft_ha_x.FixParameter(2, HA_Rm); // Molière radius
  ft_ha_x.SetTitle("transversal development function x (hadronic)");

  int n = 1000;
  float inc = (ZMax - ZMin) / float(n);
  TGraph *gr_l_eff = new TGraph(n-1);
  gr_l_eff->SetName("efficiency_long");
  gr_l_eff->SetTitle("efficiency (longitudinal dist)");
  TGraph *gr_l_rej = new TGraph(n-1);
  gr_l_rej->SetName("rejection_long");
  gr_l_rej->SetTitle("rejection (longitudinal dist)");
  TGraph *gr_l_prod = new TGraph(n-1);
  gr_l_prod->SetName("product_long");
  gr_l_prod->SetTitle("product (longitudinal dist)");
  TGraph *gr_tx_eff = new TGraph(n-1);
  gr_tx_eff->SetName("efficiency_trans_x");
  gr_tx_eff->SetTitle("efficiency (transverse dist x)");
  TGraph *gr_tx_rej = new TGraph(n-1);
  gr_tx_rej->SetName("rejection_trans_x");
  gr_tx_rej->SetTitle("rejection (transverse dist x)");
  TGraph *gr_tx_prod = new TGraph(n-1);
  gr_tx_prod->SetName("product_trans_x");
  gr_tx_prod->SetTitle("product (transverse dist x)");
  // efficiency
  for (int i=1; i<n; i++)
  {
    gr_l_eff->SetPoint(i, ZMin + i * inc, fl_em.Integral(ZMin, ZMin + i * inc) / fl_em.Integral(ZMin, ZMax));
    gr_l_rej->SetPoint(i, ZMin + i * inc, fl_ha.Integral(ZMin, ZMax) / fl_ha.Integral(ZMin, ZMin + i * inc));
    gr_l_prod->SetPoint(i, ZMin + i * inc, fl_em.Integral(ZMin, ZMin + i * inc) / fl_em.Integral(ZMin, ZMax)
                                         * fl_ha.Integral(ZMin, ZMax) / fl_ha.Integral(ZMin, ZMin + i * inc));
    gr_tx_eff->SetPoint(i, ZMin + i * inc, ft_em_x.Integral(ZMin, ZMin + i * inc) / ft_em_x.Integral(ZMin, ZMax));
    gr_tx_rej->SetPoint(i, ZMin + i * inc, ft_ha_x.Integral(ZMin, ZMax) / ft_ha_x.Integral(ZMin, ZMin + i * inc));
    gr_tx_prod->SetPoint(i, ZMin + i * inc, ft_em_x.Integral(ZMin, ZMin + i * inc) / ft_em_x.Integral(ZMin, ZMax)
                                          * ft_ha_x.Integral(ZMin, ZMax) / ft_ha_x.Integral(ZMin, ZMin + i * inc));
  }
  fl_em.Write();
  fl_ha.Write();
  ft_em_x.Write();
  ft_ha_x.Write();
  gr_l_eff->Write();
  gr_l_rej->Write();
  gr_l_prod->Write();
  gr_tx_eff->Write();
  gr_tx_rej->Write();
  gr_tx_prod->Write();
}
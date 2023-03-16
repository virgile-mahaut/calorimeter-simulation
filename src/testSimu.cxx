#include "CaloSimulation.h"
#include "CaloConstants.h"

// #include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
using namespace CalConst;
using namespace std;



void testSimu()
{
  TCanvas *c = new TCanvas("transverse");
  c->cd();
  TH2F *ht = new TH2F("ht", "Transverse development", 
                      NbCellsInXY, XYMin * 100, XYMax * 100,
                      NbCellsInXY, XYMin * 100, XYMax * 100);
  CaloSimulation calo_sim;
  calo_sim.SimulateShower(0., 0., 50.);
  std::vector<CaloCell> caldata = calo_sim.calData();
  for (long unsigned int i=0; i<caldata.size(); i++){
    CaloCell calo_cell = caldata.at(i);
    CellAddress cell_address = calo_cell.address();
    cout << "[" << cell_address << " " << calo_cell.energy() << "]" << endl;
    ht->SetBinContent(cell_address.ix(), cell_address.iy(), calo_cell.energy());
  }
  ht->Draw("colZ");
  c->Update();
  c->Print("transverse.pdf");
}
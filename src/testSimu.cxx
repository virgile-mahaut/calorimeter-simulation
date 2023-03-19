#include "CaloSimulation.h"
#include "CaloConstants.h"

// #include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TFile.h"
using namespace CalConst;
using namespace std;



void testSimu()
{

  TH1F *hlong = new TH1F("hlong", "test longitudinal",
                      NbLayers, ZMin, ZMax);
                   
  TH2F *htrans = new TH2F("htrans", "test transverse", 
                      NbCellsInXY, XYMin, XYMax,
                      NbCellsInXY, XYMin, XYMax);
  CaloSimulation calo_sim; // call to simulate shower
  calo_sim.SimulateShower(0., 0., 50.);
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
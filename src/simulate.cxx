#include "Event.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TROOT.h"
#include "CaloConstants.h"
using namespace CalConst;

/**
 * @brief simulate a shower in the calorimeter
 * @details 1) generate a random position in the central cell ([-10,0] cm )
 * 2) simulate the shower from the random impact parameter and store cells energy in Event object
 * @param event Event object
 * @param had true to simulate a hadronic jet event, false to simulate an EM jet event
 */
void simulate(Event& event, bool had)
{
  // simulate the event
  float eTrue = 50.;
  event.seteTrue(eTrue); // fixed true energy
  gRandom->SetSeed(0);
  
  // impact on the cell defined by [-10, 0] wrt the centre of the calorimeter
  float x = gRandom->Uniform(XYMin + (XYMax - XYMin) / 2 - (XYMax - XYMin)/float(NbCellsInXY), XYMin + (XYMax - XYMin) / 2);
  float y = gRandom->Uniform(XYMin + (XYMax - XYMin) / 2 - (XYMax - XYMin)/float(NbCellsInXY), XYMin + (XYMax - XYMin) / 2);
  event.setx(x);
  event.sety(y);
  CaloSimulation calo_sim;
  if (had) {
    float f = gRandom->Uniform();
    calo_sim.SimulateHadShower(f, x, y, eTrue);
  }
  else {
    calo_sim.SimulateHadShower(0., x, y, eTrue);
  }
  std::vector<CaloCell> caldata;
  calo_sim.CalorimeterData(caldata);
  event.setCalData(caldata);
}

/**
 * @brief Draw the histogram of longitudinal developpment as well as those of transversal development
 * 
 * @param event 
 */
void make_histogram(Event& event)
{
  TH1F *hl = new TH1F("hlon", "Longitudinal development (1st event)",
                      NbLayers, ZMin, ZMax);
                   
  TH2F *ht = new TH2F("htra", "Transverse development (1st event)", 
                      NbCellsInXY, XYMin, XYMax,
                      NbCellsInXY, XYMin, XYMax);
  for (long unsigned int i=0; i<event.calData().size(); i++){
    CaloCell calo_cell = event.calData().at(i);
    CellAddress cell_address = calo_cell.address();
    hl->AddBinContent(cell_address.layer() + 1, calo_cell.energy());
    if (cell_address.layer() == 0){
      ht->SetBinContent(cell_address.ix() + 1, cell_address.iy() + 1, calo_cell.energy());
    }
  }
}

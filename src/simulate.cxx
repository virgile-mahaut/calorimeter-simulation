#include "Event.h"
#include "TRandom.h"
#include "TH1F.h"
#include "TH2F.h"
#include "CaloConstants.h"
using namespace CalConst;

void simulate(Event& event)
{
  // simulate the event
  float eTrue = 50.;
  event.seteTrue(eTrue); // fixed true energy
  gRandom->SetSeed(0);
  float x = gRandom->Uniform(XYMin/2., XYMax/2.);
  float y = gRandom->Uniform(XYMin/2., XYMax/2.);
  // float x = gRandom->Gaus((XYMin + XYMax) / 2., sqrt((pow(XYMax, 2) - pow(XYMin, 2)) / 12));
  // float y = gRandom->Gaus((XYMin + XYMax) / 2., sqrt((pow(XYMax, 2) - pow(XYMin, 2)) / 12));
  event.setx(x);
  event.sety(y);
  CaloSimulation calo_sim;
  calo_sim.SimulateShower(x, y, eTrue);
  std::vector<CaloCell> caldata;
  calo_sim.CalorimeterData(caldata);
  event.setCalData(caldata);
}

void make_histogram(Event& event)
{
  TH1F *hl = new TH1F("hl", "Longitudinal development (1st event)",
                      NbLayers, ZMin, ZMax);
                   
  TH2F *ht = new TH2F("ht", "Transverse development (1st event)", 
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

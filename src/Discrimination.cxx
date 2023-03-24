#include "TF1.h"
#include "TH1F.h"
#include "Event.h"
#include "CaloConstants.h"
using namespace CalConst;

// Cuts chosen for maximizing efficiency x rejection
float a_trans = 8;
float a_long = 7.34;

// threshold for rejection (obtained by trial and error)
float R_tra_threshold = 1 + 0.1;
float R_lon_threshold = 2 + 0.92;


/**
* @brief This function estimates the jet nature of an event
* @details The discrimination between both jet natures is determined by comparing the ratio
* R(x) to values of rejection and efficiency
* @param[in] event Event object.
* @param[out] boolean true if the jet is estimated to be hadronic, false if electromagnetic
*/
bool is_had(Event& event)
{
  TH1F hl("hl","Gaussian z",NbLayers, ZMin, ZMax);
  TH1F ht("ht","Gaussian x",NbCellsInXY, XYMin, XYMax);
  std::vector<CaloCell> caldata = event.calData();
  for (long unsigned int i=0; i<caldata.size(); i++) // treat all the cells
  {
    hl.AddBinContent(caldata.at(i).address().layer() + 1, caldata.at(i).energy_rec());
    // ht.AddBinContent(caldata.at(i).address().ix() + 1, caldata.at(i).energy_rec());
  }
  float efficiency_l = hl.Integral(1, int(a_long / ZSize))
                     / hl.Integral(1,NbLayers);
  float rejection_l = 1. / efficiency_l;
  // float efficiency_t = ht.Integral(NbCellsInXY/2, NbCellsInXY/2 + int( a_trans / XYSize))
  //                    / ht.Integral(NbCellsInXY/2, NbCellsInXY);
  // float rejection_t = 1. / efficiency_t;
  // return (rejection_t > R_tra_threshold);
  return (rejection_l > R_lon_threshold); // best estimate for the moment
  // return (rejection_t > R_tra_threshold && rejection_l > R_lon_threshold);
}
#include <iostream>
#include "CaloCell.h"
#include "CaloGeometry.h"
#include "CaloConstants.h"
using namespace std;
using namespace CalConst;


// assess the validity of CellAddress, CaloCell and CaloGeometry's methods
void testCalo()
{
  // Check whether CellAddress class works well
  cout << "CellAddress tests:\n";

  // boundary conditions
  cout << "boundary conditions: " << "-1 < x < " << NbCellsInXY << " AND " << "-1 < layer < " << NbLayers << endl;
  CellAddress cell_address_invalid1; // empty address
  cout << "cell_address_invalid1" << endl;
  cout << cell_address_invalid1 << endl;
  cout << "m_ix = " << cell_address_invalid1.ix() << ", "
       << "m_iy = " << cell_address_invalid1.iy() << ", "
       << "m_layer = " << cell_address_invalid1.layer() << endl;
  cout << "validity : " << cell_address_invalid1.IsValid() << endl;
  CellAddress cell_address_invalid2(1,NbCellsInXY,0); // y out of bound
  cout << "cell_address_invalid2(1," << NbCellsInXY << ",0)" << endl;
  cout << cell_address_invalid2 << endl;
  cout << cell_address_invalid2.IsValid() << endl;
  CellAddress cell_address_invalid3(1,38,NbLayers); // z (layer) out of bound
  cout << "cell_address_invalid3(1,38," << NbLayers << ")" << endl;
  cout << cell_address_invalid3 << endl;
  cout << cell_address_invalid3.IsValid() << endl;
  CellAddress cell_address_valid(1,2,0);
  cout << "cell_address_valid(1,2,0)" << endl;
  cout << cell_address_valid << endl;
  cout << cell_address_valid.IsValid() << endl;

  CellAddress cell_address1(1, 1, 2);
  CellAddress cell_address2(1, 1, 3);
  CellAddress cell_address3(1, 2, 3);
  CellAddress cell_address4(2, 1, 1);
  cout << cell_address1 << " < " << cell_address2 << " (bool): " << (cell_address1 < cell_address2) << endl;
  cout << cell_address1 << " < " << cell_address3 << " (bool): " << (cell_address1 < cell_address3) << endl;
  cout << cell_address4 << " > " << cell_address1 << " (bool): " << (cell_address4 > cell_address1) << endl;
  cout << cell_address2 << " < " << cell_address1 << " (bool): " << (cell_address2 < cell_address1) << endl;
  cout << endl;

  // Check whether CaloCell class works as expected
  cout << "CaloCell tests:\n";

  CaloCell calo_cell(cell_address_valid, 1);
  cout << "calo_cell(cell address=cell_address_valid, energy=1)" << endl;
  cout << "cell address (calo_cell.address()): " << calo_cell.address() << endl;
  cout << "energy (calo_cell.energy()): " << calo_cell.energy() << endl;

  cout << endl;


  // check whether CaloGeometry class works as expected
  cout << "CaloGeometry tests: \n";

  // invalid coordinates -> cell should not be filled
  double xyz[3] = {1., 30., NbLayers};
  CellAddress cell_address_geo;
  cout << "cell_address_geo: " << cell_address_geo;
  cout << "xyz = [" << xyz[0] << ", " << xyz[1] << ", " << xyz[2] << "]" << endl;
  cout << "CaloGeometry::IsInside(xyz, cell_adress_geo) (bool):" << CaloGeometry::IsInside(xyz, cell_address_geo) << endl;
  cout << "cell_address_geo: " << cell_address_geo << endl;

  // valid coordinates -> cell should be filled
  xyz[2] = 0.;
  cout << "xyz = [" << xyz[0] << ", " << xyz[1] << ", " << xyz[2] << "]" << endl;
  cout << "CaloGeometry::IsInside(xyz, cell_address_geo) (bool):" << CaloGeometry::IsInside(xyz, cell_address_geo) << endl;
  cout << "cell_address_geo: " << cell_address_geo << endl;
  cout << "CaloGeometry::xCentre(cell_address_geo): " << CaloGeometry::xCentre(cell_address_geo) << endl;
  cout << "CaloGeometry::yCentre(cell_address_geo): " << CaloGeometry::yCentre(cell_address_geo) << endl;
  cout << endl;
}
#include <iostream>
#include "CaloCell.h"
#include "CaloGeometry.h"
#include "CaloConstants.h"
using namespace std;
using namespace CalConst;

void test()
{
  // Check whether CellAddress class works well
  // boundary conditions
  cout << "boundary conditions: " << "-1 < x < " << NbCellsInXY << " AND " << "-1 < layer < " << NbLayers << endl;
  CellAddress cell_address_invalid1;
  cout << "cell_address_invalid1" << endl;
  cout << cell_address_invalid1 << endl;
  cout << "m_ix = " << cell_address_invalid1.ix() << ", "
       << "m_iy = " << cell_address_invalid1.iy() << ", "
       << "m_layer = " << cell_address_invalid1.layer() << endl;
  cout << "validity : " << cell_address_invalid1.IsValid() << endl;
  CellAddress cell_address_invalid2(1,40,0);
  cout << "cell_address_invalid2(1,40,0)" << endl;
  cout << cell_address_invalid2 << endl;
  cout << cell_address_invalid2.IsValid() << endl;
  CellAddress cell_address_invalid3(1,38,1);
  cout << "cell_address_invalid3(1,38,1)" << endl;
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

  // Check whether CaloCell class works well
  CaloCell calo_cell(cell_address_valid, 1);
  cout << "calo_cell(cell address=cell_address_valid, energy=1)" << endl;
  cout << "cell address (calo_cell.address()): " << calo_cell.address() << endl;
  cout << "energy (calo_cell.energy()): " << calo_cell.energy() << endl;


  // check whether CaloGeometry class works well
  double xyz[3] = {1., 30., 1.};
  CellAddress cell_address_geo;
  cout << "cell_address_geo: " << cell_address_geo;
  cout << "xyz = [" << xyz[0] << ", " << xyz[1] << ", " << xyz[2] << "]" << endl;
  cout << "CaloGeometry::IsInside(xyz, cell_adress_geo) (bool):" << CaloGeometry::IsInside(xyz, cell_address_geo) << endl;
  cout << "cell_address_geo: " << cell_address_geo << endl;

  xyz[2] = 0.;
  cout << "xyz = [" << xyz[0] << ", " << xyz[1] << ", " << xyz[2] << "]" << endl;
  cout << "CaloGeometry::IsInside(xyz, cell_address_geo) (bool):" << CaloGeometry::IsInside(xyz, cell_address_geo) << endl;
  cout << "cell_address_geo: " << cell_address_geo << endl;
  cout << "CaloGeometry::xCentre(cell_address_geo): " << CaloGeometry::xCentre(cell_address_geo) << endl;
  cout << "CaloGeometry::yCentre(cell_address_geo): " << CaloGeometry::yCentre(cell_address_geo) << endl;
}
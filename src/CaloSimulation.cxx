#include "CaloSimulation.h"
#include "CaloConstants.h"
#include "CaloGeometry.h"
#include <vector>

using namespace std;
using namespace CalConst;

CaloSimulation::void CalorimeterData(vector<CaloCell>& caldata) const{
    for (int ix=0; ix < NbCellsInXY; ix++){
        for (int iy=0; iy <NbCellsInXY; iy++){
            for (int iz=0; iz<NbLayers; iz++) {
                CellAd = CellAddress(ix,iy,iz);
                CalCell = CaloCell(CellAd, 0.);
                caldata.push_back(CalCell);
            }
        }
     }
}

CaloSimulation::void SimulateShower(float x, float y, float energy){


}

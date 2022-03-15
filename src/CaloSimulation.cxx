#include "CaloSimulation.h"
#include "CaloConstants.h"
#include "CaloGeometry.h"
#include <vector>

using namespace std;
using namespace CalConst;

CaloSimulation::void CalorimeterData(vector<CaloCell>& caldata) const{
    for (int x=0; x< NbCellsInXY; x++){
        for (int y=0; y<NbCellsInXY; y++){
            for (int z=0; z<NbLayers; z++) {
                CellAd = CellAddress(x-NbCellsInXY/2.,y-NbCellsInXY/2.,z);
                CalCell = CaloCell(CellAd, 0.);
                caldata.push_back();
            }
        }
     }
}

CaloSimulation::void SimulateShower(float x, float y, float energy){


}

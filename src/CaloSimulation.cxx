#include "CaloSimulation.h"
#include "CaloConstants.h"
#include "CaloGeometry.h"
#include "CaloCell.h"
#include <vector>
#include <math.h>

using namespace std;
using namespace CalConst;

CaloSimulation::void CalorimeterData(vector<CaloCell>& caldata) const{
    for (int iz=0; iz < NbLayers; iz++){
        for (int iy=0; iy <NbCellsInXY; iy++){
            for (int ix=0; ix <NbCellsInXY; ix++) {
                CellAd = CellAddress(ix,iy,iz);
                CalCell = CaloCell(CellAd, 0.);
                caldata.push_back(CalCell);
            }
        }
     }
}

CaloSimulation::int caldataIndex(int ix, int iy, int iz) const{
    return iz*NbCellsInXY*NbCellsInXY + iy*NbCellsInXY + ix;
}

CaloSimulation::void SimulateShower(float x, float y, float energy){
    // Function for longitudinal development

    float Func(t){return energy * b * (b*t)**(a-1) * exp(- b*t) / tgamma(a)};
    TF1 *F = new TF1("F", "Func(t)", 0, ZMax/X0);

    // Creation of the calorimeter
    vector<CaloCell> caldata;
    CalorimeterData(caldata);

    // Initialisation : energy at the impact
    double xyz[3];
    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = 0; // the impact is at the front end of the calorimeter
    CellAddress cell_ad = CellAddress();
    IsInside(xyz,cell_ad);
    ix0 = cell_ad.ix();
    iy0 = cell_ad.iy();
    iz0 = cell_ad.layer();
    CaloCell ImpactCell = CaloCell(cell_ad,energy);
    caldata[caldataIndex(ix0,iy0,iz0)] = ImpactCell;

    // Development of the shower
    float zMaxShower = (a - 1) * X0 /b;
    int izMaxShower = int( zMaxShower / ZSize );
    float sigma = MR; // sigma of the gaussian
    while( iz <= izMaxShower ) {
        energy_z = energy - ROOT::Math::IntegratorOneDim::Integral(F, 0, z/X0);
        for(int ix=0; ix < NbCellsInXY; ix++){
            for(int iy=0; iy < NbCellsInXY; iy++){
                caldata[caldataIndex(ix,iy,iz)]
                // recreer celladress; isinside; creer callocell et mettre la calocelld ans caldata
        }

    }

}

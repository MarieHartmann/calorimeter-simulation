#include "CaloSimulation.h"
#include "CaloConstants.h"
#include "CaloGeometry.h"
#include "CaloCell.h"
#include "CellAddress.h"
#include "TF1.h"
#include <vector>
#include <math.h>

using namespace std;
using namespace CalConst;

CaloSimulation::~CaloSimulation(){

}

CaloSimulation::CaloSimulation(){

}

void CaloSimulation::CalorimeterData() {
    for (int iz=0; iz < NbLayers; iz++){
        for (int iy=0; iy <NbCellsInXY; iy++){
            for (int ix=0; ix <NbCellsInXY; ix++) {
                CellAddress CellAd = CellAddress(ix,iy,iz);
                CaloCell CalCell = CaloCell(CellAd, 0.);
                m_caldata.push_back(CalCell);
            }
        }
     }
}

void CaloSimulation::ClearCalorimeter(){
    for (int iz=0; iz < NbLayers; iz++){
        for (int iy=0; iy <NbCellsInXY; iy++){
            for (int ix=0; ix <NbCellsInXY; ix++) {
                int index = caldataIndex(ix,iy,iz);
                m_caldata[index].energy()=0;
            }
        }
    }
}

vector<CaloCell> CaloSimulation::caldata() const{
    return m_caldata;
}

int CaloSimulation::caldataIndex(int ix, int iy, int iz) const{
    return iz*NbCellsInXY*NbCellsInXY + iy*NbCellsInXY + ix;
}

void CaloSimulation::SimulateShower(float x, float y, float energy){
    // Development of the shower
    float zMaxShower = (a - 1) * X0 /b;
    int izMaxShower = int( zMaxShower / ZSize );
    float sigma = MR; // sigma of the gaussian
    int iz = 1;

    // Function for longitudinal development
    TF1 *F = new TF1("F", " [1] * pow(([1]*x),([0]-1)) * exp(- [1]*x) / tgamma([0])");
    F->SetParameters(a,b);
    // Functions for lateral development
    TF1 *GX = new TF1("GX", "gaus(0)", XYMin, XYMax);
    TF1 *GY = new TF1("GY", "gaus(0)", XYMin, XYMax);
    GX->SetParameters(1/sqrt(2*M_PI*sigma), x, sigma);
    GY->SetParameters(1/sqrt(2*M_PI*sigma), y, sigma);

    // Initialisation : energy at the impact
    double xyz[3];
    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = 0; // the impact is at the front end of the calorimeter

    // we get the indices corresponding to the impact
    CellAddress cell_ad = CellAddress();
    CaloGeometry::IsInside(xyz,cell_ad);
    int ix0 = cell_ad.ix();
    int iy0 = cell_ad.iy();
    int iz0 = cell_ad.layer();
    // we add the incident energy in the impact cell
    CaloCell ImpactCell = CaloCell(cell_ad,energy);
    m_caldata[caldataIndex(ix0,iy0,iz0)] = ImpactCell;

    // while the particle is in the calo and has enough energy
    while( iz <= izMaxShower && iz <= NbLayers ) {
        // compute the energy loss at the considered layer
        float DeltaE = F->Integral(0, iz*NbLayers/X0);
        // and remove it from the initial energy
        float energy_z = energy - DeltaE * energy;
        // loop over all cells in the layer
        for(int ix=0; ix < NbCellsInXY; ix++){
            for(int iy=0; iy < NbCellsInXY; iy++){
                // compute the energy in the cell
                CellAddress address = m_caldata[caldataIndex(ix,iy,iz)].address();
                double DeltaGX = GX->Integral(ix*XYSize, (ix+1)*XYSize);
                double DeltaGY = GY->Integral(iy*XYSize, (iy+1)*XYSize);
                float NewEnergy = energy_z * DeltaGX * DeltaGY;
                // and add it to the calorimeter
                CaloCell NewCell = CaloCell(address,NewEnergy);
                m_caldata[caldataIndex(ix,iy,iz)] = NewCell;
            }
        }
        iz = iz +1;
    }
    delete GX;
    delete GY;
    delete F;
}

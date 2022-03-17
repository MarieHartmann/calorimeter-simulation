#include "CaloSimulation.h"
#include "CaloConstants.h"
#include "CaloGeometry.h"
#include "CaloCell.h"
#include "CellAddress.h"
#include "TF1.h"
#include <vector>
#include <math.h>
#include <iostream>

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
        for (int iy=0; iy < NbCellsInXY; iy++){
            for (int ix=0; ix < NbCellsInXY; ix++) {
                int index = caldataIndex(ix,iy,iz);
                m_caldata[index].setEnergy(0.);
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
    int iz = 0;
    float ParticleEnergy = energy;
    float EnergyDeposited = 0.;

    // Function for longitudinal development
    TF1 *F = new TF1("F", " [1] * pow(([1]*x),([0]-1)) * exp(- [1]*x) / tgamma([0]) ");
    F->SetParameters(a,b);
    // Functions for lateral development
    TF1 *GX = new TF1("GX", "gaus(0)", XYMin, XYMax);
    TF1 *GY = new TF1("GY", "gaus(0)", XYMin, XYMax);
    GX->SetParameters(1/(sqrt(2*M_PI)*sigma), x, sigma);
    GY->SetParameters(1/(sqrt(2*M_PI)*sigma), y, sigma);


    // while the particle is in the calo and has enough energy
    while( iz <= izMaxShower && iz <= NbLayers ) {
        // compute the energy loss at the considered layer
        EnergyDeposited = F->Integral(iz*ZSize/X0, (iz+1)*ZSize/X0)*ParticleEnergy;
        ParticleEnergy = ParticleEnergy - EnergyDeposited;

        // loop over all cells in the layer
        for(int ix = 0; ix < NbCellsInXY; ix++){
            for(int iy = 0; iy < NbCellsInXY; iy++){
                // compute the energy deposited in the cell
                CellAddress address = m_caldata[caldataIndex(ix,iy,iz)].address();
                double DeltaGX = GX->Integral(ix*XYSize+XYMin, (ix+1)*XYSize+XYMin, 1e-12);
                double DeltaGY = GY->Integral(iy*XYSize+XYMin, (iy+1)*XYSize+XYMin, 1e-12);
                float NewEnergy = EnergyDeposited * DeltaGX * DeltaGY;
                // and add it to the calorimeter
                CaloCell NewCell = CaloCell(address, NewEnergy);
                m_caldata[caldataIndex(ix,iy,iz)] = NewCell;
            }
        }
        iz = iz +1;
    }

    delete GX;
    delete GY;
    delete F;
}

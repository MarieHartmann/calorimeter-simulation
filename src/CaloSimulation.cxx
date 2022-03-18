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
    float sigma = MR; // sigma of the gaussian
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

    for( int iz = 0; iz < NbLayers; iz++ ) {
        // compute the energy loss at the considered layer
        EnergyDeposited = F->Integral(iz*ZSize/X0, (iz+1)*ZSize/X0, 1e-12)*energy;
        ParticleEnergy = ParticleEnergy - EnergyDeposited;

        // if the particle has not enough energy, we stop the shower
        if(ParticleEnergy < 0 ){
          break;
        }

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
    }
    delete GX;
    delete GY;
    delete F;
}

void CaloSimulation::SimulateHadShower(float x, float y, float energy, float f){
    // Development of the shower
    float sigma = MR; // sigma of the electromagnetic gaussian
    float sigmaHad = MRHad; // sigma of the hadronic gaussian
    float ParticleEnergy = energy;
    float EnergyDepositedHad = 0.;
    float EnergyDepositedEm = 0.;
    float EnergyDeposited = 0.;

    // Function for longitudinal development
    TF1 *FEm = new TF1("FEm", " [1] * pow(([1]*x),([0]-1)) * exp(- [1]*x) / tgamma([0]) ");
    TF1 *FHad = new TF1("FHad", " [1] * pow(([1]*x),([0]-1)) * exp(- [1]*x) / tgamma([0]) ");
    FEm->SetParameters(a,b);
    FHad->SetParameters(aHad,bHad);
    // Functions for lateral development
    TF1 *GXEm = new TF1("GXEm", "gaus(0)", XYMin, XYMax);
    TF1 *GYEm = new TF1("GYEm", "gaus(0)", XYMin, XYMax);
    TF1 *GXHad = new TF1("GXHad", "gaus(0)", XYMin, XYMax);
    TF1 *GYHad = new TF1("GYHad", "gaus(0)", XYMin, XYMax);
    GXEm->SetParameters(1/(sqrt(2*M_PI)*sigma), x, sigma);
    GYEm->SetParameters(1/(sqrt(2*M_PI)*sigma), y, sigma);
    GXHad->SetParameters(1/(sqrt(2*M_PI)*sigmaHad), x, sigmaHad);
    GYHad->SetParameters(1/(sqrt(2*M_PI)*sigmaHad), y, sigmaHad);



    for( int iz = 0; iz < NbLayers; iz++ ) {
        // compute the energy loss at the considered layer
        EnergyDepositedEm = FEm->Integral(iz*ZSize/X0, (iz+1)*ZSize/X0, 1e-12)*energy;
        EnergyDepositedHad = FHad->Integral(iz*ZSize/L, (iz+1)*ZSize/L, 1e-12)*energy;
        //the energy is a mixture of EM and hadronic contribution with weigth f
        EnergyDeposited = f * EnergyDepositedEm + (1-f)*EnergyDepositedHad;
        ParticleEnergy = ParticleEnergy - EnergyDeposited;

        // if the particle has not enough energy, we stop the shower
        if(ParticleEnergy < 0 ){
          break;
        }

        // loop over all cells in the layer
        for(int ix = 0; ix < NbCellsInXY; ix++){
            for(int iy = 0; iy < NbCellsInXY; iy++){
                // compute the energy deposited in the cell
                CellAddress address = m_caldata[caldataIndex(ix,iy,iz)].address();
                double DeltaGXEm = GXEm->Integral(ix*XYSize+XYMin, (ix+1)*XYSize+XYMin, 1e-12);
                double DeltaGYEm = GYEm->Integral(iy*XYSize+XYMin, (iy+1)*XYSize+XYMin, 1e-12);
                double DeltaGXHad = GXHad->Integral(ix*XYSize+XYMin, (ix+1)*XYSize+XYMin, 1e-12);
                double DeltaGYHad = GYHad->Integral(iy*XYSize+XYMin, (iy+1)*XYSize+XYMin, 1e-12);
                //the energy is a mixture of EM and hadronic contribution with weigth f
                float NewEnergy = EnergyDeposited * ( f * DeltaGXEm * DeltaGYEm + (1-f) * DeltaGXHad * DeltaGYHad );
                // and add it to the calorimeter
                CaloCell NewCell = CaloCell(address, NewEnergy);
                m_caldata[caldataIndex(ix,iy,iz)] = NewCell;
            }
        }
    }

    delete GXHad;
    delete GXEm;
    delete GYEm;
    delete GYHad;
    delete FEm;
    delete FHad;
}

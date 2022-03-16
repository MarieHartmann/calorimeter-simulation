#include "CaloSimulation.h"
#include "CaloConstants.h"
#include "CaloGeometry.h"
#include "CaloCell.h"
#include "CellAddress.h"
#include "TF1.h"
#include "TH2.h"
#include <vector>
#include <math.h>


using namespace std;
using namespace CalConst;

void CaloSimulation::CalorimeterData(vector<CaloCell>& caldata) const{
    for (int iz=0; iz < NbLayers; iz++){
        for (int iy=0; iy <NbCellsInXY; iy++){
            for (int ix=0; ix <NbCellsInXY; ix++) {
                CellAddress CellAd = CellAddress(ix,iy,iz);
                CaloCell CalCell = CaloCell(CellAd, 0.);
                caldata.push_back(CalCell);
            }
        }
     }
}

int CaloSimulation::caldataIndex(int ix, int iy, int iz) const{
    return iz*NbCellsInXY*NbCellsInXY + iy*NbCellsInXY + ix;
}

float CaloSimulation::EnergyEvolution(float t) {
  return b * pow((b*t),(a-1)) * exp(- b*t) / tgamma(a);
}

void CaloSimulation::SimulateShower(float x, float y, float energy){
    // Development of the shower
    float zMaxShower = (a - 1) * X0 /b;
    int izMaxShower = int( zMaxShower / ZSize );
    float sigma = MR; // sigma of the gaussian
    int iz = 0;

    // Function for longitudinal development
    TF1 *F = new TF1("F", "energy * CaloSimulation::EnergyEvolution(t)", 0, ZMax/X0);
    // Functions for lateral development
    TF1 *GX = new TF1("GX", "gaus(0)", XYMin, XYMax);
    TF1 *GY = new TF1("GY", "gaus(0)", XYMin, XYMax);
    GX->SetParameters(1/sqrt(2*M_PI*sigma), x, sigma);
    GY->SetParameters(1/sqrt(2*M_PI*sigma), y, sigma);

    // Creation of the calorimeter
    vector<CaloCell> caldata;
    CalorimeterData(caldata);

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
    caldata[caldataIndex(ix0,iy0,iz0)] = ImpactCell;

    // while the particle is in the calo and has enough energy
    while( iz <= izMaxShower && iz <= NbLayers ) {
        // compute the energy difference between 2 layers
        float DeltaE = F->Integral(0, iz*NbLayers/X0);
        float energy_z = energy - DeltaE;
        // loop over all cells in the layer
        for(int ix=0; ix < NbCellsInXY; ix++){
            for(int iy=0; iy < NbCellsInXY; iy++){
                // and add the energy to the cell
                CellAddress address = caldata[caldataIndex(ix,iy,iz)].address();
                float NewEnergy = energy_z * GX->Eval(ix*XYSize) * GY->Eval(iy*XYSize) * XYSize * XYSize;
                CaloCell NewCell = CaloCell(address,NewEnergy);
                caldata[caldataIndex(ix,iy,iz)] = NewCell;
            }
        }
        iz++;
    }

////////////////////////////////////////////////////////////////////////////////
    TH2 *hist2D = new TH2F("hist2D", "First layer", NbCellsInXY, 0, NbCellsInXY, NbCellsInXY, 0, NbCellsInXY);
    for( int i=0; i<NbCellsInXY*NbCellsInXY; i++ ){
        hist2D->Fill(caldata[i].address().ix(), caldata[i].address().iy(), caldata[i].energy());
    }
    hist2D->Draw();
////////////////////////////////////////////////////////////////////////////////
}

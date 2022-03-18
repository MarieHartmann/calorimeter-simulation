////////////////////////////////////////////////////////////////////////
//
//             A simple example with a ROOT tree
//             =================================
//
//  This program creates :
//    - a ROOT file
//    - a tree
// One possible argument : number of events
//   ---Running/Linking instructions----
//  This program consists of the following files and procedures.
//    - Event.h event class description
//    - Event.C event class implementation
//    - MainEvent.C the main program to demo this class might be used (this file)
//
//   ---Analyzing the event.root file with the interactive root
//        example of a simple session
//   Root > TFile f("Event.root")
//   Root > eventTree.Draw("eTrue") // histogram true x
//   Root > eventTree.Draw("eReco:eTrue", "eventNumber<10") // histogram E reco vs E true for first 10 events
//
////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>

#include "TFile.h"
#include "TRandom3.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2.h"
#include "TStopwatch.h"

#include "Event.h"
#include "CellAddress.h"
#include "CaloCell.h"
#include "CaloGeometry.h"
#include "CaloConstants.h"
#include "CaloSimulation.h"

using namespace std;
using namespace CalConst;

void reconstruct(Event& event);
void simulate(Event& event, CaloSimulation& Calorimeter, float xTrue, float yTrue);
void ana_simu(const Event& event, CaloSimulation& Calorimeter);

//______________________________________________________________________________
int main(int argc, char **argv)
{
    // By default create 400 events.
    int nEventsMax = 400;
    // If command line argument provided, take it as max number of events.
    if (argc > 1) nEventsMax = atoi(argv[1]);

    // Creation of the calorimeter
    CaloSimulation Calorimeter;
    Calorimeter.CalorimeterData();

    // Create a new ROOT binary machine independent file.
    // Note that this file may contain any kind of ROOT objects, histograms,
    // pictures, graphics objects, detector geometries, tracks, events, etc..
    // This file is now becoming the current directory.
    TFile outFile("Event.root", "RECREATE");

    // Create a ROOT Tree and the branches to be written.
    // The instruction "Branch" tells ROOT that the value stored in this variable
    // should be written in the tree when the TTree::Fill() method is called.
    // The first arg of Branch is the name given in the Tree, the second is the
    // address of the variable to be written.
    // !!! You should add similar groups of lines if you want to store other
    // variables in the output tree.
    TTree outTree("eventTree", "Calo sim root tree");
    int eventNumber;
    float eTrue, eReco, eRecoBiais;
    float xReco, yReco;
    float xTrue, yTrue;

    // Initialization of the histograms (they will be accesible from the tree)
    TH1F* h = new TH1F("h", "Calorimeter resolution", 100, -3., 3.);
    TH1F* g = new TH1F("g", "Calorimeter resolution with biais", 100, -5., 5.);
    TH2* hist2D = new TH2F("hist2D", "Last layer", NbCellsInXY, 0, NbCellsInXY, NbCellsInXY, 0, NbCellsInXY);
    TH1* hist1DEnergyZ = new TH1F("hist1DEnergyZ", "Energy deposited per layers", NbLayers, 0., NbLayers);
    TH1* hist1DEnergyX = new TH1F("hist1DEnergyX", "Energy projection on X", NbCellsInXY, 0, NbCellsInXY);
    TH1* hist1DEnergyY = new TH1F("hist1DEnergyY", "Energy projection on Y", NbCellsInXY, 0, NbCellsInXY);

    // Create TreeBranches
    outTree.Branch("Transverse energy representation ", &hist2D);
    outTree.Branch("Energy projection on X", &hist1DEnergyX);
    outTree.Branch("Energy projection on Y", &hist1DEnergyY);
    outTree.Branch("Longitudinal energy representation", &hist1DEnergyZ);
    outTree.Branch("eventNumber", &eventNumber);
    outTree.Branch("eTrue", &eTrue);
    outTree.Branch("eReco", &eReco);
    outTree.Branch("eRecoBiais", &eRecoBiais);
    outTree.Branch("CaloRes", &h);
    outTree.Branch("CaloResBiais", &g);
    outTree.Branch("xReco", &xReco);
    outTree.Branch("yReco", &yReco);
    outTree.Branch("xTrue", &xTrue);
    outTree.Branch("yTrue", &yTrue);



//////////////////////////////////////////////////////
    // Test of the CellAdress class
    CellAddress cell_ad1, cell_ad2;
    cell_ad1 = CellAddress(1,1,1);
    cell_ad2 = CellAddress(5,1,1);

    cout << "Is address valid ? " << cell_ad1.IsValid() << endl;
    cout << "Is address valid ? " << cell_ad2.IsValid() << endl;
    cout << "X coordinate of the cell " << cell_ad1.ix() << endl;

    // Test of the CaloCell class
    CaloCell cell1, cell2;
    cell1 = CaloCell(cell_ad1, 10);
    cell2 = CaloCell(cell_ad2, 5);

    cout << "Energy = " << cell1.energy() << endl;
    cout << "Energy = " << cell2.energy() << endl;
    cout << "Is address valid ? " << cell1.address().IsValid() << endl;
    cout << "X coordinate of the cell " << cell1.address().ix() << endl;

    // Test of the CaloGeometry class
    double xyz[3];
    CellAddress cell_ad3 = CellAddress();
    xyz[0] =-1.06; //we expect Xcenter -1 and ix = -10
    xyz[1] = 0.06; //we expect Ycenter 0.1 and iy = 1
    xyz[2] = 0.; //we expect layers = 0

    cout << "Is inside calorimeter ? " << CaloGeometry::IsInside(xyz, cell_ad3) << endl;
    cout << "Coordinates " << cell_ad3.ix() << " "
                           << cell_ad3.iy() << " "
                           << cell_ad3.layer() << endl;
    cout << "Xcenter " << CaloGeometry::xCentre(cell_ad3) << endl;
    cout << "YCenter " << CaloGeometry::yCentre(cell_ad3) << endl;


///////////////////////////////////////////////////////

    // Create a dummy event that will be build in the loop.
    Event event;

    // Loop over the events.
    for (eventNumber = 0; eventNumber < nEventsMax; eventNumber++) {
        if (eventNumber % 100 == 0) {
            // Just to check everything is going smoothly.
            cout << "Doing event: " << eventNumber << endl;
        }

        // initialize event
        event.build(eventNumber);

        // draw randomly the impact point in the calorimeter
        //xTrue = gRandom->Uniform(XYMax - XYMin) + XYMin;
        //yTrue = gRandom->Uniform(XYMax - XYMin) + XYMin;

        // draw randomly the impact point in a particular cell
        xTrue = gRandom -> Uniform(0.1) - 0.1;
        yTrue = gRandom -> Uniform(0.1) - 0.1;

        // simulation
        simulate(event, Calorimeter, xTrue, yTrue);
        ana_simu(event, Calorimeter);

        // reconstruction
        reconstruct(event);

        eTrue = event.eTrue();
        eReco = event.eReco();
        eRecoBiais = event.eRecoBiais();

        //histogram describing the calorimeter resolution
        //it matches the distribution used in reconstruct.cxx
        //flat, between -0.5 and 0.5
        h->Fill(eReco-eTrue);
        h->Fit("gaus");
        //histogram discribing the biaised calorimeter resolution
        //We find the 0.1GeV biais back
        g->Fill(eRecoBiais-eTrue);
        g->Fit("gaus"); // Prepare to fill the output tree.

        // Fill the histograms
        int LayerToPlot = 1;  //choose the layer for the 2D plot
        float MaxEnergy = 0.; //parameters used to determine the impact cell
        int iMaxEnergy = 0;
        vector<CaloCell> CaloElements = Calorimeter.caldata();

        //loop over all the cells
        for (int iz=0; iz < NbLayers; iz++){
            for (int iy=0; iy < NbCellsInXY; iy++){
                for (int ix=0; ix < NbCellsInXY; ix++) {
                    int i = Calorimeter.caldataIndex(ix, iy, iz); // get the indice of the cell in the vector
                    float EnergyCell = CaloElements[i].energy();

                    hist1DEnergyZ -> Fill(iz, EnergyCell);
                    hist1DEnergyX -> Fill(ix, EnergyCell);
                    hist1DEnergyY -> Fill(iy, EnergyCell);

                    if (iz==LayerToPlot){
                      hist2D->SetBinContent(CaloElements[i].address().ix()+1, CaloElements[i].address().iy()+1, EnergyCell);
                    }
                    //we only look at the first layer to determine the impact cell
                    if (iz==0){
                        if (EnergyCell > MaxEnergy){
                            MaxEnergy = EnergyCell;
                            iMaxEnergy = i;
                        }
                    }
                }
            }
        }

        xReco = CaloElements[iMaxEnergy].address().ix() * XYSize+XYMin;
        yReco = CaloElements[iMaxEnergy].address().iy() * XYSize+XYMin;

        outTree.Fill(); // Fill the tree.

        Calorimeter.ClearCalorimeter();


    } // End event loop

    outFile.cd(); // Make sure we are in the outupt file.
    outFile.Write(); // Write all current in the current directory.
    outTree.Print();
    outFile.Close();




    return 0;
}

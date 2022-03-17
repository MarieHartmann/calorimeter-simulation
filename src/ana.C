

void ana()
{
    // macro to plot distributions from the Event tree
    TFile* inFile = TFile::Open("Event.root");
    TTree* inTree = (TTree*)inFile->Get("eventTree");
    cout <<  inFile << endl; // check the pointer to the root file
    cout <<  inTree << endl; // check the pointer to the the tree
    cout << "Number of Entries in tree : " << inTree->GetEntries() << endl;
    inTree->Draw("eTrue");
}

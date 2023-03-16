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
#include "TStopwatch.h"

#include "CellAddress.h"
#include "Event.h"

using namespace std;

void reconstruct(Event& event);
void simulate(Event& event);
void ana_simu(const Event& event);

void test();

//______________________________________________________________________________
int main(int argc, char **argv)
{
    // By default create 400 events.
    int nEventsMax = 400;
    // If command line argument provided, take it as max number of events.
    if (argc > 1) nEventsMax = atoi(argv[1]);
    
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
    float eTrue;
    float eReco;
    float eRecoBias;
    outTree.Branch("eventNumber", &eventNumber);
    outTree.Branch("eTrue", &eTrue);
    outTree.Branch("eReco", &eReco);
    outTree.Branch("eRecoBias", &eRecoBias);
    
    test();

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

        // simulation
        simulate(event);
        ana_simu(event);

        // reconstruction
        reconstruct(event);

        // Prepare to fill the output tree.
        eTrue = event.eTrue();
        eReco = event.eReco();
        eRecoBias = event.eRecoBias();
        outTree.Fill(); // Fill the tree.
    } // End event loop

    outFile.cd(); // Make sure we are in the outupt file.
    outFile.Write(); // Write all current in the current directory.
    outTree.Print();

    outFile.Close();
    return 0;
}

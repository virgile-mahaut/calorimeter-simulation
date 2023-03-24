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
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TMath.h"

#include "CellAddress.h"
#include "Event.h"

using namespace std;

void reconstruct_fit(Event& event);
void reconstruct_barycentre(Event& event);
void simulate(Event& event, bool had);
bool is_had(Event& event);

void testCalo();
void testSimu();
void testHadSimu();
void display_rejection_efficiency();
void make_histogram(Event& event);

void s_shape_display(TGraph *gr_sshape_x_fit, TGraph *gr_sshape_y_fit,
                     TGraph *gr_sshape_x_bar, TGraph *gr_sshape_y_bar,
                     TF1 *&f_sshape_x_fit, TF1 *&f_sshape_y_fit,
                     TF1 *&f_sshape_x_bar, TF1 *&f_sshape_y_bar);

//______________________________________________________________________________
int main(int argc, char **argv)
{
  // By default create 400 events.
  int nEventsMax = 400;

  // Should be set to true if one aims to evaluate performance of jet nature (EM or hadronic) determination
  // false otherwise (only EM jet)
  bool testDiscrimination;
  bool hadronic; // Real nature of the jet (true if hadronic, false if EM)
  // assess the performance of discrimination function
  int success = 0;        // number of times the algorithm has successfully identified the jet nature
  int false_positive = 0; // number of times the algorithm has identified a hadronic jet when it is actually electromagnetic
  int false_negative = 0; // number of times the algorithm has identified an electromagnetic jet when it is actually hadronic

  // If command line argument provided, take it as max number of events.
  if (argc > 1) nEventsMax = atoi(argv[1]);

  int temp;
  printf("Do you want to evaluate discrimination (jet identification) ? (1 or 0)");
  scanf("%d", &temp);
  testDiscrimination = temp;
    
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
  float xTrue;
  float yTrue;
  float xRecoFit;
  float yRecoFit;
  float xRecoBar;
  float yRecoBar;
  outTree.Branch("eventNumber", &eventNumber);
  outTree.Branch("eTrue", &eTrue);
  outTree.Branch("eReco", &eReco);
  outTree.Branch("eRecoBias", &eRecoBias);
  outTree.Branch("xTrue", &xTrue);
  outTree.Branch("xRecoFit", &xRecoFit);
  outTree.Branch("xRecoBar", &xRecoBar);
  outTree.Branch("yTrue", &yTrue);
  outTree.Branch("yRecoFit", &yRecoFit);
  outTree.Branch("yRecoBar", &yRecoBar);

  // perform all the tests 
  testCalo();
  testSimu();
  testHadSimu();
  display_rejection_efficiency();

  // Initiate the graphs for the s shape
  TGraph *gr_sshape_x_fit = new TGraph(nEventsMax);
  gr_sshape_x_fit->SetName("sshape_x_fit"); gr_sshape_x_fit->SetTitle("s shape for xReco (fit method)");
  TGraph *gr_sshape_y_fit = new TGraph(nEventsMax);
  gr_sshape_y_fit->SetName("sshape_y_fit"); gr_sshape_y_fit->SetTitle("s shape for yReco (fit method)");
  TGraph *gr_sshape_x_bar = new TGraph(nEventsMax);
  gr_sshape_x_bar->SetName("sshape_x_bar"); gr_sshape_x_bar->SetTitle("s shape for xReco (barycentre method)");
  TGraph *gr_sshape_y_bar = new TGraph(nEventsMax);
  gr_sshape_y_bar->SetName("sshape_y_bar"); gr_sshape_y_bar->SetTitle("s shape for yReco (barycentre method)");

  // Create a dummy event that will be build in the loop.
  Event event;

  // random number generator
  gRandom->SetSeed(0);
  float rand_nb;

  // Loop over the events.
  for (eventNumber = 0; eventNumber < nEventsMax; eventNumber++) {
    if (eventNumber % 100 == 0) {
      // Just to check everything is going smoothly.
      cout << "Doing event: " << eventNumber << endl;
    }

    // initialize event
    event.build(eventNumber);

    // simulation

    if (!(testDiscrimination))
    {
      // purely electromagnetic shower
      hadronic = false;
      simulate(event, false);
    }
    else
    {
      // hadronic shower with 50% probability
      // electromagnetic shower with 50% probability
      rand_nb = gRandom->Uniform(0.,1.);
      hadronic = rand_nb > 0.5;
      simulate(event, hadronic);
    }

    // Test simulation
    // display longitudinal and transverse development for the first event
    if (eventNumber == 0) {
      make_histogram(event);
    }

    // reconstruction
    reconstruct_fit(event);
    reconstruct_barycentre(event);

    if (testDiscrimination)
    {
      // estimate from the reconstructed energy whether the jet is electromagnetic or hadronic
      bool hadronic_estimate = is_had(event);
      if (hadronic_estimate == hadronic) success ++;
      else {
        if (hadronic_estimate) false_positive ++;
        else false_negative ++;
      }
    }
    

    // Prepare to fill the output tree.
    eTrue = event.eTrue();
    eReco = event.eReco();
    eRecoBias = event.eRecoBias();
    xTrue = event.x();
    yTrue = event.y();
    xRecoFit = event.xReco();
    yRecoFit = event.yReco();
    xRecoBar = event.xRecoBar();
    yRecoBar = event.yRecoBar();
    outTree.Fill(); // Fill the tree.

    // compute the s shape
    gr_sshape_x_fit->SetPoint(eventNumber, xRecoFit, xRecoFit - event.x());
    gr_sshape_y_fit->SetPoint(eventNumber, yRecoFit, yRecoFit - event.y());
    gr_sshape_x_bar->SetPoint(eventNumber, xRecoBar, xRecoBar - event.x());
    gr_sshape_y_bar->SetPoint(eventNumber, yRecoBar, yRecoBar - event.y());

  } // End event loop

  // fit the s shape
  TF1 *f_sshape_x_fit; TF1 *f_sshape_y_fit;
  TF1 *f_sshape_x_bar; TF1 *f_sshape_y_bar;
  s_shape_display(gr_sshape_x_fit, gr_sshape_y_fit,
                  gr_sshape_x_bar, gr_sshape_y_bar,
                  f_sshape_x_fit, f_sshape_y_fit,
                  f_sshape_x_bar, f_sshape_y_bar);

  // perform the s shape correction
  // and store the corrected the data in another tree
  Long64_t nentries = outTree.GetEntries();
  TTree *outTreeCorr = outTree.CloneTree(0);
  outTreeCorr->SetName("eventTreeCorr");
  outTreeCorr->SetTitle("Calo sim root tree (s shape corrected)");
  for (Long64_t i=0; i<nentries; i++) {
    outTree.GetEntry(i);
    xRecoFit = xRecoFit - f_sshape_x_fit->GetParameter("amplitude") 
                    * sin(f_sshape_x_fit->GetParameter("period") * (xRecoFit + 5));
    yRecoFit = yRecoFit - f_sshape_y_fit->GetParameter("amplitude") 
                    * sin(f_sshape_y_fit->GetParameter("period") * (yRecoFit + 5));
    xRecoBar = xRecoBar - f_sshape_x_bar->GetParameter("amplitude") 
                    * sin(f_sshape_x_bar->GetParameter("period") * (xRecoBar + 5));
    yRecoBar = yRecoBar - f_sshape_y_bar->GetParameter("amplitude") 
                    * sin(f_sshape_y_bar->GetParameter("period") * (yRecoBar + 5));
    outTreeCorr->Fill();
  }

  outFile.cd(); // Make sure we are in the outupt file.
  outFile.Write(); // Write all current in the current directory.
  outFile.Close();

  if (testDiscrimination)
  {
    // show the performance of the discrimination algorithm (for estimating the nature of the jet)
    cout << "discrimination success rate: " << float(success) / float(nEventsMax) << "\n";
    cout << "rate of type I error (false positive): " << float(false_positive) / float(nEventsMax - success) << "\n";
    cout << "rate of type II error (false negative): " << float(false_negative) / float(nEventsMax - success) << "\n";
  }
}

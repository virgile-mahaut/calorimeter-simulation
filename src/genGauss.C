#include "TMath.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TLegend.h"

float Gauss(float x, float mean, float sigma)
{
  return exp( - pow((x - mean) / sigma, 2) / 2) / (sigma * sqrt(2 * TMath::Pi()));
}

/**
 * @brief generates a random gaussian distribution using Monte Carlo method
 * 
 * @param h histogram where the gaussian distribution is stored
 */
void genGauss(TH1F *h)
{
  // Computes using Monte Carlo method a gaussian distribution of mean=0 and sigma=0.5 over
  // the interval [-2, 2]
  // Draw 10000 numbers according to the gaussian law
  // We use TRandom->Uniform(MAX) to draw numbers
  // uniformly between 0. and MAX

  TRandom3 *rand = new TRandom3(0);
  for(int i=0; i<1000000; i++){
    float x = 0.;
    float y = 0.;
    x = rand->Uniform(-2, 2);
    y = rand->Uniform();
    if (y < Gauss(x, 0, 0.5) * sqrt(2 * TMath::Pi()) * 0.5){
      h->Fill(x);
    }
  }
  delete rand;
}

/**
 * @brief Draw on a same canvas (hGauss) the gaussian distribution from our Monte Carlo estimation 
 * as well as the gaussian distribution obtained from TRandom::Gaus()
 * 
 */
void comparison()
{
  // Display on the same canvas the gaussian distributions respectively obtained thanks to 
  // Monte Carlo generation and TRandom

  TCanvas *c = new TCanvas();

  // first histogram of the gaussiand function is obtained thanks to Monte Carlo generation
  TH1F *hgen = new TH1F("hGauss", "Gaussian distribution", 100, -2., 2.);;
  genGauss(hgen);

  // compute the area under the gaussian for |x| > 3 sigma
  cout << hgen->GetNbinsX() << " " << hgen->GetBinWidth(0) << endl;
  int lower_bound = int((2. + 3. * 0.5) / hgen->GetBinWidth(0));
  int upper_bound = hgen->GetNbinsX();
  cout << "area(|x| > 3 sigma) = " << hgen->Integral(lower_bound, upper_bound) << endl;

  // histogram is normalized
  hgen->Scale(1./(hgen->Integral()));
  hgen->Draw("HIST");

  // second histogram is obtained using the gaussian distribution implemented in TRandom
  TH1F* href = new TH1F("hGaussRef", "Gaussian distribution (ref)", 100, -2., 2.);
  TRandom3 *rand = new TRandom3(0);
  for (int i=0; i < 100000; i++){
    href->Fill(rand->Gaus(0, 0.5));
  }
  delete rand;
  href->Scale(1./(href->Integral()));
  href->SetLineColor(kRed);
  href->Draw("same, HIST");
  TLegend* legend = new TLegend(0.1, 0.7, 0.4, 0.9);
  legend->AddEntry(hgen, "gaussian distribution (Monte-Carlo)");
  legend->AddEntry(href, "gaussian distribution (TRandom)");
  legend->Draw();
  c->Update();
  c->Draw();
}

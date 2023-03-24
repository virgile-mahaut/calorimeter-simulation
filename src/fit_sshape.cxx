#include <cmath>
#include "TGraph.h"
#include "TF1.h"

// sinusoid function used to fit the s shape
double sshape(double *x, double *par)
{
  return par[0] * sin(par[1] * (x[0] + 5));
}

/**
 * @brief fit the s shape using a sinusoid function and store the fitted graphs 
 * into the output file Event.root
 * 
 * @param gr_sshape_x_fit 
 * @param gr_sshape_y_fit 
 * @param gr_sshape_x_bar 
 * @param gr_sshape_y_bar 
 * @param f_sshape_x_fit 
 * @param f_sshape_y_fit 
 * @param f_sshape_x_bar 
 * @param f_sshape_y_bar 
 */
void s_shape_display(TGraph *gr_sshape_x_fit, TGraph *gr_sshape_y_fit,
                     TGraph *gr_sshape_x_bar, TGraph *gr_sshape_y_bar,
                     TF1 *&f_sshape_x_fit, TF1 *&f_sshape_y_fit,
                     TF1 *&f_sshape_x_bar, TF1 *&f_sshape_y_bar)
{
  // define s shape drawing options
  gr_sshape_x_fit->SetMarkerStyle(kRed); gr_sshape_x_fit->SetMarkerStyle(kFullCircle);
  gr_sshape_y_fit->SetMarkerStyle(kRed); gr_sshape_y_fit->SetMarkerStyle(kFullCircle);
  gr_sshape_x_bar->SetMarkerStyle(kRed); gr_sshape_x_bar->SetMarkerStyle(kFullCircle);
  gr_sshape_y_bar->SetMarkerStyle(kRed); gr_sshape_y_bar->SetMarkerStyle(kFullCircle);

  f_sshape_x_fit = new TF1("f_sshape_x_fit",sshape, -10, 0, 2);
  f_sshape_x_fit->SetParameters(0, TMath::Pi() /5.);
  f_sshape_x_fit->SetParNames("amplitude", "period");
  f_sshape_y_fit = new TF1("f_sshape_y_fit",sshape, -10, 0, 2);
  f_sshape_y_fit->SetParameters(0, TMath::Pi() /5.);
  f_sshape_y_fit->SetParNames("amplitude", "period");
  f_sshape_x_bar = new TF1("f_sshape_x_bar",sshape, -10, 0, 2);
  f_sshape_x_bar->SetParameters(0, TMath::Pi() /5.);
  f_sshape_x_bar->SetParNames("amplitude", "period");
  f_sshape_y_bar = new TF1("f_sshape_y_bar",sshape, -10, 0, 2);
  f_sshape_y_bar->SetParameters(0, TMath::Pi() /5.);
  f_sshape_y_bar->SetParNames("amplitude", "period");

  gr_sshape_x_fit->Fit(f_sshape_x_fit, "Q");
  gr_sshape_y_fit->Fit(f_sshape_y_fit, "Q");
  gr_sshape_x_bar->Fit(f_sshape_x_bar, "Q");
  gr_sshape_y_bar->Fit(f_sshape_y_bar, "Q");

  // s shape
  gr_sshape_x_fit->Write();
  gr_sshape_y_fit->Write();
  gr_sshape_x_bar->Write();
  gr_sshape_y_bar->Write();
}
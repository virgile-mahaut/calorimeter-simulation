# Energy deposition positions reconstruction in the calorimeter

The first part of the training has setup the simulation of the information measured by the calorimeter when an electron travels accross its volume. With these informations, one now needs to work on the information reconstruction before using the calorimeter data for physics analyses. First of all, one needs to find the positions in the calorimeter of the incoming particle. This part of work is what would be done in a real calorimeter with real data. For each event (i.e. for each electron entering the calorimeter), the calorimeter measures the energy deposited in each cell.

- Using the calorimeter geometry description (i.e. the position in each cell) write a code to determine the impact position in the calorimeter.
- The result (the reconstructed position), will be saved in the ROOT TTree (eventTree) of the exercise (which is written Event.root), by adding in the Event class two extra variables, xReco and yReco, which represent the reconstruct particle position (and functions to access them), as well as the corresponding branches to be written in MainEvent.cxx. 

For the following, it is important to have well configured calorimeter parameters (mainly the size and division parameters), and shower size, as described in the simulation part.

To simplify the problem, the impact positions of the electron at the entrance of the calorimeter will be generated between [-0.1,0] in X and Y, which means that only one cell will be explored. The results will be studied first of all without noise, nor dead cells. The effect of the noise and dead cells, could be studied in a second step.

In the eventTree of the ROOT file Event.root you will save:
- the reconstruct energy (and the true one)
- the reconstruct position xReco and yReco of this deposit (and the true positions). 

## Determination of the energy and position resolution (X and Y)

## Project the data (Energy, X or Y) in a 1 dimension histogram (TH1).
- Determine the energy and position resolutions fitting the histograms using an adjustment function of your choice, to be optimized (keep the results - parameters, errors, plots,... of the different tried fit). 

NB: use the doc Root!

Some fit examples can be found here.

## S Shape distribution

The S shape is defined by :

Sshape(Xreco) = (X_reco-X_true)

and similarly for the Y variable.

One will start with the X reconstruction for example:
- Plot the X S-shape: for that the ntuple variables can be retrieved in vectors using the ROOT GetV1() and GetV2() functions (other methods are also possible).
- Adjust the S-shape with an appropriate function of your choice (like in the exercise 1, you may have to combine several functions to obtain the better fit).
- Correct using the fitted shape function, the position of reconstructed events, and check that there is no bias anymore.
- Evaluate the new position resolution after the S-shape correction.
- Repeat the S-shape correction for the Y variable. 

## Cell size

To evaluate the influence of the cell size on the S shape, redo the simulation using different cell sizes and repeat the Step 2, in order to determine new resolutions on the corrected positions.

## Optimization of the reconstruction method (optional)

This section can be skipped if you don't have time.

Instead of correcting the reconstructed position with the S-shape, one can try to modify the formula used to estimate the position so that the S-shape correction is minimal: X=Sum(xi Eiα log(Ei)β) / Sum(Eiα log(Ei)β) with α and β the optimized parameters (don't forget the case where Ei=0).

- Code this new formula.
- Perform the following measurements on the position resolution (in X only) with first (α=1/2 β=0) and then (α=0 β=1).
        Resolution before the S-shape correction
        S-shape parametrisation
        Resolution after the S-shape correction 
- Can you find the optimum values of α and β? 

## Subsidiary questions (optional)

This section can be skipped if you don't have time.

- The noise in the calorimeter cannot be neglected. Simulate a Gaussian noise with a RMS value of 5 GeV, every cell being affected in the same way by the noise. Re-evaluate the position resolution.
- A high proportion (10%) of dead cell are present in the calorimeter (the energy deposition is the then null in these cells). The dead cells are the same for all events. Re-evaluate also the resolutions. 
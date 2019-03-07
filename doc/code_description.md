# Code description

- `MainEvent.cxx`: main program, must be modified to include more informations in eventTree. You can use it to test your classes.
- `Event.h`, `Event.cxx`: the main class holding the simulation/reconstruction results. You will probably have to modify a bit this class at some point.
- `simulate.cxx`: simulation (in the skeleton, only the simulated energy is defined). You will have to heavily develop this file.
- `reconstruct.cxx`: reconstruction (in the skeleton, the measured energy is drawn from a distribution centered around the "true" value). You will have to heavily develop this file.
- `CaloConstants.h`: list of useful definitions. You will probably have to modify a bit this file later. Not needed until next step.
- `CaloCell.h`: represent a cell in the calorimeter. The corresponding implementation file (.cxx) has to be written.
- `CaloGeometry.h: implements the geometry of the calorimeter. The corresponding implementation file (.cxx) has to be written.
- `CaloSimulation.h`: proceeds to the simulation of the calorimeter. The corresponding implementation file (.cxx) has to be written.
- `Makefile`: file driving the compilation. Modify really carefully.
- `ana_simu.cxx`: can be used to develop the analysis of your results (graphs...).
- `ana.C`: ROOT macro to create graphs from the event.root file. This is not compiled by the Makefile (standalone ROOT macro).

# Exercises

- Store the resolution `(eReco-eTrue)` in a histogram. Does it match the distribution used in `reconstruct.cxx`?
- In `reconstruct.cxx` replace the uniform distribution with a gaussian (see the [ROOT documentation](https://root.cern.ch/doc/master/index.html) and look for TRandom).
- Fit the resolution with a Gaussian.
- Is the sigma of the Gaussian the expected value? 
- Introduce a new variable in `Event.h` (and `Event.cxx` ): eRecoBias fixed to be equal to eReco+0.1 GeV in `reconstruct.cxx`.
- Fit `eRecoBias-eTrue`
- Do you find the 0.1 GeV bias back ? 
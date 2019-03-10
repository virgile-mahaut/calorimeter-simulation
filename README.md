# CalorimeterSimulation

## Contributors

- [Florent Robinet](mailto:robinet@lal.in2p3.fr)
- Yasmine Amhis
- Antoine Laudrain
- Aurelien Martens

## Scope of the project

The goal of the computer project is to build a 3 steps project as done in many experiments in particle physics:
- Monte-Carlo simulation
- Reconstruction
- Particule identification 

In practice, a simplified calorimeter will be used. The electron and hadron showers is simulated via Monte-Carlo simulation technics. The second step is to reconstruct the particles in the calorimeter and to study their performance (S shape, energy resolution...). The last step of the project is to identify variables to discriminate electrons (signal) and hadrons (background).

## Documentation

- [ROOT](https://root.cern/) libraries are used as a tool box to perform the analysis. See also the [C++ class documentation](https://root.cern.ch/doc/master/index.html)

## Project description

- [Calorimeter description](./doc/calo_description.md)
- [Code description](./doc/code_description.md)
- [Simulation](./doc/simulation.md)
- [S shape distribution](./doc/calo_sshape.md)
- [Electron-pion discrimination](./doc/calo_discrimination.md)
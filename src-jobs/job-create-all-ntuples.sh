#!/bin/bash

#SBATCH --time=03:00:00
#SBATCH --mem=2G

# Go to executable folder
cd ../bin

# Execute all configs
./create-ntuples 0
./create-ntuples 1
./create-ntuples 2
./create-ntuples 3
#!/bin/bash

#SBATCH --time=00:30:00
#SBATCH --mem=2G

simu_target=${1}

# Bin convention : starts from 0
Q2_bin=${2}
Nu_bin=${3}
Zh_bin=${4}

echo "Working on directory " $(pwd)

cd ../bin

./acceptance ${simu_target} ${Q2_bin} ${Nu_bin} ${Zh_bin}

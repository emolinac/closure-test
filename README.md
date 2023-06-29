# closure-test

## How to use?
### Setting what is necessary
1. Copy a background treated pt2 distributions file into the **input-files** folder, with the name **pt2-distributions-nominal.root**.
2. In **include/names.h** modify the values of *sim_dir* and *dat_dir* with the folders where you have your simulations and data, respectively.
### Obtaining the results
1. Go to **src-jobs** and execute:
```
sbatch job-create-all-ntuples.sh
```
2. After the job is ready, modify *simu_target* in **send-jobs-acc** and execute:
```
bash send-jobs-acc.sh
```
3. After obtaining all the results, merge them into a file called **phi-distributions.root** and move it to **input-files**.
4. Execute **weights-routine.sh** in the top folder.

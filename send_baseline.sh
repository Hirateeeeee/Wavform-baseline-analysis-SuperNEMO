#!/bin/sh
#SBATCH --mem 8192M
#SBATCH --licenses sps
#SBATCH --job-name=baseline

cd /sps/nemo/scratch/pli/aussois_tuto_data/root_macro
source /sps/nemo/sw/config/supernemo_profile_1.bash
load_falaise_setup_new_2022_05_12 
/sps/nemo/scratch/pli/aussois_tuto_data/root_macro/marco.exe

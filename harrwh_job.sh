#!/bin/sh

#PBS -N harrwh_job
#PBS -l select=1:ncpus=24:mpiprocs=8
#PBS -l walltime=00:05:00
#PBS -mea
#PBS -M william.harris2@inl.gov
#PBS -A harrwh_project

cd /home/harrwh/projects/tiger
source /etc/profile.d/modules.sh
module load use.moose
module load moose-dev-gcc

pwd
mpiexec ./tiger-opt -i ./HomogenizedK.i
echo "done"


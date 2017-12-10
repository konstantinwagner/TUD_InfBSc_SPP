#!/bin/bash

# If path given use it, otherwise fetch current one by pwd
dir=$1
dir=${dir:-`pwd`}

read -p "Jobname: [UNTITLED_JOB]" jobname
jobname=${jobname:-UNTITLED_JOB}

read -p "Processes [1]: " processes
processes=${processes:-1}

read -p "Cores [4]: " cores
cores=${cores:-4}

read -p "RAM per Core (MByte) [1750]: " ram
ram=${ram:-1750}

read -p "Max execution time (hh:mm:ss) [00:01:00]: " time
time=${time:-00:01:00}

cat > run_job <<EOL
#!/bin/bash
#SBATCH -J ${jobname}
#SBATCH --mail-type=NONE
#SBATCH -e ${dir}/${jobname}.err
#SBATCH -o ${dir}/${jobname}.out
#SBATCH --account=kurs00015
#SBATCH --partition=kurs00015
#SBATCH --reservation=kurs00015
#SBATCH -n ${processes}
#SBATCH -c ${cores}
#SBATCH --mem-per-cpu=${ram}
#SBATCH -t ${time}
cd ${dir}

####################
# YOUR STUFF BELOW #
####################
EOL

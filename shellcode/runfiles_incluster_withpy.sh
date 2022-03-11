#runjob script

#!/bin/sh
hereDir=$PWD

printf "Delete log file!\n"
cd log/l_cluster_log
rm *.log
cd $hereDir

cd $hereDir
printf "Now, we are at '$hereDir'!\n"
echo "Now, we start to run job !"


echo "Run file4_11root"
bsub -q 1d -o log/s_cluster_log/file4_11.log python cluster_arr.py -f /home/chengyu/paper/sjet_ljet/root_numpy/rootfile/file4_11_sjet.root file4_11


echo "Finish the script !"


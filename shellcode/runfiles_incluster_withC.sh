#runjob script

#!/bin/sh
hereDir=$PWD

printf "Delete log file!\n"
cd log
rm *.log
cd $hereDir
cd output
rm *.root

cd $hereDir
printf "Now, we are at '$hereDir'!\n"

echo "Run file1"
for i in `seq 32`
do
    echo "Run file1_$i"

    if [ $i -lt "10" ]
    then
	bsub -q 1d -o log/file1_$i.log root -l "ttbar_ntuple.C(\"/home/saito/datafiles/ntuple/QGTagging/VBS-20211020/user.masaito.410470.PhPy8EG.DAOD_JETM6.e6337_s3126_r10201_p4310.20211020-01_output_root/user.masaito.27102138._00000$i.output.root\",1,$i)"
	sleep 1
    fi
    if [ $i -ge "10" ]
    then
	bsub -q 1d -o log/file1_$i.log root -l "ttbar_ntuple.C(\"/home/saito/datafiles/ntuple/QGTagging/VBS-20211020/user.masaito.410470.PhPy8EG.DAOD_JETM6.e6337_s3126_r10201_p4310.20211020-01_output_root/user.masaito.27102138._0000$i.output.root\",1,$i)"
	sleep 1
    fi
done

echo "---successful job!---"

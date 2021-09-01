path="results-pc-ufsc/par/v2_s_vs_g"
header="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

export OMP_NUM_THREADS=4

printf "\nCompilling-Static\n"
rm -f cpp_par_v2
g++ common/src/* parallel-v2/src/* -o cpp_par_v2 -fopenmp -O2 -DSTATIC

printf "$header" >> $path/static.txt
for i in {1..50}
do
    printf "static-%d\n" $i
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 2 2 >> $path/static.txt
done

#Use data from exec_min_seq.bash, by default it is using guided
#printf "\nCompilling-Guided\n"
#rm -f cpp_par_v2
#g++ common/src/* parallel-v2/src/* -o cpp_par_v2 -fopenmp -O2 -DGUIDED

#printf "$header" >> $path/guided.txt
#for i in {1..50}
#do
#    printf "guided-%d\n" $i
#    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 2 2 >> $path/guided.txt
#done
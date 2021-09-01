path="results-pc-ufsc/par/v1_s_vs_d"
header="n_odds\tisEulerian\tlistPairs\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

export OMP_NUM_THREADS=4

printf "\nCompilling-Static\n"
rm -f cpp_par_v1
g++ common/src/* parallel-v1/src/* -o cpp_par_v1 -fopenmp -O2 -DSTATIC

printf "$header" >> $path/static.txt
for i in {1..50}
do
    printf "static-%d\n" $i
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v1 2 2 >> $path/static.txt
done

printf "\nCompilling-Dynamic\n"
rm -f cpp_par_v1
g++ common/src/* parallel-v1/src/* -o cpp_par_v1 -fopenmp -O2 -DDYNAMIC

printf "$header" >> $path/dynamic.txt
for i in {1..50}
do
    printf "dynamic-%d\n" $i
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v1 2 2 >> $path/dynamic.txt
done

#
#   V1 EXECUTIONS
#
path="results-pc-ufsc/par/v1_vs_v2/v1"
header="n_odds\tisEulerian\tlistPairs\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

export OMP_NUM_THREADS=4

printf "\nCompilling-Static-V1\n"
rm -f cpp_par_v1
g++ common/src/* parallel-v1/src/* -o cpp_par_v1 -fopenmp -O2 -DDYNAMIC

printf "$header" >> $path/6odd.txt
printf "$header" >> $path/10odd.txt
printf "$header" >> $path/16odd.txt
printf "$header" >> $path/18odd.txt
for i in {1..50}
do
    printf "V1-%d\n" $i
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v1 0 1 >> $path/6odd.txt
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v1 1 0 >> $path/10odd.txt
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v1 2 0 >> $path/16odd.txt
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v1 2 1 >> $path/18odd.txt
done

#
#   V2 EXECUTIONS
#
path="results-pc-ufsc/par/v1_vs_v2/v2"
header="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"
min_seq=8

mkdir -p $path

export OMP_NUM_THREADS=4

printf "\nCompilling-Static-V2\n"
rm -f cpp_par_v2
g++ common/src/* parallel-v2/src/* -o cpp_par_v2 -fopenmp -O2 -DGUIDED

printf "$header" >> $path/6odd.txt
printf "$header" >> $path/10odd.txt
printf "$header" >> $path/16odd.txt
printf "$header" >> $path/18odd.txt
for i in {1..50}
do
    printf "V2-%d\n" $i
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 0 1 $min_seq >> $path/6odd.txt
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 1 0 $min_seq >> $path/10odd.txt
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 2 0 $min_seq >> $path/16odd.txt
    taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 2 1 $min_seq >> $path/18odd.txt
done
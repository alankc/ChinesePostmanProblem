printf "\n***** exp-min-seq *****\n"

root="results-g5/par/v2_min_seq"
header="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

printf "\nCompilling-cpp_parallel_v2\n"
rm -f cpp_parallel_v2
g++ common/src/* parallel-v2/src/* -o cpp_parallel_v2 -fopenmp -O2 -DGUIDED

export OMP_NUM_THREADS=6

for min_seq in 6 8 10 12
do
    path="$root/$min_seq"
    mkdir -p $path

    printf "$header" >> $path/6odd.txt
    printf "$header" >> $path/10odd.txt
    printf "$header" >> $path/16odd.txt
    printf "$header" >> $path/18odd.txt
    printf "$header" >> $path/20odd.txt
    for i in {1..50}
    do
        printf "$min_seq cpp_parallel_v2-%d\n" $i
        taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2 0 1 $min_seq >> $path/6odd.txt
        taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2 1 0 $min_seq >> $path/10odd.txt
        taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2 2 0 $min_seq >> $path/16odd.txt
        taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2 2 1 $min_seq >> $path/18odd.txt
        taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2 2 2 $min_seq >> $path/20odd.txt
    done
done
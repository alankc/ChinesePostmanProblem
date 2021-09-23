root="results-g5/par/v1_vs_v2"
header_v1="n_odds\tisEulerian\tlistPairs\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"
header_v2="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

path_v1="$root/v1"
path_v2="$root/v2"
mkdir -p $path_v1
mkdir -p $path_v2

printf "\nCompilling-cpp_parallel_v1\n"
rm -f cpp_parallel_v1
g++ common/src/* parallel-v1/src/* -o cpp_parallel_v1 -fopenmp -O2 -DDYNAMIC #preencher

printf "\nCompilling-cpp_parallel_v2\n"
rm -f cpp_parallel_v2
g++ common/src/* parallel-v2/src/* -o cpp_parallel_v2 -fopenmp -O2 -DGUIDED #preencher

num_seq=8 #preencher

printf "$header_v1" >> $path_v1/6odd.txt
printf "$header_v1" >> $path_v1/10odd.txt
printf "$header_v1" >> $path_v1/16odd.txt
printf "$header_v1" >> $path_v1/18odd.txt

printf "$header_v2" >> $path_v2/6odd.txt
printf "$header_v2" >> $path_v2/10odd.txt
printf "$header_v2" >> $path_v2/16odd.txt
printf "$header_v2" >> $path_v2/18odd.txt
printf "$header_v2" >> $path_v2/20odd.txt

export OMP_NUM_THREADS=6
for i in {1..50}
do
    printf "v1_vs_v2-%d\n" $i
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v1 0 1 >> $path_v1/6odd.txt
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v1 1 0 >> $path_v1/10odd.txt
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v1 2 0 >> $path_v1/16odd.txt
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v1 2 1 >> $path_v1/18odd.txt

    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2 0 1 $num_seq >> $path_v2/6odd.txt
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2 1 0 $num_seq >> $path_v2/10odd.txt
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2 2 0 $num_seq >> $path_v2/16odd.txt
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2 2 1 $num_seq >> $path_v2/18odd.txt
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2 2 2 $num_seq >> $path_v2/20odd.txt
done
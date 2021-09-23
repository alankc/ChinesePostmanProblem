printf "\n***** exp-v1-s-vs-d *****\n"

path="results-g5/par/v1_s_vs_d"
header="n_odds\tisEulerian\tlistPairs\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

printf "\nCompilling-cpp_parallel_v1_s\n"
rm -f cpp_parallel_v1_s
g++ common/src/* parallel-v1/src/* -o cpp_parallel_v1_s -fopenmp -O2 -DSTATIC

printf "\nCompilling-cpp_parallel_v1_d\n"
rm -f cpp_parallel_v1_d
g++ common/src/* parallel-v1/src/* -o cpp_parallel_v1_d -fopenmp -O2 -DDYNAMIC

printf "$header" >> $path/static.txt
printf "$header" >> $path/dynamic.txt

export OMP_NUM_THREADS=6
for i in {1..50}
do
    printf "exp-v1-s-vs-d-$i\n"
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v1_s 2 1 >> $path/static.txt
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v1_d 2 1 >> $path/dynamic.txt
done
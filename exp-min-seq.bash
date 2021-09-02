root="results-g5/par/v2_min_seq"
header="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

printf "\nCompilling-cpp_sequential\n"
rm -f cpp_sequential
g++ common/src/* sequential/src/* -o cpp_sequential -O2

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
        printf "$min_seq cpp_sequential-%d\n" $i
        taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_sequential 0 1 >> $path/6odd.txt
        taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_sequential 1 0 >> $path/10odd.txt
        taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_sequential 2 0 >> $path/16odd.txt
        taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_sequential 2 1 >> $path/18odd.txt
        taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_sequential 2 2 >> $path/20odd.txt
    done
done
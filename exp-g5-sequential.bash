printf "\n***** exp-sequential *****\n"

path="results-g5/seq"
header="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

printf "\nCompilling-cpp_sequential\n"
rm -f cpp_sequential
g++ common/src/* sequential/src/* -o cpp_sequential -O2

printf "$header" >> $path/6odd.txt
printf "$header" >> $path/10odd.txt
printf "$header" >> $path/16odd.txt
printf "$header" >> $path/18odd.txt
printf "$header" >> $path/20odd.txt
for i in {1..30}
do
    printf "exp-sequential-$i\n"
    taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_sequential 0 1 >> $path/6odd.txt
    taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_sequential 1 0 >> $path/10odd.txt
    taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_sequential 2 0 >> $path/16odd.txt
    taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_sequential 2 1 >> $path/18odd.txt
    taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_sequential 2 2 >> $path/20odd.txt
done
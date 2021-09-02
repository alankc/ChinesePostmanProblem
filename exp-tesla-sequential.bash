path="results-tesla/sequential"
header="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

printf "\nCompilling-cpp_sequential-V1\n"
rm -f cpp_sequential
g++ common/src/* sequential/src/* -o cpp_sequential -O2

printf "$header" >> $path/18odd.txt
for i in {1..50}
do
    printf "cpp_sequential-%d\n" $i
    taskset --cpu-list 0 ./cpp_sequential 2 1 >> $path/18odd.txt
done
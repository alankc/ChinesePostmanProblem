printf "\n***** exp-tesla-v2 *****\n"

path="results-tesla/par/v2_threads/20odd"
header="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

reps=25
threads=20
min_seq=8

printf "\nCompilling-cpp_parallel_v2-exp-tesla-v2\n"
rm -f cpp_parallel_v2
g++ common/src/* parallel-v2/src/* -o cpp_parallel_v2 -fopenmp -O2 -DGUIDED

t=16
let core=$t-1
export OMP_NUM_THREADS=$t
printf "$header" >> $path/"$t"_th.txt
for ((i=1; i<=8; i++))
do
	printf "$t threads -- rep $i\n"
	taskset --cpu-list 0-$core ./cpp_parallel_v2 2 2 $min_seq >> $path/"$t"_th.txt
done

for ((t=18; t<=$threads; t=t+2))
do
	let core=$t-1
	export OMP_NUM_THREADS=$t
	printf "$header" >> $path/"$t"_th.txt
	for ((i=1; i<=$reps; i++))
	do
		printf "$t threads -- rep $i\n"
		taskset --cpu-list 0-$core ./cpp_parallel_v2 2 2 $min_seq >> $path/"$t"_th.txt
	done
done
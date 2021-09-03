printf "\n***** exp-tesla-v1 *****\n"

path="results-tesla/par/v1_threads/18odd"
header="n_odds\tisEulerian\tlistPairs\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

reps=25
threads=20

printf "\nCompilling-cpp_parallel_v1-exp-tesla-v1\n"
rm -f cpp_parallel_v1
g++ common/src/* parallel-v1/src/* -o cpp_parallel_v1 -fopenmp -O2 -DDYNAMIC

for ((t=2; t<=$threads; t=t+2))
do
	let core=$t-1
	export OMP_NUM_THREADS=$t
	printf "$header" >> $path/"$t"_th.txt
	for ((i=1; i<=$reps; i++))
	do
		printf "$t threads -- rep $i\n"
		taskset --cpu-list 0-$core ./cpp_parallel_v1 2 1 >> $path/"$t"_th.txt
	done
done
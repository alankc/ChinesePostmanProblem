printf "\n***** exp-g5-threads *****\n"

reps=25
threads=6
min_seq=8

#********************************
#********** V2 - 20 *************
#********************************
path="results-g5/par/v2_threads/20odd"
header="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

printf "\nCompilling-cpp_parallel_v2-exp-g5-threads\n"
rm -f cpp_parallel_v2
g++ common/src/* parallel-v2/src/* -o cpp_parallel_v2 -fopenmp -O2 -DGUIDED

for ((t=2; t<=$threads; t=t+2))
do
	let core=$t-1
	export OMP_NUM_THREADS=$t
	printf "$header" >> $path/"$t"_th.txt
	for ((i=1; i<=$reps; i++))
	do
		printf "V2-20odd - $t threads -- rep $i\n"
		taskset --cpu-list 0-$core ./cpp_parallel_v2 2 2 $min_seq >> $path/"$t"_th.txt
	done
done

#********************************
#********** V2 - 18 *************
#********************************
path="results-g5/par/v2_threads/18odd"
header="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

printf "\nCompilling-cpp_parallel_v2-exp-g5-threads\n"
#rm -f cpp_parallel_v2
#g++ common/src/* parallel-v2/src/* -o cpp_parallel_v2 -fopenmp -O2 -DGUIDED

for ((t=2; t<=$threads; t=t+2))
do
	let core=$t-1
	export OMP_NUM_THREADS=$t
	printf "$header" >> $path/"$t"_th.txt
	for ((i=1; i<=$reps; i++))
	do
		printf "V2-18odd - $t threads -- rep $i\n"
		taskset --cpu-list 0-$core ./cpp_parallel_v2 2 1 $min_seq >> $path/"$t"_th.txt
	done
done


#********************************
#********** V1 - 18 *************
#********************************

path="results-g5/par/v1_threads/18odd"
header="n_odds\tisEulerian\tlistPairs\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

printf "\nCompilling-cpp_parallel_v1-exp-g5-threads\n"
rm -f cpp_parallel_v1
g++ common/src/* parallel-v1/src/* -o cpp_parallel_v1 -fopenmp -O2 -DDYNAMIC

for ((t=2; t<=$threads; t=t+2))
do
	let core=$t-1
	export OMP_NUM_THREADS=$t
	printf "$header" >> $path/"$t"_th.txt
	for ((i=1; i<=$reps; i++))
	do
		printf "V1-18odd - $t threads -- rep $i\n"
		taskset --cpu-list 0-$core ./cpp_parallel_v1 2 1 >> $path/"$t"_th.txt
	done
done
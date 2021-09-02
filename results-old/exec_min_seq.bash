printf "\nCompilling\n"
g++ common/src/* parallel-v2/src/* -o cpp_par_v2 -fopenmp -O2

path="results-pc-ufsc/par-v2/min_seq"

export OMP_NUM_THREADS=4
printf "\n\n OMP_NUM_THREADS=4 \n\n"

odd="6odd"
printf "$odd\n"
for j in 6 8 10 12
do
	path_complete="$path/$j"
	printf "n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n" >> $path_complete/min_seq"$j"_"$odd".txt
done
for i in {1..50}
do
	printf "$odd-min_seq-%d\n" $i
	for j in 6 8 10 12
	do
		path_complete="$path/$j"
		taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 0 1 $j >> $path_complete/min_seq"$j"_"$odd".txt
	done
done

odd="10odd"
printf "$odd\n"
for j in 6 8 10 12
do
	path_complete="$path/$j"
	printf "n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n" >> $path_complete/min_seq"$j"_"$odd".txt
done
for i in {1..50}
do
	printf "$odd-min_seq-%d\n" $i
	for j in 6 8 10 12
	do
		path_complete="$path/$j"
		taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 1 0 $j >> $path_complete/min_seq"$j"_"$odd".txt
	done
done

odd="16odd"
printf "$odd\n"
for j in 6 8 10 12
do
	path_complete="$path/$j"
	printf "n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n" >> $path_complete/min_seq"$j"_"$odd".txt
done
for i in {1..50}
do
	printf "$odd-min_seq-%d\n" $i
	for j in 6 8 10 12
	do
		path_complete="$path/$j"
		taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 2 0 $j >> $path_complete/min_seq"$j"_"$odd".txt
	done
done

odd="18odd"
printf "$odd\n"
for j in 6 8 10 12
do
	path_complete="$path/$j"
	printf "n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n" >> $path_complete/min_seq"$j"_"$odd".txt
done
for i in {1..50}
do
	printf "$odd-min_seq-%d\n" $i
	for j in 6 8 10 12
	do
		path_complete="$path/$j"
		taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 2 1 $j >> $path_complete/min_seq"$j"_"$odd".txt
	done
done

odd="20odd"
printf "$odd\n"
for j in 6 8 10 12
do
	path_complete="$path/$j"
	printf "n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n" >> $path_complete/min_seq"$j"_"$odd".txt
done
for i in {1..50}
do
	printf "$odd-min_seq-%d\n" $i
	for j in 6 8 10 12
	do
		path_complete="$path/$j"
		taskset --cpu-list 0-3 sudo -S <<< "0894" nice -n -19 ./cpp_par_v2 2 2 $j >> $path_complete/min_seq"$j"_"$odd".txt
	done
done
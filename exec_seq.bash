printf "\nCompilling\n"
g++ sequential/src/* common/src/* -o cpp_seq -O2

printf "Sequencial\n"
printf "6\n"
printf "n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n" >> seq_6odd.txt
for i in {1..50}
do
	taskset --cpu-list 0 sudo -S <<< "0894" nice -n -19 ./cpp_seq 0 1 >> seq_6odd.txt
done
printf "10\n"
printf "n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n" >> seq_10odd.txt
for i in {1..50}
do
	taskset --cpu-list 0 sudo -S <<< "0894" nice -n -19 ./cpp_seq 1 0 >> seq_10odd.txt
done
printf "16\n"
printf "n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n" >> seq_16odd.txt
for i in {1..50}
do
	taskset --cpu-list 0 sudo -S <<< "0894" nice -n -19 ./cpp_seq 2 0 >> seq_16odd.txt
done
printf "18\n"
printf "n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n" >> seq_18odd.txt
for i in {1..50}
do
	taskset --cpu-list 0 sudo -S <<< "0894" nice -n -19 ./cpp_seq 2 1 >> seq_18odd.txt
done
printf "20\n"
printf "n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n" >> seq_20odd.txt
for i in {1..50}
do
	taskset --cpu-list 0 sudo -S <<< "0894" nice -n -19 ./cpp_seq 2 2 >> seq_20odd.txt
done
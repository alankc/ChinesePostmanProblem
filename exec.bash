g++ sequential/src/* -o cpp_problem
printf "\nLIXO-AQUECIMENTO"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 5 2 0 >> lixo.txt
#V1 solve - ph
printf "\nv1_5reps_0n_1p_6odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 1 5 0 1 >> v1_5reps_0n_1p_6odd.txt
printf "\nv1_5reps_1n_0p_10odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 1 5 1 0 >> v1_5reps_1n_0p_10odd.txt
printf "\nv1_5reps_2n_0p_16odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 1 5 2 0 >> v1_5reps_2n_0p_16odd.txt
printf "\nv1_5reps_2n_1p_18odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 1 5 2 1 >> v1_5reps_2n_1p_18odd.txt
#V2 solve
printf "\nv2_5reps_0n_1p_6odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 5 0 1 >> v2_5reps_0n_1p_6odd.txt
printf "\nv2_5reps_1n_0p_10odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 5 1 0 >> v2_5reps_1n_0p_10odd.txt
printf "\nv2_5reps_2n_0p_16odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 5 2 0 >> v2_5reps_2n_0p_16odd.txt
printf "\nv2_5reps_2n_1p_18odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 5 2 1 >> v2_5reps_2n_1p_18odd.txt
printf "\nv2_5reps_2n_2p_20odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 5 2 2 >> v2_5reps_2n_2p_20odd.txt
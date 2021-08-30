./exec_parallel_v1.bash

rm -f cpp_problem
g++ sequential/src/* common/src/* -o cpp_problem -O2
printf "\nLIXO-AQUECIMENTO"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 5 2 0 >> lixo.txt
#V1 solve - ph
printf "\nv1_5reps_0n_1p_6odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 1 10 0 1 >> v1_5reps_0n_1p_6odd.txt
printf "\nv1_5reps_1n_0p_10odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 1 10 1 0 >> v1_5reps_1n_0p_10odd.txt
printf "\nv1_5reps_2n_0p_16odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 1 10 2 0 >> v1_5reps_2n_0p_16odd.txt
printf "\nv1_5reps_2n_1p_18odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 1 5 2 1 >> v1_5reps_2n_1p_18odd.txt
#V2 solve
printf "\nv2_5reps_0n_1p_6odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 20 0 1 >> results/Seq/v2/v2_5reps_0n_1p_6odd.txt
printf "\nv2_5reps_1n_0p_10odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 20 1 0 >> results/Seq/v2/v2_5reps_1n_0p_10odd.txt
printf "\nv2_5reps_2n_0p_16odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 20 2 0 >> results/Seq/v2/v2_5reps_2n_0p_16odd.txt
printf "\nv2_5reps_2n_1p_18odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 20 2 1 >> results/Seq/v2/v2_5reps_2n_1p_18odd.txt
printf "\nv2_5reps_2n_2p_20odd"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 20 2 2 >> results/Seq/v2/v2_5reps_2n_2p_20odd.txt
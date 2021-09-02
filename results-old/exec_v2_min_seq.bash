rm -f cpp_problem
g++ common/src/* parallel-v2/src/* -o cpp_problem -fopenmp -O2

export OMP_NUM_THREADS=6
printf "\n\n OMP_NUM_THREADS=6 \n\n"

printf "\nLIXO"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 2 0 6 >> results/Par/v2/LIXO.txt

printf "\n\n MIN_SEQ=6 \n\n"
printf "\nv2_5reps_0n_1p_6odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 0 1 6 >> results/Par/v2/min_seq/6/v2_10reps_0n_1p_6odd.txt
printf "\nv2_5reps_1n_0p_10odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 1 0 6 >> results/Par/v2/min_seq/6/v2_10reps_1n_0p_10odd.txt
printf "\nv2_5reps_2n_0p_16odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 2 0 6 >> results/Par/v2/min_seq/6/v2_10reps_2n_0p_16odd.txt
printf "\nv2_5reps_2n_1p_18odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 2 1 6 >> results/Par/v2/min_seq/6/v2_10reps_2n_1p_18odd.txt
printf "\nv2_5reps_2n_2p_20odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 2 2 6 >> results/Par/v2/min_seq/6/v2_10reps_2n_2p_20odd.txt

printf "\n\n MIN_SEQ=8 \n\n"
printf "\nv2_5reps_0n_1p_6odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 0 1 8 >> results/Par/v2/min_seq/8/v2_10reps_0n_1p_6odd.txt
printf "\nv2_5reps_1n_0p_10odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 1 0 8 >> results/Par/v2/min_seq/8/v2_10reps_1n_0p_10odd.txt
printf "\nv2_5reps_2n_0p_16odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 2 0 8 >> results/Par/v2/min_seq/8/v2_10reps_2n_0p_16odd.txt
printf "\nv2_5reps_2n_1p_18odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 2 1 8 >> results/Par/v2/min_seq/8/v2_10reps_2n_1p_18odd.txt
printf "\nv2_5reps_2n_2p_20odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 2 2 8 >> results/Par/v2/min_seq/8/v2_10reps_2n_2p_20odd.txt

printf "\n\n MIN_SEQ=10 \n\n"
printf "\nv2_5reps_0n_1p_6odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 0 1 10 >> results/Par/v2/min_seq/10/v2_10reps_0n_1p_6odd.txt
printf "\nv2_5reps_1n_0p_10odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 1 0 10 >> results/Par/v2/min_seq/10/v2_10reps_1n_0p_10odd.txt
printf "\nv2_5reps_2n_0p_16odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 2 0 10 >> results/Par/v2/min_seq/10/v2_10reps_2n_0p_16odd.txt
printf "\nv2_5reps_2n_1p_18odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 2 1 10 >> results/Par/v2/min_seq/10/v2_10reps_2n_1p_18odd.txt
printf "\nv2_5reps_2n_2p_20odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 30 2 2 10 >> results/Par/v2/min_seq/10/v2_10reps_2n_2p_20odd.txt
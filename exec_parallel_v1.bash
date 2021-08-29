g++ common/src/* parallel-v1/src/* -o cpp_problem -fopenmp -O2

export OMP_NUM_THREADS=6
printf "\nLIXO-AQUECIMENTO"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 5 2 0 >> lixo.txt

export OMP_NUM_THREADS=6
printf "\n\n OMP_NUM_THREADS=6 \n\n"
printf "\nv2_5reps_0n_1p_6odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 0 1 >> results/Par/v1/6th/v2_10reps_0n_1p_6odd.txt
printf "\nv2_5reps_1n_0p_10odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 1 0 >> results/Par/v1/6th/v2_10reps_1n_0p_10odd.txt
printf "\nv2_5reps_2n_0p_16odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 2 0 >> results/Par/v1/6th/v2_10reps_2n_0p_16odd.txt
printf "\nv2_5reps_2n_1p_18odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 2 1 >> results/Par/v1/6th/v2_10reps_2n_1p_18odd.txt
printf "\nv2_5reps_2n_2p_20odd"
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 2 2 >> results/Par/v1/6th/v2_10reps_2n_2p_20odd.txt

export OMP_NUM_THREADS=4
printf "\n\n OMP_NUM_THREADS=4 \n\n"
printf "\nv2_5reps_0n_1p_6odd"
taskset --cpu-list 0-3 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 0 1 >> results/Par/v1/4th/v2_10reps_0n_1p_6odd.txt
printf "\nv2_5reps_1n_0p_10odd"
taskset --cpu-list 0-3 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 1 0 >> results/Par/v1/4th/v2_10reps_1n_0p_10odd.txt
printf "\nv2_5reps_2n_0p_16odd"
taskset --cpu-list 0-3 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 2 0 >> results/Par/v1/4th/v2_10reps_2n_0p_16odd.txt
printf "\nv2_5reps_2n_1p_18odd"
taskset --cpu-list 0-3 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 2 1 >> results/Par/v1/4th/v2_10reps_2n_1p_18odd.txt
printf "\nv2_5reps_2n_2p_20odd"
taskset --cpu-list 0-3 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 2 2 >> results/Par/v1/4th/v2_10reps_2n_2p_20odd.txt

export OMP_NUM_THREADS=2
printf "\n\n OMP_NUM_THREADS=2 \n\n"
printf "\nv2_5reps_0n_1p_6odd"
taskset --cpu-list 0-1 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 0 1 >> results/Par/v1/2th/v2_10reps_0n_1p_6odd.txt
printf "\nv2_5reps_1n_0p_10odd"
taskset --cpu-list 0-1 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 1 0 >> results/Par/v1/2th/v2_10reps_1n_0p_10odd.txt
printf "\nv2_5reps_2n_0p_16odd"
taskset --cpu-list 0-1 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 2 0 >> results/Par/v1/2th/v2_10reps_2n_0p_16odd.txt
printf "\nv2_5reps_2n_1p_18odd"
taskset --cpu-list 0-1 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 2 1 >> results/Par/v1/2th/v2_10reps_2n_1p_18odd.txt
printf "\nv2_5reps_2n_2p_20odd"
taskset --cpu-list 0-1 sudo -S <<< "281094" nice -n -19 ./cpp_problem 2 10 2 2 >> results/Par/v1/2th/v2_10reps_2n_2p_20odd.txt
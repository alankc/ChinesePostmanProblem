g++ sequential/src/* -o cpp_problem
#V1 solve
taskset --cpu-list 0-0 sudo nice -n -19 ./cpp_problem 1 5 0 1 >> v1_5reps_0n_1p_6odd.txt
taskset --cpu-list 0-0 sudo nice -n -19 ./cpp_problem 1 5 1 0 >> v1_5reps_1n_0p_10odd.txt
taskset --cpu-list 0-0 sudo nice -n -19 ./cpp_problem 1 5 2 0 >> v1_5reps_2n_0p_16odd.txt
taskset --cpu-list 0-0 sudo nice -n -19 ./cpp_problem 1 5 2 1 >> v1_5reps_2n_1p_18odd.txt
#V2 solve
taskset --cpu-list 0-0 sudo nice -n -19 ./cpp_problem 2 5 0 1 >> v2_5reps_0n_1p_6odd.txt
taskset --cpu-list 0-0 sudo nice -n -19 ./cpp_problem 2 5 1 0 >> v2_5reps_1n_0p_10odd.txt
taskset --cpu-list 0-0 sudo nice -n -19 ./cpp_problem 2 5 2 0 >> v2_5reps_2n_0p_16odd.txt
taskset --cpu-list 0-0 sudo nice -n -19 ./cpp_problem 2 5 2 1 >> v2_5reps_2n_1p_18odd.txt
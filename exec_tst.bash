printf "\nCompilling\n"
g++ sequential/src/* common/src/* -o cpp_seq -O2
g++ common/src/* parallel-v1/src/* -o cpp_par_v1 -fopenmp -O2
g++ common/src/* parallel-v2/src/* -o cpp_par_v2 -fopenmp -O2

printf "\nSequencial\n"
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_seq 0 1
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_seq 1 0
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_seq 2 0
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_seq 2 1
taskset --cpu-list 0 sudo -S <<< "281094" nice -n -19 ./cpp_seq 2 2

printf "\nParallel-V1\n"
export OMP_NUM_THREADS=6
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_par_v1 0 1
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_par_v1 1 0
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_par_v1 2 0
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_par_v1 2 1
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_par_v1 2 2

printf "\nParallel-V2\n"
export OMP_NUM_THREADS=6
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_par_v2 0 1 8
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_par_v2 1 0 8
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_par_v2 2 0 8
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_par_v2 2 1 8
taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_par_v2 2 2 8
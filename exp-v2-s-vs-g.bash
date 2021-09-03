printf "\n***** exp-v2-s-vs-g *****\n"

path="results-g5/par/v2_s_vs_g"
header="n_odds\tisEulerian\tlistPairs\ttime_tmp\ttime_for\tlistPairsCombinationsBase\tmodifyGraph\thierholzer\ttotal_time\ttotal_distance\tpath\n"

mkdir -p $path

#cuidado, utilizando ele, mas pode ser que seja outro...
min_seq=8

printf "\nCompilling-cpp_parallel_v2_s\n"
rm -f cpp_parallel_v2_s
g++ common/src/* parallel-v2/src/* -o cpp_parallel_v2_s -O2 -DSTATIC

#o guiado posso usar do min-seq
#printf "\nCompilling-cpp_parallel_v2_g\n"
#rm -f cpp_parallel_v2_g
#g++ common/src/* parallel-v2/src/* -o cpp_parallel_v2_g -O2 -DGUIDED

printf "$header" >> $path/static_18odd.txt
#printf "$header" >> $path/guided_18odd.txt
printf "$header" >> $path/static_20odd.txt
#printf "$header" >> $path/guided_20odd.txt

export OMP_NUM_THREADS=6
for i in {1..50}
do
    printf "18odd-cpp_parallel_v1(s vs g)-%d\n" $i
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2_s 2 1 $min_seq >> $path/static_18odd.txt
    #taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2_g 2 1 $min_seq >> $path/guided_18odd.txt
done

for i in {1..50}
do
    printf "20odd-cpp_parallel_v1(s vs g)-%d\n" $i
    taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2_s 2 2 $min_seq >> $path/static_20odd.txt
    #taskset --cpu-list 0-5 sudo -S <<< "281094" nice -n -19 ./cpp_parallel_v2_g 2 2 $min_seq >> $path/guided_20odd.txt
done
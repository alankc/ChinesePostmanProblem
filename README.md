# Chinese Postman Problem (CPP)

[common](common): files used in both sequential and parallel versions

[sequential](sequential): sequential version of the CPP solver

[parallel-v1](parallel-v1): parallel version 1 of the CPP solver

[parallel-v2](parallel-v2): parallel version 2 of the CPP solver

[results-g5](results-g5): results obtained using Computer A. 

[results-tesla](results-tesla): results obtained using Computer B

[results-old](results-old): preliminary results.

## Experiments in Dell G5 computer (Computer A)

[exp-g5-all.bash](exp-g5-all.bash): run all experiments below (exp-g5-*). I recommend run one by one. For instance, exp-g5-v1-vs-v2.bash, depends on results of exp-g5-v1-s-vs-d.bash, exp-g5-min-seq.bash and exp-g5-v2-s-vs-g.bash.

[exp-g5-sequential.bash](exp-g5-sequential.bash): run the experiment to the sequential version of the solver.

[exp-g5-v1-s-vs-d.bash](exp-g5-v1-s-vs-d.bash): run the experiment to compare static and dynamic scheduling in parallel-v1.

[exp-g5-min-seq.bash](exp-g5-min-seq.bash): run the experiment to define ideal min_seq in parallel-v2.

[exp-g5-v2-s-vs-g.bash](exp-g5-v2-s-vs-g.bash): run the experiment to compare static and guided scheduling in parallel-v2.

[exp-g5-v1-vs-v2.bash](exp-g5-v1-vs-v2.bash): run the experiment to compare parallel-v1 and parallel-v2 for different problem sizes.

[exp-g5-threads.bash](exp-g5-threads.bash): run the experiment to compare parallel-v1 and parallel-v2 varying the number of threads.


## Experiments in Tesla computer (Computer B)

[exp-tesla-all.bash](exp-tesla-all.bash): run all experiments below (exp-tesla-*).

[exp-tesla-sequential.bash](exp-tesla-sequential.bash): run the experiment to the sequential version of the solver.

[exp-tesla-v1-18odd.bash](exp-tesla-v1-18odd.bash): run the experiment to compare parallel-v1 varying the number of threads for 18 odd vertices.

[exp-tesla-v2-18odd.bash](exp-tesla-v2-18odd.bash): run the experiment to compare parallel-v2 varying the number of threads for 18 odd vertices.

[exp-tesla-v2-20odd.bash](exp-tesla-v2-20odd.bash): run the experiment to compare parallel-v2 varying the number of threads for 20 odd vertices.

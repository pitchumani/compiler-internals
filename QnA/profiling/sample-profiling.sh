clang++ sample.cpp -lprofiler -L$(brew --prefix gperftools)/lib -o sample.out
CPUPROFILE=./sample.profile ./sample.out
pprof --text ./sample.out ./sample.profile


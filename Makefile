naive: naive.cpp
	g++ naive.cpp -mcpu=apple-m1 -mtune=native -std=c++11 -O3 -o naive

less_naive: less_naive.cpp
	g++ less_naive.cpp -mcpu=apple-m1 -mtune=native -std=c++11 -O3 -o less_naive

multi_thread: multi_thread.cpp
	g++ multi_thread.cpp -mcpu=apple-m1 -mtune=native -std=c++11 -O3 -o multi_thread

gpu: gpu.cu
	nvcc gpu.cu -o gpu

benchmark: less_naive naive multi_thread
	time ./naive 100000000
	time ./less_naive 100000000
	time ./multi_thread 100000000

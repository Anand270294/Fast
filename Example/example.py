import fast.fast as ft
import numpy as np
import time, json, cpuinfo

limit = 50000000 # Try to limit limit to 10 000 / 50 000
size = 5
npy = []
cpu_list = []
cpuEx_list = []
gpu_list = []

gpu = ft.gpu()
cpu = ft.cpu()


while(True):
    A = [x * 0.183736125 for x in range(0, size)]
    C = []

    start_time1 = time.perf_counter()
    C = np.multiply(A, A)
    time_taken1 = time.perf_counter() - start_time1
    npy.append(time_taken1)

    start_time2 = time.perf_counter()
    C = cpu.ExMul(A, A)
    time_taken2 = time.perf_counter() - start_time2
    cpuEx_list.append(time_taken2)

    start_time = time.perf_counter()
    C = cpu.mul(A, A, 0)
    time_taken = time.perf_counter() - start_time
    cpu_list.append(time_taken)

    start_time3 = time.perf_counter()
    C = gpu.mul(A, A)
    time_taken = time.perf_counter() - start_time3
    gpu_list.append(time_taken)

    print("Completed Test Number : {}".format(size) )

    if size >= limit:
        break
    
    size = size * 10

        
bnmk = dict()
bnmk['Test'] = 'Python CXX Wrapper Benchmark'
bnmk['CPU/GPU Used'] = cpuinfo.get_cpu_info()['brand'] 
bnmk['numpy'] = npy
bnmk['cpu'] = cpu_list
bnmk['cpuEx'] = cpuEx_list
bnmk['gpu'] = gpu_list
 
jsonfile = 'wrapper_test.json'

with open(jsonfile, 'w') as json_file:
    json.dump(bnmk, json_file)

print("Benchmarking Complete!")

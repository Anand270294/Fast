import fast.fast as ft
import numpy as np
import time, json, cpuinfo

limit = 50000000 # Try to limit limit to 10 000 / 50 000
norm = []
npy = []
cpu_list = []
gpu_list = []
sizes = []

gpu = ft.gpu()
cpu = ft.cpu()


for i in range(49999990,limit):
    #A = np.arange(0,i,0.00000015)
    A = range(0,limit)
    C = []

    #sizes.append(A.size)

    start_time1 = time.perf_counter()
    C = np.multiply(A, A)
    time_taken1 = time.perf_counter() - start_time1
    npy.append(time_taken1)

    start_time2 = time.perf_counter()
    C = cpu.ExMul(A, A)
    time_taken2 = time.perf_counter() - start_time2
    cpu_list.append(time_taken2)

    start_time = time.perf_counter()
    C = gpu.mul(A, A)
    time_taken = time.perf_counter() - start_time
    gpu_list.append(time_taken)

    print("Completed Test Number : {}".format(i) )

        
bnmk = dict()
bnmk['Test'] = 'Python CXX Wrapper Benchmark'
bnmk['CPU/GPU Used'] = cpuinfo.get_cpu_info()['brand'] 
bnmk['normal'] = norm
bnmk['numpy'] = npy
bnmk['cpu'] = cpu_list
bnmk['gpu'] = gpu_list
bnmk['sizes'] = sizes
 
jsonfile = 'wrapper_test.json'

with open(jsonfile, 'w') as json_file:
    json.dump(bnmk, json_file)

print("Benchmarking Complete!")





#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <omp.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <CL/cl.hpp>
#include <Eigen/Dense>
#include <Eigen/Core>


using device = cl::Device;

class gpu {

public:
	// Function to find available GPU locally
	std::string find_GPU() {
		std::string result = "";

		std::vector<cl::Platform> v;
		cl::Platform::get(&v);

		if (v.size() == 0) {
			result = "No Vendors Found. Please install OpenCL Drivers.";
		} else {

			auto plt = v.front();
			std::vector<cl::Device> vD;
			plt.getDevices(CL_DEVICE_TYPE_GPU, &vD);

			if (vD.size() == 0) {

				result = " Unable to find a device for OpenCL. Check if you have installed the right Drivers";
				
			} else {
				
				auto dflt = vD.front();
				result = dflt.getInfo<CL_DEVICE_NAME>();
			}
		}

		return result;
	}

	device get_Device() {
		cl::Device deflt;
		std::vector<cl::Platform> v;
		cl::Platform::get(&v);

		if (v.size() == 0) {
			throw "Unable to find GPU";
		} else {

			auto plt = v.front();
			std::vector<cl::Device> vD;
			plt.getDevices(CL_DEVICE_TYPE_GPU, &vD);

			if (vD.size() == 0) {
				throw "Unable to find GPU";
			} else {
				cl::Device deflt = vD.front();
			}
		}

		return deflt;
	}


	std::vector<int> mul(std::vector<int> A, std::vector<int> B) {

		// Assert that Matricies A & B are of the same size
		if (A.size() != B.size()) {
			std::vector<int> empty;
			return empty;
		}

		// Save the size of the arrays
		int size = int(A.size());

		std::vector<int> C(size, 0);

		// Get default platform 
		std::vector <cl::Platform> plt;
		cl::Platform::get(&plt);

		// Use Nvidia Platform for to obtain Device GPU
		auto platform = plt.front();
		std::vector < cl::Device > devices;
		platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
		cl::Device device = devices.front();

		std::string cl_src = "__kernel void Mul(const __global int* A, const __global int* B, __global int* C) { C[get_global_id(0)] = A[get_global_id(0)] * B[get_global_id(0)] ;}";
		cl::Program::Sources sources(1, std::make_pair(cl_src.c_str(), cl_src.length()));

		// Make a context for the GPU 
		cl::Context context(device);

		// Generate and build the program using OpenCL2.2
		cl::Program prg(context, sources);
		cl_int error = 0;
		error = prg.build("-cl-std=CL1.2 -cl-fast-relaxed-math");
 
		
		// Create buffers for the variables being used A, B and C
		cl::Buffer A_buffer(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, size * sizeof(int), A.data());
		cl::Buffer B_buffer(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, size * sizeof(int), B.data());
		cl::Buffer C_buffer(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, size * sizeof(int));

		// Try breaking here as well it could work.......

		cl::Kernel kernel(prg, "Mul", &error);

		kernel.setArg(0, A_buffer);
		kernel.setArg(1, B_buffer);
		kernel.setArg(2, C_buffer);

		cl::Event event;
		cl::CommandQueue queue(context, device);

		error = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(size), cl::NullRange, NULL, &event);
		error = queue.enqueueReadBuffer(C_buffer, CL_TRUE, 0, size * sizeof(int), C.data());
		event.wait();

	  	return C;
	}

	std::vector<float> mul(std::vector<float> A, std::vector<float> B) {

		// Assert that Matricies A & B are of the same size
		if (A.size() != B.size()) {
			std::vector<float> empty;
			return empty;
		}

		// Save the size of the arrays
		int size = int(A.size());

		std::vector<float> C(size, 0);

		// Get default platform 
		std::vector <cl::Platform> plt;
		cl::Platform::get(&plt);

		// Use Nvidia Platform for to obtain Device GPU
		auto platform = plt.front();
		std::vector < cl::Device > devices;
		platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);
		auto device = devices.front();

		std::string cl_src = "__kernel void Mul(const __global float* A, const __global float* B, __global float* C) { C[get_global_id(0)] = A[get_global_id(0)] * B[get_global_id(0)] ;}";
		cl::Program::Sources sources(1, std::make_pair(cl_src.c_str(), cl_src.length()));

		// Make a context for the GPU 
		cl::Context context(device);

		// Generate and build the program using OpenCL1.2
		cl::Program prg(context, sources);
		cl_int error = 0;
		error = prg.build("-cl-std=CL1.2 -cl-fast-relaxed-math");
		
		// Create buffers for the variables being used A, B and C
		cl::Buffer A_buffer(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, size * sizeof(float), A.data());
		cl::Buffer B_buffer(context, CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR, size * sizeof(float), B.data());
		cl::Buffer C_buffer(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, size * sizeof(float));

		cl::Kernel kernel(prg, "Mul", &error);

		kernel.setArg(0, A_buffer);
		kernel.setArg(1, B_buffer);
		kernel.setArg(2, C_buffer);

		cl::Event event;
		cl::CommandQueue queue(context, device);

		error = queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(size), cl::NullRange, NULL, &event);
		error = queue.enqueueReadBuffer(C_buffer, CL_TRUE, 0, size * sizeof(float), C.data());
		event.wait();

	  	return C;
	}

};

class cpu {

	public:
	
	int get_maxCores() {
		return omp_get_max_threads();
	}


	std::vector<float> mul(std::vector<float> A, std::vector<float> B) {
		Eigen::initParallel();

		int cores = omp_get_max_threads();
		Eigen::setNbThreads(cores);

		// Convert into Eigen Class Arrays	
		Eigen::ArrayXf _A = Eigen::Map<Eigen::ArrayXf, Eigen::Unaligned>(A.data(), A.size());
		Eigen::ArrayXf _B = Eigen::Map<Eigen::ArrayXf, Eigen::Unaligned>(B.data(), B.size());
			
		# pragma omp parallel for simd
		for(std::size_t i = 0; i < _A.size(); i ++){
			_A[i] = _A[i] * _B[i];
		}	
		

		std::vector<float> C (_A.data(), _A.data() + _A.size());
		return C;
	}	

	std::vector<int> mul(std::vector<int> A, std::vector<int> B) {
		Eigen::initParallel();

		int cores = omp_get_max_threads();
		Eigen::setNbThreads(cores);
		
		// Convert into Eigen Class Arrays	
		Eigen::ArrayXi _A = Eigen::Map<Eigen::ArrayXi, Eigen::Unaligned>(A.data(), A.size());
		Eigen::ArrayXi _B = Eigen::Map<Eigen::ArrayXi, Eigen::Unaligned>(B.data(), B.size());

		# pragma omp parallel for simd
		for(std::size_t i = 0; i < _A.size(); i ++){
			_A[i] = _A[i] * _B[i];
		}	
		
		std::vector<int> C (_A.data(), _A.data() + _A.size());
		return C;
	}	

};

namespace py = pybind11;

PYBIND11_MODULE(fast, m) {
        
		// GPU class to access gpus and perform calculations
		py::class_<gpu> (m, "gpu", py::dynamic_attr())
			.def(py::init())
			.def("findGPU", [](gpu & g){
				return g.find_GPU();
			})
			.def("getDevice", [](gpu & g) -> device {
				return g.get_Device();
			})
			// Overloaded functions for different primitve types
			.def("mul", [](gpu & g, std::vector<int>  A, std::vector<int> B){
				return g.mul(A, B);
			})
			.def("mul", [](gpu & g, std::vector<float> A, std::vector<float> B){
				return g.mul(A, B);
			})
			;

		// CPU multi-core class for MultiCore multiplications
		py::class_<cpu> (m, "cpu", py::dynamic_attr())
		.def(py::init())
		.def("get_maxCore", [](cpu & c){
				return c.get_maxCores();
		})
		.def("mul", [](cpu & c, std::vector<int> A, std::vector<int> B){
				return c.mul(A, B);
		})
		.def("mul", [](cpu & c, std::vector<float> A, std::vector<float> B){
				return c.mul(A, B);
		})
		;

}

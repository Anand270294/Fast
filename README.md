# Fast
A library for Linear Algebra Calculations (In Progress). **__Fast__** allows users to perform linear algebra calculations in *python* faster than native `python` language or even `Numpy` since **__Fast__** uses [**PyBind11**](https://github.com/pybind/pybind11) to wrap C++ code into a *python* object. Furthermore, **__Fast__** utilises [**Eigen3**](http://eigen.tuxfamily.org/index.php?title=Main_Page) Library which specialises in linear algebra calculations and [**OpenMP**](https://www.openmp.org/wp-content/uploads/OpenMP-4.5-1115-CPP-web.pdf) to allow parallel matrix calculations to boost performance.

## System Requirements:
1. Python 3.x
2. C++ 11.0
3. OpenCL and Grpahics Drivers depending on the User's Graphics Card
4. PyBind11
5. Eigen3 Library
6. OpenMP 4.5 and above
7. CMake 


## Quick Installation 
If all the aforementioned systems requirements have been met, you can do a quick installtion and use the **__Fast__** Library, else it is highly recommended that you follow the **full installtion procedure** before this step. 

### Step to Take:

1.  Clone **__Fast__**  repository to your preferred location.

2.  Clone [**PyBind11**](https://github.com/pybind/pybind11) into the **__Fast__** Folder as shown below:
![alt text](docs/imgs/clonepybind.png "Where to clone Pybind11")

3.  Open Terminal and go to the **__Fast__** directory e.g.
```linux
user@user:~$ cd Desktop/Fast
user@user:~/Desktop/Fast$
```

4.  Install the Library! 
```
user@user:~/Desktop/Fast$ python setup.py [option]
```
* For the `option` parameter it is advised to use `develop` if users wish to customise the functions available in the library. However users can also use `install` as a parameter.
* If no Error messages are shown during the build and installation process,you are no able to use **__Fast__**, see the next section on how to use Fast.
* However, if there are errors, it is highly recommended that you follow **full installtion procedure** as you may have missing dependencies.


### Using __Fast__

Congratulations! You have finished the hardest part of using this library (installation), **__Fast__**  allows the use of _multi-core CPUs_ and _GPUs_ to run matrix calculations.

#### Using the CPU version
The `cpu` class uses [**Eigen3**](http://eigen.tuxfamily.org/index.php?title=Main_Page) and [**OpenMP**](https://www.openmp.org/wp-content/uploads/OpenMP-4.5-1115-CPP-web.pdf) to run matrix calculations. Users just have to make a `cpu` object in python and run the function they desire. 

* An example of an element-wise matrix multiplication:
``` python
# Import Fast Library
import fast.fast as ft

# Create the cpu python object
cpu = ft.cpu()

# Create a vector of size 20
A = range(0,20)

# Run the Multiplication!
C = cpu.mul(A,A)

```
Viola! You are done with the multiplication.

* **Available functions**:
1. `mul(A,B)` : Element-wise vector multiplication where `A` and `B` are 1-D Arrays with the same size and data-type.


#### Using the GPU version:
The `gpu` class utilises the PC's Graphics Processing Unit(GPU) to run the calculations that can be parallelized using [**OpenCL**](). Its working is similar to the `cpu` class, whereby a `gpu` object needs to created before it can used. However it is also advisable to check the available GPUs on your PC before running.

* An example of an element-wise matrix multiplication:
```python
# Import Fast Library
import fast.fast as ft

# Create the cpu python object
gpu = ft.gpu()

# Check available GPU 
print(gpu.findGPU())

# Create a vector of size 20
A = range(0,20)

# Run the Multiplication!
C = gpu.mul(A,A)

```
Again You are Done!  

* **WARNING**: If the `gpu.findGPU()` functions does not print out any string related to your PC's GPUs, it is safe to assume that you have not installed your drivers for your native GPUs yet, as such please go through **full installtion procedure**.

* **Available functions**:
1. `findGPU()` : Provides a List of GPUs available in your PC and uses the first GPU on the list to perform the operations on.

2. `mul(A,B)`  : Element-wise vector multiplication where `A` and `B` are 1-D Arrays with the same size and data-type.


### Problems and Help
If you encounter any problems with the **__Fast__** Library, send an issue on the repository page along with the details of the error/problem and our support team will get back to you as early as possible! 
Enjoy!
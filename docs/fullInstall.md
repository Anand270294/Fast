# Full Installation Guide 
A step-by-step guide on how fulfill all dependencies before [installing the library](../README.md#quick-installation). To use **__Fast__** , the user must meet multiple system requirements since this would allow the users to modify and update thier library.

## 1. Installing Python
Most users would already have `python` installed in thier system by now and **__Fast__** requires the `python` version to be `python 3.x`. To check if you meet the version requirement:

```
$ python --version
```

If you do not have the required version or the language support install in your PC, you download it from [python website](https://www.python.org/downloads/)


## 2. Installing C++ 
Installing C++ would mean installing the g++ compiler. First the user should check if g++ compiler is available on the OS:
```
$ g++ --version

g++ (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

```

If you get similar result as shown above, you are good to go! However, If you did not get a similar result you can try:
```
$ sudo apt install build-essential
```
or :
```
$ sudo apt install g++
```
This should install the g++ compiler into your OS.

## 3. Make CMake
[**CMake**](https://cmake.org/) is an essential build tool for the library. As such you should check the available version on your PC:
```
$ cmake --version
```

Similar to most installation on linux systems, you can install by typing the following into the terminal:
```
$ sudo apt-get -y install cmake
```
 Now you have [**CMake**](https://cmake.org/) and almost half way there! Keep it up!

## 4. Faster and Parallel
This step will guide you on how to get [**Eigen3**](http://eigen.tuxfamily.org/index.php?title=Main_Page) and [**OpenMP**](https://www.openmp.org/wp-content/uploads/OpenMP-4.5-1115-CPP-web.pdf) which are core software of this library. Just follow the next few steps:

1. Installing Eigen3 on your system:
```
$ sudo apt-get install libeigen3-dev
```

 2. Installing OpenMP on your system:
```
 $ sudo apt-get install libomp-dev
```
 Now you should have 2 of the most important software for this library.

 ## 5. Binding with pybind11
 Even though you will require to clone pybind11 into your local repository, we highly recommend that you install *pybind11* into your python enviroment(Ananconda) to do so:
 ```
 (base) user@user:~/$ conda install -c conda-forge pybind11
 ```

 or:

```
(base) user@user:~/$ pip install pybind11
```


## 6. Maximize Your Graphics Card
**__Fast__** requires [**OpenCL**](https://www.khronos.org/opencl/) to run. With regards to utilising your graphics card, users are provided with *2* options:

1. Not Uitilising the GPU
2. Utilising the GPU

If you feel that you would not require the use of your Graphics Card, you are still required to install [**OpenCL**](https://www.khronos.org/opencl/) into your OS but we highly recommedn that you atleast try it out especially if you are dealing with large vectors/matrices, regardless you should follow part 1 of this installation process.

### 1. Not Uitilising the GPU
If you do not intend to utilise the GPU, you are at the right place! All you have to do is just install [**OpenCL**](https://www.khronos.org/opencl/) into your system:
```
$ sudo apt update
$ sudo apt install ocl-icd-opencl-dev
```
Now you should be able to use **__Fast__** , go to [installing the library](https://github.com/Anand270294/Fast/tree/v1.1_Ex#quick-installation) to complete the installation.

### 2. Utilising the GPU
If you are an opportunist and would like boost your calculation speeds this is the section you should be at! Using your GPU for **__Fast__** requires multiple steps:

#### 1. Install A Driver For Your Graphics Card
Depending on your hardware you might have an AMD/Nvidia external GPU or a integrated Graphics Processor which comes with your CPU(Intel/AMD). In some Linux system your external graphics card may not be detected since the proper drivers are not installed. To check what graphics card your OS is using:

Go to **Settings**  > **Detail** > **About** in the graphics section you should see:
![alt text](docs/imgs/identifygraphics.png "It should tell what graphics card you are using")

If the **About** page shows you the correct (external) graphics card you intend to use, then you have the relevant drivers installed, however, if you intend to use the integrated graphics card the you need to install the opencl drivers for [intel](https://software.intel.com/en-us/articles/opencl-drivers) CPUs or [AMD](https://developer.amd.com/tools-and-sdks/)

#### 2. Missing Drivers For External Cards
You need to install the drivers for the external graphics cards you are using, for that you can go to:
**Software & Updates** > **Additional Drivers**  
and you should see:
![alt text](docs/imgs/drivernvidia.png "Install one of the drivers shown")

and install one of the recommended drivers for you. After installation you will be promted with a terminal:
![alt text](docs/imgs/mokpasswrd.png "Calm Down its all good")

Do not Fret! Press **Ok** and this will ask you to type in a password which will be required in the next boot up, you can type in any password you are comfortable with and restart your PC once the terminal closes.

When you restart your PC, you will see blue screen :
![alt text](docs/imgs/uefi_enroll_key.png "Enter the password you created earlier") 

Go to **Enroll MOK** > Enter the password you made before rebooting the system > Your PC should go to the login screen

Now you should check if your graphics card driver has been installed.
Go to **Settings**  > **Detail** > **About** in the graphics section you should see:
![alt text](docs/imgs/identifygraphics.png "It should be there now!")

You should have your external graphics card installed!

#### 3. Getting OpenCL 
Now that you have your drivers installed you can download [**OpenCL**](https://www.khronos.org/opencl/) library for your OS. Open a new terminal and enter:

```
$ sudo apt update
$ sudo apt install ocl-icd-opencl-dev
```

This should install the [**OpenCL**](https://www.khronos.org/opencl/) library and with that you have all the required components to run the **__Fast__** library, go to [installing the library](../README.md#quick-installation) to complete your setup! 

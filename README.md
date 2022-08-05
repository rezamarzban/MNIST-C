# MNIST-C
Fast handwritten digit recognition by using MNIST dataset in full C++ code

The C++ programming language, Fastest processing and lowest memory usage in world of computer programing languages. It load MNIST dataset into less than 10MB of RAM and test dataset images in few seconds. Let's go!

Minimum hardware requirements:

Intel pentium II CPU

64MB RAM

100MB free disk space


Requirements:

"mnist_train.csv" and "mnist_test.csv" files from Google.

Installed "Clang" compiler.


Running instruction guide:

1- Clone this repository to your working directory.

2- Go to cloned repository folder.

3- Unzip "UnzipMe.zip" file which is in the repository folder or download required CSV files from Google to repository folder.

4- Compile "test.cpp" code and build binary file with "clang++" command.

5- Execute binary file.

Doing above instructions in my VPS:
![Image1](https://github.com/marzban2030/MNIST-C/raw/main/test0100.jpg)

Result: "9609 out of 10001 testing images are passed."

It means 96% accuracy for handwritten digit recognition by this C++ code. Actually this C++ code compare each BW test image with all of BW train images by bitwise operation and find difference between these, Then choose that train image which has minimum difference with desired test image.

At future versions of this C++ code, I define more effective comparison function to taking 99% accuracy at least.

So, This C++ code do fast billion comparison between test images and train images and find minimum difference.

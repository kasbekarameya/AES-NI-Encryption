# AES-NI Encryption
The Advanced Encryption Standard New Instruction (AES NI) Instructions is the instruction set designed by Intel to enable AES encryption algorithm to work along with the hardware. This can significantly improve the performance of the algorithm, as the amount of time required to encrypt and decrypt is reduced due to hardware acceleration. In total, Intel provides six AES NI instructions that are used for hardware accelerated AES. They are AESENC, AESENCLAST, AESDEC, AESDECLAST, AESIMC & AESKEYGENASSIST.

As these instructions are machine level instructions and as high level languages do not work with machine level instructions, it is not possible to use these six AES NI Instructions in such languages like JAVA, Python, etc. These AES NI Instructions are only available to be used in the C programming language. This is because, C programming language is considered as a middle level language, as it combines the functionality of a high level as well as a low level programming language i.e. we can do System programming as well as Application programming using C. Hence, we can use the wmmintrin.h header file, to implement all the six AES NI Instructions for AES algorithm.

#Comparing performance of AES-NI Instructions 

Here, two types of AES Encryption programs have been compared based on the Total Time taken by each of the programs to encrypt 1000 1-block messages. The major difference between the two programs compared here is the use of Intel’s AES NI (Advanced Encryption Standard New Instructions) instructions in one of them and using a high level cryptographic library in the other.
In order to even further improve the accuracy of performance offered by both the programs, we will take an average of six attempts of running the same code, that is running each program to encrypt 1000 1-block message at least six times.

#Program 1:
Programming Language Used: C Programming

Use of AES NI Instructions: YES

Total time taken:
Attempt 1: 0.001952 seconds
Attempt 2: 0.001868 seconds
Attempt 3: 0.001813 seconds
Attempt 4: 0.001825 seconds
Attempt 5: 0.001785 seconds
Attempt 6: 0.001825 seconds
Hence, the Average Time Taken = (0.001952 + 0.001868 + 0.001813 + 0.001825 + 0.001785 + 0.001825) ÷ 6 = 0.001844 seconds

#Program 2:
Programming Language Used: Python

Use of AES NI Instructions: NO

Total time taken:
Attempt 1: 0.173830 seconds
Attempt 2: 0.195814 seconds
Attempt 3: 0.174242 seconds
Attempt 4: 0.179104 seconds
Attempt 5: 0.175519 seconds
Attempt 6: 0.198447 seconds
Hence, the Average Time Taken = (0.173830 + 0.195814 + 0.174242 + 0.179104 + 0.175519 + 0.198447) ÷ 6 = 0.182826 seconds

In order to determine the performance improvement observed due to AES NI instructions, lets do the following calculations:
Percentage of performance improvement = (0.182826 - 0.001844) ÷ 0.182826 = 0.9899 * 100 = 98.99 %

Hence, based on the time taken observed for both the programs, we can definitely conclude that use of AES NI instructions gives a huge boost in performance to the AES Encryption process.


# This code has been released under the license terms specified in the LICENSE file
# By using this code, you agree to adhere to the LICENSE terms

# microarch_stressbench
This repository hosts a suite of micro test program kernels that can stress individual resources in a microprocessor. Such tests are useful when we are interested in observing the performance of a machine in a certain kind of load, for example TLB or cache pressure. 

#*** Compiling 
make clean
make 

#**** Tests *** 

# TLB stress test
./TLB 

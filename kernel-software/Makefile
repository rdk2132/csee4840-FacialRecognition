ifneq (${KERNELRELEASE},)

# KERNELRELEASE defined: we are being compiled as part of the Kernel
        obj-m := cnn_driver.o

else

# We are being compiled as a module: use the Kernel build system

  KERNEL_SOURCE := /usr/src/linux-headers-$(shell uname -r)
    PWD := $(shell pwd)


default: module driver_test

module: ../software-testbench/Parameters.h
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} modules

clean:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
	${RM} driver_test

endif 

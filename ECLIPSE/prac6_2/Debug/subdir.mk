################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../prac6_2_mmesp_project.cpp 

OBJS += \
./prac6_2_mmesp_project.o 

CPP_DEPS += \
./prac6_2_mmesp_project.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/guille/workspace/prac6_2/components/ccsuperserver/include" -I"/home/guille/workspace/prac6_2/components/ccserver/include" -I"/home/guille/workspace/prac6_2/components/ccclient/include" -I"/home/guille/workspace/prac6_2/components/prac6_2/include" -I"/home/guille/workspace/prac6_2/config/include" -I"/home/guille/workspace/prac6_2/edroom_glue/include" -I"/home/guille/workspace/prac6_2/edroombp_swr/include" -I"/home/guille/workspace/prac6_2/edroomsl_swr/include" -I"/home/guille/workspace/prac6_2/edroomsl_types_swr/include" -I"/home/guille/workspace/prac6_2/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



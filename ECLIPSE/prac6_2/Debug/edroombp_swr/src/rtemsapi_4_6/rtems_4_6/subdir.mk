################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../edroombp_swr/src/rtemsapi_4_6/rtems_4_6/edroombp.cpp 

OBJS += \
./edroombp_swr/src/rtemsapi_4_6/rtems_4_6/edroombp.o 

CPP_DEPS += \
./edroombp_swr/src/rtemsapi_4_6/rtems_4_6/edroombp.d 


# Each subdirectory must supply rules for building sources it contributes
edroombp_swr/src/rtemsapi_4_6/rtems_4_6/%.o: ../edroombp_swr/src/rtemsapi_4_6/rtems_4_6/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/guille/workspace/prac6_2/components/ccsuperserver/include" -I"/home/guille/workspace/prac6_2/components/ccserver/include" -I"/home/guille/workspace/prac6_2/components/ccclient/include" -I"/home/guille/workspace/prac6_2/components/prac6_2/include" -I"/home/guille/workspace/prac6_2/config/include" -I"/home/guille/workspace/prac6_2/edroom_glue/include" -I"/home/guille/workspace/prac6_2/edroombp_swr/include" -I"/home/guille/workspace/prac6_2/edroomsl_swr/include" -I"/home/guille/workspace/prac6_2/edroomsl_types_swr/include" -I"/home/guille/workspace/prac6_2/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



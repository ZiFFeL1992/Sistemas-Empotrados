################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/vehicle/src/VehicleC.cpp \
../components/vehicle/src/VehicleE.cpp 

OBJS += \
./components/vehicle/src/VehicleC.o \
./components/vehicle/src/VehicleE.o 

CPP_DEPS += \
./components/vehicle/src/VehicleC.d \
./components/vehicle/src/VehicleE.d 


# Each subdirectory must supply rules for building sources it contributes
components/vehicle/src/%.o: ../components/vehicle/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/components/ccavoidobstacles/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/bprint_swr/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/dataclasses/CDLocation/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/dataclasses/CDPath/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/actuators_drv/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/components/capathplanner/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/components/vehicle/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/planner_swr/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/random_swr/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/components/capathtracker/include" -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/config/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/sensors_drv/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/edroom_glue/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/edroombp_swr/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/edroomsl_swr/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/edroomsl_types_swr/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac7_1/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



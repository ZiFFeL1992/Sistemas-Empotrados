################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/ccserver/src/CCServerC.cpp \
../components/ccserver/src/CCServerE.cpp 

OBJS += \
./components/ccserver/src/CCServerC.o \
./components/ccserver/src/CCServerE.o 

CPP_DEPS += \
./components/ccserver/src/CCServerC.d \
./components/ccserver/src/CCServerE.d 


# Each subdirectory must supply rules for building sources it contributes
components/ccserver/src/%.o: ../components/ccserver/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: SPARC RTEMS C++ Compiler'
	sparc-rtems-g++ -I/opt/rtems-4.6/sparc-rtems/leon3/lib/include -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac6_2/components/ccsuperserver/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac6_2/components/ccserver/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac6_2/components/ccclient/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac6_2/components/prac6_2/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac6_2/config/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac6_2/edroom_glue/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac6_2/edroombp_swr/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac6_2/edroomsl_swr/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac6_2/edroomsl_types_swr/include" -I"/home/guille/Documents/Sistemas-Empotrados/ECLIPSE/prac6_2/rtems_osswr/include" -O0 -g3 -Wall -msoft-float -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



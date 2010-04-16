################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Building.cpp \
../DistructableObj.cpp \
../Obj.cpp \
../Sector.cpp \
../main.cpp 

OBJS += \
./Building.o \
./DistructableObj.o \
./Obj.o \
./Sector.o \
./main.o 

CPP_DEPS += \
./Building.d \
./DistructableObj.d \
./Obj.d \
./Sector.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -lGLU -lglut -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



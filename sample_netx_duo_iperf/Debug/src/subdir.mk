################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/nx_driver_renesas_rz.c \
../src/nx_iperf.c \
../src/sample_netx_duo_iperf.c 

C_DEPS += \
./src/nx_driver_renesas_rz.d \
./src/nx_iperf.d \
./src/sample_netx_duo_iperf.d 

OBJS += \
./src/nx_driver_renesas_rz.o \
./src/nx_iperf.o \
./src/sample_netx_duo_iperf.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	arm-none-eabi-gcc -mcpu=cortex-a9 -march=armv7-a -marm -mthumb-interwork -mlittle-endian -mfloat-abi=hard -mfpu=vfpv3-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wnull-dereference -g -Wstack-usage=1000 -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\compiler\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\configuration" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\configuration\os_abstraction\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\configuration\sc\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\application\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\application\graphics\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\application\console\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\application\system\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\application\system\iodefines" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\application\system\iobitmasks" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\drivers\adc\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\drivers\r_gpio\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\drivers\intc\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\drivers\ostm\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\drivers\r_cache\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\src\renesas\middleware\ethernet\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\rz_bsp\azure\ports\cortex_a9\gnu\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\filex\common\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\threadx\common\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\netxduo\common\inc" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\netxduo\addons\dhcp" -I"C:\workspace\RZA1\Azure\rza1_gcc_azure_rtos_bsp_private\netxduo\addons\http" -I"C:/workspace/RZA1/Azure/rza1_gcc_azure_rtos_bsp_private/sample_netx_duo_iperf/src" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"


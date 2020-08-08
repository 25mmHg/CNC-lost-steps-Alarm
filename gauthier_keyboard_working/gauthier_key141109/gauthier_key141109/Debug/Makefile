################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../gauthier_key141109.c \
../usb_keyboard.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
gauthier_key141109.o \
usb_keyboard.o

OBJS_AS_ARGS +=  \
gauthier_key141109.o \
usb_keyboard.o

C_DEPS +=  \
gauthier_key141109.d \
usb_keyboard.d

C_DEPS_AS_ARGS +=  \
gauthier_key141109.d \
usb_keyboard.d

OUTPUT_FILE_PATH +=gauthier_key141109.elf

OUTPUT_FILE_PATH_AS_ARGS +=gauthier_key141109.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler





./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 3.4.2
	$(QUOTE)C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -DDEBUG  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32u4 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 3.4.2
	$(QUOTE)C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="gauthier_key141109.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega32u4 
	@echo Finished building target: $@
	"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "gauthier_key141109.elf" "gauthier_key141109.hex"
	"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "gauthier_key141109.elf" "gauthier_key141109.eep" || exit 0
	"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "gauthier_key141109.elf" > "gauthier_key141109.lss"
	"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "gauthier_key141109.elf" "gauthier_key141109.srec"
	"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-size.exe" "gauthier_key141109.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "gauthier_key141109.elf" "gauthier_key141109.a" "gauthier_key141109.hex" "gauthier_key141109.lss" "gauthier_key141109.eep" "gauthier_key141109.map" "gauthier_key141109.srec"
	
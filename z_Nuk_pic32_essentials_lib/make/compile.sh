#!/bin/sh

#
# Sintax
# ../make/compile.sh mprocessor
#
#  where
#
#    mprocessor 
#      The name of the processor target ( like 32MX170F226B )




# -----------------------------------------------------------------------------
# Parameters
#
PROC=$1




# -----------------------------------------------------------------------------
# Own directori
#
DIR_NAME=$(pwd)




# -----------------------------------------------------------------------------
# Own includes
#
INC=" "
INC=$INC" "-Iinclude
INC=$INC" "-I../include
INC=$INC" "-I../../include




# -----------------------------------------------------------------------------
# Compiling and linking
#
cd implementation
cd ../implementation

OPTC=-mprocessor=$PROC" "-O1


echo
EXE="xc32-g++ -c "$OPTC" "$INC" -o Callable.o Callable.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Caller.o Caller.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Fifo.o Fifo.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o IrqObject.o IrqObject.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o TimerObject.o TimerObject.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Timer.o Timer.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Pwm.o Pwm.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Analog.o Analog.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Digital.o Digital.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Ei.o Ei.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Serial_Rx.o Serial_Rx.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Serial_Tx.o Serial_Tx.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Serial.o Serial.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Spi_mstr.o Spi_mstr.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Spi_slv.o Spi_slv.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o I2c.o I2c.cpp"
echo $EXE
$EXE
EXE="xc32-g++ -c "$OPTC" "$INC" -o Nuk_pic32_essentials.o Nuk_pic32_essentials.cpp"
echo $EXE
$EXE

EXE="xc32-ar r Nuk_pic32_essentials_lib.a \
	Callable.o \
	Caller.o \
	Fifo.o \
	IrqObject.o \
	TimerObject.o \
	Timer.o \
	Pwm.o \
	Analog.o \
	Digital.o \
	Ei.o \
	Serial_Rx.o \
	Serial_Tx.o \
	Serial.o \
	Spi_mstr.o \
	Spi_slv.o \
	I2c.o \
	Nuk_pic32_essentials.o"
echo
echo $EXE
$EXE






# -----------------------------------------------------------------------------
# Move lib and clean *.o
#
mv *.a ../
rm *.o




# -----------------------------------------------------------------------------
# Return to the original directory
#
cd $DIR_NAME



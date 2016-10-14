#!/bin/sh

#
# Sintax
#
# ../make/compile.sh mprocessor lib_directori source
#
# where
#
#  mprocessor 
#    The name of the processor target ( like 32MX170F226B )
#    if -p dialog apairs
#
#  lib_dir
#    The direcctori where you have the libraries
#      if -p dialog apairs
#
#   source
#    The name of your C source code
#    if -p dialog apairs
			


# -----------------------------------------------------------------------------
# Own directory
#
DIR_NAME=$(pwd)




# -----------------------------------------------------------------------------
# Parameters
#
# $1 mprocessor
# $2 library directori
# $3 source file name

PROC=$1
DIR_LIBS=$2

A=`expr $3 != "-p"`
case $A in 1 )
	NAME=`basename $3`
	;;
	esac




# -----------------------------------------------------------------------------
# -p parameters
#

# $1 mprocessor
A=`expr $1 = "-p"`
case $A in 1 )

	PROC=$(zenity --list \
		--title="Processor" \
		--column="Processor" \
		32MX110F016B \
		32MX120F032B \
		32MX130F064B \
		32MX130F256B \
		32MX150F128B \
		32MX170F256B \
		32MX210F016B \
		32MX220F032B \
		32MX230F064B \
		32MX230F256B \
		32MX250F128B \
		32MX270F256B \
		)
	;;
	esac


# $2 library directori
A=`expr $2 = "-p"`
case $A in 1 )
	DIR_LIBS=$(zenity --file-selection --directory\
		--title="Lib directory" \
		)
	;;
	esac


# $3 source file name
A=`expr $3 = "-p"`
case $A in 1 )
	FULLNAME=$(zenity --file-selection\
		--title="Code" \
		)
	NAME=`basename $FULLNAME`
	;;
	esac




# -----------------------------------------------------------------------------
# Own INCudes
#
cd $DIR_NAME

INC=""
INC=$INC" "-Iinclude
INC=$INC" "-I../include
INC=$INC" "-I../../include





# -----------------------------------------------------------------------------
# Libs and libs INCudes
#
cd $DIR_LIBS


LIBS=""
for LIB in $(ls -d *lib);
do
	cd $DIR_LIBS/$LIB
	make/compile.sh  $PROC $DIR_LIBS
	LIBS=$LIBS" "$DIR_LIBS"/"$LIB"/"*.a
	INC=$INC" "-I$DIR_LIBS"/"$LIB"/"include
done




# -----------------------------------------------------------------------------
# Compiling and linking
#
cd $DIR_NAME
cd implementation


OPTC=-mprocessor=$PROC" "-O1
HEAP=-Wl,--defsym=_min_heap_size=1024
#REPORT=-Wl,--report-mem

echo
echo "compiling" $NAME
echo "compiler options = " $OPTC
echo "incudes = " $INC
xc32-g++ -c $OPTC $INC -o $NAME.o $NAME

echo
echo "link"
echo "linker options = " $OPTC $HEAP
echo "libs = " $LIBS
xc32-g++ $OPTC $HEAP -o $NAME.elf $NAME.o $LIBS $REPORT
xc32-bin2hex $NAME.elf




# -----------------------------------------------------------------------------
# Move lib and clean *.o
#
mv $NAME.hex ../bin
rm *.o
rm *.elf

cd $DIR_NAME



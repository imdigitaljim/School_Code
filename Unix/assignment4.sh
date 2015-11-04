#!/bin/sh
#==========================
#BACH, JAMES
#COP3353
#ASSIGNMENT 4
#NOVEMBER 18 2014
#===========================
if [ $# -eq 0 ] 
then
    echo "Usage: $0 directory_name"
elif [ ! -d $1 ]
then
    echo "$1: No such directory" 
else
    echo "In the directory $1"
#initialize the counting variables
    dirCount=0
    fileCount=0
    readCount=0
    writeCount=0
    exeCount=0
#for loop through the given directory
#if directory, file, read, write execute
#optionally could use dirCount=`expr $dirCount + 1`

    for f in $1/*
    do
	if [ -d $f ]
	then
	    dirCount=$((dirCount + 1))
	elif [ -f $f ]
	then
	    fileCount=$((fileCount + 1))
	fi
	
	if [ -r $f ]
	then
	    readCount=$((readCount + 1))
	fi

	if [ -w $f ]
	then
	    writeCount=$((writeCount + 1))
	fi
	
	if [ -x $f ]
	then
	    exeCount=$(($exeCount + 1))
	fi
    done
    
    echo "  Number of directories     : $dirCount" 
    echo "  Number of files           : $fileCount" 
    echo "  Number of readable items  : $readCount"
    echo "  Number of writable items  : $writeCount" 
    echo "  Number of executable items: $exeCount"
    echo ""
fi

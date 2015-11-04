#!/bin/sh
#==========================
#COP3353
#ASSIGNMENT 3
#OCTOBER 26 2014
#===========================
cp ~vastola/ufiles/* .
chmod 700 grades
printf "===================\nGrades test 1\n" >> output.txt
printf "===================\n" >> output.txt
grades < t1 >> output.txt 
printf "===================\nGrades test 2\n" >> output.txt
printf "===================\n" >> output.txt
grades < t2 >> output.txt
chmod 644 file1 file2
printf "===================\ndiff test 1\n===================\n" >> output.txt
diff file1 file2 >> output.txt
printf "===================\ndiff test 2\n===================\n" >> output.txt
diff -w file1 file2 >> output.txt
printf "===================\ndiff test 3\n===================\n" >> output.txt
diff -wi file1 file2 >> output.txt
printf "===================\ngrep test 1\n===================\n" >> output.txt
grep -in "the" file1 >> output.txt 
printf "===================\ngrep test 2\n===================\n" >> output.txt
grep -n '^The' file1 >> output.txt
printf "===================\ngrep test 3\n===================\n" >> output.txt
grep -nw "who" file1 >> output.txt
printf "===================\nProcess command 1\n" >> myprocess.txt
printf "===================\n" >> myprocess.txt
ps -ef >> myprocess.txt
printf "===================\nProcess command 2\n" >> myprocess.txt
printf "===================\n" >> myprocess.txt
ps -ef | grep "root" >> myprocess.txt
printf "===================\nDirectory listing\n" >> output.txt
printf "===================\n" >> output.txt
ls -l >> output.txt
tar -cvf myTar.tar file1 file2 grades output.txt myprocess.txt
gzip myTar.tar

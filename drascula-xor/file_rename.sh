#!/bin/bash
FILES=`ls *.xored`
for file in $FILES
do
	mv_file=`basename $file .xored`
	# echo $file "->" $mv_file
	mv $file $mv_file
done

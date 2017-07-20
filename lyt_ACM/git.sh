#!/bin/bash -
if [ ! $1 ]; then
    ab=`date +%F-%T`
else
    ab=$1
fi
rm a.out
git add .
git commit -m $ab
git push

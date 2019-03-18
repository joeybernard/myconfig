#!/bin/bash
curr_dir=`pwd`
for repo in `ls -d ~/repos/*`; do
    cd $repo
    echo "==============="
    echo "git pull in "
    pwd
    git pull
done
cd $curr_dir

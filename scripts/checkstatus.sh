#!/bin/bash
curr_dir=`pwd`
for repo in `ls -d ~/repos/*`; do
    cd $repo
    echo "==============="
    echo "git status in "
    pwd
    git status -s
done
cd $curr_dir

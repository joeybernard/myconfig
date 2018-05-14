#!/bin/bash
curr_dir=`pwd`
for repo in `ls -d ~/repos/*`; do
    cd $repo
    echo "git status in "
    pwd
    git status
done
cd $curr_dir

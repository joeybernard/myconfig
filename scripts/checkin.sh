#!/bin/bash
curr_dir=`pwd`
for repo in `ls -d ~/repos/*`; do
    cd $repo
    echo "git push in "
    pwd
    git push
done
cd $curr_dir

#!/bin/bash
curr_dir=`pwd`
for repo in `ls -d ~/repos/*`; do
    cd $repo
    echo "==============="
    echo "git push in "
    pwd
    git commit -a -m "Automatic backup"
    git push
done
cd $curr_dir

#!/bin/bash

if [ ! -d ~/repos ]; then
    mkdir ~/repos
fi

curr_dir=`pwd`
cd ~/repos
git clone https://joeybernard@bitbucket.org/joeybernard/lwang.git
git clone https://github.com/joeybernard/writing.git
git clone https://github.com/joeybernard/joeybernard.github.io.git
git clone https://git.chain-project.net/Joey/jbernard.git
git clone https://git.chain-project.net/RadioPhysics/GeneralInfo.git

cd $curr_dir


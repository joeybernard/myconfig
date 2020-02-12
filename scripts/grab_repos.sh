#!/bin/bash

if [ ! -d ~/repos ]; then
    mkdir ~/repos
fi

curr_dir=`pwd`
cd ~/repos

git clone https://github.com/joeybernard/writing.git
git clone https://github.com/joeybernard/joeybernard.github.io.git
git clone https://github.com/joeybernard/scratch.git

git clone https://git.chain-project.net/Joey/jbernard.git
git clone https://git.chain-project.net/RadioPhysics/GeneralInfo.git
#git clone https://git.chain-project.net/RadioPhysics/Ionosonde.git

git clone https://github.com/MotusWTS/motusServer.git
git clone https://github.com/MotusWTS/find_tags.git
#git clone https://github.com/MotusWTS/MotusRBook.git
#git clone https://github.com/MotusWTS/Documentation.git
#git clone https://github.com/MotusWTS/motus.git
#git clone https://github.com/MotusWTS/motusClient.git
#git clone https://github.com/MotusWTS/motus-metadata-history.git
#git clone https://github.com/MotusWTS/motusData.git
git clone https://github.com/MotusWTS/program_options.git

#git clone https://github.com/MotusDev/MotusAPI.git

cd $curr_dir


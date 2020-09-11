#!/bin/bash

path=$(cd `dirname $0`;pwd)
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$path/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$path/lib/mysql
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$path/lib/uuid
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$path/lib/redis
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$path/lib/occi

if test $( nvidia-smi | grep 'GPU'| wc -l ) -eq 0
then
    echo "start on cambricon"
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$path/lib/cambricon_mlu100d4
else
    echo "start on nvidia"
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$path/lib/nvidia_1070
fi

echo "export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}

cd $path/bin

chmod 755 $path/bin/hunHeJiaoTong

ID=`ps -ef | grep -w "hunHeJiaoTong" | grep -v "$0" | grep -v "grep" | awk '{print $2}'`
echo $ID
for id in $ID 
do
kill -9 $id 
echo "killed $id"
done

./hunHeJiaoTong $* &

#!/bin/bash

core_dir=/opt/vehicle/program/
core_path= # default :core_path=${core_dir}/coredump/coredump_files
alg_process_name=chejian_redis
app_layer_name=hunHeJiaoTong


function test_init()
{
  core_dir=/home/yuyang/develop/cplusplus/test/
  alg_process_name=chejian
  app_layer_name=str
  create_path
}

function test_delete()
{
  echo "alg_process_name = "  $alg_process_name  
  echo "app_layer_name = " $app_layer_name
  echo "corepath = " $core_path

  echo clear======
  echo "清除 车检不相关进程"
  clear_other_processfiles
  echo  "清除算法旧 core文件" 
  clear_old_coredump_files  $alg_process_name
  echo  "清除 上层应用旧的core文件"
  clear_old_coredump_files  $app_layer_name
}

function test_start()
{
  test_init
  
  test_delete
}

function local_init()
{
   create_path
}

function disable_coredump()
{
    conf_filename=profile
    touch ${conf_filename}
    sed  '/ulimit -S/d'  /etc/profile   > ${conf_filename}
     echo "ulimit  -c 0 > /dev/null 2>&1" >> ${conf_filename}
    cp -f ${conf_filename}  /etc/profile 
    source  /etc/profile 
    ulimit  -c  0
}

function enable_coredump()
{
    conf_filename=profile
    touch ${conf_filename}
    sed  '/ulimit/d'  /etc/profile   > ${conf_filename}
     echo "ulimit -S -c unlimited > /dev/null 2>&1" >> ${conf_filename}
    cp -f ${conf_filename}  /etc/profile 
    source  /etc/profile 
    ulimit -S -c unlimited
}

function create_path()
{
  core_path=${core_dir}/coredump/coredump_files
  mkdir -p  $core_path
  chmod 777 $core_path
  logfile=${core_dir}/coredump/core_delete.log
  touch -f $logfile
}

function record_log()
{
  logtime=`date '+%Y%m%d-%H%M%S'`
  echo "[$logtime]: $*" >> $logfile
}

 

function setup_coredump_permit()
{
  enable_coredump
# testconfig=`cat /etc/profile |grep ulimit |grep unlimited `
# if [ -z  "$testconfig" ];then
#   enable_coredump
# else
#   echo "nothing to do ..."
# fi
}

function setup_core_path_and_format()
{
  echo "1" > /proc/sys/kernel/core_uses_pid
  echo "$core_path/core-%e-%p-%t" > /proc/sys/kernel/core_pattern
  echo "1" > /proc/sys/fs/suid_dumpable
}


function clear_old_coredump_files()
{
  
  corefilename=$1
  #旧core 文件
  files=`ls -t $core_path | grep $corefilename `
  filestr=(${files//,/})
  i=0
  for item in ${filestr[*]} ;do
#    echo $item
    if [ $i -lt 3  ];then
      echo $i
        i=$((i+1))
        # echo "keepfile:  $item"
    else
        record_log `echo "delete :$i  filename:$item"` 
        rm  -f $core_path/$item 
    fi
   
  
  done
}

function clear_other_processfiles()
{
  
  files=`ls $core_path |grep -v $app_layer_name | grep -v $alg_process_name`
  filestr=(${files//,/})    
  for item in ${filestr[*]};do
     record_log `echo  "delete filename: $item " `
     rm -f $core_path/$item
  done 
}

function checkfile()
{
  ls -t $core_path
}

function Useage()
{
  echo '
  USAGE:   ./cmd  -prameter
  
  -help:
    print help info message
  -init:
    init coredump permited by system 
  -clear:
    clear old core file ,only keep the lastest three files
  -disable:
    disable create coredump
  -list:
    show all coredump files by create time 
  '
}


OPTION=$1
function start()
{
  local_init

echo $OPTION "-------------------"
 case $OPTION in 
   "-init")
    echo init ======
    setup_core_path_and_format
    setup_coredump_permit
    
 ;;
   "-clear")
    echo clear======
    echo "清除 车检不相关进程"
    clear_other_processfiles
    echo  "清除算法旧 core文件" 
    clear_old_coredump_files  $alg_process_name
    echo  "清除 上层应用旧的core文件"
    clear_old_coredump_files  $app_layer_name
 ;;
   "-list") 
    echo list ========
    checkfile
 ;;
  "-disable")
    echo "disable-----------"
    disable_coredump
 ;;
   "-help")
    Useage
 ;;
   *)
   Useage
 ;;
 esac
}



#test_start
start 


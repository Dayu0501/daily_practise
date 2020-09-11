
关于 processCoredump.sh 脚本说明


1.

请通过 sudo -i  切换到 root 用户执行可执行程序  才能生成core文件

2.生成文件名

core-进程名-进程id-时间戳
example:
core-hunHeJiaoTong-3497-1591760717
core_delete.log 会记录 删除的旧core 文件


3.
用法:
root@public-desktop:/opt/vehicle/program/programPath/bin# /opt/vehicle/program/programPath/processCoredump.sh   -help
-help

  USAGE:   ./cmd  -parameter

   -help:
  print help info message
   -init:
  init coredump permited by system
   -disable:
  disable create coredump
   -clear:
  clear old core file ,only keep the lastest three files
   -list:
  show all coredump files by create time

---------------------------------------
  -clear 参数目前会删除不相关进程core文件,  保留三个 最新的chejian_redis 和 三个最新的 hunHeJiaoTong

4.
默认配置:
core_dir=/opt/vehicle/program/
core_path= # default :core_path=${core_dir}/coredump/coredump_files
alg_process_name=chejian_redis
app_layer_name=hunHeJiaoTong

如:进程名 有改动需要手动修改脚本变量值

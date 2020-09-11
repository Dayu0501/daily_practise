echo "this is safe start shell script..."



while true;do
    NUM=`ps aux | grep chejian$ | grep -v grep | wc -l`
    echo "NUM is $NUM"
    if [ "${NUM}" -lt "3" ] ;then   # 当程序宕机,则重启
		#cd programPath
		chmod 777 programPath/start.sh
        ./programPath/start.sh 
    fi   
    sleep 10
done
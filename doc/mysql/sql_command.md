查看当前数据库的连接及状态
show processlist; == select * from information_schema.processlist;

删表语句
drop table u;

show variables = show global variables;
客户端如果太长时间没动静，连接器就会自动将它断开。这个时间是由参数 wait_timeout 控制的，默认值是 8 小时。
show variables like 'wait_timeout';

查询缓存类型的变量
query_cache_type -->DEMAND
	            -->OFF

下面的两条是传说中的双1策略：
这个参数设置成 1 的时候，表示每次事务的 redo log 都直接持久化到磁盘。这个参数我建议你设置成 1，这样可以保证 MySQL 异常重启之后数据不丢失。
innodb_flush_log_at_trx_commit

每次事务的 binlog 都持久化到磁盘。这个参数我也建议你设置成 1，这样可以保证 MySQL 异常重启之后 binlog 不丢失。
sync_binlog 

数据库的隔离级别变量
transaction_isolation

锁等待超时时间
innodb_lock_wait_timeout

死锁检测
innodb_deadlock_detect

change buffer的大小
innodb_change_buffer_max_size

change buffer的开关状态
innodb_change_buffering

控制是否刷邻居的脏页
innodb_flush_neighbors

设置全局变量的值，然后需要退出重连才能使变量针对重连的线程生效，未重连的不生效。
SET GLOBAL  wait_timeout = 604800;
SET @@GLOBAL.wait_timeout = 604800;

information_schema 库的 innodb_trx 这个表中查询长事务，比如下面这个语句，用于查找持续时间超过 60s 的事务。
select * from information_schema.innodb_trx where TIME_TO_SEC(timediff(now(),trx_started))>60;

查询变量
show variables like '%value%';

更新语句
mysql> update T set c=c+1 where ID=2;

建表语句
create table T(id int primary key, k int not null, name varchar(16),index (k))engine=InnoDB;

重建普通索引
alter table T drop index k;
alter table T add index(k);   //非主键索引是可以通过这种方式来重建的

重建主键索引
alter table T drop primary key;
alter table T add primary key(id);    //主键索引不能用这两句的sql重建

alter table T engine=InnoDB //主键索引重建的正确方式

模糊查询
mysql> select * from tuser where name like '张%' and age=10 and ismale=1;

###锁
给表加全局读锁，阻塞写、更新、建表、修改表结构，使整个数据库的实例处于只读的状态。---->使用场景：做全库逻辑备份
Flush tables with read lock ;(FTWRL)

指定表 t 的话，代表的是只关闭表 t；
flush tables t with read lock;
没有指定具体的表名，则表示关闭 MySQL 里所有打开的表。
flush tables with read lock;

给表加表锁（读锁）
LOCK TABLES RecordSoapRequestTimes READ;
给表加表锁（写锁）
LOCK TABLES RecordSoapRequestTimes WRITE;
或者给两个表上锁
lock tables RecordSoapRequestTimes read, system_info write;

给表解锁
unlock tables;
获得MDL的写锁，这是其他线程的针对表t的查询语句就会阻塞住如：select * from t;
lock table t write;  
解锁  
lock table;

[flush table需要研究]
每行都调用一次 sleep(1)，这样这个语句默认要执行该表行数的秒，在这期间表t一致被打开着，这个时候别的线程的flush tables t 命令再要去关闭表 t，就需要等 session A 的查询结束
select sleep(1) from t;

设置可重复读隔离级别
SET SESSION TRANSACTION ISOLATION LEVEL REPEATABLE READ;

启动一个事务并开启一致性快照（一致性视图）
START TRANSACTION  WITH CONSISTENT SNAPSHOT；

####行锁
加共享锁读（）
select k from t where id=1 lock in share mode;
加排它锁读
select k from t where id=1 for update;

例子：
------------------------------------------------------------------------------------------------------------
情况一
线程A                                                     线程B
begin;                                                 	
update t set c=c+1 where id = 1;           				  
														  select * from t where id = 1;
														  不会阻塞（如果是RR级别）
------------------------------------------------------------------------------------------------------------
情况二														  
线程A                                                     线程B
begin;                                                 	
update t set c=c+1 where id = 1;           				  
														  select * from t where id = 1 lock in share mode;
														  会阻塞（RR级别，加锁会使用当前读的方式）
-------------------------------------------------------------------------------------------------------------
mysql 5.7版本
查看在mysql_learnning.t表上加锁的线程：
select * from sys.innodb_lock_waits where locked_table='`mysql_learnning`.`t`'\G
{通过查询 sys.innodb_lock_waits 这张表，我们就可以直接找出造成阻塞的 process id，把这个连接用 kill 命令断开即可。
MySQL启动时设置 performance_schema=on，相比于设置为 off 会有 10% 左右的性能损失} 有待研究，自己测试是空的

干掉4号线程正在执行的语句
KILL QUERY 4;

干掉4号线程
KILL 4；

插入十万条数据的sql
delimiter ;;
create procedure idata()
begin
  declare i int;
  set i=1;
  while(i<=100000)do
    insert into t values(i, i, i);
    set i=i+1;
  end while;
end;;
delimiter ;
call idata();

查看某条语句的执行情况
explain select * from t where a between 10000 and 20000;

告诉优化器，强制使用某一个索引
select * from t force index(a) where a between 10000 and 20000;

查看一个表的索引情况
show index from t；

可以用来重新统计索引信息，重新统计之后，就好了（explain的输出就准确了）
analyze table t；

计算某一列不同值的数量（也就是该列基数的值）
select count(distinct email) as L from SUser;
选取不同长度的前缀来看这个值
select 
  count(distinct left(email,4)）as L4,
  count(distinct left(email,5)）as L5,
  count(distinct left(email,6)）as L6,
  count(distinct left(email,7)）as L7,
from SUser;

让字符串反转
select field_list from t where id_card = reverse('input_id_card_string');

show table status 获取表的信息
show table status like 'tableName' \G

mysql内存池中，脏页比例计算
从mysql5.7.6开始information_schema.global_status已经开始被舍弃，为了兼容性，此时需要打开 show_compatibility_56
下面的计算需要打开 show_compatibility_56，先看一下show variables like '%show_compatibility_56%'; 如果未OFF，set global show_compatibility_56=on;
Innodb_buffer_pool_pages_dirty/Innodb_buffer_pool_pages_total 
select VARIABLE_VALUE into @a from information_schema.global_status where VARIABLE_NAME = 'Innodb_buffer_pool_pages_dirty';  //Innodb_buffer_pool_pages_dirty变量在5.7以后是在performance_schema库中
select VARIABLE_VALUE into @b from information_schema.global_status where VARIABLE_NAME = 'Innodb_buffer_pool_pages_total';  //Innodb_buffer_pool_pages_total变量在5.7以后是在performance_schema库中
select @a/@b;

注：
In MySQL 5.6, system and status variable information is available from these SHOW statements:
SHOW VARIABLES
SHOW STATUS
And from these INFORMATION_SCHEMA tables:
INFORMATION_SCHEMA.GLOBAL_VARIABLES
INFORMATION_SCHEMA.SESSION_VARIABLES
INFORMATION_SCHEMA.GLOBAL_STATUS
INFORMATION_SCHEMA.SESSION_STATUS
 
MySQL 5.7
As of MySQL 5.7.6, the Performance Schema includes these tables as new sources of system and status variable information:
performance_schema.global_variables
performance_schema.session_variables
performance_schema.variables_by_thread
performance_schema.global_status
performance_schema.session_status
performance_schema.status_by_thread
performance_schema.status_by_account
performance_schema.status_by_host
performance_schema.status_by_user


磁盘的IOPS

不存在则插入，存在则忽略（表要求：有PrimaryKey，或者unique索引 ）结果：表id都会自增
insert ignore into friend(friend_1_id, friend_2_id) values(B,A);

on duplicate key update 不存在则插入，存在则更新
1：ON DUPLICATE KEY UPDATE需要有在INSERT语句中有存在主键或者唯一索引的列，并且对应的数据列已经在表中才会执行更新操作。
    而且如果要更新的字段是主键或者唯一索引，不能和表中已有的数据重复，否则插入或更新都失败。
2：不管是更新还是增加语句都不允许将主键或者唯一索引的对应字段的数据变成表中已经存在的数据。
insert into `like`(user_id, liker_id, relation_ship) values(B, A, 2) on duplicate key update relation_ship=relation_ship | 2;
on duplicate key update 比较好的blog
https://blog.csdn.net/qq_22771739/article/details/84668620

optimizer_trace参数？

max_length_for_sort_data，是 MySQL 中专门控制用于排序的行数据的长度的一个参数。它的意思是，如果单行的长度超过这个值，MySQL 就认为单行太大，要换一个算法。
SET max_length_for_sort_data = 16;

explain命令的输出？
binlog_format？
binlog_row_image

下面语句是从第10000条开始的100行数据
select * from t where city in ('杭州',"苏州") order by name limit "10000,100"; 

mysql的慢查询日志？

tmp_table_size 这个配置限制了内存临时表的大小，默认值是 16M。
如果临时表大小超过了 tmp_table_size，那么内存临时表就会转成磁盘临时表。
磁盘临时表使用的引擎默认是 InnoDB，是由参数 internal_tmp_disk_storage_engine 控制的。
set tmp_table_size=1024;
set sort_buffer_size=32768;
set max_length_for_sort_data=16;
/* 打开 optimizer_trace，只对本线程有效 */
SET optimizer_trace='enabled=on'; 

/* 执行语句 */
select word from words order by rand() limit 3;

/* 查看 OPTIMIZER_TRACE 输出 */
SELECT * FROM `information_schema`.`OPTIMIZER_TRACE`\G

MySQL RAND()函数调用可以在0和1之间产生一个随机数，当传入一个整数参数（即种子值）时即指定了seed，则返回可重复的随机数序列。如果未指定种子，则返回完全随机的数字。


###sql语句执行顺序 
1，from 
2，join 
3，on 
4，where（where子句内部执行顺序默认是.. and .. or .. and ..从做往右的，但是mysql的优化器会更具自己的原则做优化，如果在数据量大的时候，最好还是自己手动编写顺序，把能过滤多的条件放到前面）
5，group by(开始使用select中的别名，后面的语句中都可以使用)
6，avg,sum.... 
7，having 
8，select 
9，distinct 
10，order by
11，limit 

order by mainid可以强制走主键索引
select * from t where mainId > 1000000 order by mainId limit 10;

###慢查询日志
查看是否开启慢查询功能
show variables like 'slow_query%';
show variables like 'long_query_time';
slow_query_log 慢查询开启状态
slow_query_log_file 慢查询日志存放的位置（这个目录需要MySQL的运行帐号的可写权限，一般设置为MySQL的数据存放目录）
long_query_time 查询超过多少秒才记录
show variables like 'log_queries_not_using_indexes'; 未使用索引的查询也被记录到慢查询日志中（可选项），如果调优的话，建议开启这个选项。另外，开启了这个参数，其实使用full index scan的sql也会被记录到慢查询日志。
log_output：日志存储方式。log_output='FILE'表示将日志存入文件，默认值是'FILE'。log_output='TABLE'表示将日志存入数据库，这样日志信息就会被写入到mysql.slow_log表中。MySQL数据库支持同时两种日志存储方式，配置的时候以逗号隔开即可，如：log_output='FILE,TABLE'。日志记录到系统的专用日志表中，要比记录到文件耗费更多的系统资源，因此对于需要启用慢查询日志，又需要能够获得更高的系统性能，那么建议优先记录到文件。
系统变量log_slow_admin_statements表示是否将慢管理语句例如ANALYZE TABLE和ALTER TABLE等记入慢查询日志。

想查询有多少条慢查询记录，可以使用系统变量。
show global status like '%Slow_queries%';

####临时配置
默认没有开启慢查询日志记录，通过命令临时开启：
mysql> set global slow_query_log='ON';  
Query OK, 0 rows affected (0.00 sec)

mysql> set global slow_query_log_file='/var/lib/mysql/instance-1-slow.log';  
Query OK, 0 rows affected (0.00 sec)
 
mysql> set global long_query_time=2;  
Query OK, 0 rows affected (0.00 sec)

####永久配置
修改配置文件达到永久配置状态:  
/etc/mysql/conf.d/mysql.cnf  
[mysqld]  
slow_query_log = ON 
slow_query_log_file = /var/lib/mysql/instance-1-slow.log  
long_query_time = 2

配置好后，重新启动 MySQL 即可。

####日志分析工具mysqldumpslow（需要后续研究）
在生产环境中，可以使用MySQL提供的日志分析工具mysqldumpslow。

-s, 是表示按照何种方式排序，
    c: 访问计数
    l: 锁定时间
    r: 返回记录
    t: 查询时间
    al:平均锁定时间
    ar:平均返回记录数
    at:平均查询时间
-t, 是top n的意思，即为返回前面多少条的数据；
-g, 后边可以写一个正则匹配模式，大小写不敏感的；
比如：
得到返回记录集最多的10个SQL。
mysqldumpslow -s r -t 10 /database/mysql/mysql06_slow.log
得到访问次数最多的10个SQL
mysqldumpslow -s c -t 10 /database/mysql/mysql06_slow.log
得到按照时间排序的前10条里面含有左连接的查询语句。
mysqldumpslow -s t -t 10 -g “left join” /database/mysql/mysql06_slow.log
另外建议在使用这些命令时结合 | 和more 使用 ，否则有可能出现刷屏的情况。
mysqldumpslow -s r -t 20 /mysqldata/mysql/mysql06-slow.log | more 


###用Where子句替换HAVING子句  
避免使用HAVING子句，HAVING 只会在检索出所有记录之后才对结果集进行过滤。这个处理需要排序,总计等操作。如果能通过WHERE子句限制记录的数目，那就能减少这方面的开销。(非 oracle中)on、where、having这三个都可以加条件的子句中，on是最先执行，where次之，having最后，因为on是先把不符合 条件的记录过滤后才进行统计，它就可以减少中间运算要处理的数据，按理说应该速度是最快的，where也应该比having快点的，因为它过滤数据后才进 行sum，在两个表联接时才用on的，所以在一个表的时候，就剩下where跟having比较了。在这单表查询统计的情况下，如果要过滤的条件没有涉及 到要计算字段，那它们的结果是一样的，只是where可以使用rushmore技术，而having就不能，在速度上后者要慢如果要涉及到计算的字段，就 表示在没计算之前，这个字段的值是不确定的，根据上篇写的工作流程，where的作用时间是在计算之前就完成的，而having就是在计算后才起作用的， 所以在这种情况下，两者的结果会不同。在多表联接查询时，on比where更早起作用。系统首先根据各个表之间的联接条件，把多个表合成一个临时表后，再 由where进行过滤，然后再计算，计算完后再由having进行过滤。由此可见，要想过滤条件起到正确的作用，首先要明白这个条件应该在什么时候起作 用，然后再决定放在那里。
提高条件查询效率的sql优化
https://www.cnblogs.com/zhaoyongjiang/p/7227254.html

where子句的执行顺序
大多时候mysql会自动根据sql语句做出优化，使用最优的sql语句进行查询
有时候mysql无法根据sql语句做出最优的优化顺序，所以还是要我们自己预判断出哪种过滤是最优，毕竟自己才最懂自己的数据。能过滤掉多的条件尽量放在左边，where子句mysql的默认的是从左往右，oracle是从右往左。

MySQL 优化器执行过程中，where 条件部分， a=b 和 b=a 的写法是一样的。


将tradid转成int类型
select * from tradelog where  CAST(tradid AS signed int) = 110717;

修改表的某字段的字符集编码
alter table trade_detail modify tradeid varchar(32) CHARACTER SET utf8mb4 default null;

将l.traideid的字符集转为utf8
select d.* from tradelog l , trade_detail d where d.tradeid=CONVERT(l.tradeid USING utf8) and l.id=2; 

$取的是tradeid的值 $需要待查
select operator from tradelog  where traideid =$R4.tradeid.value; 

c上非唯一索引
select * from t where c >=15 and c <= 20 order by desc lock in share mode;
这个语句where条件的处理流程是先c<=20,在c>=15，因为是降序

select * from t where c >=15 and c <= 20 lock in share mode;
这个语句where条件的处理流程是先c>=15，在c <= 20，因为默认是升序

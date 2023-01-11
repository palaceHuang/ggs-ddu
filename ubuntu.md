# Linux常用命令

1. 查看操作系统版本
   cat /proc/version
   uname -a
2. 修改密码
   sudo passwd user-name
3. 关机/重启
   shutdown -h now 
   shutdown -r now | reboot
4. 查看文件|文件系统状态
   stat [OPTION]... FILE...
5. 远程登录linux机器
   ssh root@ip

# docker命令

1. 查看docker版本
   docker version
2. 查看docker容器
   docker ps
3. 进入docker容器bash
   docker run -i -t image-name /bin/bash
4. 退出docker容器bash
   exit或者CTRL+D
5. 在宿主机查看容器内标准输出
   docker logs container-id
6. 启动容器/停止容器
   docker run -d image-name
   docker stop image-id


# 脚本解析

## 备份脚本

```bash
#!bin/bash
cd /root/gitlab

set -e

/usr/local/bin/docker-compose stop gitlab
/usr/local/bin/docker-compose rm -f gitlab
/usr/local/bin/docker-compose run --rm gitlab app:rake gitlab:backup:create
/usr/local/bin/docker-compose up -d

rsync -vh --remove-source-files --progress /data/docker/gitlab/gitlab/backups/*.tar root@192.168.50.83:/backups/gitlab/docker

```
1. #!bin/bash
   使用/bin/bash执行脚本
2. set -e
   只要脚本发生错误，就停止执行
3. docker-compose stop gitlab
   ```
   Usage: docker-compose stop [options] [SERVICE...]

   Options:
    -t, --timeout TIMEOUT Specify a shutdown timeout in seconds.(default 10)
   ```
   Stops running containers without removing them. They can be started again with docker-compose start.
4. docker-compose rm -f gitlab
    ```
    Usage: docker-compose rm [options] [SERVICE...]

    Options:
       -f, --force   Don't ask to confirm removal
       -s, --stop    Stop the containers, if required, before removing
       -v            Remove any anonymous volumes attached to containers
       -a, --all     Deprecated - no effect.
    ```
    Removes stopped service containers


5. docker-compose run --rm gitlab app:rake gitlab:backup:create
   sameersbn/gitlab提供的备份命令，详情参见：https://github.com/sameersbn/docker-gitlab/issues/987
   ```
    Usage: 
        docker-compose run [options] [-v VOLUME...] [-p PORT...] [-e KEY=VAL...] [-l KEY=VALUE...] 
            SERVICE [COMMAND] [ARGS...]
    Options:
        --rm Remove container after run. Ignored in detached mode.
   ```
   Runs a one-time command against a service.
6. docker-compose up -d
   ```
    Usage:
        docker-compose up [options] [--scale SERVICE=NUM...] [SERVICE...]
    
    Options:
        -d, --detach Detached mode: Run containers in the background, print new container names. Incompatible with --abort-on-container-exit.

   ```
   Builds, (re)creates, starts, and attaches to containers for a service.

   Unless they are already running, this command also starts any linked services.
7. rsync -vh --remove-source-files --progress /data/docker/gitlab/gitlab/backups/*.tar root@192.168.50.83:/backups/gitlab/docker  
   rsync 是一个常用的Linux应用程序，用于本地计算机与本地计算机或远程计算机之间同步文件（但不支持两台远程计算机之间的同步）。与其它文件传输工具（如FTP或SCP）不同，rsync最大的特点是会检查发送方和接收方已有的文件，金传输有变动的部分（默认规则是文件大小和修改时间有变动）  
   rsync is a file transfer program capable of efficient remote update via a fast differencing algorithm.
   ```
   Usage: rsync [OPTION]... SRC [SRC]... DEST
      or rsync [OPTION]... SRC [SRC]... [USER@]HOST:DEST
      or rsync [OPTION]... SRC [SRC]... [USER@]HOST::DEST
      or rsync [OPTION]... SRC [SRC]... rsync://USER@]HOST[:PORT]/DEST
      or rsync [OPTION]... [USER@]HOST:SRC [DEST]
      or rsync [OPTION]... [USER@]HOST::SRC [DEST]
      or rsync [OPTION]... rsync://[USER@]HOST[:PORT]/SRC [DEST]

   Options:
      -v increase vervosity
      -h output numbers in a human-readable format
      --progress  show progress during transfer
      --remove-source-files  sender removes synchronized files(non-dirs)
   ```
## 计划任务

crontab计划任务实现自动备份和清理，脚本目录：/var/spool/cron

计划内容
```
0 4 * * 6 /root/gitlab/backup.sh >/root/gitlab/backup.log 2>&1
```
命令详解
```
Usage: crontab [ -u user ] file
   or crontab [ -u user ] {-l | -r | -e}

Params：
   -e 执行文字编辑器来设定时程表，默认为vi
   -r 删除目前的时程表
   -l 列出当前的时程表

计划内容格式：f1 f2 f3 f4 f5 program
   *    *    *    *    *
   -    -    -    -    -
   |    |    |    |    |
   |    |    |    |    +----- 星期中星期几 (0 - 6) (星期天 为0)
   |    |    |    +---------- 月份 (1 - 12) 
   |    |    +--------------- 一个月中的第几天 (1 - 31)
   |    +-------------------- 小时 (0 - 23)
   +------------------------- 分钟 (0 - 59)
   当f1为*时表示每分钟都要执行program, f2为*表示每小时都要执行program，其余类推
   当f1为a-b时表示从第a分钟到第b分钟这段时间内要执行，其余类推
   当f1为*/n时表示每n分钟个时间间隔执行一次，其余类推
   当f1为a,b,c时，表明第a,b,c分钟要执行，其余类推
```
## 清理脚本

脚本内容
```bash
find /backups/gitlab/docker -type f -mtime +40 -exec rm -f {} \; # 保留40天
find /backups/clpdnpm/docker -type f -mtime +40 -exec rm -f {} \; # 保留40天
find /backups/redmine -type f -mtime +40 -exec rm -f {} \; # 保留40天
find /backups/zendao -type f -mtime +40 -exec rm -f {} \; # 保留40天
```
find命令详解
```
Usage: find [path...] [expression]

Expression:
   选项 总是影响所有操作
   测试 返回一个真值或假值
   动作 

   TESTS
      数字参数格式：
         +n    比n大
         -n     比n小
         n       等于n
      
         -atime   n 对文件的最后一次访问是在n*24小时之前
         -ctime   n 对文件状态的最后一次修改是在n*24小时之前
         -mtime  n 对文件数据的最后一次修改是在n*24小时之前
          -type   c
               文件类型c可取值列表：
                  b 特殊块文件（缓冲的)
                  c 特殊字符文件（不缓冲）
                  d 目录
                  p 命名管道（FIFO)
                  f  普通文件
                  l  符号链接
                  s  套接字

   ACTIONS
      -exec command
         如果command返回值为0，exec返回true。command以;结束，其中所有的{}，都将以正在处理的文件名替换。
```

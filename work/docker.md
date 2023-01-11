[toc]

# CentOS8 使用 yum 报错

## 问题

```
[test@localhost lib]$ sudo yum install -y yum-utils
CentOS-8 - AppStream                            118  B/s |  38  B     00:00
Error: Failed to download metadata for repo 'AppStream': Cannot prepare internal                                                                                                                               mirrorlist: No URLs in mirrorlist
```

## 原因

在 2022 年 1 月 31 日，CentOS 团队从官方镜像中删除 CentOS 8 的所有包。现在它们被转移到https://vault.centos.org/

## 解决方法 1

如果你仍需要运行 CentOS 8，你可以在/etc/yum.repos.d 中更新一下源，使用 vault.centos.org 代替 mirror.centos.org

```
# sudo sed -i -e "s|mirrorlist=|#mirrorlist=|g" /etc/yum.repos.d/CentOS-*
# sudo sed -i -e "s|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g" /etc/yum.repos.d/CentOS-*
```

## 解决方法 2

可以通过更改为阿里云的源来解决问题

1. 配置文件备份  
   cd /etc/yum.repos.d/ && mkdir backup && mv \*repo backup/
2. 下载阿里源文件  
   curl -o /etc/yum.repos.d/CentOS-Base.repo http://mirrors.aliyun.com/repo/Centos-8.repo
3. 更新源里的地址
   ```
   # sudo sed -i -e "s|mirrors.cloud.aliyuncs.com|mirrors.aliyun.com|g" /etc/yum.repos.d/CentOS-*
   # sudo sed -i -e "s|releasever|releasever-stream|g" /etc/yum.repos.d/CentOS-*
   ```
4. 生成缓存  
   yum clean all && yum makecache

# 用户 test 执行 sudo 报错

```
test is not in the sudoers file.  This incident will be reported.
```

切换到 root 用户下，然后为/etc/sudoers 文件赋权，之后编辑文件，添加 test ALL=(ALL) ALL,保存

```
su
chmod 777 /etc/sudoers
vi /etc/sudoers
```

若想在 sudo 的时候不输入密码，配置调整为：test ALL=(ALL) NOPASSWD:ALL

# Docker 安装和卸载

## 安装

```
dnf check-update
dnf upgrade --allowerasing --skip-broken --nobest
sudo dnf remove podman buidah -y
sudo yum install -y yum-utils
sudo yum-config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
sudo yum remove docker \
                   docker-client \
                   docker-client-latest \
                   docker-common \
                   docker-latest \
                   docker-latest-logrotate \
                   docker-logrotate \
                   docker-engine \
                   podman \
                   runc

sudo yum install docker-ce docker-ce-cli containerd.io

systemctl enable --now docker

systemctl status docker

```

### Uninstall old versions

```
sudo yum remove docker \
                  docker-client \
                  docker-client-latest \
                  docker-common \
                  docker-latest \
                  docker-latest-logrotate \
                  docker-logrotate \
                  docker-engine
```

### Set up the repository

```
$ sudo yum install -y yum-utils
$ sudo yum-config-manager \
    --add-repo \
    https://download.docker.com/linux/centos/docker-ce.repo
```

### Install Docker engine

1. Install the latest version of Docker Engine,containerd,and Docker Compose or go to the next step to install a specific version:
2.

## 卸载 docker

### yum 卸载 docker

查看已安装的 docker

```
yum list installed | grep docker
```

运行之后显示如下：

```
containerd.io.x86_64                 1.4.3-3.1.el7                  @docker-ce-stable
docker-ce.x86_64                     3:20.10.1-3.el7                @docker-ce-stable
docker-ce-cli.x86_64                 1:20.10.1-3.el7                @docker-ce-stable
docker-ce-rootless-extras.x86_64     20.10.1-3.el7                  @docker-ce-stable
```

依次删除

```bash
yum -y remove docker-ce.x86_64
yum -y remove docker-ce-cli.x86_64
yum -y remove containerd.io.x86_64
```

接着删除 docker 储存的文件、镜像、容器

```
rm -rf /var/lib/docker
```

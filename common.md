2022-2-16
--------------------------------------------------------------------------
GITHUB上的REPO无法CLONE
	GIT配置代理
		git config --global http.proxy 127.0.0.1:7890
	重新clone
		成功
	注意操作完github之后，要将配置还原，否则公司的gitlab将无法正常使用
		git config --global --unset http.proxy
		
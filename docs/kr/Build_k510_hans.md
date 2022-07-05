
## git clone
```shell
git clone https://github.com/kendryte/k510_buildroot.git
```

## docker
```shell
sh k510_buildroot/tools/docker/run_k510_docker.sh
```

## compile dl / Deep Learing, Neural Network engine
modify Makefile not to download nl.tar if you have aready have it.

```shell
[CAN k510_buildroot]$ make dl
```

#### downloaded files:
* https://github.com/kendryte/k510_buildroot/releases/download/v1.6/dl.tar.gz  to  pkg-download/dl.tar.gz
* https://github.com/kendryte/k510_buildroot/releases/download/v1.7/ai_kmodel_data.tar.xz  to  dl/ai/ai_kmodel_data.tar.xz
* https://github.com/kendryte/nncase/releases/download/v1.7.0/nncaseruntime-k510-v1.7.0.tgz to dl/nncase_linux_runtime
* https://github.com/kendryte/nncase/releases/download/v1.7.0/nncase-1.7.0.20220530-cp310-cp310-manylinux_2_24_x86_64.whl to dl/nncase_linux_runtime
* https://github.com/kendryte/nncase/releases/download/v1.7.0/nncase-1.7.0.20220530-cp36-cp36m-manylinux_2_24_x86_64.whl to dl/nncase_linux_runtime
* https://github.com/kendryte/nncase/releases/download/v1.7.0/nncase-1.7.0.20220530-cp37-cp37m-manylinux_2_24_x86_64.whl to dl/nncase_linux_runtime
* https://github.com/kendryte/nncase/releases/download/v1.7.0/nncase-1.7.0.20220530-cp38-cp38-manylinux_2_24_x86_64.whl to dl/nncase_linux_runtime
* https://github.com/kendryte/nncase/releases/download/v1.7.0/nncase-1.7.0.20220530-cp39-cp39-manylinux_2_24_x86_64.whl to dl/nncase_linux_runtime
* https://github.com/kendryte/nncase/releases/download/v1.7.0/nncase_k510-1.7.0.20220606-py2.py3-none-manylinux_2_24_x86_64.whl to dl/nncase_linux_runtime


## first compile.

==>  first compile 이전에 config 파일을 수정할 필요가 있다. menuconfig로 하면 되는데, 그러려면 first comile이 필요하다.
config 파일을 수정하면 바로 컴파일이 가능하다.
[k510_crb_lp3_v1_2_defconfig](..\conf_files\k510_crb_lp3_v1_2_defconfig) ==> K510SDK\configs

```shell
[CAN k510_buildroot] make CONF=k510_crb_lp3_v1_2_defconfig

```
> directory k510_crb_lp3_v1_2_defconfig is created




[first comile log](firstcompile.log)

## menuconfig
```shell
[CAN k510_buildroot] make CONF=k510_crb_lp3_v1_2_defconfig menuconfig

```














## config files
[rc.sysinit](../conf_files/rc.sysinit)  to  /etc/init.d/rc.sysinit
[nginx.conf](../conf_files/nginx.conf)   to /etc/nginx/nginx.comf
[php-fpm.conf](../conf_file/php-fpm.conf)   to /etc/php-fpm.conf
[sshd_config](../conf_file/sshd_config)   to /etc/ssh/sshd_config






umount /root/emmc/p2
umount /root/emmc/p3
umount /root/emmc/p4
mount | grep emmc

/bin/echo "Starting copying"
dd if=/root/sd/p3/sysimage-emmc.img of=/dev/mmcblk0 bs=1M

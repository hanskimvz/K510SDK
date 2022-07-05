


#### realtime clock
Kernel (make linux-menuconfig)
```shell
Main -> Device-drivers -> Real Time Clock 
[*] Set system time from RTC on startup and resume 
    (rtc0)  RTC used to set the system time
[*] Set the RTC time based on NTP synchronization 
    (rtc0)  RTC used to synchronize NTP adjustment
[ ] RTC debug support
[*] RTC non volatile storage support
*** RTC interfaces ***
[*] /sys/class/rtc/rtcN (sysfs)
[*] /proc/driver/rtc (procfs for rtcN)
[*] /dev/rtcN (character devices)
[ ] RTC UIE emulation on dev interface
.
.
.
<*>   Kendryte Real Time Clock
```
```shell
[root@canaan ~ ]$ dmesg |grep rtc
[    2.829660] kendryte-rtc 970d0000.rtc: hctosys: unable to read the hardware clock
```

```c
    fd = open("/dev/rtc0", O_RDWR);
    if (fd == -1) {
        printf("RESULT:FAIL /dev/rtc0 %s",strerror(errno));
        exit(errno);
    }
    retval = ioctl(fd, RTC_RD_TIME, &rtc_tm);
    if (retval == -1) {
        printf("RESULT:FAIL ioctl %s",strerror(errno));
        exit(errno);
    }

    fprintf(stdout, "RTC date/time: %d/%d/%d %02d:%02d:%02d\n",
        rtc_tm.tm_mday, rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,
        rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);

    close(fd);
```

** 아직 문제가 있슴. 일다 한번 쓰기에 성공하면 다음부터 읽는 것은 가능, 그러나 이 기능은 아무 쓸모 없슴.
** 쓰는게 문제가 아니라 부팅시에 ntp에 연결이 안되면 system과 동기화 하는게 rtc의 목적이니까...

/proc/driver/rtc, 아래는 정상
rtc_time	: 03:09:15
rtc_date	: 2022-07-05
alrm_time	: 00:00:00
alrm_date	: 1970-01-01
alarm_IRQ	: no
alrm_pending	: no
update IRQ enabled	: no
periodic IRQ enabled	: no
periodic IRQ frequency	: 1
max user IRQ frequency	: 64
24hr		: yes
alarm_IRQ	: no
tick_IRQ	: no

초기 시스템은 아래와 같이 rtc_time과 rtc_date가 존재하지 않는다.
아마 뱃터리가 없엇 값이 없어진 것 같다.
alrm_time	: 00:00:00
alrm_date	: 1970-01-01
alarm_IRQ	: no
alrm_pending	: no
update IRQ enabled	: no
periodic IRQ enabled	: no
periodic IRQ frequency	: 1
max user IRQ frequency	: 64
24hr		: yes
alarm_IRQ	: no
tick_IRQ	: no

reboot 명령어로 reboot을 하면 rtc_time과 rtc_date가 살아있다.
그런데 시간이 엉망이다. 


rtc_time	: 08:44:51
rtc_date	: 2022-07-05








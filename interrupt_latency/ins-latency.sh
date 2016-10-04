#!/bin/bash
TMP=$PWD
cd /usr/realtime/modules/

check=`lsmod | grep -c "^rtai_hal"`
if [ $check == 0 ]
then
	/sbin/insmod ./rtai_hal.ko
fi

cd $TMP
check=`lsmod | grep -c "^latency"`
if [ $check == 0 ]
then
	/sbin/insmod ./latency.ko
else
	/sbin/rmmod latency
	/sbin/insmod ./latency.ko
fi

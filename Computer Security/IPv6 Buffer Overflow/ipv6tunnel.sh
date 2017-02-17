#!/bin/bash
#HE 6in4 Script Configuration

HE_REMOTE_IP="209.51.161.58"
YOUR_IPV4_IP=""

if[ -z $1 ]
then
	echo "$0 <start|stop>"
	exit
fi

case "$1" in
	start)
		ip tunnel add he-ipv6 mode sit remote $HE_REMOTE_IP local $YOUR_IPV4_IP ttl 255
		ip link set he-ipv6 up
		ip addr add 2001:470:4:ca8::2/64 dev he-ipv6
		ip route add ::/0 via 2001:470:4:ca8::1 dev he-ipv6
		ip -f inet6 addr
		;;
	stop)
		ip link set he-ipv6 down
		ip tunnel del he-ipv6
		;;
	*)
		echo "type ./ipv6tunnel.sh"
	;;
esac

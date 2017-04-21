#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <netinet/ip.h> 
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <linux/if_packet.h>
#include <linux/if_ether.h>

#define FAILURE -1
#define TARGET_MAC "\x08\x00\x27\xa3\x74\xad"
#define HOST_MAC   "\x08\x00\x27\x7c\x74\xc4"
#define IFACE	"eth0"

#define TARGET_IP "192.168.1.121"
#define HOST_IP "192.168.1.138"

#define BUFFER_SIZE 1024
#define ARP_REPLY 0x02
#define MAC_LENGTH 6
#define PROTO_ARP 0x0806
#define IPV4_LENGTH 4
#define HW_TYPE 1

struct arp_header {
    unsigned short hardware_type;
    unsigned short protocol_type;
    unsigned char hardware_len;
    unsigned char protocol_len;
    unsigned short opcode;
    unsigned char sender_mac[MAC_LENGTH];
    unsigned char sender_ip[IPV4_LENGTH];
    unsigned char target_mac[MAC_LENGTH];
    unsigned char target_ip[IPV4_LENGTH];
} __attribute__((packed));
/*
ETH_ALEN = 6
struct ethhdr {
         unsigned char   h_dest[ETH_ALEN];       /* destination eth addr 
         unsigned char   h_source[ETH_ALEN];     /* source ether addr    
         __be16          h_proto;                /* packet type ID field 
} __attribute__((packed));     
*/
int main(int argc , char** argv)
{
	/* set up socket*/
    int sockfd;   
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) == FAILURE)
    {
        fprintf(stderr, "Could not create socket\n");
		exit(1);
    }
	
	/* binding socket for use */
	struct sockaddr_ll linklayer;
    memset(&linklayer, 0, sizeof(struct sockaddr_ll));
    linklayer.sll_family = AF_PACKET;
    linklayer.sll_ifindex =  if_nametoindex(IFACE);
    if (bind(sockfd, (struct sockaddr*) &linklayer, sizeof(struct sockaddr_ll)) == FAILURE) {	
		fprintf(stderr, "Could not bind socket\n");
		close(sockfd);
		exit(1);
    }
	/* set up packet for ARP*/
	linklayer.sll_protocol = htons(ETH_P_ARP);
	linklayer.sll_hatype = ARPHRD_ETHER;
	linklayer.sll_pkttype = PACKET_BROADCAST; 
	linklayer.sll_halen = MAC_LENGTH;
	linklayer.sll_addr[6] = 0x00;
	linklayer.sll_addr[7] = 0x00;
	
	/*get IPs in network form*/
	struct sockaddr_in sa;
	inet_pton(AF_INET, HOST_IP, &(sa.sin_addr));
	uint32_t src_ip = htonl(sa.sin_addr.s_addr);
	inet_pton(AF_INET, TARGET_IP, &(sa.sin_addr));
	uint32_t dst_ip = htonl(sa.sin_addr.s_addr);

	/*set up packet */
	unsigned char packet[BUFFER_SIZE];
	memset(packet, 0, BUFFER_SIZE);
	
	/*ethernet header*/
	struct ether_header* eth_header = (struct ether_header*) packet;
	memcpy(eth_header->ether_dhost, TARGET_MAC, MAC_LENGTH);
	memcpy(eth_header->ether_shost, HOST_MAC, MAC_LENGTH);
	eth_header->ether_type = htons(ETHERTYPE_ARP);
	
	/*ARP portion*/
	struct arp_header* arp_header = (struct arp_header*) (packet + sizeof(struct ether_header));	
	memcpy(arp_header->target_mac, TARGET_MAC, MAC_LENGTH);
	memcpy(arp_header->sender_mac, HOST_MAC, MAC_LENGTH);
    memcpy(arp_header->sender_ip, &src_ip, IPV4_LENGTH);
    memcpy(arp_header->target_ip, &dst_ip, IPV4_LENGTH);
	arp_header->hardware_type = htons(HW_TYPE);
    arp_header->protocol_type = htons(ETH_P_IP);
    arp_header->hardware_len = MAC_LENGTH;
    arp_header->protocol_len = IPV4_LENGTH;
    arp_header->opcode = htons(ARP_REPLY);
	
	/*send on socket*/
	uint32_t ARP_PACKET_SIZE = sizeof(struct ether_header) + sizeof(struct arp_header);	
    if (sendto(sockfd, packet, ARP_PACKET_SIZE, 0, (struct sockaddr*) &linklayer, sizeof(struct sockaddr_ll)) == -1)
	{
		fprintf(stderr, "Failed to send\n");
	}
	close(sockfd);
	printf("ARP reply packet sent\n");
	return 0;
}
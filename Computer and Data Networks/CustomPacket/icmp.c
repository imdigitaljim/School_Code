#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <netinet/ip.h> 
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <linux/if_packet.h>
#include <linux/if_ether.h>

#define FAILURE -1
#define IFACE	"eth0"

#define TARGET_IP "192.168.1.121"
#define HOST_IP "192.168.1.138"

#define BUFFER_SIZE 1024
#define HW_TYPE 1
#define IP4_HDRLEN 20         

struct icmp_header {
    unsigned char type;
    unsigned char code;
    unsigned short checksum;
	unsigned short identifier;
	unsigned short sequence_num;
	unsigned int originate_time;
	unsigned int receive_time;
	unsigned int transmit_time;
} __attribute__((packed));

int main(int argc , char** argv)
{
	int sd;
	struct ifreq iface;

	if ((sd = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) == FAILURE) {
		fprintf(stderr, "Could not create socket\n");	
		exit(1);
	}

	// Use ioctl() to look up interface index which we will use to
	// bind socket descriptor sd to specified interface with setsockopt() since
	// none of the other arguments of sendto() specify which interface to use.
	memset(&iface, 0, sizeof (iface));
	memcpy(iface.ifr_name, IFACE, sizeof(iface.ifr_name));
	if (ioctl (sd, SIOCGIFINDEX, &iface) == FAILURE) {
		fprintf(stderr, "SIOCGIFINDEX\n");
		exit(1);
	}
	close (sd);
	printf ("Index for interface %s is %i\n", IFACE, iface.ifr_ifindex);
	
	/* set up socket*/
    int sockfd;   
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) == FAILURE)
    {
        fprintf(stderr, "Could not create socket\n");
		exit(1);
    }
	// Set flag so socket expects us to provide IPv4 header.
	const int on = 1;
	if (setsockopt (sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof (on))  == FAILURE) {
		fprintf(stderr, "Could not set IP_HDRINCL \n");
		exit (1);
	}

	// Bind socket to interface index.
	if (setsockopt (sockfd, SOL_SOCKET, SO_BINDTODEVICE, &iface, sizeof(iface)) == FAILURE) {
		fprintf(stderr, "Could bind to interface \n");
		exit (1);
	}

	/*get IPs in network form*/
	struct sockaddr_in sa;
	inet_pton(AF_INET, HOST_IP, &(sa.sin_addr));
	uint32_t src_ip = sa.sin_addr.s_addr;
	inet_pton(AF_INET, TARGET_IP, &(sa.sin_addr));
	uint32_t dst_ip = sa.sin_addr.s_addr;

	/*set up packet */
	unsigned char packet[BUFFER_SIZE];
	memset(packet, 0, BUFFER_SIZE);
	
	
	struct ip *iphdr = (struct ip *) packet;
    struct icmp_header *icmp = (struct icmp_header *) (packet + sizeof (struct ip));
	memset(icmp, 0, sizeof(struct icmp_header));
	int PACKET_SIZE = sizeof (struct iphdr) + sizeof (struct icmp_header);

	iphdr->ip_hl = 5; 
	iphdr->ip_v = 4;
	iphdr->ip_tos = 0;
	
	iphdr->ip_len = htons (IP4_HDRLEN +  sizeof (struct icmp_header));

	iphdr->ip_id = 0;
	iphdr->ip_off = 0;
	iphdr->ip_ttl = 255;
	iphdr->ip_p = IPPROTO_ICMP;
	
	iphdr->ip_src.s_addr = src_ip;
	iphdr->ip_dst.s_addr = dst_ip;
		
    icmp->type = ICMP_TIMESTAMPREPLY;
    icmp->code = 0;
    icmp->checksum = 0;
	icmp->originate_time = 123456;
	icmp->receive_time = 789456;
	icmp->transmit_time = 555555;
		
	struct sockaddr_in host_info;
    host_info.sin_family = AF_INET;
    host_info.sin_addr.s_addr = dst_ip;
    memset(&host_info.sin_zero, 0, sizeof (host_info.sin_zero));
	
    if (sendto(sockfd, packet, PACKET_SIZE, 0, (struct sockaddr*) &host_info, sizeof(struct sockaddr_in)) == -1)
	{
		fprintf(stderr, "Failed to send\n");
		exit(1);
	}
	close(sockfd);
	printf("ICMP packet sent\n");
	return 0;
}
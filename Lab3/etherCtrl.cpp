#include <errno.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>

#define NAME_SIZE 16

using namespace std;

int main()
{
    int fd;
    int ret;
    int selection;
    struct sockaddr_in *addr;
    char *address;
    unsigned char ip_address[15];
    struct ifreq ifr;
    struct ifconf ifc;
    char if_name[NAME_SIZE];
    unsigned char *mac=NULL;

    cout << "Enter the interface name: ";
    cin >> if_name;

    size_t if_name_len=strlen(if_name);
    if (if_name_len<sizeof(ifr.ifr_name)) {
        memcpy(ifr.ifr_name,if_name,if_name_len);
        ifr.ifr_name[if_name_len]=0;
    } else {
        cout << "Interface name is too long!" << endl;
	return -1;
    }

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd<0) {
        cout << strerror(errno);
	return -1;
    }

    system("clear");
    do {
        cout << "Choose from the following:" << endl;
	cout << "1. Hardware address" << endl;
	cout << "2. IP address" << endl;
	cout << "3. Network mask" << endl;
	cout << "4. Broadcast address" << endl;
	cout << "0. Exit" << endl << endl;
	cin >> selection;
	switch(selection) {
        case 1:
            ret = ioctl(fd, SIOCGIFHWADDR, &ifr);
            if(ret<0) {
                cout << strerror(errno);
            } else if(ifr.ifr_hwaddr.sa_family!=ARPHRD_ETHER) {
                cout << "not an Ethernet interface" << endl;
            } else {
                mac=(unsigned char*)ifr.ifr_hwaddr.sa_data;
                printf("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n", mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	    }
            break;
        case 2:
            ioctl(fd, SIOCGIFADDR, &ifr);

              strcpy(reinterpret_cast<char*>(ip_address),inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
              printf("System IP Address is: %s\n",ip_address);
            break;
        case 3:
           ioctl(fd, SIOCGIFNETMASK, &ifr);
           printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_netmask)->sin_addr));
	   //MW: You want to retrieve ifr_netmask, not sin_addr. Take a close look at the
	   //    structure to see how to retrieve ifr_netmask
            break;
        case 4:
	if(ioctl(fd,SIOCGIFBRDADDR, &ifr)== -1)
	perror("ioctl error"),exit(1);
	addr = (struct sockaddr_in *) &ifr.ifr_broadaddr;
	address = inet_ntoa(addr->sin_addr);
	printf("broad address is:%s\n",address);
            break;
        }
	if(selection!=0) {
            char key;
            cout << "Press any key to continue: ";
            cin >> key;
            system("clear");
        }
    } while (selection!=0);


    close(fd); 
    return 0;
}

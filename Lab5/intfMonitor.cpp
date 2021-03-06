//intfMonitor_solution.cpp - An interface monitor
//
// 13-Jul-20  M. Watler         Created.

#include <fcntl.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

const int MAXBUF=128;
bool isRunning=false;

//TODO: Declare your signal handler function prototype
static void interruptHandler(int signum); 
int main(int argc, char *argv[])
{
    //TODO: Declare a variable of type struct sigaction
    struct sigaction action;
    //      For sigaction, see http://man7.org/linux/man-pages/man2/sigaction.2.html
     action.sa_handler = interruptHandler
     action.sa_flags = 0;
    char interface[MAXBUF];
    char statPath[MAXBUF];
    const char logfile[]="Network.log";//store network data in Network.log
    int retVal=0;

    //TODO: Register signal handlers for SIGUSR1, SIGUSR2, ctrl-C and ctrl-Z
     sigaction(SIGINT, &action, NULL);
     sigaction(SIGUSR1, &action, NULL);
     sigaction(SIGUSR2, &action, NULL);
     sigaction(SIGTSTP, &action, NULL);
    //TODO: Ensure there are no errors in registering the handlers
     if (action1 < 0 || action2 < 0 || action3 < 0 || action4 < 0 ) {
       cout << "There was an error" << endl;
       return -1;
    }
    strncpy(interface, argv[1], MAXBUF);//The interface has been passed as an argument to intfMonitor
    int fd=open(logfile, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    cout<<"intfMonitor:main: interface:"<<interface<<":  pid:"<<getpid()<<endl;

    //TODO: Wait for SIGUSR1 - the start signal from the parent
    pause();
    while(isRunning) {
        //gather some stats
        int tx_bytes=0;
        int rx_bytes=0;
        int tx_packets=0;
        int rx_packets=0;
	    ifstream infile;
            sprintf(statPath, "/sys/class/net/%s/statistics/tx_bytes", interface);
	    infile.open(statPath);
	    if(infile.is_open()) {
	        infile>>tx_bytes;
	        infile.close();
	    }
            sprintf(statPath, "/sys/class/net/%s/statistics/rx_bytes", interface);
	    infile.open(statPath);
	    if(infile.is_open()) {
	        infile>>rx_bytes;
	        infile.close();
	    }
            sprintf(statPath, "/sys/class/net/%s/statistics/tx_packets", interface);
	    infile.open(statPath);
	    if(infile.is_open()) {
	        infile>>tx_packets;
	        infile.close();
	    }
            sprintf(statPath, "/sys/class/net/%s/statistics/rx_packets", interface);
	    infile.open(statPath);
	    if(infile.is_open()) {
	        infile>>rx_packets;
	        infile.close();
	    }
	    char data[MAXBUF];
	    //write the stats into Network.log
	    int len=sprintf(data, "%s: tx_bytes:%d rx_bytes:%d tx_packets:%d rx_packets: %d\n", interface, tx_bytes, rx_bytes, tx_packets, rx_packets);
	    write(fd, data, len);
	    sleep(1);
    }
    close(fd);

    return 0;
}

//TODO: Create a signal handler that starts your program on SIGUSR1 (sets isRunning to true),
//      stops your program on SIGUSR2 (sets isRunning to false),
//      and discards any ctrl-C or ctrl-Z.
       static void interruptHandler(int signum) {  
       switch(signum) {      
//      If the signal handler receives a SIGUSR1, the following message should appear on the screen:
//      intfMonitor: starting up
        case SIGUSR1:
        cout << "intfMonitor: starting up" << endl;
        isRunning = true;       
        break;
//      If the signal handler receives a ctrl-C, the following message should appear on the screen:
//      intfMonitor: ctrl-C discarded
        case SIGINT:
        cout << "intfMonitor: ctrl-C discarded" << endl;
        break;
//      If the sig
//      If the signal handler receives a ctrl-Z, the following message should appear on the screen:
//      intfMonitor: ctrl-Z discarded
        case SIGTSTP:
        cout << "intfMonitor: ctrl-Z discarded" << endl;
        break;
//      If the signal handler receives a SIGUSR2, the following message should appear on the screen:
//      intfMonitor: shutting down
        case SIGUSR2:
        cout << "intfMonitor: shutting down" << endl;
        isRunning = false;
	break;
//      If the signal handler receives any other signal, the following message should appear on the screen:
//      intfMonitor: undefined signal
        default:
        cout << "intfMonitor: undefined signal" << endl;  
        break;
  }     
}
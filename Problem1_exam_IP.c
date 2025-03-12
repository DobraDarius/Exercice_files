 /*
 Write the necessary data structures and algorithm to find the network address to which a device with a particular IP is connected.
 An IP address is a 32 bit unsigned integer. It is usual that it is presented in human readable format where it is represented as 4 bytes separated by a dot (.) .
 Ex: 0xC1E20C02  will be 193.226.12.2 in human readable format.
 A network mask is 4 bytes unsigned integer similar to the IP address. In human readable format a network mask would look like, for example: 255.255.255.0
 A network address can be found by performing a bitwise AND operation between the IP address and the network mask.
 For the purposes of this problem we will not care for any other real life constraints for these concepts not mentioned above.
 Your program will read as command line arguments the IP address in hex format, with capital letters, and a network mask
in human readable format and prints to the standard output the 
network address associated with those IP and network mask in human readable format. Take great care that there are no leading or trailing whitespaces 
for the output of your code.
 your_program   IP_in_hex   Network_mask_in_human_readeable_format
 Ex1: For the call
 name_of_your_program 0xC1E20C02 255.255.255.0
 the output will be:
 193.226.12.0
 Ex2: For the call:
 name_of_your_program 0xAC1EFF04 255.255.248.0
 the output will be:
 172.30.248.0
 Points will be deducted for unnecessary code.
 */

#include <stdio.h>
#include <stdint.h>

typedef union{
    struct{
        uint8_t b1;
        uint8_t b2;
        uint8_t b3;
        uint8_t b4;
    }; 
    uint32_t ip_addr;
}IP;

int main(int argc, char** argv){
    if(argc != 3){
        printf("not enough arguments\n");
    }

    IP mask = {0};
    IP addr = {0};
    IP net = {0};

    sscanf(argv[1], "%X", &addr.ip_addr);
    sscanf(argv[2], "%hhu.%hhu.%hhu.%hhu", &mask.b4, &mask.b3, &mask.b2, &mask.b1);

    net.ip_addr = addr.ip_addr & mask.ip_addr;

    printf("%d.%d.%d.%d\n", net.b4, net.b3, net.b2, net.b1);

    return 0;

}
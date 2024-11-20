#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void calculate_network_address(const char *ip, int prefix, char *network) {
    int octets[4], mask = ~((1 << (32 - prefix)) - 1);
    sscanf(ip, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);
    int ip_binary = (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];
    ip_binary &= mask;
    sprintf(network, "%d.%d.%d.%d", ip_binary >> 24, (ip_binary >> 16) & 255, (ip_binary >> 8) & 255, ip_binary & 255);
}

int main() {
    char ip[16], network[16];
    int prefix;
    printf("Enter an IP address: ");
    scanf("%s", ip);
    printf("Enter the prefix length: ");
    scanf("%d", &prefix);
    calculate_network_address(ip, prefix, network);
    printf("Network address: %s/%d\n", network, prefix);
    return 0;
}

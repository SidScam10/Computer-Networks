#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ip_classless(char *ip_address) {
    int octets[4], bits = 0;
    sscanf(ip_address, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);
    for (int i = 0; i < 4; i++) bits += __builtin_popcount(octets[i]);
    static char mask[20];
    sprintf(mask, "%s/%d", ip_address, bits);
    return mask;
}

int main() {
    char ip_address[16];
    printf("Enter an IP address: ");
    scanf("%s", ip_address);
    printf("Classless address: %s\n", ip_classless(ip_address));
    return 0;
}

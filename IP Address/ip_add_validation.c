#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_valid_ip(const char *ip) {
    int num, dots = 0;
    char *copy = strdup(ip), *token = strtok(copy, ".");
    while (token) {
        if (!isdigit(*token) || (num = atoi(token)) < 0 || num > 255) return 0;
        token = strtok(NULL, ".");
        dots++;
    }
    free(copy);
    return dots == 4;
}

int main() {
    char ip[16];
    printf("Enter an IP address: ");
    scanf("%s", ip);
    printf("The IP address is %s\n", is_valid_ip(ip) ? "valid" : "invalid");
    return 0;
}

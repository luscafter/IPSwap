#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define reset "\e[0m"
#define R     "\e[1;31m"
#define G     "\e[1;36m"
#define W     "\e[0;90m"

/*

 Copyright (c) 2020, Lucas Araújo
 All rights reserved.

 GitHub:    https://www.github.com/luscafter
 Twitter:   https://twitter.com/spartancode_
 Instagram: https://www.instagram.com/luscafter
 YouTube:   https://www.youtube.com/spartancode

 https://protonvpn.com/support/linux-vpn-tool/

*/

void banner()
{
    system("clear");
    printf(R "\n ." W "___" R " ." W "_______" R " ." W "________         ___" R " ." W "______" R "  ." W "_______\n");
    printf(R " : " W "__|" R ": " W "____  ||    ___/" R "." W "___    |   |" R ":" W "      \\ " R ":" W " ____  |\n");
    printf(W " | " R ":" W " ||    " R ":  " W "||___    \\" R ":   " W "| /\\|   ||   " R "." W "   ||    " R ":" W "  |\n");
    printf(W " |   ||   |___||       /|   |/  " R ":" W "   ||   " R ":" W "   ||   |___|\n");
    printf(W " |   ||___|    |__" R ":" W "___/ |   /       ||___|   ||___|\n");
    printf(" |___|            " R ":" W "     |______/|___|    |___|\n" R);
    printf("                                :\n                                :" reset);
    printf("         version 1.0.0\n                                   github.com/luscafter\n\n");
}

void install(char os)
{
    if(os == 'D' || os == 'd')
        system("sudo apt install -y openvpn dialog python3-pip python3-setuptools");
    else if(os == 'A' || os == 'a')
        system("sudo pacman -S openvpn dialog python-pip python-setuptools");
    else
        system("sudo dnf install -y openvpn dialog python3-pip python3-setuptools");

    system("sudo pip3 install protonvpn-cli --upgrade");
    printf("\n");
    system("protonvpn --version");
    printf("\n");
}

void run(int time)
{
    while(1){
        for(int i = 0; i < 50; i++){
            printf("\n[" G "+" reset "] Switching IP to the server [" G "%d" reset "]\n", i + 1);
            system("sudo protonvpn c -r");
            system("protonvpn status");
            sleep(time);
        }
    }
}

void secure_core(int time)
{
    while(1){
        printf("\n[" G "+" reset "] Connecting to the fastest Secure Core server\n");
        system("sudo protonvpn c --sc");
        system("protonvpn status");
        sleep(time);
    }
}

int main(int argc, char **argv)
{
    banner();
    char option;
    uid_t getuid(void);
    uid_t user = getuid();
    
    if(user != 0){
        printf("\n[" R "!" reset "] You must run as a super user\n\n$ sudo %s\n\n", argv[0]);
        exit(1);
    }

    printf("\nWhich OS is your distro based on?\n");
    printf("\n[" G "D" reset "]ebian | [" G "A" reset "]rch Linux | [" G "R" reset "]ed Hat  >  ");
    fgets(&option, 2, stdin);
    setbuf(stdin, NULL);   

    if(option != 'D' && option != 'd' && option != 'A' && option != 'a' && option != 'R' && option != 'r'){
        printf("\n[" R "!" reset "] Invalid option! Try again.\n\n");
        exit(1);
    }

    printf("\n[" G "+" reset "] Install the dependencies\n\n");
    sleep(1);
    
    install(option);

    printf("Connect to the Secure Core server faster? [Y/n]: ");
    fgets(&option, 2, stdin);
    setbuf(stdin, NULL);

    if(option != 'Y' && option != 'y' && option != 'N' && option != 'n'){
        printf("\n[" R "!" reset "] Invalid option! Try again.\n\n");
        exit(1);
    }

    int time;
    printf("\nEnter the time range (in seconds) to switch the IP address: ");
    scanf("%d", &time);

    if(time < 1){
        printf("\n[" R "!" reset "] Invalid value! Try again.\n\n");
        exit(1);
    }

    printf("\n");
    system("protonvpn status");

    printf("\n");
    system("sudo protonvpn init");

    printf("\n[" G "+" reset "] Initializing IP exchange\n");

    if(option == 'Y' || option == 'y')
        secure_core(time);
    else
        run(time);

    return 0;
}

#include "command.h"
#include "record.h"
#include "all.h"
#include "base.h"




#define DEBUG
#define PORT 5555




int main(int argc, char* argv[]){
    base basik;
    if(argc == 2){
        if(basik.read_base(argv[1])){
            printf("ne delaet list\n");
            return 1;
        }
    }
    printf("prochitalo\n");
    char message[4] = "end";
    int i, err, opt = 1;
    int sock, new_sock;
    fd_set active_set, read_set;
    struct sockaddr_in addr;
    socklen_t size;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        perror("Server cannot create socket");
        exit(EXIT_FAILURE);
    }
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char* ) &opt, sizeof(opt));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(sock, (struct sockaddr*) &addr, sizeof(addr));
    if(err < 0){
        perror("server cannot bind socket");
        exit(EXIT_FAILURE);
    }
    err = listen (sock, 3);
    if(err < 0){
        perror("server listen queue failure");
        exit(EXIT_FAILURE);
    }
    FD_ZERO (&active_set);
    FD_SET (sock, &active_set);
    for(;;){
        read_set = active_set;
        if(select(FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0){
            perror("server select failure");
            exit(EXIT_FAILURE);
        }
        for(i = 0; i < FD_SETSIZE; i++){
            if(FD_ISSET(i, &read_set)){
                if(i == sock){
                    struct sockaddr_in client;
                    size = sizeof(client);
                    new_sock = accept(sock, (struct sockaddr*) &client, &size);
                    if(new_sock < 0){
                        perror("server cannot accept socket");
                        exit(EXIT_FAILURE);
                    }
#ifdef DEBUG
                    printf("server connect from host %s port %d\n", inet_ntoa(client.sin_addr), (unsigned int)ntohs(client.sin_port));
#endif
                    FD_SET(new_sock, &active_set);
                }
                else{
                    char buf[BUF_LEN];
                    if(read_from_socket(i, buf) < 0){//можно передавать буфлен, самому писать эту функуию, <0 - ошибка
                        close(i);
                        FD_CLR(i, &active_set);
                    }
                    else{
                        command a;
                        //printf("buf = %s\n", buf);
                        if(a.parse(buf)){
                            //a.print_cmd();

                            if(a.get_type() != QUIT){
                                if(a.get_type() == STOP){
                                    close(sock);//тут очень плохо отправлять эндбь очень-очень плохо
                                    return 0;
                                }
                                else{
                                    basik.comanda(i, a);
                                    write_to_socket(i, message);
                                }
                            }
                            else{
                                close(i);
                                FD_CLR(i, &active_set);
                            }
                        }
                        else
                            write_to_socket(i, message);

                    }
                }

            }
        }
    }
    //протокол верх уровня: отправить -> получить строчки
}



int read_from_socket(int fd, char* buf){
    //протокол Ж длину 4 битб буфер этой длины
    int nbytes, len, i;
    if(read(fd, &len, sizeof(int)) != (int) sizeof(int)){
        perror("read length");
        return -1;
    }
    for(i = 0; len > 0; i+= nbytes, len -= nbytes){
        nbytes = read (fd, buf + i, len);//сколько данных прошло
        if(nbytes < 0){
            perror("read");
            return -1;
        }
        else
            if(nbytes == 0){
                perror("read truncated");
                return -1;
            }
    }
    return 1;

}
int write_to_socket(int fd, char* buf){
    //протокол Ж длину 4 битб буфер этой длины
    int nbytes, i;
    int len = strlen(buf) + 1;
    if(write(fd, &len, sizeof(int)) != (int) sizeof(int)){
        perror("write length");
        return -1;
    }
    for(i = 0; len > 0; i+= nbytes, len -= nbytes){
        nbytes = write (fd, buf + i, len);//сколько данных прошло
        if(nbytes < 0){
            perror("write");
            return -1;
        }
        else
            if(nbytes == 0){
                perror("write truncated");
                return -1;
            }
    }
    return 1;

}

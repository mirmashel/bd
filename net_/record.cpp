#include "record.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define LEN 1234
#define BUF_LEN 512
int read_from_socket(int fd, char* buf);
int write_to_socket(int fd, char* buf);

//-1 if ploho mem, 0 horosho
int record::init(const char* name, int phone, int group)
{
    this->phone = phone;
    this->group = group;
    if(name)
    {
        this->name = std::unique_ptr<char[]>(new char [strlen(name) + 1]);
        if(!this->name)
            return -1;
        strcpy(this->name.get(), name);
    }
    else this->name = 0;

    return 0;
}


record::record(const record &a)
{
    init(a.get_name(), a.get_phone(), a.get_group());
}

record::record(record &&a)
{
    phone = a.phone;
    name = std::move(a.name);
    a.phone = 0;
    a.name = 0;
    a.group = 0;
}
record& record::operator=(const record &x)
{
    init(x.get_name(), x.get_phone(), x.get_group());
    return *this;
}
//this < a -1, = 0 , > 1
int record::operator<(const record& a)const
{
    int res;
    if(name && a.name)
    {
        res = strcmp(name.get(), a.name.get());
        if(res) return res;
        return phone - a.phone;
    }
    if(!name && a.name) return -1;
    if(name && !a.name) return 1;
    return phone - a.phone;
}

//1 - ne prochitalos, -1 mem ploho
int record::read(FILE *fp)
{
    char buf[LEN];
    int v, g;
    if(fscanf(fp, "%s%d%d", buf, &v, &g) != 3)
        return 1;
    return init(buf, v, g);
}

void record::move(record& b)
{
    b.name = std::move(name);
    b.phone = phone;
    b.group = group;
    phone = 0;
    name = 0;
    group = 0;
}
/*
void record::swap(record& b)
{
    char *s;
    int v;
    s = this->name;
    this->name = b.name;
    b.name = s;
    v = this->phone;
    this->phone = b.phone;
    b.phone = v;
}


*/


void record::print_sock(int sock){
    char buf[BUF_LEN];
    sprintf(buf, "%s %d %d", name.get(), phone, group);
    //printf("buf = %s\n", buf);
    write_to_socket(sock, buf);
}


















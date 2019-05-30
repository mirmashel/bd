#ifndef RECORD_H
#define RECORD_H

#define LEN 1234
#include <memory>
#include <string.h>

class record
{
private:
    std::unique_ptr <char[]> name;
    int phone = 0;
    int group = 0;
public:
    record(const char* name = 0, int phone = 0, int group = 0){
        init(name, phone, group);
    }
    record(record && a);
    record(const record & a);
    ~record(){}
    record& operator=(const record& x);
    int operator<(const record& a)const;
    int get_phone()const{
        return phone;
    }
    int get_group()const{
        return group;
    }
    const char* get_name() const{
        return name.get();
    }
    void set_phone(int p){
        phone = p;
    }
    void set_group(int p){
        group = p;
    }
    int read(FILE* fp);
    int init(const char* name = 0, int phone = 0, int group = 0);
    void swap(record& b);
    void move(record& b);
    void print(const char* s = 0){
        if(s)
            printf("%s %d %d%s", name.get(), phone, group, s);
        else
            printf("%s %d %d\n", name.get(), phone, group);
    }

    void print_sock(int sock);
};


#endif //RECORD_H

#ifndef BASE_H
#define BASE_H
#include <memory>

#include "all.h"

#define GROUP_I 1000
class base
{
private:
    list* lists_head = 0;
    hash* hh = 0;
    avl* ah = 0;
public:
    base(){
        ah = new avl;
        hh = new hash(MOD);
        lists_head = new list[GROUP_I];
    }
    ~base(){
        if(ah)
            delete ah;
        if(hh)
            delete hh;
        delete[] lists_head;
    }
    int read_base(const char* filename);

    void comanda(int sock, command& a);
    void delete_base(command& a);
    void insert_base(command& a);
    void select_base(int sock, command& a);
    void delete_all_base();
    void print_base();
};
#endif //BASE_H


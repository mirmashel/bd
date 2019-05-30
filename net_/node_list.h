#ifndef NODE_LIST_H
#define NODE_LIST_H
#include "record.h"
#include "command.h"

class node_list_rec : public record
{
    private:
        node_list_rec* next = 0;
        node_list_rec* prev = 0;
    public:
        node_list_rec(const char* name = 0, int phone = 0, int group = 0) : record(name, phone, group){}
        node_list_rec(const node_list_rec & i) : record(i){}
        node_list_rec(const command & i) : record(i){}
        ~node_list_rec(){
            next = 0;
            prev = 0;
        }
        node_list_rec & operator=(const record& rhs){
            *((record *) this) = rhs;
            next = 0;
            prev = 0;
            return *this;
        }
        node_list_rec* get_next() const{
            return next;
        }
        node_list_rec* get_prev() const{
            return prev;
        }
        void set_next(node_list_rec* next){
            this->next = next;
        }

        void set_prev(node_list_rec* prev){
            this->prev = prev;
        }
};

#endif //NODE_LIST_H

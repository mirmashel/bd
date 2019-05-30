#ifndef ALL_H
#define ALL_H
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
#include "node_list.h"
#define MOD 10000
#define BUF_LEN 512
class hash;
class avl;
class list;


int read_from_socket(int fd, char* buf);
int write_to_socket(int fd, char* buf);

class avl_node{
private:
    node_list_rec* data = 0;
    avl_node* left = 0;
    avl_node* right = 0;
    int bal = 0;
    int height = 1;
    int del = 0;
public:
    avl_node(node_list_rec* a = 0, avl_node* b = 0, avl_node* c = 0){
        data = a;
        left = b;
        right = c;
    }
    ~avl_node(){}
    node_list_rec* get_data(){
        return data;
    }
    avl_node* get_left(){
        return left;
    }
    avl_node* get_right(){
        return right;
    }
    void bal_height(){
        int h1 = 0, h2 = 0;
        if(left)
            h1 = left->get_height();
        if(right)
            h2 = right->get_height();
        bal = h2 - h1;
        height = ((h2 > h1) ? h2 : h1) + 1;
    }
    void set_del(int d){
        del = d;
    }
    int get_del(){
        return del;
    }
    int get_bal(){
        return bal;
    }
    int get_height(){
        return height;
    }
    void set_data(node_list_rec* a){
        data = a;
    }
    void set_left(avl_node* b){
        left = b;
    }
    void set_right(avl_node* c){
        right = c;
    }
    void set_bal(int q){
        bal = q;
    }
    void set_height(int q){
        height = q;
    }
    void print(){
        data->print(" ");
        printf("%d %d %d\n", bal, height, del);
    }
    void print_sock(int sock){
        data->print_sock(sock);
    }
};

class avl{
private:
    avl_node* head = 0;
    avl_node* curr = 0;
public:
    avl(){
        head = 0;
    }
    ~avl(){
        curr = head;
        delete_all_avl();
    }
    void goto_head(){
        curr = head;
    }
    void set_curr(avl_node* tmp){
        curr = tmp;
    }
    void goto_right(){
        if(curr)
            curr = curr->get_right();
    }
    void goto_left(){
        if(curr)
            curr = curr->get_left();
    }
    avl_node* get_curr(){
        return curr;
    }
    avl_node* get_head(){
        return head;
    }
    void set_head(avl_node* h){
        head = h;
    }
    void print(avl_node* curr = 0, int l = 0);
    void insert_avl(node_list_rec* ret);
    node_list_rec *insert_avl(command& a_);
    node_list_rec* delete_avl(command& a, node_list_rec *h);
    void delete_base_(list* ll, hash* hh);
    void delete_base_eq(command& a, list* ll, hash* hh);

    node_list_rec* delete_base(command& a, node_list_rec* h, hash* hash_head, avl* ah, hash* hh);
    node_list_rec* delete_base_(node_list_rec* h, hash* hash_head, avl* ah, hash* hh);
    node_list_rec* delete_base_eq(command& a, node_list_rec* h, hash* hash_head, avl* ah, hash* hh);
    void delete_base(command& a, list* ll, hash* hh);
    void delete_avl_eq(avl_node* a);
    void delete_avl_eq(node_list_rec* a);
    node_list_rec* delete_ah(command& a, node_list_rec* h, hash* hh);
    node_list_rec* delete_ah_(node_list_rec* h, hash* hh);
    node_list_rec* insert_ah(command& a_, hash* hh);
    node_list_rec* delete_ah_eq(command& a, node_list_rec* h, hash* hh);
    node_list_rec* delete_avl_(node_list_rec* h, hash* hh);
    node_list_rec *delete_avl_eq(command& a, node_list_rec *h);
    void delete_all_avl();

    void select_avl(int sock, command& a);
    void select_avl_eq(int sock, command& a);
    void select_avl_(int sock, command& a);
    void select_avl_g(int sock, command& a);
    void select_avl_l(int sock, command& a);

    node_list_rec *delete_avl_(node_list_rec *h);
    node_list_rec *delete_avl_eq(avl_node* a, node_list_rec *h);
    void delete_avl_otmet(command& a);
    void left_rot_izi();
    void right_rot_izi();
    avl_node* left_rot_izi(avl_node* c);
    avl_node* right_rot_izi(avl_node* c);
    void left_rot_hard();
    void right_rot_hard();
    avl_node* left_rot_hard(avl_node* c);
    avl_node* right_rot_hard(avl_node* c);
    avl_node *balance(avl_node* a);
    avl_node* min(avl_node* c);
};

class hash_node_data{
private:
    node_list_rec* data = 0;
    hash_node_data* next = 0;
public:
    hash_node_data(node_list_rec* a = 0, hash_node_data* b = 0){
        data = a;
        next = b;
    }
    ~hash_node_data(){}
    node_list_rec* get_data(){
        return data;
    }
    hash_node_data* get_next(){
        return next;
    }
    void set_data(node_list_rec* a){
        data = a;
    }
    void set_next(hash_node_data* b){
        next = b;
    }
    void print();
};

class hash{
private:
    hash_node_data** head;
    int mod = 0;
public:
    node_list_rec* delete_hash(command& a, node_list_rec *head_list);
    void select_hash(int sock, command& a);
    hash(int m){
        mod = m;
        head = new hash_node_data*[m];
        for(int i = 0; i < m; i++){
            head[i] = 0;
        }
    }
    ~hash(){
        delete_all_hash();
    }
    node_list_rec *insert_hash(command& a_);
    void insert_hash(node_list_rec* a);
    node_list_rec* insert_ah(command &a_, avl* ah);
    void delete_all_hash();
    void delete_hash(node_list_rec* a);

    node_list_rec* delete_base(command& a, node_list_rec* head_list, avl* avl_head, avl* ah, hash* hh);
    void delete_base(command& a, list* ll, avl* ah);
    node_list_rec* delete_ah(command& a, node_list_rec* head_list, avl* ah);
    void print();

    void delete_all_hash_base();
};
class list : public node_list_rec
{
private:
    node_list_rec* head = 0;
    node_list_rec* curr = 0;
    avl* avl_head = 0;
    hash* hash_head = 0;
public:
    list(){
        avl_head = new avl;
        hash_head = new hash(MOD);
    }
    ~list(){
        delete avl_head;
        delete hash_head;

        if(head)
            delete_list();
        head = 0;
        curr = 0;

    }
    node_list_rec* get_head() const{
        return head;
    }
    node_list_rec* get_curr() const{
        return curr;
    }
    void set_head(node_list_rec* a){
        head = a;
    }
    void set_curr(node_list_rec* a){
        curr = a;
    }
    void goto_head(){
        curr = head;
    }
    avl* get_avl(){
        return avl_head;
    }
    hash* get_hash(){
        return hash_head;
    }
    void select_lah(int sock, command& a);
    int read_list(const char* filename);

    node_list_rec* insert_base(command &a);
    void insert_base(node_list_rec* a);
    void comanda(int sock, command& a);
    void deletee(command & a);
    void deletee(node_list_rec* a);
    void select(command & a);
    void insert(command & a);
    void insert(node_list_rec* a);
    void delete_lah(command & a);
    void insert_lah(command & a);
    void destroy_base(avl* ah, hash* hh){
        if(avl_head)
            avl_head->delete_all_avl();
        avl_head->set_head(0);
        if(hash_head)
            hash_head->delete_all_hash_base();

        if(head)
            delete_list_base(ah, hh);
        head = curr = 0;
    }

    void delete_list_base(avl* ah, hash* hh);
    void delete_base(command & a, avl* ah, hash* hh);
    void delete_list();
    void print_list();

    void print_list_sock(int sock);
    int operator<(const list& a)const{
        return (*head < *(a.get_head()));
    }
};

#endif //ALL_H

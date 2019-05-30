#include "record.h"
#include "node_list.h"
#include "all.h"

#define MAX_PRINT 15
int list::read_list(const char* filename)
{
    FILE* fp;
    node_list_rec *tmp;
    char buf[LEN];
    int p, g;
    if(!(fp = fopen(filename, "r")))
        return -1;
    while(fscanf(fp, "%s%d%d", buf, &p, &g) == 3)
    {
        tmp = new node_list_rec;
        if(!tmp)
        {
            fclose(fp);
            return -10;
        }
        tmp->init(buf, p, g);
        tmp->set_next(head);
        if(head)
            head->set_prev(tmp);
        head = tmp;
        //avl_head->goto_head();
        avl_head->insert_avl(tmp);

    }
    if(!feof(fp))
    {
        fclose(fp);
        return -3;
    }
    fclose(fp);
    return 0;
}
void list::print_list()
{
    int i;
    goto_head();
    for(i = 0; i < MAX_PRINT && curr; i++, curr = curr->get_next())
    {
        curr->print();
    }
    printf("\n");
}
void list::print_list_sock(int sock)
{
    int i = 0;
    goto_head();
    for(;curr; i++, curr = curr->get_next())
    {
        curr->print_sock(sock);
    }
}
void list::delete_list(){
    node_list_rec* curr = head;
    while(head){
        curr = head->get_next();
        delete head;
        head = curr;
    }
}
void list::delete_list_base(avl* ah, hash* hh){
    node_list_rec* curr = head;
    while(head){
        ah->delete_avl_eq(head);
        hh->delete_hash(head);
        curr = head->get_next();
        delete head;
        head = curr;
    }
}

void list::select(command & a){
    if(!head)
        return;
    int i = 0;
    for(curr = head; curr; curr = curr->get_next()){
        if(a.check(curr)){
            i++;
        }
    }
    printf("%d\n", i);
}
void list::insert(command & a){
    if(!head){
        node_list_rec* tmp = new node_list_rec(a);
        head = tmp;
        curr = head;
        return;
    }
    for(curr = head; curr->get_next(); curr = curr->get_next()){
        if(a.check(curr))
            return;
    }
    node_list_rec* next_ = curr->get_next();
    node_list_rec* tmp = new node_list_rec(a);
    curr->set_next(tmp);
    tmp->set_prev(curr);
    tmp->set_next(next_);
    if(next_)
        next_->set_prev(tmp);
}
void list::insert(node_list_rec* a){
    if(!a)
        return;
    a->set_next(head);
    if(head)
        head->set_prev(a);
    head = a;
}

void list::deletee(command& a){
    if(!head)
        return;
    node_list_rec *prev, *tmp, *next;
    goto_head();
    while(curr && a.check(curr)){
        tmp = curr->get_next();
        delete curr;
        curr = tmp;
    }
    head = curr;
    if(!head)
        return;
    head->set_prev(0);
    for(curr = head->get_next(), prev = head; curr;){
        if(a.check(curr)){
            next = curr->get_next();
            prev->set_next(next);
            if(next)
                next->set_prev(prev);
            delete curr;
            curr = next;
        }
        else{
            prev = curr;
            curr = curr->get_next();
        }
    }
}
void list::deletee(node_list_rec* a){
    if(!a)
        return;
}
void list::select_lah(int sock, command& a){
    if(!avl_head->get_head())
        return;
    if(a.get_group() && a.get_oper() == OP_NONE){
        print_list_sock(sock);
        return;
    }
    if(a.get_phone() && a.get_phone() && a.get_oper() == OR){
        int p = a.get_phone();
        op_type o = a.get_oper();
        cond_type c = a.get_c_phone();
        a.del_for_select();
        avl_head->select_avl(sock, a);
        a.set_for_select(p, o, c);
        a.inverse();
        hash_head->select_hash(sock, a);
        return;
    }
    if(a.get_phone())
        hash_head->select_hash(sock, a);
    else
        avl_head->select_avl(sock, a);
}
void list::delete_lah(command & a){
    if(!avl_head->get_head())
        return;
    if(a.get_phone())
        head = hash_head->delete_ah(a, head, avl_head);
    else{
        avl_head->goto_head();
        head = avl_head->delete_ah(a, head, hash_head);
    }
}
void list::delete_base(command & a, avl* ah, hash* hh){
    if(a.get_phone())
        head = hash_head->delete_base(a, head, avl_head, ah, hh);
    else{
        avl_head->goto_head();
        head = avl_head->delete_base(a, head, hash_head, ah, hh);
    }
}
void list::insert_lah(command &a){
    avl_head->goto_head();
    node_list_rec* tmp = avl_head->insert_ah(a, hash_head);
    if(!tmp)
        return;
    tmp->set_next(head);
    if(head)
        head->set_prev(tmp);
    head = tmp;
}
void list::insert_base(node_list_rec* a){
    avl_head->goto_head();
    goto_head();
    avl_head->insert_avl(a);
    hash_head->insert_hash(a);
    a->set_next(head);
    if(head)
        head->set_prev(a);
    head = a;
}
node_list_rec* list::insert_base(command &a){
    node_list_rec* tmp = 0;
    avl_head->goto_head();
    goto_head();
    tmp = avl_head->insert_ah(a, hash_head);
    if(!tmp)
        return 0;
    tmp->set_next(head);
    hash_head->insert_hash(a);
    if(head)
        head->set_prev(tmp);
    head = tmp;
    return tmp;
}
void list::comanda(int sock, command &a){
    switch(a.get_type()){
    case SELECT:
        select_lah(sock, a);
        break;
    case INSERT:{
        insert_lah(a);
        break;
    }
    case DELETE:{
        delete_lah(a);
        break;
    }
    default:
        break;
    }
}

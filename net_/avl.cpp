#include "command.h"
#include "all.h"
#define MAX_PRINT_AVL 10
int cmp_avl(node_list_rec* a, node_list_rec* b){
    int cmp = strcmp(a->get_name(), b->get_name());
    if(cmp)
        return cmp;
    if(a->get_phone() < b->get_phone())
        return -1;
    if(a->get_phone() > b->get_phone())
        return 1;
    if(a->get_group() < b->get_group())
        return -1;
    if(a->get_group() > b->get_group())
        return 1;
    return 0;
}
node_list_rec* del_data(node_list_rec* data, node_list_rec* h){
    node_list_rec* new_head = h;
    if(data->get_prev())
        data->get_prev()->set_next(data->get_next());
    else
        new_head = data->get_next();
    if(data->get_next())
        data->get_next()->set_prev(data->get_prev());
    delete data;
    return new_head;
}
int cmp_avl_ins(command& a, node_list_rec* b){
    int cmp = strcmp(a.get_name(), b->get_name());
    if(cmp)
        return cmp;
    if(a.get_phone() < b->get_phone())
        return -1;
    if(a.get_phone() > b->get_phone())
        return 1;
    if(a.get_group() < b->get_group())
        return -1;
    if(a.get_group() > b->get_group())
        return 1;
    return 0;
}
int cmp_avl_del(command& a, node_list_rec* b){
    int cmp = strcmp(a.get_name(), b->get_name());
    return cmp;
}
void avl::print(avl_node* curr, int l){
    if(!head)
        return;
    if(!curr)
        curr = head;
    curr->print();
    l++;
    if(l > MAX_PRINT_AVL)
        return;
    if(curr->get_left()){
        for(int i = 0; i < l; i++)
            printf("   ");
        print(curr->get_left(), l);
    }
    if(curr->get_right()){
        for(int i = 0; i < l; i++)
            printf("   ");
        print(curr->get_right(), l);
    }
}
avl_node* avl::balance(avl_node* a){
    if(!a)
        return a;
    avl_node* b = a;
    while(b->get_bal() >= 2){
        if(b->get_right()->get_bal() < 0)
            b = left_rot_hard(b);
        else
            b = left_rot_izi(b);
    }
    while(b->get_bal() <= -2){
        if(b->get_left()->get_bal() > 0)
            b = right_rot_hard(b);
        else
            b = right_rot_izi(b);
    }
    return b;
}

void avl::insert_avl(node_list_rec* ret){
    if(!head){
        avl_node* tmp = new avl_node(ret, 0, 0);
        head = tmp;
        return;
    }
    if(!curr)
        curr = head;
    avl_node* c = curr;
    int cmp = cmp_avl(ret, curr->get_data());
    if(!cmp)
        return;
    if(cmp > 0){
        if(curr->get_right()){
            c = curr;
            curr = curr->get_right();
            insert_avl(ret);//v curr vershina pravogo poddereva
            c->set_right(curr);
            c->bal_height();
            curr = balance(c);
        }
        else{
            avl_node* tmp = new avl_node(ret, 0, 0);
            curr->set_right(tmp);
            curr->bal_height();
            //balance ne nado vrode
        }
    }
    else{
        if(curr->get_left()){
            c = curr;
            curr = curr->get_left();
            insert_avl(ret);//v curr vershina pravogo poddereva
            c->set_left(curr);
            c->bal_height();
            curr = balance(c);
        }
        else{
            avl_node* tmp = new avl_node(ret, 0, 0);
            curr->set_left(tmp);
            curr->bal_height();
            //balance ne nado vrode
        }
    }
    head = curr = balance(curr);
}
node_list_rec* avl::insert_avl(command& a_){
    node_list_rec* ret = 0;
    if(!head){
        ret = new node_list_rec(a_);
        avl_node* tmp = new avl_node(ret, 0, 0);
        head = tmp;
        return ret;
    }
    avl_node* c = curr;
    int cmp = cmp_avl_ins(a_, curr->get_data());
    if(!cmp)
        return 0;
    if(cmp > 0){
        if(curr->get_right()){
            c = curr;
            curr = curr->get_right();
            ret = insert_avl(a_);//v curr vershina pravogo poddereva
            c->set_right(curr);
            c->bal_height();
            curr = balance(c);
        }
        else{
            ret = new node_list_rec(a_);
            avl_node* tmp = new avl_node(ret, 0, 0);
            curr->set_right(tmp);
            curr->bal_height();
            //balance ne nado vrode
        }
    }
    else{
        if(curr->get_left()){
            c = curr;
            curr = curr->get_left();
            ret = insert_avl(a_);//v curr vershina pravogo poddereva
            c->set_left(curr);
            c->bal_height();
            curr = balance(c);
        }
        else{
            ret = new node_list_rec(a_);
            avl_node* tmp = new avl_node(ret, 0, 0);
            curr->set_left(tmp);
            curr->bal_height();
            //balance ne nado vrode
        }
    }
    head = curr = balance(curr);
    return ret;
}
node_list_rec* avl::insert_ah(command& a_, hash* hh){
    node_list_rec* ret = 0;
    if(!head){
        ret = new node_list_rec(a_);
        avl_node* tmp = new avl_node(ret, 0, 0);
        hh->insert_hash(ret);
        head = tmp;
        return ret;
    }
    avl_node* c = curr;
    int cmp = cmp_avl_ins(a_, curr->get_data());
    if(!cmp)
        return 0;
    if(cmp > 0){
        if(curr->get_right()){
            c = curr;
            curr = curr->get_right();
            ret = insert_ah(a_, hh);//v curr vershina pravogo poddereva
            c->set_right(curr);
            c->bal_height();
            curr = balance(c);
        }
        else{
            ret = new node_list_rec(a_);
            avl_node* tmp = new avl_node(ret, 0, 0);
            hh->insert_hash(ret);

            curr->set_right(tmp);
            curr->bal_height();
            //balance ne nado vrode
        }
    }
    else{
        if(curr->get_left()){
            c = curr;
            curr = curr->get_left();
            ret = insert_ah(a_, hh);//v curr vershina pravogo poddereva
            c->set_left(curr);
            c->bal_height();
            curr = balance(c);
        }
        else{
            ret = new node_list_rec(a_);
            avl_node* tmp = new avl_node(ret, 0, 0);
            hh->insert_hash(ret);
            curr->set_left(tmp);
            curr->bal_height();
            //balance ne nado vrode
        }
    }
    head = curr = balance(curr);
    return ret;
}
//ishet min i vitaskivaet ego
avl_node* avl::min(avl_node* c){
    if(!c)
        return 0;
    avl_node* left = c->get_left(), *mini;
    if(!left)
        return 0;//iskluchim etot sluchay v delete
    if(left->get_left()){
        mini = min(left);
        c->set_left(curr);
        c->bal_height();
        curr = balance(c);
        return mini;
    }
    else{//left i est minimalniy
        c->set_left(left->get_right());
        c->bal_height();
        curr = balance(c);
        return left;
    }
}
//udalyaet kak avl, udalyaet a,
node_list_rec* avl::delete_avl_eq(avl_node* a, node_list_rec* h){
    if(!a){
        curr = 0;
        return h;
    }
    node_list_rec* new_head = h;
    avl_node*a_right = a->get_right();
    avl_node *mini;
    if(!a_right){
        curr = balance(a->get_left());
        new_head = del_data(a->get_data(), new_head);
        delete a;
    }
    else{
        if(!a_right->get_left()){
            a_right->set_left(a->get_left());
            a_right->bal_height();
            curr = balance(a_right);
            new_head = del_data(a->get_data(), new_head);
            delete a;
        }
        else{
            mini = min(a_right);//mb a_right?
            mini->set_right(curr);
            mini->set_left(a->get_left());
            mini->bal_height();
            curr = balance(mini);
            new_head = del_data(a->get_data(), new_head);
            delete a;
        }
    }
    head = curr = balance(curr);
    return new_head;
}
//udalyaet kak avl, udalyaet a,
void avl::delete_avl_eq(avl_node* a){
    if(!a){
        curr = 0;
        return;
    }
    avl_node*a_right = a->get_right();
    avl_node *mini;
    if(!a_right){
        curr = balance(a->get_left());
        delete a;
    }
    else{
        if(!a_right->get_left()){
            a_right->set_left(a->get_left());
            a_right->bal_height();
            curr = balance(a_right);
            delete a;
        }
        else{
            mini = min(a_right);//mb a_right?
            mini->set_right(curr);
            mini->set_left(a->get_left());
            mini->bal_height();
            curr = balance(mini);
            delete a;
        }
    }
    head = curr = balance(curr);
}
//udalyaet esli v command EQ
node_list_rec* avl::delete_avl_eq(command& a, node_list_rec* h){
    if(!curr)
        return 0;
    node_list_rec* new_head = h;
    avl_node* tmp = 0;
    int cmp = cmp_avl_del(a, curr->get_data());
    tmp = curr;
    if(cmp <= 0 && curr->get_left()){
        curr = curr->get_left();
        new_head = delete_avl_eq(a, new_head);
        tmp->set_left(curr);
        curr = tmp;
    }
    tmp = curr;
    if(cmp >= 0 && curr->get_right()){
        curr = curr->get_right();
        new_head = delete_avl_eq(a, new_head);
        tmp->set_right(curr);
        curr = tmp;
    }
    curr->bal_height();
    if(a.check(curr->get_data())){
        new_head = delete_avl_eq(curr, new_head);
    }
    else
        curr = balance(curr);
    head = curr;
    return new_head;
}
void avl::delete_avl_eq(node_list_rec* a){
    if(!curr)
        return;
    avl_node* tmp = 0;
    int cmp = cmp_avl(a, curr->get_data());
    tmp = curr;
    if(cmp <= 0 && curr->get_left()){
        curr = curr->get_left();
        delete_avl_eq(a);
        tmp->set_left(curr);
        curr = tmp;
    }
    tmp = curr;
    if(cmp >= 0 && curr->get_right()){
        curr = curr->get_right();
        delete_avl_eq(a);
        tmp->set_right(curr);
        curr = tmp;
    }
    curr->bal_height();
    if(!cmp_avl(a, curr->get_data())){
        delete_avl_eq(curr);
    }
    else
        curr = balance(curr);
    head = curr;
}
//udalyaet esli v command EQ ah
node_list_rec* avl::delete_ah_eq(command& a, node_list_rec* h, hash* hh){
    if(!curr)
        return 0;
    node_list_rec* new_head = h;
    avl_node* tmp = 0;
    int cmp = cmp_avl_del(a, curr->get_data());
    tmp = curr;
    if(cmp <= 0 && curr->get_left()){
        curr = curr->get_left();
        new_head = delete_ah_eq(a, new_head, hh);
        tmp->set_left(curr);
        curr = tmp;
    }
    tmp = curr;
    if(cmp >= 0 && curr->get_right()){
        curr = curr->get_right();
        new_head = delete_ah_eq(a, new_head, hh);
        tmp->set_right(curr);
        curr = tmp;
    }
    curr->bal_height();
    if(a.check(curr->get_data())){
        hh->delete_hash(curr->get_data());
        new_head = delete_avl_eq(curr, new_head);
    }
    else
        curr = balance(curr);
    head = curr;
    return new_head;
}
void avl::delete_base_eq(command& a, list* ll, hash* hh){
    if(!curr)
        return;
    avl_node* tmp = 0;
    int cmp = cmp_avl_del(a, curr->get_data());
    tmp = curr;
    if(cmp <= 0 && curr->get_left()){
        curr = curr->get_left();
        delete_base_eq(a, ll, hh);
        tmp->set_left(curr);
        curr = tmp;
    }
    tmp = curr;
    if(cmp >= 0 && curr->get_right()){
        curr = curr->get_right();
        delete_base_eq(a, ll, hh);
        tmp->set_right(curr);
        curr = tmp;
    }
    curr->bal_height();
    if(a.check(curr->get_data())){
        hh->delete_hash(curr->get_data());
        int g = curr->get_data()->get_group();
        ll[g].get_avl()->delete_avl_eq(curr->get_data());
        ll[g].get_hash()->delete_hash(curr->get_data());
        ll[g].set_head(delete_avl_eq(curr, ll[g].get_head()));
    }
    else
        curr = balance(curr);
    head = curr;
}
//otmechaet kakie nado udalit
void avl::delete_avl_otmet(command& a){
    if(!head)
        return;
    if(!curr)
        curr = head;
    avl_node* left = curr->get_left(), *right = curr->get_right(), *tmp = curr;
    if(left){
        curr = left;
        delete_avl_otmet(a);
    }
    if(right){
        curr = right;
        delete_avl_otmet(a);
    }
    if(a.check(tmp->get_data()))
        tmp->set_del(1);
}
//udalyaet otmechennie
node_list_rec* avl::delete_avl_(node_list_rec* h){
    if(!curr)
        return h;
    node_list_rec* new_head = h;
    avl_node* tmp = 0;
    tmp = curr;
    if(curr->get_left()){
        curr = curr->get_left();
        new_head = delete_avl_(new_head);
        tmp->set_left(curr);
        curr = tmp;
    }
    tmp = curr;
    if(curr->get_right()){
        curr = curr->get_right();
        new_head = delete_avl_(new_head);
        tmp->set_right(curr);
        curr = tmp;
    }
    curr->bal_height();
    if(curr->get_del())
        new_head = delete_avl_eq(curr, new_head);
    else
        curr = balance(curr);
    head = curr;
    return new_head;
}
node_list_rec* avl::delete_ah_(node_list_rec* h, hash* hh){
    if(!curr)
        return h;
    node_list_rec* new_head = h;
    avl_node* tmp = 0;
    tmp = curr;
    if(curr->get_left()){
        curr = curr->get_left();
        new_head = delete_ah_(new_head, hh);
        tmp->set_left(curr);
        curr = tmp;
    }
    tmp = curr;
    if(curr->get_right()){
        curr = curr->get_right();
        new_head = delete_ah_(new_head, hh);
        tmp->set_right(curr);
        curr = tmp;
    }
    curr->bal_height();
    if(curr->get_del()){
        hh->delete_hash(curr->get_data());
        new_head = delete_avl_eq(curr, new_head);
    }
    else
        curr = balance(curr);
    head = curr;
    return new_head;
}
void avl::delete_base_(list* ll, hash* hh){
    if(!curr)
        return;
    avl_node* tmp = 0;
    tmp = curr;
    if(curr->get_left()){
        curr = curr->get_left();
        delete_base_(ll, hh);
        tmp->set_left(curr);
        curr = tmp;
    }
    tmp = curr;
    if(curr->get_right()){
        curr = curr->get_right();
        delete_base_(ll, hh);
        tmp->set_right(curr);
        curr = tmp;
    }
    curr->bal_height();
    if(curr->get_del()){
        hh->delete_hash(curr->get_data());
        int g = curr->get_data()->get_group();
        ll[g].get_avl()->delete_avl_eq(curr->get_data());
        ll[g].get_hash()->delete_hash(curr->get_data());
        ll[g].set_head(delete_avl_eq(curr, ll[g].get_head()));
    }
    else
        curr = balance(curr);
    head = curr;
}
node_list_rec* avl::delete_avl(command& a, node_list_rec* h){
    node_list_rec* new_head = h;
    if(a.get_name() && a.get_c_name() == EQ){
        curr = head;
        new_head = delete_avl_eq(a, h);
        head = curr;
    }
    else{
        curr = head;
        delete_avl_otmet(a);
        //print();
        curr = head;
        new_head = delete_avl_(h);
        head = curr;
    }
    return new_head;
}

node_list_rec* avl::delete_ah(command& a, node_list_rec* h, hash* hh){
    node_list_rec* new_head = h;
    if(a.get_name() && a.get_c_name() == EQ){
        curr = head;
        new_head = delete_ah_eq(a, h, hh);
        head = curr;
    }
    else{
        curr = head;
        delete_avl_otmet(a);
        //print();
        curr = head;
        new_head = delete_ah_(h, hh);
        head = curr;
    }
    return new_head;
}


node_list_rec* avl::delete_base_eq(command& a, node_list_rec* h, hash* hash_head, avl* ah, hash* hh){
    if(!curr)
        return 0;
    node_list_rec* new_head = h;
    avl_node* tmp = 0;
    int cmp = cmp_avl_del(a, curr->get_data());
    tmp = curr;
    if(cmp <= 0 && curr->get_left()){
        curr = curr->get_left();
        new_head = delete_base_eq(a, new_head, hash_head, ah, hh);
        tmp->set_left(curr);
        curr = tmp;
    }
    tmp = curr;
    if(cmp >= 0 && curr->get_right()){
        curr = curr->get_right();
        new_head = delete_base_eq(a, new_head, hash_head, ah, hh);
        tmp->set_right(curr);
        curr = tmp;
    }
    curr->bal_height();
    if(a.check(curr->get_data())){
        hh->delete_hash(curr->get_data());
        hash_head->delete_hash(curr->get_data());
        ah->delete_avl_eq(curr->get_data());

        new_head = delete_avl_eq(curr, new_head);
    }
    else
        curr = balance(curr);
    head = curr;
    return new_head;
}

node_list_rec* avl::delete_base_(node_list_rec* h, hash* hash_head, avl* ah, hash* hh){
    if(!curr)
        return h;
    node_list_rec* new_head = h;
    avl_node* tmp = 0;
    tmp = curr;
    if(curr->get_left()){
        curr = curr->get_left();
        new_head = delete_base_(new_head, hash_head, ah, hh);
        tmp->set_left(curr);
        curr = tmp;
    }
    tmp = curr;
    if(curr->get_right()){
        curr = curr->get_right();
        new_head = delete_base_(new_head, hash_head, ah, hh);
        tmp->set_right(curr);
        curr = tmp;
    }
    curr->bal_height();
    if(curr->get_del()){
        hh->delete_hash(curr->get_data());
        hash_head->delete_hash(curr->get_data());
        ah->delete_avl_eq(curr->get_data());

        new_head = delete_avl_eq(curr, new_head);
    }
    else
        curr = balance(curr);
    head = curr;
    return new_head;
}
node_list_rec* avl::delete_base(command& a, node_list_rec* h, hash* hash_head, avl* ah, hash* hh){
    node_list_rec* new_head = h;
    if(a.get_name() && a.get_c_name() == EQ){
        curr = head;
        new_head = delete_base_eq(a, h, hash_head, ah, hh);
        head = curr;
    }
    else{
        curr = head;
        delete_avl_otmet(a);
        //print();
        curr = head;
        new_head = delete_base_(h, hash_head, ah, hh);
        head = curr;
    }
    return new_head;
}
void avl::delete_base(command& a, list* ll, hash* hh){
    if(a.get_name() && a.get_c_name() == EQ){
        curr = head;
        delete_base_eq(a, ll, hh);
        head = curr;
    }
    else{
        curr = head;
        delete_avl_otmet(a);
        curr = head;
        delete_base_(ll, hh);
        head = curr;
    }
}
void avl::select_avl_eq(int sock, command& a){
    if(!curr)
        return;
    avl_node* tmp = curr;
    int cmp = cmp_avl_del(a, curr->get_data());
    if(cmp > 0){
        if(curr->get_right()){
            goto_right();
            select_avl_eq(sock, a);
            curr = tmp;
        }
    }
    else{
        if(cmp < 0){
            if(curr->get_left()){
                goto_left();
                select_avl(sock, a);
                curr = tmp;
            }
        }
        else{
            select_avl_(sock, a);
        }
    }
}
void avl::select_avl_g(int sock, command& a){
    if(!curr)
        return;
    avl_node* tmp = curr;
    int cmp = cmp_avl_del(a, curr->get_data());
    if(cmp > 0){
        if(curr->get_right()){
            goto_right();
            select_avl_g(sock, a);
            curr = tmp;
        }
    }
    else{
        select_avl_(sock, a);
    }
}
void avl::select_avl_l(int sock, command& a){
    if(!curr)
        return;
    avl_node* tmp = curr;
    int cmp = cmp_avl_del(a, curr->get_data());
    if(cmp < 0){
        if(curr->get_left()){
            goto_left();
            select_avl_l(sock, a);
            curr = tmp;
        }
    }
    else{
        select_avl_(sock, a);
    }
}
void avl::select_avl_(int sock, command& a){
    if(!curr)
        return;
    avl_node* tmp = curr;
    if(curr->get_right()){
        goto_right();
        select_avl(sock, a);
        curr = tmp;
    }
    if(curr->get_left()){
        goto_left();
        select_avl(sock, a);
        curr = tmp;
    }
    if(a.check(curr->get_data()))
        curr->print_sock(sock);
}
void avl::select_avl(int sock, command& a){
    switch(a.get_c_name()){
    case EQ:select_avl_eq(sock, a);
        break;
    case NE:select_avl_(sock, a);
        break;
    case GT:select_avl_g(sock, a);
        break;
    case GE:select_avl_g(sock, a);
        break;
    case LT:select_avl_l(sock, a);
        break;
    case LE:select_avl_l(sock, a);
        break;
    case LIKE:select_avl_(sock, a);
        break;
    case COND_NONE:select_avl_(sock, a);
        break;
    }
}


void avl::delete_all_avl(){
    if(!head)
        return;
    if(!curr)
        return;
    avl_node* left = curr->get_left(), *right = curr->get_right(), *tmp = curr;
    curr = left;
    delete_all_avl();
    curr = right;
    delete_all_avl();
    delete tmp;
}
avl_node* avl::left_rot_izi(avl_node* c){
    if(!c)
        return 0;
    avl_node *right = c->get_right();
    if(!right){
        printf("eto ne left rot\n");
        return 0;
    }
    c->set_right(right->get_left());
    right->set_left(c);

    c->bal_height();
    right->bal_height();
    return right;
}
avl_node* avl::right_rot_izi(avl_node* c){
    if(!c)
        return 0;
    avl_node *left = c->get_left();
    if(!left){
        printf("eto ne left rot\n");
        return 0;
    }

    c->set_left(left->get_right());
    left->set_right(c);
    c->bal_height();
    left->bal_height();
    return left;
}
avl_node* avl::left_rot_hard(avl_node* c){
    if(!c)
        return 0;
    c->set_right(right_rot_izi(c->get_right()));
    return left_rot_izi(c);
}
avl_node* avl::right_rot_hard(avl_node* c){
    if(!c)
        return 0;
    c->set_left(left_rot_izi(c->get_left()));
    return right_rot_izi(c);
}

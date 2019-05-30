#include "record.h"
#include "all.h"
#include "command.h"
#define MAX_HASH_PRINT 10
#define MAX_PRINT_HASH_LIST 5

node_list_rec* del_data(node_list_rec* data, node_list_rec* h);
//по сумме цифр номера телефона по указанному модулю
int hash_phone(int phone, int mod){
    return phone % mod;
}
//остаток при делении
//int hash_phone(int phone, int mod){
//    if(mod)
//        return phone % mod;
//    return phone;
//}
//chekaet na = < >
int cmp_hash_list(command& a, node_list_rec* b){
    if(!b)
        return 1;
    if(a.get_phone() > b->get_phone())
        return 1;
    if(a.get_phone() < b->get_phone())
        return -1;
    int cmp = strcmp(a.get_name(), b->get_name());
    if(cmp)
        return cmp;
    if(a.get_group() > b->get_group())
        return 1;
    if(a.get_group() < b->get_group())
            return -1;
    return 0;
}
int cmp_hash_list(node_list_rec* a, node_list_rec* b){
    if(!b)
        return 1;
    if(a->get_phone() > b->get_phone())
        return 1;
    if(a->get_phone() < b->get_phone())
        return -1;
    int cmp = strcmp(a->get_name(), b->get_name());
    if(cmp)
        return cmp;
    if(a->get_group() > b->get_group())
        return 1;
    if(a->get_group() < b->get_group())
            return -1;
    return 0;
}
void hash_node_data::print(){
    int i;
    hash_node_data* curr = this;
    for(i = 0; curr && i < MAX_PRINT_HASH_LIST; i++){
        curr->get_data()->print("    ");
        curr = curr->get_next();
    }
    printf("\n");
}
void hash::print(){
    int i;
    for (i = 0; i < MAX_HASH_PRINT; i++){
        printf("%d: ", i);
        if(head[i])
            head[i]->print();
        else
            printf("\n");
    }
}
node_list_rec *hash::delete_hash(command& a, node_list_rec* head_list){
    int i = 0, h = -1;
    hash_node_data* curr = 0, *prev = 0, *next = 0;
    node_list_rec* data = 0, *new_head = head_list;
    if(a.get_phone() && a.get_c_phone() == EQ){
        h = hash_phone(a.get_phone(), mod);
        curr = head[h];
        prev = 0;
        while(curr){
            data = curr->get_data();
            if(!data){
               printf("cho, data = 0????\n");
               return new_head;
            }
            if(a.check(data)){
                new_head = del_data(data, new_head);

                next = curr->get_next();
                if(prev)
                    prev->set_next(next);
                else
                    head[h] = next;
                delete curr;
                curr = next;
            }
            else{
                prev = curr;
                curr = curr->get_next();
            }
        }
        return new_head;
    }
    else{
        for(i = 0; i < mod; i++){
            curr = head[i];
            prev = 0;
            while(curr){
                data = curr->get_data();
                if(!data){
                   printf("cho, data = 0????\n");
                   return new_head;
                }
                if(a.check(data)){
                    new_head = del_data(data, new_head);

                    next = curr->get_next();
                    if(prev)
                        prev->set_next(next);
                    else
                        head[i] = next;
                    delete curr;
                    curr = next;
                }
                else{
                    prev = curr;
                    curr = curr->get_next();
                }
            }
        }
        return new_head;
    }
    return new_head;
}
node_list_rec *hash::delete_ah(command& a, node_list_rec* head_list, avl* ah){
    int i = 0, h = -1;
    hash_node_data* curr = 0, *prev = 0, *next = 0;
    node_list_rec* data = 0, *new_head = head_list;
    if(a.get_phone() && a.get_c_phone() == EQ){
        h = hash_phone(a.get_phone(), mod);
        curr = head[h];
        prev = 0;
        while(curr){
            data = curr->get_data();
            if(!data){
               printf("cho, data = 0????\n");
               return new_head;
            }
            if(a.check(data)){
                ah->delete_avl_eq(data);
                new_head = del_data(data, new_head);

                next = curr->get_next();
                if(prev)
                    prev->set_next(next);
                else
                    head[h] = next;
                delete curr;
                curr = next;
            }
            else{
                prev = curr;
                curr = curr->get_next();
            }
        }
        return new_head;
    }
    else{
        for(i = 0; i < mod; i++){
            curr = head[i];
            prev = 0;
            while(curr){
                data = curr->get_data();
                if(!data){
                   printf("cho, data = 0????\n");
                   return new_head;
                }
                if(a.check(data)){
                    ah->delete_avl_eq(data);
                    new_head = del_data(data, new_head);

                    next = curr->get_next();
                    if(prev)
                        prev->set_next(next);
                    else
                        head[i] = next;
                    delete curr;
                    curr = next;
                }
                else{
                    prev = curr;
                    curr = curr->get_next();
                }
            }
        }
        return new_head;
    }
    return new_head;
}
node_list_rec *hash::delete_base(command& a, node_list_rec* head_list, avl* avl_head, avl* ah, hash* hh){
    int i = 0, h = -1;
    hash_node_data* curr = 0, *prev = 0, *next = 0;
    node_list_rec* data = 0, *new_head = head_list;
    if(a.get_phone() && a.get_c_phone() == EQ){
        h = hash_phone(a.get_phone(), mod);
        curr = head[h];
        prev = 0;
        while(curr){
            data = curr->get_data();
            if(!data){
               printf("cho, data = 0????\n");
               return new_head;
            }
            if(a.check(data)){
                ah->delete_avl_eq(data);
                avl_head->delete_avl_eq(data);
                hh->delete_hash(data);
                new_head = del_data(data, new_head);

                next = curr->get_next();
                if(prev)
                    prev->set_next(next);
                else
                    head[h] = next;
                delete curr;
                curr = next;
            }
            else{
                prev = curr;
                curr = curr->get_next();
            }
        }
        return new_head;
    }
    else{
        for(i = 0; i < mod; i++){
            curr = head[i];
            prev = 0;
            while(curr){
                data = curr->get_data();
                if(!data){
                   printf("cho, data = 0????\n");
                   return new_head;
                }
                if(a.check(data)){
                    ah->delete_avl_eq(data);
                    avl_head->delete_avl_eq(data);
                    hh->delete_hash(data);
                    new_head = del_data(data, new_head);

                    next = curr->get_next();
                    if(prev)
                        prev->set_next(next);
                    else
                        head[i] = next;
                    delete curr;
                    curr = next;
                }
                else{
                    prev = curr;
                    curr = curr->get_next();
                }
            }
        }
        return new_head;
    }
    return new_head;
}
void hash::delete_base(command& a, list* ll, avl* ah){
    int i = 0, h = -1;
    hash_node_data* curr = 0, *prev = 0, *next = 0;
    node_list_rec* data = 0;
    if(a.get_phone() && a.get_c_phone() == EQ){
        h = hash_phone(a.get_phone(), mod);
        curr = head[h];
        prev = 0;
        while(curr){
            data = curr->get_data();
            if(!data){
               printf("cho, data = 0????\n");
               return;
            }
            if(a.check(data)){
                ah->delete_avl_eq(data);

                int g = curr->get_data()->get_group();
                ll[g].get_avl()->delete_avl_eq(data);
                ll[g].get_hash()->delete_hash(data);

                ll[g].set_head(del_data(data, ll[g].get_head()));

                next = curr->get_next();
                if(prev)
                    prev->set_next(next);
                else
                    head[h] = next;
                delete curr;
                curr = next;
            }
            else{
                prev = curr;
                curr = curr->get_next();
            }
        }
    }
    else{
        for(i = 0; i < mod; i++){
            curr = head[i];
            prev = 0;
            while(curr){
                data = curr->get_data();
                if(!data){
                   printf("cho, data = 0????\n");
                   return;
                }
                if(a.check(data)){
                    ah->delete_avl_eq(data);

                    int g = curr->get_data()->get_group();
                    ll[g].get_avl()->delete_avl_eq(data);
                    ll[g].get_hash()->delete_hash(data);

                    ll[g].set_head(del_data(data, ll[g].get_head()));

                    next = curr->get_next();
                    if(prev)
                        prev->set_next(next);
                    else
                        head[i] = next;
                    delete curr;
                    curr = next;
                }
                else{
                    prev = curr;
                    curr = curr->get_next();
                }
            }
        }
    }
}
void hash::delete_hash(node_list_rec* a){
    int h = -1;
    hash_node_data* curr = 0, *prev = 0, *next = 0;
    node_list_rec* data = 0;
    h = hash_phone(a->get_phone(), mod);
    curr = head[h];
    prev = 0;
    while(curr){
        data = curr->get_data();
        if(!data){
           printf("cho, data = 0????\n");
           return;
        }
        if(!cmp_hash_list(a, data)){
            next = curr->get_next();
            if(prev)
                prev->set_next(next);
            else
                head[h] = next;
            delete curr;
            curr = next;
         }
         else{
             prev = curr;
             curr = curr->get_next();
        }
    }
}

node_list_rec* hash::insert_hash(command &a_){
    int h = -1, cmp_hash = 0;
    //vrode tut mojno check iz command use
    h = hash_phone(a_.get_phone(), mod);
    if(!head[h]){
        node_list_rec* a = new node_list_rec(a_);
        hash_node_data* tmp = new hash_node_data(a);
        head[h] = tmp;
        tmp->set_next(0);
        return a;
    }
    hash_node_data* curr = head[h], *prev = head[h];
    while(curr && (cmp_hash = !a_.check(curr->get_data()))){
        prev = curr;
        curr = curr->get_next();
    }
    if(!cmp_hash){
        return 0;
    }
    node_list_rec* a = new node_list_rec(a_);
    hash_node_data* tmp = new hash_node_data(a);
    prev->set_next(tmp);
    tmp->set_next(curr);
    return a;
}
node_list_rec* hash::insert_ah(command &a_, avl* ah){
    int h = -1, cmp_hash = 0;
    //vrode tut mojno check iz command use
    h = hash_phone(a_.get_phone(), mod);
    if(!head[h]){
        node_list_rec* a = new node_list_rec(a_);
        hash_node_data* tmp = new hash_node_data(a);
        ah->insert_avl(a);
        head[h] = tmp;
        tmp->set_next(0);
        return a;
    }
    hash_node_data* curr = head[h], *prev = head[h];
    while(curr && (cmp_hash = !a_.check(curr->get_data()))){
        prev = curr;
        curr = curr->get_next();
    }
    if(!cmp_hash){
        return 0;
    }
    node_list_rec* a = new node_list_rec(a_);
    hash_node_data* tmp = new hash_node_data(a);
    ah->insert_avl(a);
    prev->set_next(tmp);
    tmp->set_next(curr);
    return a;
}
void hash::insert_hash(node_list_rec* a){
    int h = -1;
    h = hash_phone(a->get_phone(), mod);
    hash_node_data* tmp = new hash_node_data(a);
    tmp->set_next(head[h]);
    head[h] = tmp;

}
void hash::select_hash(int sock, command &a){
    int i = 0, h = -1;
    hash_node_data* curr = 0;
    if(a.get_phone() && a.get_c_phone() == EQ){
        h = hash_phone(a.get_phone(), mod);
        curr = head[h];
        while(curr){
            if(a.check(curr->get_data()))
                curr->get_data()->print_sock(sock);
            curr = curr->get_next();
        }
    }
    else{
        for(i = 0; i < mod; i++){
            curr = head[i];
            while(curr){
                if(a.check(curr->get_data()))
                    curr->get_data()->print_sock(sock);
                curr = curr->get_next();
            }
        }
    }
}
//TODO select in hash and avl
void hash::delete_all_hash(){
    hash_node_data* curr = 0;
    for(int i = 0; i < mod; i++){
        curr = head[i];
        while (curr){
            head[i] = curr->get_next();
            delete curr;
            curr = head[i];
        }
    }
    delete [] head;
}

void hash::delete_all_hash_base(){
    hash_node_data* curr = 0;
    for(int i = 0; i < mod; i++){
        curr = head[i];
        while (curr){
            head[i] = curr->get_next();
            delete curr;
            curr = head[i];
        }
        head[i] = 0;
    }

}

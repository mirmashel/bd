#include "all.h"
#include "record.h"
#include "node_list.h"
#include "base.h"
#define MAX_PRINT 15
int base::read_base(const char* filename)
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
        tmp->init(buf, p, g % GROUP_I);
        lists_head[g % GROUP_I].insert_base(tmp);
        ah->insert_avl(tmp);
        hh->insert_hash(tmp);
    }
    if(!feof(fp))
    {
        fclose(fp);
        return -3;
    }
    fclose(fp);
    return 0;
}


void base::select_base(int sock, command& a){
    if(a.get_name()){
        ah->select_avl(sock, a);
        return;
    }
    if(a.get_group()&& a.get_oper()==OP_NONE){
        lists_head[a.get_group()].print_list_sock(sock);
        return;
    }
    if(a.get_group()){
        if(a.get_oper() == OR){
            if(a.get_phone()){
                int p = a.get_phone();
                op_type o = a.get_oper();
                cond_type c = a.get_c_phone();
                a.del_for_select();
                lists_head[a.get_group()].select_lah(sock, a);
                a.set_for_select(p, o, c);
                a.inverse_();
                hh->select_hash(sock, a);
                return;
            }
            int p = a.get_group();
            op_type o = a.get_oper();
            cond_type c = a.get_c_group();
            a.del_for_select_();
            ah->select_avl(sock, a);
            a.set_for_select_(p, o, c);
            a.inverse();
            lists_head[a.get_group()].select_lah(sock, a);
            return;
        }
        else
            lists_head[a.get_group()].select_lah(sock, a);
    }
    else{
        if(a.get_phone() && a.get_name() && a.get_oper() == OR){
            int p = a.get_phone();
            op_type o = a.get_oper();
            cond_type c = a.get_c_phone();
            a.del_for_select();
            ah->select_avl(sock, a);
            a.set_for_select(p, o, c);
            a.inverse();
            hh->select_hash(sock, a);
            return;
        }
        if(a.get_name())
            ah->select_avl(sock, a);
        else
            hh->select_hash(sock, a);
    }
}
void base::delete_base(command & a){
    int m = 0, n = 0, k = -1, l = -2, i;
    if(a.get_group()){
        if(a.get_oper() != AND){
            switch(a.get_c_group()){
            case EQ: m = n = a.get_group();
                break;
            case GT: m = a.get_group() + 1;
                n = GROUP_I - 1;
                break;
            case GE:m = a.get_group();
                n = GROUP_I - 1;
                break;
            case LE:m = 0;
                n = a.get_group();
                break;
            case LT:m = 0;
                n = a.get_group() - 1;
                break;
            case LIKE: break;
            case COND_NONE:
                break;
            case NE:if(a.get_group() == 0){
                    m = 1;
                    n = GROUP_I;
                }else{
                    if(a.get_group() == GROUP_I - 1){
                        m = 0;
                        n = GROUP_I - 2;
                    }else{
                        m = 0;
                        n = a.get_group() - 1;
                        k = a.get_group() + 1;
                        l = GROUP_I - 1;
                    }
                }
            }
            for(i = m; i <= n; i++){
                lists_head[i].destroy_base(ah, hh);
            }
            for(i = k; i <= l; i++){
                lists_head[i].destroy_base(ah, hh);
            }

        }
        else
            lists_head[a.get_group() % GROUP_I].delete_base(a, ah, hh);
        if(a.get_oper() != OR)
            return;
    }
    if(a.get_phone()){
        hh->delete_base(a, lists_head, ah);
        if(a.get_oper() != OR)
            return;
    }
    if(a.get_name()){
        ah->goto_head();
        ah->delete_base(a, lists_head, hh);
    }
}
void base::insert_base(command &a){
    node_list_rec* tmp = lists_head[a.get_group()].insert_base(a);
    if(!tmp)
        return;
    ah->insert_avl(tmp);
    hh->insert_hash(tmp);
}
void base::comanda(int sock, command &a){
    switch(a.get_type()){
    case SELECT:
        select_base(sock, a);
        break;
    case INSERT:{
        insert_base(a);
        break;
    }
    case DELETE:{
        delete_base(a);
        break;
    }
    default:
        break;
    }
}


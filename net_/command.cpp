#include "command.h"
#define KOL 30

void command::del(){
    type = CMD_NONE;
    c_name = COND_NONE;
    c_phone = COND_NONE;
    c_group = COND_NONE;
    oper = OP_NONE;
    this->init(NULL, 0, 0);
}

//QUIT, STOP, SELECT, INSERT, DELETE
cmd_type choose_type(const char* b){
    if(!strcmp(b, "quit"))
        return QUIT;
    if(!strcmp(b, "stop"))
        return STOP;
    if(!strcmp(b, "select"))
        return SELECT;
    if(!strcmp(b, "insert"))
        return INSERT;
    if(!strcmp(b, "delete"))
        return DELETE;
    return CMD_NONE;
}
//COND_NONE, EQ, NE, LT, GT, LE, GE, LIKE
cond_type choose_cond(const char* b){
    if(!strcmp(b, "="))
        return EQ;
    if(!strcmp(b, "<>"))
        return NE;
    if(!strcmp(b, "<"))
        return LT;
    if(!strcmp(b, ">"))
        return GT;
    if(!strcmp(b, "<="))
        return LE;
    if(!strcmp(b, ">="))
        return GE;
    if(!strcmp(b, "like"))
        return LIKE;
    return COND_NONE;
}
op_type choose_oper(const char* b){
    if(!strcmp(b, "and"))
        return AND;
    if(!strcmp(b, "or"))
        return OR;
    return OP_NONE;
}

void command::print_cmd(){
    int flag = 0;
    switch(type){
    case QUIT: printf("quit;\n");
        return;
    case STOP: printf("stop;");
        return;
    case SELECT:printf("select * where ");
        break;
    case INSERT: printf("insert (");
        break;
    case DELETE: printf("delete where ");
        break;
    default: printf("ochen ploho\n");
        return;
    }
    if(type != INSERT){
        if(c_name){
            printf("name ");
            switch(c_name){
            case 1:
                printf("= ");
                break;
            case 2:
                printf("<> ");
                break;
            case 3:
                printf("< ");
                break;
            case 4:
                printf("> ");
                break;
            case 5:
                printf("<= ");
                break;
            case 6:
                printf(">= ");
                break;
            case 7:
                printf("like ");
                break;
            default:
                printf("ochen ploho\n");
                return;
            }
            printf("%s", get_name());
            if(oper)
                switch(oper){
                    case 1: printf(" and ");
                    break;
                case 2: printf(" or ");
                    break;
                default:printf(" ochen ploho\n");
                    return;
                }
            else{
                printf(";\n");
                return;
            }
            flag = 1;
        }
        if(c_phone){
            printf("phone ");
            switch(c_phone){
            case 1:
                printf("= ");
                break;
            case 2:
                printf("<> ");
                break;
            case 3:
                printf("< ");
                break;
            case 4:
                printf("> ");
                break;
            case 5:
                printf("<= ");
                break;
            case 6:
                printf(">= ");
                break;
            case 7:
                printf("like ");
                break;
            default:
                printf("ochen ploho\n");
                return;
            }
            printf("%d", get_phone());
            if(!flag && oper)
                switch(oper){
                    case 1: printf(" and ");
                    break;
                case 2: printf(" or ");
                    break;
                default:printf("ochen ploho\n");
                    return;
                }
            else{
                printf(";\n");
                return;
            }
            flag = 1;
        }
        if(c_group){
            printf("group ");
            switch(c_group){
            case 1:
                printf("= ");
                break;
            case 2:
                printf("<> ");
                break;
            case 3:
                printf("< ");
                break;
            case 4:
                printf("> ");
                break;
            case 5:
                printf("<= ");
                break;
            case 6:
                printf(">= ");
                break;
            case 7:
                printf("like ");
                break;
            default:
                printf("ochen ploho\n");
                return;
            }
            printf("%d", get_group());
            if(!flag && oper)
                switch(oper){
                    case 1: printf(" and ");
                    break;
                case 2: printf(" or ");
                    break;
                default:printf("ochen ploho\n");
                    return;
                }
            else{
                printf(";\n");
                return;
            }
        }
    }
    else{
        printf("%s, %d, %d);\n", get_name(), get_phone(), get_group());
        return;
    }
}

int div_words(char** words, char* str){
    int i = 0, j = 0, k = 0, flag_tz = 0;
    for(i = 0, k = 0; str[i] && k < KOL; i = j, k++){
        while (str[j] && str[j] != ' ' && str[j] != ';' && str[j] != ',' && str[j] != ')' && str[j] != '(' && str[j] != '\n') j++;
        if(str[j] && flag_tz){
            printf("vot zdes 1\n");
            return 0;
        }
        if(str[j] == ';')
            flag_tz = 1;
        str[j] = 0;
        j++;
        while(str[j] && (str[j] == ',' || str[j] == ')' || str[j] == '(' || str[j] == '\n' || str[j] == ' ')) j++;
        words[k] = str + i;
    }
    return 1;
}
int command::parse(char* str){
    int i = 0, k = 0, k_name = -1;
    //char name_[LEN];
    char phone_s[LEN];
    char group_s[LEN];
    int phone_ = 0;
    int group_ = 0;
    char* words[KOL];
    for(i = 0; i < KOL; i++)
        words[i] = 0;
    i = 0;
    //printf("jopa0: %s %d %d\n", name_, phone_, group_);
    if(!div_words(words, str))
        return 0;
    //for(i = 0; i < KOL; i++)
    //    printf("words[%d] = %s\n", i, words[i]);
    type = choose_type(words[k]);
    k++;
    if(!type)
        return 0;
    if(type == QUIT){
            return 1;
    }
    if(type == STOP)
        return 1;

    if(type == SELECT || type == DELETE){
        if(type == SELECT && strcmp(words[k], "*"))
            return 0;
        if(type == SELECT)
            k++;
        if(strcmp(words[k], "where"))
            return 0;
        k++;
        if(!strcmp(words[k], "name")){
            k++;
            c_name = choose_cond(words[k]);
            k++;
            //strcpy(name_, words[k]);
            k_name = k;
            k++;
        }
        else{
            if(!strcmp(words[k], "phone")){
                k++;
                c_phone = choose_cond(words[k]);
                k++;
                strcpy(phone_s, words[k]);
                k++;
                phone_ = atoi(phone_s);
            }
            else{
                if(!strcmp(words[k], "group")){
                    k++;
                    c_group = choose_cond(words[k]);
                    k++;
                    strcpy(group_s, words[k]);
                    k++;
                    group_ = atoi(group_s);
                }
                else
                    return 0;
            }
        }
        if(!words[k]){
            //printf("jopa1: %s %d %d\n", name_, phone_, group_);
            if(k_name < 0)
                init(0, phone_, group_);
            else
                init(words[k_name], phone_, group_);
            return 1;
        }
        oper = choose_oper(words[k]);
        k++;

        if(!strcmp(words[k], "name")){
            k++;
            c_name = choose_cond(words[k]);
            k++;
            //strcpy(name_, words[k]);
            k_name = k;
            k++;
        }
        else{
            if(!strcmp(words[k], "phone")){
                k++;
                c_phone = choose_cond(words[k]);
                k++;
                strcpy(phone_s, words[k]);
                k++;
                phone_ = atoi(phone_s);
            }
            else{
                if(!strcmp(words[k], "group")){
                    k++;
                    c_group = choose_cond(words[k]);
                    k++;
                    strcpy(group_s, words[k]);
                    k++;
                    group_ = atoi(group_s);
                }
                else
                    return 0;
            }
        }
        if(words[k])
            return 0;
        //printf("jopa2: %s %d %d\n", name_, phone_, group_);
        if(k_name < 0)
            init(0, phone_, group_);
        else
            init(words[k_name], phone_, group_);
        return 1;
    }
    if(type == INSERT){
        c_name = EQ;
        c_group = EQ;
        c_phone = EQ;
        k_name = k;
        k++;
        strcpy(phone_s, words[k]);
        k++;
        phone_ = atoi(phone_s);
        strcpy(group_s, words[k]);
        k++;
        group_ = atoi(group_s);
        init(words[k_name], phone_, group_);
        return 1;
    }
    return 0;
}
//=
int cmp1 (const char* a, const char* b){
    return !strcmp(a, b);
}
//<>
int cmp2 (const char* a, const char* b){
    return strcmp(a, b);
}
//>=
int cmp3 (const char* a, const char* b){
    return (strcmp(a, b) <= 0);
}
//<=
int cmp4 (const char* a, const char* b){
    return (strcmp(a, b) >= 0);
}
//>
int cmp5 (const char* a, const char* b){
    return (strcmp(a, b) < 0);
}
//<
int cmp6 (const char* a, const char* b){
    return (strcmp(a, b) > 0);
}
//=
int cmp1 (int a, int b){
    return (a == b);
}
//<>
int cmp2 (int a, int b){
    return (a != b);
}
//>=
int cmp3 (int a, int b){
    return (a <= b);
}
//<=
int cmp4 (int a, int b){
    return (a >= b);
}
//>
int cmp5 (int a, int b){
    return (a < b);
}
//<
int cmp6 (int a, int b){
    return (a > b);
}
int cmp_like(const char* a, const char* b){
    int i, j, ans = 0;
    for(i = 0, j = 0; b[j] && a[i]; ){
        if(a[i] != '%' && a[i] != '_'){
            if(a[i] == '\\')
                i++;
            if(a[i] != b[j])
                return 0;
            j++;
            i++;
        }
        else{
            if(a[i] == '_'){
                i++;
                j++;
            }
            else{
                while(a[i] == '%') i++;
                ans = cmp_like(a + i, b + j);
                //printf("%d %s %s\n", ans, a + i, b + j);
                while(b[j] && !ans){
                    j++;
                    ans = cmp_like(a + i, b + j);
                    //printf("%d %s %s\n", ans, a + i, b + j);
                }
                if(ans)
                    return 1;
            }
        }
    }
    while(a[i] == '%') i++;
    if(a[i] || b[j])
        return 0;
    return 1;
}
int command::check(const record* b){
    int n = 0, g = 0, p = 0;
    if(this->get_name()){
        switch(c_name){
        case EQ:
            if(cmp1(this->get_name(), b->get_name()))
                n = 1;
            break;
        case NE:
            if(cmp2(this->get_name(), b->get_name()))
                n = 1;
            break;
        case GE:
            if(cmp3(this->get_name(), b->get_name()))
                n = 1;
            break;
        case LE:
            if(cmp4(this->get_name(), b->get_name()))
                n = 1;
            break;
        case GT:
            if(cmp5(this->get_name(), b->get_name()))
                n = 1;
            break;
        case LT:
            if(cmp6(this->get_name(), b->get_name()))
                n = 1;
            break;
        case LIKE:
            if(cmp_like(this->get_name(), b->get_name()))
                n = 1;
            break;
        case COND_NONE:
            printf("vse ochen' ploho\n");
        }
    }
    else if(oper != OR) n = 1;
    if(this->get_phone()){
        switch(c_phone){
        case EQ:
            if(cmp1(this->get_phone(), b->get_phone()))
                p = 1;
            break;
        case NE:
            if(cmp2(this->get_phone(), b->get_phone()))
                p = 1;
            break;
        case GE:
            if(cmp3(this->get_phone(), b->get_phone()))
                p = 1;
            break;
        case LE:
            if(cmp4(this->get_phone(), b->get_phone()))
                p = 1;
            break;
        case GT:
            if(cmp5(this->get_phone(), b->get_phone()))
                p = 1;
            break;
        case LT:
            if(cmp6(this->get_phone(), b->get_phone()))
                p = 1;
            break;
        case LIKE:
            break;
        case COND_NONE:
            printf("vse ochen' ploho\n");
        }
    }
    else if(oper != OR) p = 1;
    if(this->get_group()){
        switch(c_group){
        case EQ:
            if(cmp1(this->get_group(), b->get_group()))
                g = 1;
            break;
        case NE:
            if(cmp2(this->get_group(), b->get_group()))
                g = 1;
            break;
        case GE:
            if(cmp3(this->get_group(), b->get_group()))
                g = 1;
            break;
        case LE:
            if(cmp4(this->get_group(), b->get_group()))
                g = 1;
            break;
        case GT:
            if(cmp5(this->get_group(), b->get_group()))
                g = 1;
            break;
        case LT:
            if(cmp6(this->get_group(), b->get_group()))
                g = 1;
            break;
        case LIKE:
            break;
        case COND_NONE:
            printf("vse ochen' ploho\n");
        }
    }
    else if(oper != OR) g = 1;
    if(oper == OR)
        return n || g || p;
    else
        return p && n && g;
}

#ifndef COMMAND_H
#define COMMAND_H
#include "record.h"
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

enum cmd_type{
    CMD_NONE, QUIT, STOP, SELECT, INSERT, DELETE
};

enum cond_type{
    COND_NONE, EQ, NE, LT, GT, LE, GE, LIKE
};

enum op_type{
    OP_NONE, AND, OR
};

class command : public record{
private:
    cmd_type type = CMD_NONE;
    cond_type c_name = COND_NONE;
    cond_type c_phone = COND_NONE;
    cond_type c_group = COND_NONE;
    op_type oper = OP_NONE;
public:
    command() : record(){}
    ~command(){}
    void print_cmd();
    int parse(char* str);
    int check(const record* b);
    void del();
    cmd_type get_type(){
        return type;
    }
    cond_type get_c_phone(){
        return c_phone;
    }
    cond_type get_c_group(){
        return c_group;
    }
    cond_type get_c_name(){
        return c_name;
    }
    op_type get_oper(){
        return oper;
    }
    void inverse(){
        oper = AND;
        switch(c_name){
        case EQ:
            c_name = NE;
            break;
        case NE:
            c_name = EQ;
            break;
        case LT:
            c_name = GE;
            break;
        case GT:
            c_name = LE;
            break;
        case LE:
            c_name = GT;
            break;
        case GE:
            c_name = LT;
            break;
        case LIKE:
            printf("ne mojet bit takoy strochki\n");
            break;
        case COND_NONE:
            break;
        }
    }
    void inverse_(){
        oper = AND;
        switch(c_group){
        case EQ:
            c_group = NE;
            break;
        case NE:
            c_group = EQ;
            break;
        case LT:
            c_group = GE;
            break;
        case GT:
            c_group = LE;
            break;
        case LE:
            c_group = GT;
            break;
        case GE:
            c_group = LT;
            break;
        case LIKE:
            printf("ne mojet bit takoy strochki\n");
            break;
        case COND_NONE:
            break;
        }
    }
    void del_for_select(){
        this->set_phone(0);
        oper = OP_NONE;
        c_phone = COND_NONE;
    }
    void set_for_select(int p, op_type o, cond_type c){
        this->set_phone(p);
        oper = o;
        c_phone = c;
    }

    void del_for_select_(){
        this->set_group(0);
        oper = OP_NONE;
        c_group = COND_NONE;
    }
    void set_for_select_(int p, op_type o, cond_type c){
        this->set_group(p);
        oper = o;
        c_group = c;
    }
};

#endif //COMMAND_H

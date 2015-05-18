#ifndef HOTELMANAGEMENT_CUSTOMERS_H
#define HOTELMANAGEMENT_CUSTOMERS_H

#include "pch.h"

typedef struct
{
    int id;
    char* first_name;
    char* last_name;
    char* telephone;
    char* pesel;
    char* id_number;
} customers_row;

customers_row** customers;

void print_customers();
void create_customer();
void remove_customer();
void modify_customer();
void search_customers();

void db_write_customers_callback(FILE* f);
void db_customers_callback(void* obj, int col, const char* buff, int buff_len);
void db_customers_push_callback(void* obj, int row);

#endif //HOTELMANAGEMENT_CUSTOMERS_H

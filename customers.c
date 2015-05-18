#include "customers.h"
#include "database.h"
#include "pch.h"

void db_write_customers_callback(FILE* f)
{
    customers_row** r = customers;
    while(r != NULL && *r != NULL){
#ifdef DEBUG
        printf("Iterate through item\n");
#endif

        fprintf(f, "%d", (*r)->id);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%s", (*r)->first_name);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%s", (*r)->last_name);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%s", (*r)->telephone);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%s", (*r)->pesel);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%s", (*r)->id_number);
        fputc(ROW_SEPARATOR, f);

        ++r;
    }

    free(r);
}

void db_customers_push_callback(void* obj, int row)
{
    customers = realloc(customers, sizeof(customers_row) * (row + 1));
    customers[row] = obj;

#ifdef DEBUG
    printf("Customer struct: %d, %s\n", ((customers_row*)obj)->id, ((customers_row*)obj)->first_name);
#endif
}

void db_customers_callback(void* obj, int col, const char* buff, int buff_len)
{
    char* copy = malloc(strlen(buff) + 1);
    strcpy(copy, buff);

    switch(col){
        case 0:
            ((customers_row*)obj)->id = atoi(buff);
            free(copy);
            break;
        case 1:
            ((customers_row*)obj)->first_name = copy;
            break;
        case 2:
            ((customers_row*)obj)->last_name = copy;
            break;
        case 3:
            ((customers_row*)obj)->telephone = copy;
            break;
        case 4:
            ((customers_row*)obj)->pesel = copy;
            break;
        case 5:
            ((customers_row*)obj)->id_number = copy;
            break;
        default:
            break;
    }
}

void print_customers()
{
    printf("Wypisywanie klientów:\n");

    customers_row** r = customers;
    while(r != NULL && *r != NULL){
        printf("Reading customer: %d, %s, %s\n", (*r)->id, (*r)->first_name, (*r)->last_name);

        ++r;
    }

    free(r);
}

void create_customer()
{
    printf("Dodawanie klienta\n");
    //TODO: get input from user

    if(customers == NULL){
        //If no rows then malloc for one
        customers = malloc(sizeof(customers_row));

        customers_row* c = malloc(sizeof(customers_row));
        c->id = 1;
        c->first_name = "Testowy Nowy";
        c->last_name = "Nowak";
        c->pesel = "910203040506";
        c->id_number = "AAA000011";
        c->telephone = "654654566";

        customers[0] = c;
    }
    else{
        int row_count = 0;
        int last_id = 0;

        //Get last id and row count
        customers_row** r = customers;
        while(*r != NULL){
            last_id = (*r)->id;
            ++row_count;
            ++r;
        }

        customers = realloc(customers, sizeof(customers_row) * (row_count + 1));

        customers_row* c = malloc(sizeof(customers_row));
        c->id = last_id + 1;
        c->first_name = "Testowy";
        c->last_name = "Nowak";
        c->pesel = "910203040506";
        c->id_number = "AAA000011";
        c->telephone = "654654566";

        customers[row_count] = c;

        free(r);
    }
}

void remove_customer()
{
    printf("Usuwanie klienta\n");

    //TODO
    int searching_id = 1;

    int row_count = 0;
    customers_row** rn = malloc(sizeof(customers_row));
    customers_row** r = customers;
    while(r != NULL && *r != NULL){
        if((*r)->id != searching_id){
            rn = realloc(rn, sizeof(customers_row) * (row_count + 1));
            rn[row_count] = *r;
            ++row_count;
        }

        ++r;
    }

    free(r);
    free(customers);
    customers = rn;
}

void modify_customer()
{
    printf("Modyfikowanie klienta\n");
    //TODO
}

void search_customers()
{
    printf("Szukanie klienta\n");
    //TODO
}
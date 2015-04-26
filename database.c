#include <stdio.h>
#include "pch.h"
#include "database.h"
#include "bookings.h"
#include "customers.h"
#include "rooms.h"

bool database_init(const char* rooms_database_filename, const char* customers_database_filename, const char* bookings_database_filename)
{
    rooms_database_file = fopen(rooms_database_filename, "a+b");
    customers_database_file = fopen(customers_database_filename, "a+b");
    bookings_database_file = fopen(bookings_database_filename, "a+b");

    if(!rooms_database_file || !customers_database_file || !bookings_database_file){
        fprintf(stderr, "Cannot open at least one of databases.");
        return false;
    }

#ifdef DEBUG
	printf("Opened databases\n");
#endif

    database_read_room_rows(rooms_database_file);
    database_read_customer_rows(customers_database_file);
    database_read_booking_rows(bookings_database_file);

    return true;
}

void database_read_room_rows(FILE* f)
{
    database_read_rows(f, db_rooms_callback, db_rooms_push_callback, sizeof(rooms_row), 5);
}

void database_read_customer_rows(FILE* f)
{
    database_read_rows(f, db_customers_callback, db_customers_push_callback, sizeof(customers_row), 6);
}

void database_read_booking_rows(FILE* f)
{
    database_read_rows(f, db_bookings_callback, db_bookings_push_callback, sizeof(bookings_row), 5);
}

void database_read_rows(FILE* f, struct_bind_func_read cb, struct_bind_func_read_push cb_push, int mem_size, int col_size)
{
    //Set caret to file begin
    rewind(f);

    void* obj = malloc(mem_size);

    unsigned char c;
    int i = 0, row = 0, col = 0;
    unsigned char buff[2048];
    memset(buff, 0, sizeof(buff));

    do {
        fread(&c, sizeof(unsigned char), 1, f);

        if(c == COLUMN_SEPARATOR || c == ROW_SEPARATOR){
            cb(obj, col, buff, i);

            memset(buff, 0, sizeof(buff));
            i = 0;

            ++col;

            if(c == ROW_SEPARATOR && col == col_size){
                //push
                cb_push(obj, row);
                obj = malloc(mem_size);

                col = 0;

                ++row;
            }
        }
        else{
            buff[i] = c;
            ++i;
        }
    }
    while(!feof(f));
}

//WRITE

void database_write_rows(FILE* f, struct_bind_func_save cb)
{
    ftruncate(fileno(f), 0);

    //Set caret to file begin
    rewind(f);

    cb(f);
}

void database_rooms_write_rows(FILE* f)
{
    database_write_rows(f, db_write_rooms_callback);
}

void database_customers_write_rows(FILE* f)
{
    database_write_rows(f, db_write_customers_callback);
}

void database_bookings_write_rows(FILE* f)
{
    database_write_rows(f, db_write_bookings_callback);
}

void database_close()
{
    fclose(rooms_database_file);
    fclose(customers_database_file);
    fclose(bookings_database_file);
}
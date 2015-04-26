//
// Created by Kamil Soko³owski on 2015-04-18.
//

#ifndef HOTELMANAGEMENT_BOOKINGS_H
#define HOTELMANAGEMENT_BOOKINGS_H

#include "pch.h"

typedef struct
{
    int customer_id;
    int room_id;
    time_t date_start;
    time_t date_end;
    int price;
} bookings_row;

bookings_row** bookings;

void database_bookings_write_rows(FILE* f);
void db_write_customers_callback(FILE* f);
void db_bookings_callback(void* obj, int col, const char* buff, int buff_len);
void db_bookings_push_callback(void* obj, int row);
void db_write_bookings_callback(FILE* f);

void print_bookings();
void create_booking();
void remove_booking();
void modify_booking();
void search_bookings();

#endif //HOTELMANAGEMENT_BOOKINGS_H

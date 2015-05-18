//
// Created by Kamil Soko³owski on 2015-04-18.
//

#ifndef HOTELMANAGEMENT_ROOMS_H
#define HOTELMANAGEMENT_ROOMS_H

#include "pch.h"


typedef enum {
    BASIC = 0,
    EXTRA = 1
} standard_t;

typedef struct
{
    int id;
    standard_t standard;
    int places;
    int price_per_day;
    bool status;
} rooms_row;

rooms_row** rooms;

void print_rooms();
void modify_room();
void search_rooms();

void db_write_rooms_callback(FILE* f);
void db_rooms_callback(void* obj, int col, const char* buff, int buff_len);
void db_rooms_push_callback(void* obj, int row);

#endif //HOTELMANAGEMENT_ROOMS_H

//
// Created by Kamil Soko³owski on 2015-04-18.
//

#ifndef HOTELMANAGEMENT_DATABASE_H
#define HOTELMANAGEMENT_DATABASE_H

#define ROW_SEPARATOR 0x1E
#define COLUMN_SEPARATOR 0x1F

FILE* rooms_database_file;
FILE* customers_database_file;
FILE* bookings_database_file;

typedef void (*struct_bind_func_read)(void* obj, int col, const char* buff, int buff_len);
typedef void (*struct_bind_func_read_push)(void* obj, int row);
typedef void (*struct_bind_func_save)(FILE* f);

void database_read_room_rows(FILE* f);
void database_read_customer_rows(FILE* f);
void database_read_booking_rows(FILE* f);

void database_read_rows(FILE* f, struct_bind_func_read cb, struct_bind_func_read_push cb_push, int mem_size, int col_size);

void database_write_rows(FILE* f, struct_bind_func_save cb);

void database_rooms_write_rows(FILE* f);
void database_customers_write_rows(FILE* f);

bool database_init(const char* rooms_database_filename, const char* customers_database_filename, const char* bookings_database_filename);
void database_close();

#endif //HOTELMANAGEMENT_DATABASE_H

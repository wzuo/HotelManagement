#include "bookings.h"
#include "database.h"
#include "pch.h"

void db_write_bookings_callback(FILE* f)
{
    bookings_row** r = bookings;
    while(r != NULL && *r != NULL){
#ifdef DEBUG
        printf("Iterate through item %d\n",  (*r)->customer_id);
#endif

        fprintf(f, "%d", (*r)->customer_id);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%d", (*r)->room_id);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%d", (*r)->date_start);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%d", (*r)->date_end);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%d", (*r)->price);
        fputc(ROW_SEPARATOR, f);

        ++r;
    }

    free(r);
}

void db_bookings_callback(void* obj, int col, const char* buff, int buff_len)
{
    switch(col){
        case 0:
            ((bookings_row*)obj)->customer_id = atoi(buff);
            break;
        case 1:
            ((bookings_row*)obj)->room_id = atoi(buff);
            break;
        case 2:
            ((bookings_row*)obj)->date_start = atoi(buff);
            break;
        case 3:
            ((bookings_row*)obj)->date_end = atoi(buff);
            break;
        case 4:
            ((bookings_row*)obj)->price = atoi(buff);
            break;
        default:
            break;
    }
}

void db_bookings_push_callback(void* obj, int row)
{
    bookings = realloc(bookings, sizeof(bookings_row) * (row + 1));
    bookings[row] = obj;

#ifdef DEBUG
    printf("Bookings struct: %d, %d\n", ((bookings_row*)obj)->room_id, ((bookings_row*)obj)->customer_id);
#endif
}


void print_bookings()
{
    printf("Wypisywanie rezerwacji:\n");

    bookings_row** r = bookings;
    while(r != NULL && *r != NULL){
        printf("Reading booking: %d, %d, %d, %d\n", (*r)->customer_id, (*r)->room_id, (*r)->date_start, (*r)->date_end);

        ++r;
    }

    free(r);
}

void create_booking()
{
    printf("Dodawanie rezerwacji\n");
    //TODO
}

void remove_booking()
{
    printf("Usuwanie rezerwacji\n");
    //TODO
}

void modify_booking()
{
    printf("Modyfikowanie rezerwacji\n");
    //TODO
}

void search_bookings()
{
    printf("Szukanie rezerwacji\n");
    //TODO
}
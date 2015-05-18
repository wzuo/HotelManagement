#include "rooms.h"
#include "database.h"
#include "pch.h"

void db_write_rooms_callback(FILE* f)
{
    rooms_row** r = rooms;
    while(r != NULL && *r != NULL){
#ifdef DEBUG
        printf("Iterate through item\n");
#endif

        fprintf(f, "%d", (*r)->id);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%d", (*r)->standard);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%d", (*r)->places);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%d", (*r)->price_per_day);
        fputc(COLUMN_SEPARATOR, f);
        fprintf(f, "%d", (*r)->status);
        fputc(ROW_SEPARATOR, f);

        ++r;
    }

    free(r);
}

void db_rooms_push_callback(void* obj, int row)
{
    rooms = realloc(rooms, sizeof(rooms_row) * (row + 1));
    rooms[row] = obj;

#ifdef DEBUG
    printf("Room struct: %d, %d\n", ((rooms_row*)obj)->id, ((rooms_row*)obj)->status);
#endif
}

void db_rooms_callback(void* obj, int col, const char* buff, int buff_len)
{
    switch(col){
        case 0:
            ((rooms_row*)obj)->id = atoi(buff);
            break;
        case 1:
            ((rooms_row*)obj)->standard = (standard_t)atoi(buff);
            break;
        case 2:
            ((rooms_row*)obj)->places = atoi(buff);
            break;
        case 3:
            ((rooms_row*)obj)->price_per_day = atoi(buff);
            break;
        case 4:
            ((rooms_row*)obj)->status = (buff[buff_len - 1] == '1');
            break;
        default:
            break;
    }
}

void print_rooms()
{
    printf("Wypisywanie pokoju:\n");

    rooms_row** r = rooms;
    while(r != NULL && *r != NULL){
        printf("Reading room: %d, %d\n", (*r)->id, (*r)->status);

        ++r;
    }

    free(r);
}

void modify_room()
{
    printf("Modyfikowanie pokoju\n");
    //TODO
}

void search_rooms()
{
    printf("Szukanie pokoju\n");
    //TODO
}
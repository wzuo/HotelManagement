#include "pch.h"
#include "database.h"
#include "bookings.h"
#include "customers.h"
#include "rooms.h"

#define DEBUG

enum first_actions_t {
	FIRST_ACTION_QUIT = 0,
	FIRST_ACTION_CUSTOMER = 1,
	FIRST_ACTION_ROOMS = 2,
	FIRST_ACTION_BOOKINGS = 3
};

enum second_actions_t {
	SECOND_ACTION_QUIT = 0,
	SECOND_ACTION_CREATE = 1,
	SECOND_ACTION_REMOVE = 2,
	SECOND_ACTION_MODIFY = 3,
	SECOND_ACTION_PRINT = 4,
	SECOND_ACTION_SEARCH = 5
};

int action[2];
bool quit_program = false;

void post_action()
{
	#ifdef DEBUG
	printf("Post action %d %d\n", action[0], action[1]);
	#endif

	if(action[0] == FIRST_ACTION_CUSTOMER){
		if(action[1] == SECOND_ACTION_CREATE){
			create_customer();
		}
		else if(action[1] == SECOND_ACTION_REMOVE){
			remove_customer();
		}
		else if(action[1] == SECOND_ACTION_MODIFY){
			modify_customer();
		}
		else if(action[1] == SECOND_ACTION_PRINT){
			print_customers();
		}
		else if(action[1] == SECOND_ACTION_SEARCH){
			search_customers();
		}
	}
	else if(action[0] == FIRST_ACTION_ROOMS){
		if(action[1] == SECOND_ACTION_MODIFY){
			modify_room();
		}
		else if(action[1] == SECOND_ACTION_PRINT){
			print_rooms();
		}
		else if(action[1] == SECOND_ACTION_SEARCH){
			search_rooms();
		}
	}
	else if(action[0] == FIRST_ACTION_BOOKINGS){
		if(action[1] == SECOND_ACTION_CREATE){
			create_booking();
		}
		else if(action[1] == SECOND_ACTION_REMOVE){
			remove_booking();
		}
		else if(action[1] == SECOND_ACTION_MODIFY){
			modify_booking();
		}
		else if(action[1] == SECOND_ACTION_PRINT){
			print_bookings();
		}
		else if(action[1] == SECOND_ACTION_SEARCH){
			search_bookings();
		}
	}
}

void second_action()
{
	int temp = 0;

	printf("\nPodaj akcje\n");
	printf("0. Koniec programu\n");
	switch(action[0]){
		case FIRST_ACTION_QUIT:
			quit_program = true;
			return;
		case FIRST_ACTION_CUSTOMER: //customer management
			printf("1. Dodaj klienta\n");
			printf("2. Usun klienta\n");
			printf("3. Modyfikuj klienta\n");
			printf("4. Wypisz klientow\n");
			printf("5. Wyszukaj klienta\n");
			break;
		case FIRST_ACTION_ROOMS: //rooms management
			printf("3. Modyfikuj pokoj\n");
			printf("4. Wypisz pokoje\n");
			printf("5. Wyszukaj pokoj\n");
			break;
		case FIRST_ACTION_BOOKINGS: //bookings management
			printf("1. Dodaj rezerwacje\n");
			printf("2. Usun rezerwacje\n");
			printf("3. Modyfikuj rezerwacje\n");
			printf("4. Wypisz rezerwacje\n");
			printf("5. Wyszukaj rezerwacje\n");
			break;

		default: //If
			second_action(); //Repeat second action till we get valid input
			break;
	}

	if(scanf("%d", &temp) != -1){
		switch(temp){
			case SECOND_ACTION_QUIT: //Quit program
				quit_program = true;
				return;
			case SECOND_ACTION_CREATE: //Quit program
			case SECOND_ACTION_REMOVE:
			case SECOND_ACTION_MODIFY:
			case SECOND_ACTION_PRINT:
			case SECOND_ACTION_SEARCH:
				action[1] = temp;

				//Move to post action
				post_action();
				break;
			default:
				second_action(); //Repeat first action till we get valid input
				return;
		}
	}
	else{
		//Repeat second action till we get valid input
		second_action();
	}
}

void first_action()
{
	int temp = 0;

	printf("Podaj akcje:\n");
	printf("0. Koniec programu\n");
	printf("1. Zarzadzanie klientem\n");
	printf("2. Zarzadzanie pokojami\n");
	printf("3. Zarzadzanie rezerwacjami\n");

	if(scanf("%d", &temp) != -1){
		switch(temp){
			case FIRST_ACTION_QUIT: //Quit program
				quit_program = true;
				return;
			case FIRST_ACTION_CUSTOMER:
			case FIRST_ACTION_ROOMS:
			case FIRST_ACTION_BOOKINGS:
				action[0] = temp;

				//Move to second action
				second_action();
				break;
			default:
				first_action(); //Repeat first action till we get valid input
				return;
		}
	}
	else{
		//Repeat first action till we get valid input
		first_action();
	}
}

int main(void)
{
	rooms = NULL;
	bookings = NULL;
	customers = NULL;

	//If database init failed then exit application
	if(!database_init("__rooms.db", "__customers.db", "__bookings.db")){
		return 1;
	}

	printf("Witaj w programie zarzadzajacym hotelem.\n");

	while(!quit_program) {
		first_action();
	}

#ifdef DEBUG
	printf("Saving database..\n");
#endif

	database_rooms_write_rows(rooms_database_file);
	database_customers_write_rows(customers_database_file);
	database_bookings_write_rows(bookings_database_file);

#ifdef DEBUG
	printf("Closing database..\n");
#endif

	database_close();

	return 0;
}

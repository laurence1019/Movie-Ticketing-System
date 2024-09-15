/*Library*/
#include "header.h"

/*File Include*/
#include "admin_main.h"
#include "admin_function.h"
#include "customer_main.h"
#include "customer_main2.h"
#include "customer_function.h"

int main()
{
	//Class Variable
	admin_class admin;
	movie_class movie;
	cust_class cust;
	TicketInfo ticket_store;
    	BookingInfo booking_store;

	//Local Variable
	char choice = ' ';
	bool retry = 1;


	// declare movies in array list to loop through 
    	Movie movie_list[10] = {
        	Movie("The Matrix", "2h", "Sci-Fi", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"}),
        	Movie("Kung Fu Panda", "2hr 30min", "Comedy", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"}),
        	Movie("Deadpool 3", "2hr 40min", "Action", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"}),
        	Movie("The Matrix", "2h", "Sci-Fi", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"}),
        	Movie("Kung Fu Panda", "2hr 30min", "Comedy", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"}),
        	Movie("Deadpool 3", "2hr 40min", "Action", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"}),
        	Movie("The Matrix", "2h", "Sci-Fi", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"}),
        	Movie("Kung Fu Panda", "2hr 30min", "Comedy", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"}),
        	Movie("Deadpool 3", "2hr 40min", "Action", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"}),
        	Movie("The Matrix", "2h", "Sci-Fi", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"})
    	};
	

	while (isspace(choice) || retry == 1) 
	{
		cout << "\nPlease select your role:" << endl;
		cout << "1. Administrator" << endl;
		cout << "2. Customer" << endl;
		cout << "0. Exit Program" << endl;
		cout << "Enter your choice: ";
		cin.get(choice);
		cin.ignore(100,'\n');

		//Validate user input
		if (isalpha(choice) || isspace(choice))
		{
			retry = 1;
			cout << "Invalid choice. Please try again." << endl;
		}
		else if (isdigit(choice))
		{
			retry = 0;
			switch (choice)
			{
				case '1':
					admin_login(admin);

					checkpoint1:
					admin_menu(admin);

					if (admin.ad_choice != 0)
					{
						switch(admin.ad_choice) {
								case 1:
									 ad_mvlist(movie);
									 break;
								case 2:
									 ad_salesreport(movie);
									 break;
								case 3:
									 ad_mfymovie(movie);
									 break;
							
						}
						goto checkpoint1;
					}
					else 
					{
						retry = 1;
						admin.username = "";
						admin.userpass = "";
						break;
					}

				case '2':
					ticket_store = CompleteTicketBuyingProcess ();
					booking_store = booking_main(movie_list, ticket_store.total_ticket_amount);
    				vector<pair<string, string>> seat_store = booking_store.seat_store;

    				cout << "\nBooking Summary:\nMovie: " << booking_store.movie_name << "\nDate: " << booking_store.date << "\nTime: " << booking_store.time << "\nNumber of Tickets: " << booking_store.ticket_amount << "\nSeat(s): ";
    				for (const auto seat : seat_store) {
        				cout << seat.first << seat.second << " ";
    				}
    				cout << endl;

    				cout << "\nTicket Summary:\nMember: " << ticket_store.is_member << "\nNumber of Tickets: " << ticket_store.total_ticket_amount << "\nGrand Total: " << ticket_store.grandTotal << endl;
    				
					for (int i = 0; i < 3; ++i) {
        				cout << "(" << get<0>(ticket_store.TicketCategoryNums[i]) << ", " << get<1>(ticket_store.TicketCategoryNums[i]) << ", " << get<2>(ticket_store.TicketCategoryNums[i]) << ")" << endl;
    				}
					break;

				case '0':
					return 0;

				default:
					cout << "Invalid choice. Please try again." << endl;
					retry = 1;
			}
		}
	}
}


    

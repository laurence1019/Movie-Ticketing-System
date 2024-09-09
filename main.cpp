/*Library*/
#include "header.h"

/*File Include*/
#include "admin_main.h"
#include "admin_function.h"
#include "customer_main.h"

int main()
{
	//Class Variable
	admin_class admin;
	movie_class movie;
	hall_class hall;
	cust_class cust;

	//Local Variable
	char choice = ' ';
	bool retry = 1;

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
									 ad_hallstatus(hall);
									 break;
								case 3:
									 ad_salesreport(movie);
									 break;
								case 4:
									 ad_addmovie(movie,hall);
									 break;
								case 5:
									 ad_dltmovie(movie,hall);
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
					cust_member(cust);
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

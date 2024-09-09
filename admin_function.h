
/*Library*/
#include "header.h"
#include "class.h"

/*Function*/
//Movie List
void ad_mvlist(movie_class movie)
{
	cout << "\n\nMovie List" << endl;
	cout << setfill('*') << setw(50) << "\n";
	cout << "\n";

	cout << left << setfill(' ') << setw(10) << "No." << setw(15) << "Movie Code" << setw(25) << "Movie Name" << endl; 
	
	for (int i = 0; i < 10; i++)
	{
		cout << left << setfill(' ') << setw(10) << (i+1) << setw(15) << movie.mv_list[i][0] << setw(25) << movie.mv_list[i][1] << endl; 
	}

	cout << "\n-- End Of List --\n";
}

//Hall Status
void ad_hallstatus(hall_class hall) 
{
	//Local Variables
	int hall_seat = 0;
	bool repeat = 1;
	char hall_num = ' ';

	cout << "\n\nHall Status" << endl;
	cout << setfill('*') << setw(50) << "\n";
	cout << "\n";

	while (isspace(hall_num) || repeat == 1)
	{
		cout << "Enter Hall Number: ";
		cin.get(hall_num);
		cin.ignore(100,'\n');

		if (isspace(hall_num) || isspace(hall_num) || isalpha(hall_num))
		{
			repeat = 1;
			cout << "Invalid Hall Number. Please re-enter." << endl; 
		}
		else
		{
			int num = stoi(string(1, hall_num));

			if (num >= 1 && num <= 10)
			{
				repeat = 0;

				cout << "Hall Number: " << num << endl;
				cout << "Movie Playing: \"" << hall.hall_playing[num] << "\"\n\n";
				cout << left;

				for (int i = 0; i < 10; i++)
        		{
          			for (int j = 0; j < 10; j++)
          			{
            			if (hall.hall_seat[num][i][j].empty())
            			{
             				cout << setfill(' ') << setw(5) << "O";
              				hall_seat++;
            			}
            			else
            			{
              				cout << setfill(' ') << setw(5) << "X";
            			}
          			}
          			cout << endl;
          		}

          		cout << "\n\nRemark: Seat Not Available (X) / Seat Available (O)\n\n";
          		cout << "Seat Available: " << hall_seat << " seat left" << endl;
			}
			else
			{
				repeat = 1;
				cout << "Invalid Hall Number. Please re-enter." << endl; 
			}
		}
	}
}

//Sales Report
void ad_salesreport(movie_class& movie)
{
	cout << "\n\nSales Status" << endl;
	cout << setfill('*') << setw(60) << "\n";
	cout << "\n";

	cout << left << setfill(' ') << setw(15) << "Movie Code";
	cout << setw(30) << "Movie Title";
	cout << setw(10) << "Revenue";
	cout << setfill('-') << setw(60) << "\n";
	cout << "\n";

	for (int i = 0; i < 10; i++)
	{
		cout << left << setfill(' ') << setw(15) << movie.mv_list[i][0];
		cout << setw(30) << movie.mv_list[i][1];
		cout << setw(10) << setprecision(3) << showpoint << movie.revenue[i] << endl;
	}

	cout << setfill('-') << setw(50) << "\n";
	cout << "\n\n";
}

//Add Movie
void ad_addmovie(movie_class& movie, hall_class& hall)
{
	//Local Variables
	string mv_name = "";
	string mv_code = "";
	char confirm = ' ';
	bool flag = 1;
	int count = 0;

	cout << "\n\nAdd Movie" << endl;
	cout << setfill('*') << setw(50) << "\n";
	cout << "\n";

	for(int i = 0; i < 10; i++)
	{
		if (movie.mv_list[i][0].empty())
		{
			continue;
		}
		count++;
	}

	if (count == 10)
	{
		cout << "Movie List is Full. Cannot add more movie." << endl;
	}
	else
	{
	while (mv_name.empty() || flag == 1)
	{
		
		cout << "Enter Movie Name: ";
		getline(cin, mv_name);

		if (mv_name.empty()) 
		{
			cout << "Invalid Movie Name. Please re-enter." << endl;
		}	
		else
		{
			flag = 0;
		}
	}

	while ((tolower(confirm) != 'y' && tolower(confirm) != 'n') || flag == 0)
	{
		cout << "Are you sure to add \"" << mv_name << "\"? (Y/N): ";
		cin.get(confirm);
		cin.ignore(100,'\n');

		if (isdigit(confirm) || isspace(confirm))
		{
			cout << "Invalid Input. Please re-enter." << endl;
			flag = 0;
		}
		else
		{
			if(tolower(confirm) == 'y')
			{
				flag = 1;
				mv_code = autoCode(movie);
				
				for (int i = 0; i < 10; i++)
				{
					if (movie.mv_list[i][0].empty())
					{
						movie.mv_list[i][0] = mv_code;
						movie.mv_list[i][1] = mv_name;
						break;
					}
				}
				cout << "\n\nMovie Code: " << mv_code;
				cout << "\nMovie Name: " << mv_name;
				cout << "\nMovie is successfully inserted!\n\n" << endl;
			}
			else if (tolower(confirm) == 'n')
			{
				mv_name = "";
				cout << "Operation Cancelled." << endl;
				break;
			}
			else
			{
				cout << "Invald Input. Please re-enter." << endl;
			}
		}
	}
	}
}

string autoCode(movie_class movie)
{
	srand(time(0));

	char chr[4];
	char num[5];

	for (int i = 0; i < 3; i++)
	{
		chr[i] = (rand() % 26 + 65);
	}
	chr[3] = '\0';

	for (int j = 0; j < 4; j++)
	{
		num[j] = static_cast<char>(rand() % 10 + 48);
	}
	num[4] = '\0';

	string chr_txt(chr);
	string num_txt(num);
	string code = chr_txt + num_txt;

	for (int k = 0; k < 10; k++)
	{
		if (code == movie.mv_list[k][0])
		{
			return autoCode(movie);
		}
	}

	return code;
}

//Delete Movie
void ad_dltmovie(movie_class& movie, hall_class& hall)
{
	//Local Variables
	string mv_code = "";
	char confirm = ' ';
	bool flag = 1;
	int count = 0;

	cout << "\n\nDelete Movie" << endl;
	cout << setfill('*') << setw(50) << "\n";
	cout << "\n";

	for(int i = 0; i < 10; i++)
	{
		if (movie.mv_list[i][0].empty())
		{
			count++;
		}
	}

	if (count == 10)
	{
		cout << "Movie List is Empty. Cannot delete more movie." << endl;
	}
	else
	{
	
	while (mv_code.empty() || flag == 1)
	{
		checkpoint3:
		cout << "Enter Movie Code: ";
		getline(cin, mv_code);

		if (mv_code.empty()) 
		{
			cout << "Invalid Movie Code. Please re-enter." << endl;
		}	
		else
		{
			flag = 0;
		}
	}

	while ((tolower(confirm) != 'y' && tolower(confirm) != 'n') || flag == 0)
	{
		cout << "Are you sure to delete \"" << mv_code << "\"? (Y/N): ";
		cin.get(confirm);
		cin.ignore(100,'\n');

		if (isdigit(confirm) || isspace(confirm))
		{
			cout << "Invalid Input. Please re-enter." << endl;
			flag = 0;
		}
		else
		{
			if(tolower(confirm) == 'y')
			{
				flag = 1;

				for (int i = 0; i < 10; i++)
				{
					if (movie.mv_list[i][0] == mv_code)
					{
						movie.mv_list[i][0] = "";
						movie.mv_list[i][1] = "";
						flag = 1;
						break;
					}
					flag = 0;
				}
				if (flag == 1)
				{
					cout << "\nMovie is successfully deleted!\n\n" << endl;
				}
				else
				{
					cout << "\nMovie is not found!\n\n" << endl;
					goto checkpoint3;
				}
			}
			else if (tolower(confirm) == 'n')
			{
				mv_code = "";
				cout << "Operation Cancelled." << endl;
				break;
			}
			else
			{
				cout << "Invald Input. Please re-enter." << endl;
			}
		}
	}
	}
}

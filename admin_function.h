
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

	cout << left << setfill(' ') << setw(10) << "No.";
	cout << setw(15) << "Movie Code";
	cout << setw(30) << "Movie Name";
	cout << setw(15) << "Duration";
	cout << setw(15) << "Category" << endl; 
	
	for (int i = 0; i < 10; i++)
	{
		cout << left << setfill(' ') << setw(10) << (i+1);
		cout << setw(15) << movie.mv_list[i][0];
		cout << setw(30) << movie.mv_list[i][1];
		cout << setw(15) << movie.mv_list[i][2];
		cout << setw(15) << movie.mv_list[i][3] << endl; 
	}

	cout << "\n-- End Of List --\n";
}

//Sales Report
void ad_salesreport(movie_class& movie)
{
	double totalrevenue = 0.0;
	
	cout << "\n\nSales Status" << endl;
	cout << setfill('*') << setw(60) << "\n";
	cout << "\n";

	cout << left << setfill(' ') << setw(15) << "Movie Code";
	cout << setw(30) << "Movie Title";
	cout << right << setw(10) << "Revenue (RM)\n";
	cout << setfill('-') << setw(60) << "\n";
	cout << "\n";

	for(int i = 0; i < 10; i++)
		{
			movie.revenue[i] = (movie.adult_tksold[i] * movie.cost_adult) + (movie.kid_tksold[i] * movie.cost_kid);	
		}

	for (int i = 0; i < 10; i++)
	{
		cout << left << setfill(' ') << setw(15) << movie.mv_list[i][0];
		cout << setw(30) << movie.mv_list[i][1];
		cout << right << setw(10) << fixed << setprecision(2) << showpoint << movie.revenue[i] << endl;
	}

	cout << setfill('-') << setw(60) << "\n";
	cout << "\nTotal Sales:";

	for(int i = 0 ;i < 10; i++)
	{
		totalrevenue = totalrevenue + movie.revenue[i];
	}
	
	cout << right << setfill(' ') << setw(33) << "RM " << fixed << setprecision(2) << showpoint << revenue << endl;
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
void ad_mfymovie(movie_class& movie)
{
	//Local Variables
	string mv_old = "";
	string mv_new = "";
	int mv_dur = 0;
	string mv_cate = "";
	int i;
	bool flag = 1;

	cout << "\n\nModify Movie" << endl;
	cout << setfill('*') << setw(50) << "\n";
	cout << "\n";

	
	while (flag)
	{
		cout << "Enter Movie (Code / Name) to Modify: ";
		getline(cin, mv_old);

		if (mv_old.empty()) 
		{
			cout << "Invalid Movie Name or Code. Please re-enter." << endl;
			flag = 1;
		}	
		else
		{
			for (i = 0; i < 10; i++)
			{
				if (mv_old == movie.mv_list[i][0] || mv_old == movie.mv_list[i][1])	
				{
					flag = 0;
					break;
				}
			}
			if (i == 10)
			{
					cout << "Movie not found. Please re-enter." << endl;
					flag = 1;
			}
		}
	}

	flag = 1;
	while (flag)
	{
		cout << "Enter New Movie Name: ";
		getline(cin, mv_new);

		if (mv_new.empty())
		{
			cout << "Invalid Movie Name. Please re-enter." << endl;
			flag = 1;
		}
		else
		{
			movie.mv_list[i][0] = autoCode(movie);
			movie.mv_list[i][1] = mv_new;
			flag = 0;
		}
	}

	flag = 1;
	while (flag)
		{
			cout << "Enter Movie Duration (Hours): ";
			cin >> mv_dur;
			cin.ignore(100,'\n');

			if (mv_dur < 1 || mv_dur > 4)
			{
				cout << "Invalid Movie Duration. Please re-enter." << endl;
				flag = 1;
			}
			else
			{
				movie.mv_list[i][2] =	to_string(mv_dur) + " Hours";
				flag = 0;
			}
		}

		flag = 1;
		while (flag)
			{
				cout << "Enter Movie Category: ";
				getline(cin, mv_cate);

				if (mv_cate.empty())
					{
						cout << "Invalid Movie Category. Please re-enter." << endl;
						flag = 1;
					}
					else
				{
						movie.mv_list[i][3] = mv_cate;
						cout << "Movie Successfully Modified!" << endl;
						flag = 0;
					}
			}

}

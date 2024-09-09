/*Library*/
#include "header.h"
#include "class.h"

/*Admin Login*/
void admin_login(admin_class& admin)
{
   //Local Variables
   string inputname = "";
   string inputpass = "";
   bool success = 0;
   int log_count = 0;

   while (inputname.empty() || inputpass.empty() || success == 0)
   {

      cout << "\nEnter Your Username: ";
      getline(cin, inputname);
      cout << "Enter Your PIN number: ";
      getline(cin, inputpass);

      if (inputname.empty() || inputpass.empty())
      {
         cout << "Please enter your username and password." << endl;
         log_count++;
      }
      else 
      {
         if (inputname == admin.realname && inputpass == admin.realpass)
         {
            success = 1;
            admin.username = inputname;
            admin.userpass = inputpass;
         }
         else 
         {
            cout << "Incorrect username or password. Please try again." << endl;
            log_count++;
         }
      }

      if (log_count == 3)
      {
         cout << "You have exceeded the maximum number of login attempts. Please try again after 20 seconds." << endl;

         for (int timer = 20; timer > 0; timer--)
         {
            this_thread::sleep_for(chrono::seconds(1));
            if (timer % 5 == 0)
            {
               cout << "Remaining time: " << timer << "seconds" << endl;
            }
         }
         log_count = 0;
      }
   }
}


/*Admin Menu*/
void admin_menu(admin_class& admin)
{
   //local Variables
   char choice = ' ';
   bool skip = 0;

   cout << "\nAdministrator Menu" << endl;
   cout << setfill('*') << setw(50) << "\n";
   cout << "\n";
   cout << "1. Movie List" << endl;
   cout << "2. Hall Status" << endl;
   cout << "3. Sales Status" << endl;
   cout << "4. Add Movie" << endl;
   cout << "5. Delete Movie" << endl;
   cout << "0. Exit" << endl;

   while (skip == 0)
   {
      cout << "\nEnter Your Choice: ";
      cin.get(choice);
      cin.ignore(100, '\n');

      if (isspace(choice) || isalpha(choice))
      {
         cout << "Invalid choice. Please try again." << endl;
      }
      else if (isdigit(choice))
      {
         switch(choice) {
            case '1':
               admin.ad_choice = 1;
               skip = 1;
               break;
            case '2':
               admin.ad_choice = 2;
               skip = 1;
               break;
            case '3':
               admin.ad_choice = 3;
               skip = 1;
               break;
            case '4':
               admin.ad_choice = 4;
               skip = 1;
               break;
            case '5':
               admin.ad_choice = 5;
               skip = 1;
               break;
            case '0':
               admin.ad_choice = 0;
               skip = 1;
               break;
            default:
               cout << "Invalid choice. Please try again." << endl;
               break;
         }
      }
   }
}

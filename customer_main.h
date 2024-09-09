/*Library*/
#include "header.h"
#include "class.h"

/*Admin Login*/
void cust_member(cust_class& cust)
{
   //Local Variables
   char owned = ' ';
   string memID = "";
   bool flag = 0;

   while (isspace(owned) || isdigit(owned))
   {
      cout << "\nDo you have a membership ID? (Y/N): ";
      cin.get(owned);
      cin.ignore(100, '\n');
   }

   while(flag == 0)
   {
      if(tolower(owned) == 'y')
      {
        cout << "Enter your membership ID: ";
        getline(cin, memID);

        if (memID.empty()) 
        {
          cout << "Invalid Input. Please re-enter again." << endl;
        }
        else
        {
          flag = 1;
        }
      } 
      else if(tolower(owned) == 'n')
      {
        cout << "Alright! Proceed to Customer Menu." << endl;
        break;
      }
      else
      {
        cout << "Invalid Input. Please re-enter again." << endl;
      }
   }

   if (flag == 1)
   {
      for (int i = 0; i < 3; i++)
      {
         if (memID == cust.cust_memID[i][0])
         {
            cust.cust_mem_log = 1;
            cout << "\nWelcome, " << cust.cust_memID[i][1] << "!" << endl;
            break;
         }  
      }
   }
   
}

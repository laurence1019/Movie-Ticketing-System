#include "header.h"
#include "class.h"

string autoID()
{
    srand(time(0));

    char num[9];

    for (int i = 0; i < 8; i++)
    {
        num[i] = (rand() % 10 + 48);
    }
    num[8] = '\0';

    return num;
}

int pay_decision() 
{ 
   //DISPLAYS CHOICES FOR SELECTION
    cout << "\n\n-----[Please Select Payment method]-----" << endl;
    cout << setfill('.');
    cout << "|" << "1." << setw(36) << right << "Credit Card" << "|" << endl;
    cout << setfill('.');
    cout << "|" << "2." << setw(36) << right << "Debit Card" << "|" << endl;
    cout << setfill('.');
    cout << "|" << "3." << setw(36) << right << "Cash" << "|" << endl;
    cout << setfill('.');
    cout << "|" << "4." << setw(36) << right << "E-Wallet" << "|" << endl;
    cout << "----------------------------------------" << endl;

    //PROMPTS USER TO CHOOSE PAYMENT METHOD

    char choice = ' ';
    bool flag = 0;

    while(flag == 0)
    {
        cout << "Enter Your Payment Method: ";
        cin.get(choice);
        cin.ignore(100,'\n');

        if(isspace(choice) || isalpha(choice))
        {
            cout << "Invalid Input. Please re-enter." << endl;
            flag = 0;
        }
        else
        {
            if(choice == '1' || choice == '2' || choice == '3' || choice == '4')
            {
                flag = 1;
                break;
            }
            else
            {
                cout << "Invalid Input. Please re-enter." << endl;
                flag = 0;
            }
        }
        
    }
    return choice - '0';
}

//PAYMENT METHOD
string payMethDec()
{
    int pay_type = 0;           //VARIABLE pay_type WILL RECEIVE RETURN VALUE FROM FUNCTION pay_decision()
    string pay_dis = " ";       //pay_dis IS USED TO DISPLAY IN THE TICKET
    pay_type = pay_decision();
    switch(pay_type) {
    case 1:
        pay_dis = "Credit Card";
        break;
    case 2:
        pay_dis = "Debit Card";
        break;
    case 3:
        pay_dis = "Cash";
        break;
    default:
        pay_dis = "E-wallet";
    }
    return pay_dis;
}


string rtc()
{
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);

    char output[50];

    strftime(output, 50, "%d/%m/%Y", &datetime);

    return output;
}


void invoice()
{
    string date = rtc();

    cout << "\n\n-----------------------------------------" << endl;
    cout << "                 INVOICE                 " << endl;
    cout << "-----------------------------------------" << endl;
    cout << setw(13) << left << "Invoice ID: " << setw(10) << left << autoID() << setw(18) << right << date << endl;
    cout << setw(23) << left << "Items" << setw(18) << right << "Price (RM)" << endl;
    cout << setw(15) << left << "1. Adult Ticket " << setw(1) << "(" << setw(2) << "1"  << setw(5) << " x 25" << setw(1) << ")" << setw(16) << right << "99.90" << endl;
    cout << setw(15) << left << "2. Child Ticket " << setw(1) << "(" << setw(2) << "1"  << setw(5) << " x 15" << setw(1) << ")" << setw(16) << right << "99.90" << endl;
    cout << setw(41) << right << "--------" << endl;
    cout << setw(23) << left << "Subtotal" << setw(18) << right << "99.90" << endl;
    cout << setw(23) << left << "Discount" << setw(11) << right << "-" << setw(7) << right << "99.90" << endl;
    cout << setw(23) << left << "Service Charge (5%)" << setw(11) << right << "-" << setw(7) << right << "99.90" << endl;
    cout << setw(23) << left << "Tax" << setw(11) << right << "-"<< setw(7) << right << "99.90" << endl;
    cout << setw(41) << right << "--------" << endl;
    cout << setw(13) << left << "Total Items: " << setw(7) << left << "4" << endl;
    cout << setw(23) << left << "Total Payable: " << setw(18) << right << "99.90" << endl;
    cout << "-----------------------------------------" << endl;
}


void receipt() 
{
    string pay_dis = payMethDec();

    //RELEVANT INFORMATION DISPLAYED INTO A TICKET FORMAT
        cout << "\n\n--------------------------------------" << endl;
        cout << "                RECEIPT               " << endl;
        cout << "--------------------------------------" << endl;
        cout << setw(20) << left << "Movie Title: " << setw(18) << right << " " << endl;
        cout << setw(20) << left << "Time: " << setw(18) << right << " " << endl;
        cout << setw(20) << left << "Hall: " << setw(18) << right << " " << endl;
        cout << setw(20) << left << "Seat ID: " << setw(18) << right << " " << endl;
        cout << setw(20) << left << "Price(RM): " << setw(18) << right << " " << endl;
        cout << setw(20) << left << "Payment Method: " << setw(18) << right << pay_dis << endl;
        cout << "--------------------------------------" << endl;

}


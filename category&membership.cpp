#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

void ticketCategoryMenu() {
	//menu for ticket category
	cout << " " << "Choose your ticket category:\n";
	cout << " " << setw(54) << setfill('_') << "\n" << setfill(' ');
	cout << " " << "|" << setw(23) << "CATEGORY" << right << setw(17) << "|" << setw(10) << "PRICE(RM)" << setw(2) << "|" << endl;
	cout << " " << "|" << setw(40) << setfill('_') << "|" << setw(12) << setfill('_') << "|" << setfill(' ') << endl;
	cout << " " << setw(40) << left << "| 1 | Adult" << right << "|" << setw(8) << right << "22.50" << setw(4) << "|" << endl;
	cout << " " << setw(40) << left << "| 2 | Children (< 18 years old)" << right << "|" << setw(8) << right << "13.50" << setw(4) << "|" << endl;
	cout << " " << setw(40) << left << "| 3 | Senior (>= 60 years old)" << right << "|" << setw(8) << right << "10.50" << setw(4) << "|" << endl;
	cout << " " << "|___|" << setw(36) << setfill('_') << "|" << setw(12) << setfill('_') << "|" << setfill(' ') << endl;
	cout << " " << setw(52) << left << "| 4 | Quit this menu" << right << "|" << endl;
	cout << " " << "|___|" << setw(48) << setfill('_') << "|" << setfill(' ') << endl;
	cout << setw(56) << setfill('=') << " " << setfill(' ') << endl;
	cout << " " << "Your choice (Enter 1/2/3/4): ";
}

int ticketChoice() {
	string cateNum = " ", cateErrMsg = " Your choice is invalid. Pls try again (1/2/3/4): ";
	int cateNum_int = 0;

	while (cateNum_int < 1 || cateNum_int > 4){
		cateNum_int = int_err_input(cateNum, cateErrMsg);
		if (cateNum_int < 1 || cateNum_int > 4){		//if user input is not 1,2,3 but other integer 
			cout << cateErrMsg;						
		}
	}
	return cateNum_int;
}

bool quitMenuf(int cateNum) {
	bool quitMenu = false;
	if (cateNum == 4) {
		quitMenu = true;
		cout << "\n ===== You have quit the menu =====\n";
	}
	return quitMenu;
}

string ticketCategory(int cateNum) {		
	//assign category according to user choice
	string category = " ";
	switch (cateNum) {
	case 1:
		category = "adult";
		break;
	case 2:
		category = "children";
		break;
	case 3:
		category = "senior";
		break;
	default:
		break;
	}
	return category;
}

bool wantOtherCategory() {
	bool otherCate = false, cdt = false;
	string input = " ";
	cout << " Would you like to purchase other category?\n" << " 'y' for yes OR 'n' for no: ";
	//ask user whether want to buy other category or not

	while (!cdt){
		cin >> input;
		if (input == "y" || input == "Y") {		
			cdt = true;
			otherCate = true;				//set true if want to buy other category
		}
		else if (input == "n" || input == "N") {
			cdt = true;
			otherCate = false;				//set false if dont want to buy other category
		}
		else {
			cout << " Please enter 'y' or 'n' only: ";		//ask user enter again if not y or n
		}
	}
	return otherCate;
}

int ticketNumf(string category, int remainTicketNum) {
	string ticketNum = " ", ticketErrMsg = " Please enter a positive integer for the ticket number you would like to purchase: ";
	int ticketNum_int = 0;
	bool ticketCond = false;

	cout << "\n How many " << category << " tickets would you like to purchase?" << "\n Enter a number: ";
	//ask user how many tickets to buy

	while (!ticketCond) {
		ticketNum_int = int_err_input(ticketNum, ticketErrMsg);
		if (ticketNum_int > remainTicketNum) {				
			//if ticket number to buy exceed the remain ticket to choose from
			cout << " You have exceeded the maximum of 12 allowed tickets per purchase. ";
			if (remainTicketNum < 12){
				//to tell user how many ticket left they can purchase when they select for other category
				if (remainTicketNum == 1){
					cout << "\n You only have a remaning of " << remainTicketNum << " ticket left to purchase. Please try again: ";
				}
				else {
					cout << "\n You only have a remaning of " << remainTicketNum << " tickets left to purchase. Please try again: ";
				}
			}
		}
		else if (ticketNum_int == 0) {
			//tell user they cannot purchase 0 ticket
			cout << " You cannot choose 0 ticket. Please enter again: ";
		}
		else {
			//user succesfully purchase their ticket
			ticketCond = true;
			cout << "\n ========== You have successfully selected " << ticketNum_int << " tickets for the " << category << " category ==========\n\n";
		}
	}
	return ticketNum_int;
}

//this function is to use for how many seat a user can choose based on the number of tickets they had purchase
int totalTicketNumf(int remainTicketNum) {
	int totalTicketNum = 12 - remainTicketNum;		//12 is the maximum number of ticket that can be bought per purchase
	return totalTicketNum;							//For zi kenn, this totalTicketNum you may need to use as an argument for choosing the seat
}

double unitPricef(int cateNum) {
	//assign unitPrice according to the category chosen 
	double unitPrice = 0.0;
	switch (cateNum) {
	case 1:
		unitPrice = 22.50;		//adult price
		break;
	case 2:
		unitPrice = 13.50;		//children price
		break;
	case 3:
		unitPrice = 10.50;		//seniot price
		break;
	}
	return unitPrice;
}

double catePricef(double unitPrice, int ticketNum) {
	double catePrice = 0.0;
	catePrice = unitPrice * ticketNum;		//calculate the total price for one category chosen by user
	return catePrice;
}

double membership(){
	double discount = 0.0;		// discount = percentage off / 100
	string input = " ";
	bool cdt = false;
	cout << "\n Are you a member of TGV cinema?\n";		//ask user if they have a membership or no
	cout << " 'y' for yes OR 'n' for no: ";
	while (!cdt){
		cin >> input;
		if (input == "y" || input == "Y") {
			cdt = true;
			cout << " \n===== You are eligible for a 10% membership discount =====\n\n";		//assign 10% discount if user is a member
			discount = 0.1;
		}
		else if (input == "n" || input == "N") {
			cdt = true;
			cout << " \n===== You are not eligible for the 10% membership discount =====\n\n";	//no discount for non-member
		}
		else {
			cout << " Please enter 'y' or 'n' only: ";		//ask user enter again if not y or n
		}
	}
	return discount;
}

//for this membership i dont know how to verify them, so if they say yes they would just instanly get the discount

int int_err_input(string int_str, string err_msg) {
	bool cdt = false;						//condition set to false
	int real_int = 0;						//the variable to stored the integer converted from string
	while (!cdt) {							//continue if condition is false
		getline(cin >> ws, int_str);		//accept user input and stored it as a string

		//assume the input is valid
		cdt = true;

		//check if every character is a digit
		for (char c : int_str) {
			if (!isdigit(c)) {
								//note that negative integer is consider as not an integer in this case as '-' sign is not a digit, same goes to decimal number
								//this only works for positive integer only (pure digit)
				cdt = false;	// If any character is not a digit, set condition to false
				break;			// Break out of the loop immediately
			}
		}
		if (!cdt) {
			cout << err_msg;
		}
		else {
			return real_int = stoi(int_str);		//retrun the input if it was truly a positive integer
		}
	}
}

double wholeTicketBuyingProcess() {
	int cateNum = 0, ticketNum = 0;
	int remainTicketNum = 12;		// initialize remain ticket number to 12 (maximum number of tickets per purchase)
	double unitPrice = 0.0, catePrice = 0.0, discount = 0.0, totalPrice = 0.0, grandTotal = 0.0;
	string category = " ";
	bool quitMenu = false, wantOtherCate = true;

	//loop only if user want to choose other category
	while (wantOtherCate) {
		ticketCategoryMenu();									//display menu 
		cateNum = ticketChoice();								//category choice
		quitMenu = quitMenuf(cateNum);
		if (quitMenu){
			break;												//immediately exit the loop if want to quit menu
		}
		category = ticketCategory(cateNum);						//assign category (adult, children, senior)
		unitPrice = unitPricef(cateNum);						//assign unitPrice according to category
		ticketNum = ticketNumf(category, remainTicketNum);		//ticket number of the category chosen
		remainTicketNum -= ticketNum;							//update the remaining number of ticket that can be purchased for every iteration
		catePrice = catePricef(unitPrice, ticketNum);			//calculate total price for one category
		totalPrice += catePrice;								//calculate total price for every category chosen

		//user only allowed to choose other category again if remainTicketNum != 0
		if (remainTicketNum > 0) {
			wantOtherCate = wantOtherCategory();				
		}
		else {
			wantOtherCate = false;								
		}
	}

	//only calculate discount and grand total if number of ticket choosen is not 0
	//in other words if user quit the menu at the very first time it does not execute the following
	if (remainTicketNum != 12){			

		//if dont want to choose other category or already reached maximum number of tickets that can be purchased
	    //ask membership and give discount
		discount = membership();

		//finally calculate grand total cost after discount 
		grandTotal = totalPrice - (totalPrice * discount);
	}
	return grandTotal;			//grand total need to be used in receipt 
}

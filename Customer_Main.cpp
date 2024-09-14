#include <iostream>
#include <iomanip>
#include <string>
#include <thread> 
#include <chrono>
#include <cctype>
#include <regex>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <array>
#include <map>
#include <tuple>
#include <vector>  
#include <algorithm>

using namespace std;

// DECLARE STRUCTS AND CONSTANTS START --
struct BookingInfo {
    // struct for storing current booking info
    // lasts only for current session

    string movie_name;
    string date;
    string time;
    int ticket_amount;
    vector<pair<string, string>> seat_store;  // Store seat information as a list
};

struct TicketInfo {
    // struct for storing ticket info
    // lasts only for current session

    tuple<int, string, double> TicketCategoryNums[3]; // [(3, adult, 18.90), (2, child, 12.60)]
    bool is_member; // true false
    int total_ticket_amount;
    double grandTotal;
};

array<string, 10> alphabs = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
array<string, 10> list_nums = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
// -- DECLARE STRUCTS AND CONSTANTS END

// CATEGORY AND MEMBERSHIP TICKET START --
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
        return 0;
}

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

int ticketNumf(string category) {
    string ticketNum = " ", ticketErrMsg = " Please enter a positive integer for the ticket number you would like to purchase: ";
    int ticketNum_int = 0;
    bool ticketCond = false;

    cout << "\n How many " << category << " tickets would you like to purchase?" << "\n Enter a number: ";
    //ask user how many tickets to buy

    while (!ticketCond) {
        ticketNum_int = int_err_input(ticketNum, ticketErrMsg);
        
        if (ticketNum_int == 0) {
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

bool membership(){
    double membership = false;		// discount = percentage off / 100
    string input = " ";
    bool cdt = false;
    cout << "\n Are you a member of TGV cinema?\n";		//ask user if they have a membership or no
    cout << " 'y' for yes OR 'n' for no: ";
    while (!cdt){
        cin >> input;
        if (input == "y" || input == "Y") {
            cdt = true;
            cout << " \n===== You are eligible for a 10% membership discount =====\n\n";		//assign 10% discount if user is a member
            membership = true;
        }
        else if (input == "n" || input == "N") {
            cdt = true;
            cout << " \n===== You are not eligible for the 10% membership discount =====\n\n";	//no discount for non-member
            break;
        }
        else {
            cout << " Please enter 'y' or 'n' only: ";		//ask user enter again if not y or n
        }
    }
    return membership;
}

TicketInfo CompleteTicketBuyingProcess () {

    TicketInfo main_store; 

    tuple<int, string, double> LocalTicketCategoryNums[3];
    int cateNum = 0, ticketNum = 0, totalticketnumber = 0, indexing= 0;
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
        ticketNum = ticketNumf(category);		                //ticket number of the category chosen

        totalticketnumber += ticketNum;

        catePrice = catePricef(unitPrice, ticketNum);			//calculate total price for one category
        totalPrice += catePrice;								//calculate total price for every category chosen

        LocalTicketCategoryNums[indexing] = make_tuple(ticketNum, category, catePrice);

        //user allowed to choose other category 
        wantOtherCate = wantOtherCategory();
        indexing += 1;			

    }

    main_store.total_ticket_amount = totalticketnumber;
    for (int i = 0; i < 3; ++i) {
        main_store.TicketCategoryNums[i] = LocalTicketCategoryNums[i];
    }

    bool is_member = membership();                              //true false
    main_store.is_member = is_member;

    if (is_member = true) {
        discount = 0.9;
    }

    grandTotal = totalPrice * discount;
    main_store.grandTotal = grandTotal;

    return main_store;
}
// -- CATEGORY AND MEMBERSHIP TICKET END


// MOVIE CLASS DEFINITION START --
class Movie {
public:
    // declare variables 
    string name;
    string length;
    string genre;
    string language;
    vector<string> dates;
    vector<string> time;
    map<string, map<string, vector<pair<string, string>>>> booking_data;

    // Constructor to initialize the movie with details, def  __init__. 
    Movie(string name, string length, string genre, string language, vector<string> dates, vector<string> times)
        : name(name), length(length), genre(genre), language(language), dates(dates), time(times) {
        booking_data = initialize_booking(dates, times);
    }

    // Initialize booking data with available dates and times
    // Nested Map, Ex.
    // main_dict = { 
    //     date = {
    //         time = {
    //             []
    //         }
    //     }
    // }
    map<string, map<string, vector<pair<string, string>>>> initialize_booking(vector<string> dates, vector<string> times) {
        map<string, map<string, vector<pair<string, string>>>> main_dict;
        for ( string date : dates) {
            map<string, vector<pair<string, string>>> plc_dict;
            for ( string time : times) {
                plc_dict[time] = vector<pair<string, string>>();  // Initialize empty seat vector for each time
            }
            main_dict[date] = plc_dict;
        }
        return main_dict;
    }

    // Print movie information
    void print_info() {
        cout << "Movie name: " << name << endl;
        cout << "Movie length: " << length << endl;
        cout << "Movie genre: " << genre << endl;
        cout << "Movie language: " << language << endl;
    }

    // Input for date selection with validation
    string in_date() {
        cout << "This is the available dates: ";
        // for date in dates, looping throught one at a time. Think of indexing
        for ( string date : dates) {
            cout << date << ", ";
        }
        cout << endl;

        string chosen_date;
        while (true) {
            cout << "Enter a valid date: ";
            cin >> chosen_date;
            // find(start of range, end of range, variable to be found)
            // If found return variable, else return end of range
            if (find(dates.begin(), dates.end(), chosen_date) != dates.end()) {
                return chosen_date;
            }
            cout << "Invalid date, please try again." << endl;
        }
    }

    // Input for time selection with validation
    string in_time() {
        cout << "This is the available times: ";
        // for time in times, looping throught one at a time. Think of indexing
        for ( string t : time) {
            cout << t << ", ";
        }
        cout << endl;

        string chosen_time;
        while (true) {
            cout << "Enter a valid time: ";
            cin >> chosen_time;
            // find(start of range, end of range, variable to be found)
            // If found return variable, else return end of range
            if (find(time.begin(), time.end(), chosen_time) != time.end()) {
                return chosen_time;
            }
            cout << "Invalid time, please try again." << endl;
        }
    }

    // Return booked seats for a given date and time
    vector<pair<string, string>>& return_seats(string date, string time) {
        // dictionary is called with keys
        // Key : Value
        // Nested Dictionary is called with two or more keys
        return booking_data[date][time]; // returns seats vector 
    }

    // Show available and booked seats
    void show_seats(const vector<pair<string, string>>& booked_seats) {
        cout << "   1   2   3   4   5   6   7   8   9   10" << endl; // hard coded, can use setw

        for ( string letter : alphabs) {
            cout << letter << " ";
            for ( string col : list_nums) {
                // find(start of range, end of range, variable to be found)
                // If found return variable, else return end of range
                // make_pair(letter, col) makes a pair which is what our booked_seats var type is. It just combines it into a tuple / pair
                if (find(booked_seats.begin(), booked_seats.end(), make_pair(letter, col)) != booked_seats.end()) {
                    cout << "|XX|"; // occupied
                } else {
                    cout << "|  |"; // unoccupied
                }
            }
            cout << endl;
        }
    }

    // Input for seat selection with validation
    pair<string, string> in_seats(string date, string time) {
        string row_alpha, col_num;
        while (true) {
            cout << "Enter seat letter (A-J): ";
            cin >> row_alpha;
            transform(row_alpha.begin(), row_alpha.end(), row_alpha.begin(), ::toupper); // transform string to upper. Could use char, but I'm more comfortable with strings
            // find(start of range, end of range, variable to be found)
            // If found return variable, else return end of range
            // Our parameters are our gobals declared at the header
            if (find(alphabs.begin(), alphabs.end(), row_alpha) == alphabs.end()) {
                cout << "Invalid row. Please try again." << endl;
                continue;
            }

            // Defining a list of valid numbers as strings

            cout << "Enter seat number (1-10): ";
            cin >> col_num;

            // Check if input is not in list_nums
            // find(start of range, end of range, variable to be found)
            // If found return variable, else return end of range
            // Our parameters are our gobals declared at the header
            if (find(list_nums.begin(), list_nums.end(), col_num) == list_nums.end()) {
                cout << "Invalid seat number. Please try again." << endl;
                continue;
            }
                

            pair<string, string> seat_n = make_pair(row_alpha, col_num);
            // return_seats returns our seat vector
            if (find(return_seats(date, time).begin(), return_seats(date, time).end(), seat_n) != return_seats(date, time).end()) {
                // checks for booked seat using find function
                cout << "Seat already booked. Please choose another seat." << endl;
            } else {
                return_seats(date, time).push_back(seat_n); // append seat_n into seat vector
                cout << "\nSeat booked successfully!\n";
                show_seats(return_seats(date, time));
                return seat_n;
            }
        }
    }

    // Main booking function
    tuple<string, string, pair<string, string>, string> booking(string date, string time, int ticket_amt) {
        // we check if date and time are empty, this is for booking multiple tickets
        // if false we enter date and time, if true we skip 
        // So users don't have to enter date and time multiple times
        if (date.empty() && time.empty()) {
            date = in_date();
            time = in_time();
        }
        
        // check if the hall is full by checking len of seat vector, hard coded limit 100
        if ((return_seats(date, time).size() + ticket_amt ) >= 100) {
            cout << "Sorry, all seats are booked. Please try another date and time." << endl;
            return make_tuple("", "", make_pair("", ""), "");
        }

        vector<pair<string, string>>& seats = return_seats(date, time);
        show_seats(seats);
        pair<string, string> seat_n = in_seats(date, time);
        return make_tuple(date, time, seat_n, name);
    }
};
// -- MOVIE CLASS DEFINITION END

// BOOKING FUNCTION START --
BookingInfo booking_main(Movie movie_list[10], int ticket_amount) {

    BookingInfo main_store;
    string date, time;
    vector<pair<string, string>> seat_store;

    // Print list of movies
    cout << "\nAvailable Movies:" << endl;
    for (size_t i = 0; i < 10; ++i) {
        cout << i + 1 << ". " << movie_list[i].name << endl;
    }

    int selected_movie_idx = 0;
    while (true) {
        // while loop to check valid input for selected_movie_idx
        cout << "Enter a number to select a movie, 0 or letter to exit: ";
        cin >> selected_movie_idx;

        if (cin.fail()) {  // Check for invalid input (e.g., letters)
            cout << "Exiting booking menu." << endl;
            break;
        }

        if (selected_movie_idx == 0) {
            cout << "Exiting booking menu." << endl;
            break;
        } else if (selected_movie_idx >= 1 && selected_movie_idx <= 10) {
            Movie selected_movie = movie_list[selected_movie_idx - 1];
            

            for (int i = 0; i < ticket_amount; ++i) {
                string movie_name;
                pair<string, string> seat_n;
                tie(date, time, seat_n, movie_name) = selected_movie.booking(date, time, ticket_amount);
                
                // to check if seat for this movie at this date and time is fully booked
                // if so, we restart the while loop
                if (movie_name.empty()) {
                    continue;
                }

                seat_store.push_back(seat_n);
                
                // declare inside cus local for loop variables
                main_store.movie_name = movie_name;
                main_store.date = date;
                main_store.time = time;
            }

            main_store.ticket_amount = ticket_amount; //amount of tickets for this session only
            main_store.seat_store = seat_store; //store of booked seats for this session only

            return {main_store};

        } else {
            cout << "Invalid selection. Please try again." << endl;
        }
    }
    // maybe we can declare defualt values for main_store   
    return {main_store}; // Default return if exiting, so struc main_store is empty
}
// -- BOOKING FUNCTION END

int main() {
    TicketInfo ticket_store;
    BookingInfo booking_store;

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


    ticket_store = CompleteTicketBuyingProcess ();

    // Wie Wie, need u add ur admin movie_list here ah size ten - [10]
    booking_store = booking_main(movie_list, ticket_store.total_ticket_amount);


    vector<pair<string, string>> seat_store = booking_store.seat_store;
    // should prob make printing this stuff a function or smt haha
    cout << "\nBooking Summary:\nMovie: " << booking_store.movie_name << "\nDate: " << booking_store.date << "\nTime: " << booking_store.time 
    << "\nNumber of Tickets: " << booking_store.ticket_amount << "\nSeat(s): ";
    for (const auto seat : seat_store) {
        cout << seat.first << seat.second << " ";
    }
    cout << endl;

    // since ticket_store.is_member returns true false, 1 or 0 - have to declare yes no on top 
    cout << "\nTicket Summary:\nMember: " << ticket_store.is_member << "\nNumber of Tickets: " << ticket_store.total_ticket_amount 
    << "\nGrand Total: " << ticket_store.grandTotal << endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "(" << get<0>(ticket_store.TicketCategoryNums[i]) << ", "
                         << get<1>(ticket_store.TicketCategoryNums[i]) << ", "
                         << get<2>(ticket_store.TicketCategoryNums[i]) << ")" << std::endl;
    }

    return 0;
}

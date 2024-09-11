#include <iostream>
#include <array>
#include <map>
#include <string>
#include <tuple>
#include <vector>  
#include <algorithm>

using namespace std;

// Alphabet & Number seating arrays for seat referencing

array<string, 10> alphabs = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
array<string, 10> list_nums = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

// Movie class definition
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
    tuple<string, string, pair<string, string>, string> booking(string date, string time) {
        // we check if date and time are empty, this is for booking multiple tickets
        // if false we enter date and time, if true we skip 
        // So users don't have to enter date and time multiple times
        if (date.empty() && time.empty()) {
            date = in_date();
            time = in_time();
        }
        
        if (return_seats(date, time).size() >= 100) {
            cout << "Sorry, all seats are booked. Please try another date and time." << endl;
            return make_tuple("", "", make_pair("", ""), "");
        }

        vector<pair<string, string>>& seats = return_seats(date, time);
        show_seats(seats);
        pair<string, string> seat_n = in_seats(date, time);
        return make_tuple(date, time, seat_n, name);
    }
};

// Have to be declared outside main !
struct BookingInfo {
    // struct for storing current booking info
    // lasts only for current session
    string movie_name;
    string date;
    string time;
    int ticket_amount;
    vector<pair<string, string>> seat_store;  // Store seat information as a list
};

// Main booking function to handle multiple movies, and multiply bookings
BookingInfo booking_main(vector<Movie>& movie_list) {

    BookingInfo main_store;
    string date, time;
    vector<pair<string, string>> seat_store;

    cout << "\nAvailable Movies:" << endl;
    // prints list of movies
    for (size_t i = 0; i < movie_list.size(); ++i) {
        cout << i + 1 << ". " << movie_list[i].name << endl;
    }

    int selected_movie_idx = 0;
    while (true) {
        // while loop to check valid input for selected_movie_idx
        cout << "Enter a number to select a movie, 0 to exit: ";
        cin >> selected_movie_idx;

        if (selected_movie_idx >= 1 && selected_movie_idx <= movie_list.size()) {
            Movie& selected_movie = movie_list[selected_movie_idx - 1];

            int ticket_amount;
            cout << "How many tickets would you like to book: ";
            cin >> ticket_amount;


            for (int i = 0; i < ticket_amount; ++i) {
                string movie_name;
                pair<string, string> seat_n;
                tie(date, time, seat_n, movie_name) = selected_movie.booking(date, time);
                
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

            // cout << "\nBooking Summary:\nMovie: " << main_store.movie_name << "\nDate: " << main_store.date << "\nTime: " << main_store.time << "\nSeat(s): ";
            // for (const auto& seat : seat_store) {
            //     cout << seat.first << seat.second << " ";
            // }
            // cout << endl;

            return {main_store};

        } else if (selected_movie_idx == 0) {
            cout << "Exiting booking menu." << endl;
            break;
        } else {
            cout << "Invalid Input. Please try again." << endl;
        }
    }
    // maybe we can declare defualt values for main_store
    return {main_store}; // Default return if exiting, so struc main_store is empty
}

int main() {

    // initialize struct
    BookingInfo booking_info;

    // declare movies
    Movie movie1("The Matrix", "2h", "Sci-Fi", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"});
    Movie movie2("Kung Fu Panda", "2hr 30min", "Comedy", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"});
    Movie movie3("Deadpool 3", "2hr 40min", "Action", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"});

    // vector list to loop through 
    vector<Movie> movie_list = {movie1, movie2, movie3};
    
    // struct variables are returned
    booking_info = booking_main(movie_list);


    // Output booking information for testing
    vector<pair<string, string>> seat_store = booking_info.seat_store;
    cout << "\nBooking Summary:\nMovie: " << booking_info.movie_name << "\nDate: " << booking_info.date << "\nTime: " << booking_info.time << "\nNumber of Tickets: " << booking_info.ticket_amount << "\nSeat(s): ";
            for (const auto& seat : seat_store) {
                cout << seat.first << seat.second << " ";
            }
            cout << endl;

    return 0;
}

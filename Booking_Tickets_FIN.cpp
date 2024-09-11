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
    string name;
    string length;
    string genre;
    string language;
    vector<string> dates;
    vector<string> time;
    map<string, map<string, vector<pair<string, string>>>> booking_data;

    // Constructor to initialize the movie with details
    Movie(string name, string length, string genre, string language, vector<string> dates, vector<string> times)
        : name(name), length(length), genre(genre), language(language), dates(dates), time(times) {
        booking_data = initialize_booking(dates, times);
    }

    // Initialize booking data with available dates and times
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
        for ( string date : dates) {
            cout << date << ", ";
        }
        cout << endl;

        string chosen_date;
        while (true) {
            cout << "Enter a valid date: ";
            cin >> chosen_date;
            if (find(dates.begin(), dates.end(), chosen_date) != dates.end()) {
                return chosen_date;
            }
            cout << "Invalid date, please try again." << endl;
        }
    }

    // Input for time selection with validation
    string in_time() {
        cout << "This is the available times: ";
        for ( string t : time) {
            cout << t << ", ";
        }
        cout << endl;

        string chosen_time;
        while (true) {
            cout << "Enter a valid time: ";
            cin >> chosen_time;
            if (find(time.begin(), time.end(), chosen_time) != time.end()) {
                return chosen_time;
            }
            cout << "Invalid time, please try again." << endl;
        }
    }

    // Return booked seats for a given date and time
    vector<pair<string, string>>& return_seats(string date, string time) {
        return booking_data[date][time];
    }

    // Show available and booked seats
    void show_seats(const vector<pair<string, string>>& booked_seats) {
        cout << "   1   2   3   4   5   6   7   8   9   10" << endl;

        for ( string letter : alphabs) {
            cout << letter << " ";
            for ( string col : list_nums) {
                if (find(booked_seats.begin(), booked_seats.end(), make_pair(letter, col)) != booked_seats.end()) {
                    cout << "|XX|";
                } else {
                    cout << "|  |";
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
            transform(row_alpha.begin(), row_alpha.end(), row_alpha.begin(), ::toupper);
            if (find(alphabs.begin(), alphabs.end(), row_alpha) == alphabs.end()) {
                cout << "Invalid row. Please try again." << endl;
                continue;
            }

            // Defining a list of valid numbers as strings

            cout << "Enter seat number (1-10): ";
            cin >> col_num;

            // Check if input is not in list_nums
            if (find(list_nums.begin(), list_nums.end(), col_num) == list_nums.end()) {
                cout << "Invalid seat number. Please try again." << endl;
                continue;
            }
                

            pair<string, string> seat_n = make_pair(row_alpha, col_num);
            if (find(return_seats(date, time).begin(), return_seats(date, time).end(), seat_n) != return_seats(date, time).end()) {
                cout << "Seat already booked. Please choose another seat." << endl;
            } else {
                return_seats(date, time).push_back(seat_n); // append seat_n into vector
                cout << "\nSeat booked successfully!\n";
                show_seats(return_seats(date, time));
                return seat_n;
            }
        }
    }

    // Main booking function
    tuple<string, string, pair<string, string>, string> booking(string date, string time) {
        if (date.empty() && time.empty()) {
            date = in_date();
            time = in_time();
        }

        vector<pair<string, string>>& seats = return_seats(date, time);
        show_seats(seats);
        pair<string, string> seat_n = in_seats(date, time);
        return make_tuple(date, time, seat_n, name);
    }
};

// Have to be declared outside main !
struct BookingInfo {
    string movie_name;
    string date;
    string time;
    int ticket_amount;
    vector<pair<string, string>> seat_store;  // Store seat information as a list
};

// Main booking function to handle multiple movies
BookingInfo booking_main(vector<Movie>& movie_list) {

    BookingInfo main_store;
    string date, time;
    vector<pair<string, string>> seat_store;

    cout << "\nAvailable Movies:" << endl;
    for (size_t i = 0; i < movie_list.size(); ++i) {
        cout << i + 1 << ". " << movie_list[i].name << endl;
    }

    int selected_movie_idx = 0;
    while (true) {
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
                seat_store.push_back(seat_n);

                main_store.movie_name = movie_name;
                main_store.date = date;
                main_store.time = time;
            }
            main_store.ticket_amount = ticket_amount; //amount of tickets
            main_store.seat_store = seat_store; //store of booked seats for this session only

            cout << "\nBooking Summary:\nMovie: " << main_store.movie_name << "\nDate: " << main_store.date << "\nTime: " << main_store.time << "\nSeat(s): ";
            for (const auto& seat : seat_store) {
                cout << seat.first << seat.second << " ";
            }
            cout << endl;

            return {main_store};

        } else if (selected_movie_idx == 0) {
            cout << "Exiting booking menu." << endl;
            break;
        } else {
            cout << "Invalid Input. Please try again." << endl;
        }
    }
    return {main_store}; // Default return if exiting, so struc main_store is empty
}

int main() {

    BookingInfo booking_info;
    BookingInfo booking_info2;

    Movie movie1("The Matrix", "2h", "Sci-Fi", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"});
    Movie movie2("Kung Fu Panda", "2hr 30min", "Comedy", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"});
    Movie movie3("Deadpool 3", "2hr 40min", "Action", "English", {"1", "2", "3", "4"}, {"12:30", "1:30", "2:00", "3:45"});

    vector<Movie> movie_list = {movie1, movie2, movie3};

    booking_info = booking_main(movie_list);
    // booking_info2 = booking_main(movie_list);

    // Output booking information for testing
    vector<pair<string, string>> seat_store = booking_info.seat_store;
    cout << "\nBooking Summary:\nMovie: " << booking_info.movie_name << "\nDate: " << booking_info.date << "\nTime: " << booking_info.time << "\nNumber of Tickets: " << booking_info.ticket_amount << "\nSeat(s): ";
            for (const auto& seat : seat_store) {
                cout << seat.first << seat.second << " ";
            }
            cout << endl;

    return 0;
}

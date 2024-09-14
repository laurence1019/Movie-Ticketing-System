#ifndef CLASS_H
#define CLASS_H

#include "header.h"

class movie_class
{
   public:
      const double cost_adult = 25.00;
      const double cost_kid = 15.00;

      //Format: Code || Name || Duration || Category
      string mv_list[10][4] = {
         {"ANM2401","The Godfather","2 Hours","Drama"},
         {"APL1324","Titanic","2 Hours","Romance"},
         {"BTJ2426","Inception","1 Hours","Sci-Fi"},
         {"DNT2402","The Dark Knight","2 Hours","Action"},
         {"EOT2410","Parasite","2 Hours","Drama"},
         {"UGL2413","Forrest Gump","2 Hours","Romance"},
         {"TRF2414","Avengers: Endgame","3 Hours","Action"},
         {"DHI9792","The Exorcist","2 Hours","Horror"},
         {"MGL2427","A Nightmare on Elm Street","2 Hours","Horror"},
         {"GOF2416","Hereditary","2 hrs","Drama"}
      };

      double adult_tksold[10] = {0,0,0,0,0,0,0,0,0,0};
      double kid_tksold[10] = {0,0,0,0,0,0,0,0,0,0};
      double revenue[10] = {0,0,0,0,0,0,0,0,0,0}; //Will Calculate itself

      /* Dummy Data
         double adult_tksold[10] = {10,20,30,40,40,30,20,10,20,30};
         double kid_tksold[10] = {40,30,20,10,10,20,30,40,40,30};
         double revenue[10] = {0,0,0,0,0,0,0,0,0,0};
      */
};

class admin_class 
{
   public:
      string username = "";
      string userpass = "";
      int ad_choice = 0; 
      const string realname = "admin";
      const string realpass = "pass";
};

class cust_class
{
   public:
      const string cust_memID[3][2] = {
               {"012345678901","Laurence"},
               {"456789098768","Daryl"},
               {"987654321098","Cindy"}
      };
      bool cust_mem_log = 0; //For After Member Discount Usage

      string record[1][5] = {
               {"Movie","Date","Time","Category","Seat"}
      };
};

//Administrator
void ad_mvlist(movie_class movie);
void ad_salesreport(movie_class& movie);
void admin_login(admin_class& admin);
void admin_menu(admin_class& admin);
void ad_mfymovie(movie_class& movie);
string autoCode(movie_class movie);

//Customer
void cust_member(cust_class& cust);
void receipt(cust_class cust);
void invoice();
int pay_decision();
string payMethDec();
string rtc();
string autoID();
void receipt();

#endif

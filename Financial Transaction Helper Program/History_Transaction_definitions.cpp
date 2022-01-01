#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"


////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//

Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date,  
                          unsigned int month_date,  unsigned year_date, 
                          bool buy_sell_trans,  unsigned int number_shares,  
                          double trans_amount ){

          symbol = ticker_symbol;
          day = day_date;
          month = month_date;
          year = year_date;
          if (buy_sell_trans==true){
            trans_type="Buy";
          } else {
            trans_type="Sell";
          }
          shares = number_shares;
          amount = trans_amount;
          trans_id = assigned_trans_id;
          ++assigned_trans_id;
          p_next = nullptr;
          acb = 0;
          acb_per_share = 0;
          share_balance = 0;
          cgl = 0;
        };


// Destructor
// TASK 1
//

Transaction::~Transaction(){

};


// Overloaded < operator.
// TASK 2
//

bool Transaction::operator<( Transaction const &other ){
  if (this->year<other.year){return true;}
  if (this->year>other.year){return false;}
  if (this->month<other.month){return true;}
  if (this->month>other.month){return false;}
  if (this->day<other.day){return true;}
  return false;
}


// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
//

History::History(){
  this->p_head = nullptr;
}

// Destructor
// TASK 3
//

History::~History(){
  Transaction *p_temp{p_head};

  while (p_temp!=nullptr){
    p_temp = p_temp->get_next();
    delete p_head;
    p_head = p_temp;
  }
}

// Read the transaction history from file.
//
void History::read_history(){
  ece150::open_file();

  while(ece150::next_trans_entry() == true){
    std::string a = ece150::get_trans_symbol();

    unsigned int b = ece150::get_trans_day();

    unsigned int c = ece150::get_trans_month();

    unsigned int d = ece150::get_trans_year();

    unsigned int e = ece150::get_trans_shares();

    double f = ece150::get_trans_amount();

    bool g = ece150::get_trans_type();

    Transaction *p_trans = new Transaction {a,b,c,d,g,e,f};

    insert(p_trans);
    
  }

  ece150::close_file();
}

// Insert transaction in linked list.
//
void History::insert(Transaction *p_new_trans){
  //Code was inspired by David Lau lab sessions
  if (p_head==nullptr){
    this->p_head = p_new_trans;
  } else {
    Transaction *p_f{p_head};

    while ((p_f->get_next())!=nullptr){
      p_f = p_f->get_next();
    }

    p_f->set_next(p_new_trans);
    //p_new_trans->set_next(nullptr);

  }
}

// Print the transaction history.
//
void History::print(){
  std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;

  Transaction *p_temp{p_head};

  while(p_temp!=nullptr){    
    p_temp->print();
    p_temp = p_temp->get_next();
  }

  std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
}

// Sort using insertion sort.
//
void History::sort_by_date(){
  Transaction *p_temp{p_head};
  Transaction *p_newhead{nullptr};
  
  while(p_head!=nullptr){
    p_temp = p_head;
    p_head = p_head->get_next();
    p_temp->set_next(nullptr);

    if (p_newhead==nullptr){
      p_newhead = p_temp;
    } else {
      Transaction *p_traverse{p_newhead};
      Transaction *p_save{p_traverse};
      while ((p_traverse!=nullptr)){
        if (*p_temp<*p_traverse){
          if (p_traverse==p_newhead){
            p_newhead = p_temp;
            p_temp->set_next(p_traverse);
            break;
          } else {
            p_temp->set_next(p_traverse);
            p_save->set_next(p_temp);
            break;
          }
        } else if (*p_traverse<*p_temp){
          p_save = p_traverse;
          p_traverse = p_traverse->get_next();
        } 
        else {
          if ((p_temp->get_trans_id())<(p_traverse->get_trans_id())){
            if (p_traverse==p_newhead){
              p_newhead = p_temp;
              p_temp->set_next(p_traverse);
              break;
            } else {
              p_temp->set_next(p_traverse);
              p_save->set_next(p_temp);
              break;
            }
          } else {
            p_save = p_traverse;
            p_traverse = p_traverse->get_next();
          }
        }
      }
      if (p_traverse==nullptr){
        p_save->set_next(p_temp);
      }
    }
  }
  p_head = p_newhead;
  //delete pointers?
  //breaks not working?
  //dont sort by trans id
  
}

// Update the acb members in the linked list. (acb, acb_per_share, share_balance, cgl)
//
void History::update_acb_cgl(){
  Transaction *p_temp{p_head};
  Transaction *p_next{p_temp->get_next()};
  int counter{};
  while(p_next!=nullptr){
    if (counter==0){
      p_temp->set_acb(p_temp->get_amount());
      p_temp->set_share_balance(p_temp->get_shares());
      p_temp->set_acb_per_share((p_temp->get_acb())/(p_temp->get_share_balance()));
      counter++;
    } else {
      if ((p_next->get_trans_type())){
        p_next->set_acb(p_temp->get_acb()+p_next->get_amount());
        p_next->set_share_balance(p_temp->get_share_balance()+p_next->get_shares());
        p_next->set_acb_per_share(p_next->get_acb()/p_next->get_share_balance());
      } else {
        p_next->set_share_balance(p_temp->get_share_balance()-p_next->get_shares());
        p_next->set_acb(p_temp->get_acb()-(p_next->get_shares()*p_temp->get_acb_per_share()));
        p_next->set_cgl(p_next->get_amount()-(p_next->get_shares()*p_temp->get_acb_per_share()));
        p_next->set_acb_per_share(p_temp->get_acb_per_share());
    }
      p_next = p_next->get_next();
      p_temp = p_temp->get_next();
    }
  }
}

// Compute the ACB, and CGL.
//
double History::compute_cgl(unsigned int year){
  Transaction *p_temp{p_head};
  double year_cgl{};

  while(p_temp!=nullptr){
    if (p_temp->get_year()==year){
      year_cgl += p_temp->get_cgl();
    }
    p_temp = p_temp->get_next();
  }

  return year_cgl;
}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }

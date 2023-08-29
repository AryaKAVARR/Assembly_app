// Name: Arya Rajeshbhai Kavar
// Seneca Student ID: 167240217
// Seneca email: akavar@myseneca.ca
// Date of completion: 28-07-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_WORKSTATION
#define SDDS_WORKSTATION
#include <iostream>
#include <queue>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"


namespace sdds
{
   extern std::deque<CustomerOrder> g_pending;
   extern std::deque<CustomerOrder> g_completed;
   extern std::deque<CustomerOrder> g_incomplete;

   class Workstation : public Station
   {
      std::deque<CustomerOrder> m_orders{};
      Workstation* m_pNextStation{};

   public:
      Workstation(const std::string& str) : Station(str){} //one argument constructor
      void fill(std::ostream &os); // it will fill the order on front
      bool attemptToMoveOrder(); // this function will move order to front if needed
      void setNextStation(Workstation* station); //this modifier stores the address of the referenced `Workstation`
      Workstation* getNextStation() const; //this query will return address of next 'Workstation'
      Workstation& operator+=(CustomerOrder&& newOrder); // it will move the order to back of queue
      void display(std::ostream& os) const; // display function
   };
}
#endif // !SDDS_WORKSTATION

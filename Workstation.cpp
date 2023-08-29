// Name: Arya Rajeshbhai Kavar
// Seneca Student ID: 167240217
// Seneca email: akavar@myseneca.ca
// Date of completion: 28-07-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"
#include "CustomerOrder.h"
#include<deque>
using namespace std;

namespace sdds
{
   deque<CustomerOrder> g_pending;
   deque<CustomerOrder> g_completed;
   deque<CustomerOrder> g_incomplete;

   void Workstation::fill(std::ostream& os)
   {
      if (!this->m_orders.empty())
         this->m_orders.front().fillItem(*this, os);
   }
   bool Workstation::attemptToMoveOrder()
   {
      if (!this->m_orders.empty())
      {
         CustomerOrder& temp = this->m_orders.front();
         if (temp.isItemFilled(this->getItemName()) || this->getQuantity() <= 0)
         {
            if (this->m_pNextStation != nullptr)
            {
               *this->m_pNextStation += std::move(temp);
            }
            else
            {
               if (temp.isOrderFilled())
               {
                  g_completed.push_back(std::move(temp));
               }
               else
               {
                  g_incomplete.push_back(std::move(temp));
               }
            }
            this->m_orders.pop_front();
            return true;
         }
      }
      return false;
   }
   void Workstation::setNextStation(Workstation* station)
   {
      this->m_pNextStation = station;

   }
   Workstation* Workstation::getNextStation() const
   {
      return this->m_pNextStation;
   }
   Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
   {
      this->m_orders.push_back(std::move(newOrder));
      return *this;
   }
   void Workstation::display(std::ostream& os) const
   {
      os << this->getItemName() << " --> ";
      if (this->m_pNextStation == nullptr)
         os << "End of Line" << endl;
      else
         os << this->m_pNextStation->getItemName() << endl;
   }
}
// Name: Arya Rajeshbhai Kavar
// Seneca Student ID: 167240217
// Seneca email: akavar@myseneca.ca
// Date of completion: 28-07-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "CustomerOrder.h"
#include "Utilities.h"
#include<string>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <string>

using namespace std;

namespace sdds
{
   size_t CustomerOrder::m_widthField{};


   CustomerOrder::CustomerOrder(const CustomerOrder& obj)
   {
      throw std::runtime_error("Copy constructor is not allowed for CustomerOrder objects.");
   }
   CustomerOrder::CustomerOrder(const std::string order)
   {
      Utilities obj{};
      size_t Next{};
      bool check = true;
      if (order[0] != '\0')
      {
         //extracting name and product
         this->m_name = obj.extractToken(order, Next, check);
         this->m_product = obj.extractToken(order, Next, check);

         bool count = check;
         size_t startCount = Next;
         while (count) {
            obj.extractToken(order, startCount, count);
            this->m_cntItem++;
         }

         // extracting all the items
         this->m_lstItem = new Item * [this->m_cntItem];

         for (size_t i = 0; i < this->m_cntItem; i++)
         {
            this->m_lstItem[i] = new Item(obj.extractToken(order, Next, check));
         }

         if (CustomerOrder::m_widthField < obj.getFieldWidth()) {
            CustomerOrder::m_widthField = obj.getFieldWidth();
         }

      }
   }
   CustomerOrder::CustomerOrder(CustomerOrder&& obj) noexcept
   {
      *this = std::move(obj);
   }
   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj) noexcept
   {
      if (this != &obj) {
         for (size_t i = 0; i < this->m_cntItem; i++) {
            delete this->m_lstItem[i];
         }
         delete[] this->m_lstItem;

         this->m_name = std::move(obj.m_name);
         this->m_product = std::move(obj.m_product);
         this->m_cntItem = obj.m_cntItem;
         this->m_lstItem = obj.m_lstItem;

         obj.m_cntItem = 0;
         obj.m_lstItem = nullptr;
      }

      return *this;

   }
   CustomerOrder::~CustomerOrder()
   {
      for (size_t i = 0; i < this->m_cntItem; i++)
      {
         delete this->m_lstItem[i];
      }

      delete[] this->m_lstItem;
   }
   bool CustomerOrder::isOrderFilled() const
   {
      for (size_t i = 0; i < this->m_cntItem; i++)
      {
         if (!this->m_lstItem[i]->m_isFilled)
            return false;
      }
      return true;
   }
   bool CustomerOrder::isItemFilled(const std::string& itemName) const
   {
      for (size_t i = 0; i < this->m_cntItem; i++)
      {
         const Item& temp = *this->m_lstItem[i];
         if (temp.m_itemName == itemName && !temp.m_isFilled)
            return false;
      }
      return true;
   }
   void CustomerOrder::fillItem(Station& station, std::ostream& os)
   {
      bool added = false;
      for (size_t i = 0; i < this->m_cntItem && !added; i++)
      {
         Item& item = *this->m_lstItem[i];

         bool MatchItems{};
         if (item.m_itemName == station.getItemName())
         {
            MatchItems = true;
         }
         bool remaining = !item.m_isFilled;

         if (MatchItems && remaining) {

            if (station.getQuantity() > 0) {
               station.updateQuantity();
               item.m_serialNumber = station.getNextSerialNumber();
               item.m_isFilled = true;
               os << "    Filled ";
               os << this->m_name << ", " << this->m_product << " [" << item.m_itemName << "]" << endl;
               added = true;
            }
            else {
               os << "    Unable to fill ";
               os << this->m_name << ", ";
               os << this->m_product << " [";
               os << item.m_itemName << "]" << endl;
            }
         }
      }
   }
   void CustomerOrder::display(std::ostream& os) const
   {
      os << this->m_name << " - " << this->m_product << endl;

      for (size_t i = 0; i < this->m_cntItem; i++) {
         const Item& thisItem = *this->m_lstItem[i];
         os << "[";
         os << setfill('0') << right << setw(6);
         os << thisItem.m_serialNumber;
         os << "] ";
         os << setfill(' ') << left << setw(CustomerOrder::m_widthField);
         os << thisItem.m_itemName;
         os << " - ";
         os << (thisItem.m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
      }
   }
}
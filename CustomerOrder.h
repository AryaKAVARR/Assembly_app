// Name: Arya Rajeshbhai Kavar
// Seneca Student ID: 167240217
// Seneca email: akavar@myseneca.ca
// Date of completion: 28-07-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_CUSTOMERORDER
#define SDDS_CUSTOMERORDER
#include<iostream>
#include<string>
#include"Station.h"

namespace sdds
{
   struct Item
   {
      std::string m_itemName;
      size_t m_serialNumber{ 0 };
      bool m_isFilled{ false };

      Item(const std::string& src) : m_itemName(src) {};
   };

   class CustomerOrder
   {
      std::string m_name{};
      std::string m_product{};
      size_t m_cntItem{};
      Item** m_lstItem{};

      static size_t m_widthField;

   public:
      CustomerOrder(const CustomerOrder& obj);
      CustomerOrder& operator=(const CustomerOrder&) = delete; // deleted function

      CustomerOrder() {};
      CustomerOrder(const std::string order);//1 argument constructor
      CustomerOrder(CustomerOrder&& obj) noexcept;//move constructor
      CustomerOrder& operator=(CustomerOrder&& obj) noexcept;//move assign operator
      ~CustomerOrder();//destructor
      bool isOrderFilled() const;//returns true if all items order are filled
      bool isItemFilled(const std::string& itemName) const;
      void fillItem(Station& station, std::ostream& os);
      void display(std::ostream& os) const;
   };
}
#endif // !SDDS_CUSTOMERORDER

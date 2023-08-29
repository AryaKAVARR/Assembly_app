// Name: Arya Rajeshbhai Kavar
// Seneca Student ID: 167240217
// Seneca email: akavar@myseneca.ca
// Date of completion: 28-07-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_STATION
#define SDDS_STATION
#include<iostream>
#include<string>


namespace sdds
{
   class Station
   {
      int id{ 1 };
      std::string m_name{};
      std::string m_desc{};
      unsigned int ser_number{};
      unsigned int no_stock{};
      static size_t m_widthField;
      static int id_generator;

      std::string trim(const std::string& str);

   public:
      Station() {};//default constructor
      Station(const std::string str);
      const std::string& getItemName() const;
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& os, bool full) const;

   };
}
#endif // !SDDS_STATION

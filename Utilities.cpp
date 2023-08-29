// Name: Arya Rajeshbhai Kavar
// Seneca Student ID: 167240217
// Seneca email: akavar@myseneca.ca
// Date of completion: 28-07-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"
#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

namespace sdds
{
   char Utilities::m_delimiter{};

   string Utilities::trim(const string& str) {
      const string& whitespace = " \t\n\r\f\v";

      const size_t start_pos = str.find_first_not_of(whitespace);
      if (start_pos == string::npos) return ""; // no content

      const size_t end_pos = str.find_last_not_of(whitespace);
      const size_t len = end_pos - start_pos + 1;

      return str.substr(start_pos, len);
   }

   void Utilities::setFieldWidth(size_t newWidth)
   {
      if (newWidth > 0)
         this->m_widthField = newWidth;
   }
   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
   {
      string temp{};

      if (next_pos <= str.length())
      {
         size_t pos = str.find(this->m_delimiter, next_pos);
         if (pos != string::npos)
         {
            //cout << str.substr(next_pos, (pos - next_pos));
            temp = this->trim(str.substr(next_pos, (pos - next_pos)));
            next_pos = pos + 1;
            more = true;
         }
         else {
            temp = str.substr(next_pos);
            next_pos = str.length() + 1;
            more = false;
         }

         if (temp.empty()) {
            more = false;
            throw str + " Error: No token found";
         }
         if (this->m_widthField < temp.length())
            this->setFieldWidth(temp.length());
      }
      return temp;
   }
   void Utilities::setDelimiter(char newDelimiter)
   {
      m_delimiter = newDelimiter;
   }
   char Utilities::getDelimiter()
   {
      return m_delimiter;
   }
}
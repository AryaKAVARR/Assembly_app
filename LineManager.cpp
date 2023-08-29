// Name: Arya Rajeshbhai Kavar
// Seneca Student ID: 167240217
// Seneca email: akavar@myseneca.ca
// Date of completion: 28-07-2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "LineManager.h"
#include "Utilities.h"
#include<iostream>
#include <deque>
#include <string>
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace sdds
{
   /*deque<CustomerOrder> g_pending{};*/


   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
   {
      if (file[0] != '\0')
      {
         ifstream ifstr(file);
         if (ifstr.is_open())
         {

            string temp{};
            string temp2{};
            Utilities obj{};
            
            while (!ifstr.eof())
            {
               string line{};
               size_t next{};
               Workstation* current{};
               Workstation* Next{};
               bool check = true;

               getline(ifstr, line);
               //extract token with help of utilities function
               temp = obj.extractToken(line, next, check);
               temp2 = obj.extractToken(line, next, check);

               //assigning the current station
               auto station1 = std::find_if(stations.begin(), stations.end(), [&](Workstation* obj)
                  {
                     return obj->getItemName() == temp;
                  });

               if (station1 != stations.end())
               {
                  current = *station1;
               }
               
               //now we will assign next station
               auto station2 = std::find_if(stations.begin(), stations.end(), [&](Workstation* obj)
                  {
                     return obj->getItemName() == temp2;
                  });

               if (station2 != stations.end())
               {
                  Next = *station2;
               }

               current->setNextStation(Next);
               this->m_activeLine.push_back(current);
            }

            this->m_firstStation = *std::find_if(this->m_activeLine.begin(), this->m_activeLine.end(), [this](const Workstation* obj)
               {
                  return none_of(this->m_activeLine.begin(), this->m_activeLine.end(), [&](Workstation* nextObj)
                     {
                        if (nextObj->getNextStation() != nullptr)
                        {
                           return obj == nextObj->getNextStation();
                        }
                        else
                        {
                           return false;
                        }

                     });
               });
            this->m_cntCustomerOrder = g_pending.size();

            ifstr.close();
         }
      }
   }

   void LineManager::reorderStations()
   {
      std::vector<Workstation*>reorder{};
      Workstation* first = this->m_firstStation;

      //reordering in correct format
      while (first)
      {
         reorder.push_back(first);
         first = first->getNextStation();
      }

      //assigning back to activeLine
      this->m_activeLine = reorder;
   }

   bool LineManager::run(std::ostream& os)
   {
      static int count = 1; //for keeping track of iteration

      os << "Line Manager Iteration: " << count++ << endl;

      if (!g_pending.empty())
      {
         *this->m_firstStation += std::move(g_pending.front());
         g_pending.pop_front();
      }

      //executing fill operation
      for_each(this->m_activeLine.begin(), this->m_activeLine.end(), [&](auto& obj)
         {
            obj->fill(os);
         });

      //executing move operator
      for_each(this->m_activeLine.begin(), this->m_activeLine.end(), [&](auto& obj)
         {
            obj->attemptToMoveOrder();
         });

      return this->m_cntCustomerOrder == (g_completed.size() + g_incomplete.size()); // this will return true or false depending upon order size

   }

   void LineManager::display(std::ostream& os) const
   {
      for_each(this->m_activeLine.begin(), this->m_activeLine.end(), [&](Workstation* obj)
         {
            obj->display(os);
         });
   }

}
#ifndef PALSTRING_H
#define PALSTRING_H
#include <iostream>
#include <cstring> // For std::strlen, std::strcpy

class PalString
{
public:
   char *data_; // A character array that stores strings

   // TODO [Optional] : define other useful variables

   // TODO: finish the constructor
   PalString(const char *pStr)
   {
      if (pStr == nullptr)
      {
         data_ = new char[1];
         data_[0] = '\0';
         return;
      }
      size_t len = std::strlen(pStr);
      data_ = new char[2 * len + 1]; // For string, reversed string, and null terminator

      // Copy original string
      for (size_t i = 0; i < len; ++i)
      {
         data_[i] = pStr[i];
      }

      // Append reversed string
      for (size_t i = 0; i < len; ++i)
      {
         data_[len + i] = pStr[len - 1 - i];
      }

      data_[2 * len] = '\0'; // Null-terminate
   }

   // TODO: finish the destructor
   ~PalString()
   {
      delete[] data_;
   }

   // TODO: finish the function getString
   char *getString()
   {
      return data_;
   }

   // TODO: finish the function changeString
   void changeString(const char *pStr)
   {
      delete[] data_;
      data_ = nullptr;

      if (pStr == nullptr)
      {
         data_ = new char[1];
         data_[0] = '\0';
         return;
      }
      size_t len = std::strlen(pStr);
      data_ = new char[2 * len + 1];

      for (size_t i = 0; i < len; ++i)
      {
         data_[i] = pStr[i];
      }

      for (size_t i = 0; i < len; ++i)
      {
         data_[len + i] = pStr[len - 1 - i];
      }

      data_[2 * len] = '\0';
   }

   // TODO: finish the copy constructor
   PalString(const PalString &rhs)
   {
      if (rhs.data_ == nullptr)
      {
         data_ = new char[1];
         data_[0] = '\0';
      }
      else
      {
         size_t len_rhs_data = std::strlen(rhs.data_);
         data_ = new char[len_rhs_data + 1];
         std::strcpy(data_, rhs.data_);
      }
   }

   // TODO: override the operator <<
   friend std::ostream &operator<<(std::ostream &os, const PalString &ps)
   {
      if (ps.data_ != nullptr)
      {
         os << ps.data_;
      }
      return os;
   }
};

#endif // #ifndef PALSTRING_H
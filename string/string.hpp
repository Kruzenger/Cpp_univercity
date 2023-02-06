#pragma once
#include <string.h>

#include <iostream>
#include <vector>

class String {
 public:
  String();
  String(size_t size, char character);
  String(const char* input);
  String(const String& other);
  ~String();
  void Clear();
  void PushBack(char character);
  void PopBack();
  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);
  void Reserve(size_t new_cap);
  void ShrinkToFit();
  void Swap(String& other);
  char& Front();
  char Front() const;
  char& Back();
  char Back() const;
  bool Empty() const;
  size_t Size() const;
  size_t Capacity() const;
  const char* Data() const;

  bool operator<(const String& other) const;
  bool operator<(const char* other) const;

  bool operator<=(const String& other) const;
  bool operator<=(const char* other) const;

  bool operator>(const String& other) const;
  bool operator>(const char* other) const;

  bool operator>=(const String& other) const;
  bool operator>=(const char* other) const;

  bool operator==(const String& other) const;
  bool operator==(const char* other) const;

  bool operator!=(const String& other) const;
  bool operator!=(const char* other) const;

  String operator*(int n) const;
  String& operator*=(int n);
  String operator+(const String& other) const;
  String& operator+=(const String& other);
  String& operator+=(const char* input);
  String& operator=(const String& other);
  String& operator=(const char* input);

  char& operator[](size_t i);
  char operator[](size_t i) const;

  friend std::ostream& operator<<(std::ostream& stream, const String& obj);
  friend std::istream& operator>>(std::istream& stream, String& obj);

  std::vector<String> Split(const String& delim = " ");
  String Join(const std::vector<String>& strings);

 private:
  size_t capacity_ = 0;
  size_t size_ = 0;
  char* array_ = nullptr;
};
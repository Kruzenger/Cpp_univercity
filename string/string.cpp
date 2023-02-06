#include "string.hpp"

const int kCapacityModifier = 2;

String::String() {}

String::String(size_t size, char character) {
  size_ = size;
  Reserve(size);
  memset(array_, character, size);
}

String::String(const char* input) {
  size_t input_size = strlen(input);
  Reserve(input_size);
  size_ = input_size;
  memcpy(array_, input, input_size);
}

String::String(const String& other) {
  Reserve(other.capacity_);
  size_ = other.size_;
  memcpy(array_, other.array_, size_);
}

String::~String() { delete[] array_; }

void String::Clear() {
  if (array_ != nullptr) {
    size_ = 0;
    memset(array_, 0, capacity_);
  }
}

void String::PushBack(char character) {
  if (capacity_ == 0) {
    Reserve(1);
  } else if (size_ == capacity_) {
    Reserve(capacity_ * kCapacityModifier);
  }
  array_[size_] = character;
  ++size_;
}

void String::PopBack() {
  if (size_ != 0) {
    --size_;
    array_[size_] = 0;
  }
}

void String::Resize(size_t new_size) {
  if (new_size > capacity_) {
    Reserve(new_size);
  }
  size_ = new_size;
}
void String::Resize(size_t new_size, char character) {
  if (new_size > capacity_) {
    Reserve(new_size);
    memset(array_ + size_, character, new_size - size_);
  }
  size_ = new_size;
}

void String::Reserve(size_t new_cap) {
  if (array_ == nullptr) {
    array_ = new char[new_cap + 1];
    memset(array_, 0, new_cap + 1);
    capacity_ = new_cap + 1;
  } else if (capacity_ <= new_cap) {
    char* buffer = new char[size_];
    memcpy(buffer, array_, size_);
    delete[] array_;
    array_ = new char[new_cap + 1];
    memset(array_, 0, new_cap + 1);
    memcpy(array_, buffer, size_);
    capacity_ = new_cap + 1;
    delete[] buffer;
  }
}

void String::ShrinkToFit() {
  if (size_ < capacity_ && array_ != nullptr) {
    char* buffer = new char[size_];
    memcpy(buffer, array_, size_);
    delete[] array_;
    array_ = new char[size_ + 1];
    memcpy(array_, buffer, size_);
    capacity_ = size_;
    delete[] buffer;
  }
}

void String::Swap(String& other) {
  int tmp_size = size_;
  size_ = other.size_;
  other.size_ = tmp_size;

  int tmp_cap = capacity_;
  capacity_ = other.capacity_;
  other.capacity_ = tmp_cap;

  char* tmp = array_;
  array_ = other.array_;
  other.array_ = tmp;
}

char& String::Front() { return array_[0]; }

char String::Front() const { return array_[0]; }

char& String::Back() { return array_[size_ - 1]; }

char String::Back() const { return array_[size_ - 1]; }

bool String::Empty() const { return (size_ == 0); }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

const char* String::Data() const { return array_; }

bool String::operator<(const String& other) const {
  if (array_ == nullptr) {
    return true;
  }
  if (other.array_ == nullptr) {
    return false;
  }
  return (strcmp(array_, other.array_) < 0);
}

bool String::operator<(const char* other) const {
  return (strcmp(array_, other) == 0);
}

bool String::operator<=(const String& other) const {
  if (array_ == nullptr) {
    return true;
  }
  if (other.array_ == nullptr) {
    return false;
  }
  return (strcmp(array_, other.array_) <= 0);
}

bool String::operator<=(const char* other) const {
  return (strcmp(array_, other) <= 0);
}

bool String::operator>(const String& other) const {
  if (array_ == nullptr) {
    return false;
  }
  if (other.array_ == nullptr) {
    return true;
  }
  return (strcmp(array_, other.array_) > 0);
}

bool String::operator>(const char* other) const {
  return (strcmp(array_, other) > 0);
}

bool String::operator>=(const String& other) const {
  if (array_ == nullptr) {
    return false;
  }
  if (other.array_ == nullptr) {
    return true;
  }
  return (strcmp(array_, other.array_) >= 0);
}

bool String::operator>=(const char* other) const {
  return (strcmp(array_, other) >= 0);
}

bool String::operator==(const String& other) const {
  if (array_ == nullptr || other.array_ == nullptr) {
    return (array_ == other.array_);
  }
  return (strcmp(array_, other.array_) == 0);
}

bool String::operator==(const char* other) const {
  return (strcmp(array_, other) == 0);
}

bool String::operator!=(const String& other) const {
  if (array_ == nullptr || other.array_ == nullptr) {
    return (array_ == other.array_);
  }
  return (strcmp(array_, other.array_) != 0);
}

bool String::operator!=(const char* other) const {
  return (strcmp(array_, other) != 0);
}

String String::operator*(int n) const {
  String result = String(this->array_);
  result *= n;
  return result;
}

String& String::operator*=(int n) {
  if (array_ != nullptr) {
    Reserve(size_ * n + 1);
    String buffer = String(this->array_);
    Clear();
    for (int i = 0; i < n; ++i) {
      *this += buffer;
    }
  }
  return *this;
}

String String::operator+(const String& other) const {
  String result = String();
  result = array_;
  result += other.array_;
  return result;
}

String& String::operator+=(const String& other) {
  if (other.array_ != nullptr) {
    Reserve(size_ + other.size_);
    memcpy(array_ + size_, other.array_, other.size_);
    size_ += other.size_;
  }
  return *this;
}

String& String::operator+=(const char* input) {
  if (input != nullptr) {
    int input_size = strlen(input);
    Reserve(size_ + input_size);
    memcpy(array_ + size_, input, input_size);
    size_ += input_size;
  }
  return *this;
}

String& String::operator=(const char* input) {
  if (input != nullptr) {
    int input_size = strlen(input);
    Clear();
    Reserve(input_size);
    size_ = input_size;
    memcpy(array_, input, input_size);
  }
  return *this;
}

String& String::operator=(const String& other) {
  Clear();
  Reserve(other.capacity_);
  Resize(other.size_);
  memcpy(array_, other.array_, size_);
  return *this;
}

char& String::operator[](size_t i) { return *(array_ + i); }

char String::operator[](size_t i) const { return array_[i]; }

std::ostream& operator<<(std::ostream& stream, const String& obj) {
  stream << obj.array_;
  return stream;
}
std::istream& operator>>(std::istream& stream, String& obj) {
  char input;
  while (stream.get(input)) {
    String tmp = String(1, input);
    obj += tmp;
  }
  return stream;
}

std::vector<String> String::Split(const String& delim) {
  std::vector<String> result;
  int word_start = 0;
  result.resize(1);
  String buffer;
  buffer.Reserve(delim.size_);
  buffer.size_ = delim.size_;
  for (size_t i = 0; i < size_; ++i) {
    memcpy(buffer.array_, array_ + i, delim.size_);
    if (delim == buffer) {
      result[result.size() - 1].Clear();
      result[result.size() - 1].Reserve(i - word_start);
      memcpy(result[result.size() - 1].array_, array_ + word_start,
             i - word_start);
      result[result.size() - 1].Resize(i - word_start);
      result.resize(result.size() + 1);
      word_start = i + delim.size_;
      i += delim.size_ - 1;
    }
  }
  result[result.size() - 1].Clear();
  result[result.size() - 1].Reserve(size_ - word_start);
  memcpy(result[result.size() - 1].array_, array_ + word_start,
         size_ - word_start);
  result[result.size() - 1].Resize(size_ - word_start);
  return result;
}

String String::Join(const std::vector<String>& strings) {
  String result = "";
  if (!strings.empty()) {
    for (size_t i = 0; i < strings.size() - 1; ++i) {
      result += strings[i];
      result += array_;
    }
    result += strings[strings.size() - 1];
  }
  return result;
}
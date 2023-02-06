#include "geometry.hpp"

////////////////// Vector //////////////////

Vector::Vector() : x_cordinate_(0), y_cordinate_(0) {}

Vector::Vector(const int64_t& x_cordinate, const int64_t& y_cordinate)
    : x_cordinate_(x_cordinate), y_cordinate_(y_cordinate) {}

Vector& Vector::operator+=(const Vector& other) {
  x_cordinate_ += other.x_cordinate_;
  y_cordinate_ += other.y_cordinate_;
  return *this;
}

Vector& Vector::operator-=(const Vector& other) {
  x_cordinate_ -= other.x_cordinate_;
  y_cordinate_ -= other.y_cordinate_;
  return *this;
}

Vector& Vector::operator*=(const int64_t& other) {
  x_cordinate_ *= other;
  y_cordinate_ *= other;
  return *this;
}

Vector Vector::operator-() const {
  Vector copy(-x_cordinate_, -y_cordinate_);
  return copy;
}

int64_t Vector::GetX() const { return x_cordinate_; }

int64_t Vector::GetY() const { return y_cordinate_; }

double Vector::GetLength() const {
  return std::sqrt(std::pow(x_cordinate_, 2) + std::pow(y_cordinate_, 2));
}

Vector operator+(const Vector& lhs, const Vector& rhs) {
  Vector copy = lhs;
  copy += rhs;
  return copy;
}

Vector operator-(const Vector& lhs, const Vector& rhs) {
  Vector copy = lhs;
  copy -= rhs;
  return copy;
}

int64_t operator*(const Vector& lhs, const Vector& rhs) {
  int64_t result = (lhs.GetX() * rhs.GetX()) + (lhs.GetY() * rhs.GetY());
  return result;
}

int64_t operator^(const Vector& lhs, const Vector& rhs) {
  int64_t vector_product =
      (lhs.GetX() * rhs.GetY()) - (rhs.GetX() * lhs.GetY());
  return vector_product;
}

Vector operator*(const Vector& lhs, const int64_t& rhs) {
  Vector copy = lhs;
  copy *= rhs;
  return copy;
}

////////////////// Point //////////////////

Point::Point() : x_cordinate_(0), y_cordinate_(0) {}

Point::Point(const int64_t& x_cordinate, const int64_t& y_cordinate)
    : x_cordinate_(x_cordinate), y_cordinate_(y_cordinate) {}

int64_t Point::GetX() const { return x_cordinate_; }

int64_t Point::GetY() const { return y_cordinate_; }

void Point::Move(const Vector& vector) {
  x_cordinate_ += vector.GetX();
  y_cordinate_ += vector.GetY();
}

bool Point::ContainsPoint(const Point& point) const {
  return point.GetX() == x_cordinate_ && point.GetY() == y_cordinate_;
}

bool Point::CrossSegment(const Segment& segment) const {
  Vector tmp_1 = *this - segment.GetA();
  Vector tmp_2 = *this - segment.GetB();
  Vector seg_vector = segment.GetA() - segment.GetB();
  return (tmp_1 ^ seg_vector) == 0 && (tmp_2 ^ seg_vector) == 0 &&
         tmp_1.GetX() * tmp_2.GetX() <= 0 && tmp_1.GetY() * tmp_2.GetY() <= 0;
}

IShape* Point::Clone() {
  Point* copy = new Point(*this);
  return copy;
}

Vector operator-(const Point& lhs, const Point& rhs) {
  Vector result(lhs.GetX() - rhs.GetX(), lhs.GetY() - rhs.GetY());
  return result;
}

////////////////// Segment //////////////////

Segment::Segment() {}

Segment::Segment(const Point& first, const Point& second)
    : first_(first), second_(second) {}

Point Segment::GetA() const { return first_; }

Point Segment::GetB() const { return second_; }

bool Point::operator==(const Point& other) const {
  return x_cordinate_ == other.x_cordinate_ &&
         y_cordinate_ == other.y_cordinate_;
}

void Segment::Move(const Vector& vector) {
  first_.Move(vector);
  second_.Move(vector);
}

bool Segment::ContainsPoint(const Point& point) const {
  return point.CrossSegment(*this);
}

bool Segment::CrossSegment(const Segment& segment) const {
  Vector seg = second_ - first_;
  Vector other_seg = segment.GetB() - segment.GetA();

  if ((seg ^ other_seg) == 0) {
    return ContainsPoint(segment.GetA()) || ContainsPoint(segment.GetB()) ||
           segment.ContainsPoint(first_) || segment.ContainsPoint(second_);
  }

  Vector tmp_1 = segment.GetA() - first_;
  Vector tmp_2 = segment.GetB() - first_;
  Vector other_tmp_1 = first_ - segment.GetA();
  Vector other_tmp_2 = second_ - segment.GetA();
  return (seg ^ tmp_1) * (seg ^ tmp_2) <= 0 &&
         (other_seg ^ other_tmp_1) * (other_seg ^ other_tmp_2) <= 0;
}

IShape* Segment::Clone() {
  Segment* copy = new Segment(*this);
  return copy;
}

////////////////// Line //////////////////

Line::Line() { RecalculateLine(); }

Line::Line(const Point& first, const Point& second)
    : first_(first), second_(second) {
  RecalculateLine();
}

int64_t Line::GetA() const { return a_value_; }

int64_t Line::GetB() const { return b_value_; }

int64_t Line::GetC() const { return c_value_; }

void Line::Move(const Vector& vector) {
  first_.Move(vector);
  second_.Move(vector);
  RecalculateLine();
}

bool Line::ContainsPoint(const Point& point) const {
  return point.GetX() * a_value_ + point.GetY() * b_value_ + c_value_ == 0;
}

bool Line::CrossSegment(const Segment& segment) const {
  Vector seg = second_ - first_;
  Vector tmp_1 = segment.GetA() - first_;
  Vector tmp_2 = segment.GetB() - first_;
  return (seg ^ tmp_1) * (seg ^ tmp_2) <= 0;
}

IShape* Line::Clone() {
  Line* copy = new Line(*this);
  return copy;
}

void Line::RecalculateLine() {
  a_value_ = second_.GetY() - first_.GetY();
  b_value_ = first_.GetX() - second_.GetX();
  c_value_ = (-b_value_) * first_.GetY() - a_value_ * first_.GetX();
}

////////////////// Ray //////////////////

Ray::Ray() {}

Ray::Ray(const Point& first, const Point& second)
    : point_(first), point_2_(second), vector_(second - first) {}

Point Ray::GetA() const { return point_; }

Vector Ray::GetVector() const { return vector_; }

void Ray::Move(const Vector& vector) { point_.Move(vector); }

bool Ray::ContainsPoint(const Point& point) const {
  Vector tmp = point - point_;
  return tmp.GetX() * vector_.GetX() + tmp.GetY() * vector_.GetY() >= 0 &&
         (vector_ ^ tmp) == 0;
}

bool Ray::CrossSegment(const Segment& segment) const {
  Line line_1(point_, point_2_);
  if (!line_1.CrossSegment(segment)) {
    return false;
  }
  Line line_2(segment.GetA(), segment.GetB());

  int64_t div = (line_1.GetA() * line_2.GetB() - line_2.GetA() * line_1.GetB());

  double point_x =
      (line_1.GetB() * line_2.GetC() - line_2.GetB() * line_1.GetC());
  double point_y =
      ((line_1.GetC() * line_2.GetA() - line_2.GetC() * line_1.GetA()));

  if (div == 0) {
    return true;
  }

  Point point(point_x / div, point_y / div);
  Vector tmp = point - point_;

  return tmp.GetX() * vector_.GetX() >= 0 && tmp.GetY() * vector_.GetY() >= 0;
}

IShape* Ray::Clone() {
  Ray* copy = new Ray(*this);
  return copy;
}

////////////////// Circle //////////////////

Circle::Circle() : radius_(0) {}

Circle::Circle(const Point& centre, const size_t& radius)
    : centre_(centre), radius_(radius) {}

Point Circle::GetCentre() const { return centre_; }

size_t Circle::GetRadius() const { return radius_; }

void Circle::Move(const Vector& vector) { centre_.Move(vector); }

bool Circle::ContainsPoint(const Point& point) const {
  return std::pow(point.GetX() - centre_.GetX(), 2) +
             std::pow(point.GetY() - centre_.GetY(), 2) <=
         std::pow(radius_, 2);
}

bool Circle::CrossSegment(const Segment& segment) const {
  Vector tmp = segment.GetB() - segment.GetA();
  return (std::abs(tmp ^ (centre_ - segment.GetA())) / tmp.GetLength()) <=
             radius_ &&
         ((centre_ - segment.GetA()).GetLength() >= radius_ ||
          (centre_ - segment.GetB()).GetLength() >= radius_);
}

IShape* Circle::Clone() {
  Circle* copy = new Circle(*this);
  return copy;
}
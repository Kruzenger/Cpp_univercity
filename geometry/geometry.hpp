#include <math.h>
#include <stdint.h>
#include <stdio.h>

////////////////// Vector //////////////////

class Vector {
 public:
  Vector();
  Vector(const int64_t& x_cordinate, const int64_t& y_cordinate);
  Vector(const Vector& other) = default;
  Vector& operator=(const Vector& other) = default;

  ~Vector() = default;

  Vector& operator+=(const Vector& other);
  Vector& operator-=(const Vector& other);
  Vector& operator*=(const int64_t& other);
  Vector operator-() const;

  int64_t GetX() const;
  int64_t GetY() const;

  double GetLength() const;

 private:
  int64_t x_cordinate_;
  int64_t y_cordinate_;
};

Vector operator+(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& lhs, const Vector& rhs);
int64_t operator*(const Vector& lhs, const Vector& rhs);
int64_t operator^(const Vector& lhs, const Vector& rhs);

Vector operator*(const Vector& lhs, const int64_t& rhs);

////////////////// Shapes //////////////////

class IShape;
class Point;
class Segment;
class Line;
class Ray;
class Circle;

////////////////// IShape //////////////////

class IShape {
 public:
  virtual ~IShape() = default;

  virtual void Move(const Vector& vector) = 0;
  virtual bool ContainsPoint(const Point& point) const = 0;
  virtual bool CrossSegment(const Segment& segment) const = 0;
  virtual IShape* Clone() = 0;

 private:
};

////////////////// Point //////////////////

class Point : public IShape {
 public:
  Point();
  Point(const int64_t& x_cordinate, const int64_t& y_cordinates);

  int64_t GetX() const;
  int64_t GetY() const;

  bool operator==(const Point& other) const;

  void Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossSegment(const Segment& segment) const override;
  IShape* Clone() override;

 private:
  int64_t x_cordinate_;
  int64_t y_cordinate_;
};

Vector operator-(const Point& lhs, const Point& rhs);

////////////////// Segment //////////////////

class Segment : public IShape {
 public:
  Segment();
  Segment(const Point& first, const Point& second);

  Point GetA() const;
  Point GetB() const;

  void Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossSegment(const Segment& segment) const override;
  IShape* Clone() override;

 private:
  Point first_;
  Point second_;
};

////////////////// Line //////////////////

class Line : public IShape {
 public:
  Line();
  Line(const Point& first, const Point& second);

  int64_t GetA() const;
  int64_t GetB() const;
  int64_t GetC() const;

  void Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossSegment(const Segment& segment) const override;
  IShape* Clone() override;

 private:
  void RecalculateLine();

  Point first_;
  Point second_;
  int64_t a_value_;
  int64_t b_value_;
  int64_t c_value_;
};

////////////////// Ray //////////////////

class Ray : public IShape {
 public:
  Ray();
  Ray(const Point& first, const Point& second);

  Point GetA() const;
  Vector GetVector() const;

  void Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossSegment(const Segment& segment) const override;
  IShape* Clone() override;

 private:
  Point point_;
  Point point_2_;
  Vector vector_;
};

////////////////// Circle //////////////////

class Circle : public IShape {
 public:
  Circle();
  Circle(const Point& centre, const size_t& radius);

  Point GetCentre() const;
  size_t GetRadius() const;

  void Move(const Vector& vector) override;
  bool ContainsPoint(const Point& point) const override;
  bool CrossSegment(const Segment& segment) const override;
  IShape* Clone() override;

 private:
  Point centre_;
  size_t radius_;
};

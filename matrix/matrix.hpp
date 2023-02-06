#pragma once

#include <algorithm>
#include <vector>

template <size_t N, size_t M, typename T = int64_t>
class Matrix {
 public:
  Matrix() {
    table_.resize(N);
    for (size_t i = 0; i < N; ++i) {
      table_[i] = std::vector<T>(M, T());
    }
  }

  Matrix(std::vector<std::vector<T>> const kInput) { table_ = kInput; }

  Matrix(const T kElem) {
    table_.resize(N);
    for (size_t i = 0; i < N; ++i) {
      table_[i] = std::vector<T>(M, kElem);
    }
  }

  Matrix(const Matrix& other) { table_ = other.table_; }

  Matrix operator+(const Matrix& other) const {
    Matrix result = *this;
    result += other;
    return result;
  }

  Matrix& operator+=(const Matrix& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        table_[i][j] += other(i, j);
      }
    }
    return *this;
  }

  Matrix operator-(const Matrix& other) const {
    Matrix result = *this;
    result -= other;
    return result;
  }

  Matrix& operator-=(const Matrix& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        table_[i][j] -= other(i, j);
      }
    }
    return *this;
  }

  Matrix operator*(const T& other) const {
    Matrix result = *this;
    result *= other;
    return result;
  }

  Matrix& operator*=(const T& other) {
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < M; ++j) {
        table_[i][j] *= other;
      }
    }
    return *this;
  }

  template <size_t P>
  Matrix<N, P, T> operator*(const Matrix<M, P, T>& second) {
    Matrix<N, P, T> result;
    for (size_t i = 0; i < N; ++i) {
      for (size_t j = 0; j < P; ++j) {
        for (size_t g = 0; g < M; ++g) {
          result(i, j) += table_[i][g] * second(g, j);
        }
      }
    }
    return result;
  }

  Matrix<M, N, T> Transposed() {
    Matrix<M, N, T> result;
    for (size_t i = 0; i < M; ++i) {
      for (size_t j = 0; j < N; ++j) {
        result(i, j) = table_[j][i];
      }
    }
    return result;
  }

  T Trace() { return TraceCalculator().Trace(*this); }

  T& operator()(const size_t kI, const size_t kJ) { return table_[kI][kJ]; }

  T operator()(const size_t kI, const size_t kJ) const {
    return table_[kI][kJ];
  }

  bool operator==(const Matrix& other) const { return table_ == other.table_; }

 private:
  std::vector<std::vector<T>> table_;

  class TraceCalculator {
   public:
    T Trace(Matrix<N, N, T> matrix) {
      T result = T();
      for (size_t i = 0; i < N; ++i) {
        result += matrix(i, i);
      }
      return result;
    }
  };
};

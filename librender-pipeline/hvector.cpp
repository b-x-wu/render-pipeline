#include "hvector.hpp"
#include "vector3.hpp"
#include <stdexcept>

const Vector3 HVector::get_normalized_vector3()
{
  if (this->values[3] == 0)
  {
    throw std::runtime_error("Cannot normalize an hvector whose last coordinate is 0.");
  }
  return (Vector3) { this->values[0] / this->values[3], this->values[1] / this->values[3], this->values[2] / this->values[3] }; 
}

HVector HVector::normalize()
{
  if (this->values[3] == 0)
  {
    throw std::runtime_error("Cannot normalize an hvector whose last coordinate is 0.");
  }
  this->values[0] /= this->values[3];
  this->values[1] /= this->values[3];
  this->values[2] /= this->values[3];
  this->values[3] = 1;
  return *this;
}

bool operator==(const HVector &lhs, const HVector &rhs)
{
  return lhs.values[0] == rhs.values[0] && lhs.values[1] == rhs.values[1] && lhs.values[2] == rhs.values[2] && lhs.values[3] == rhs.values[3];
}

bool operator!=(const HVector &lhs, const HVector &rhs)
{
  return lhs.values[0] != rhs.values[0] || lhs.values[1] != rhs.values[1] || lhs.values[2] != rhs.values[2] || lhs.values[3] != rhs.values[3];
}

/*
 * Vector class
 *  - represents Vector that forms the curve.
 *
 * From CPSC 589
 *
 * Sean Brown
 *
 */


 #include "Vector.h"

Vector::Vector() {

}

 Vector::Vector(double x, double y, double z) {
 	this->x = x;
 	this->y = y;
 	this->z = z;
 }

 Vector Vector::operator*(double arg) {
 	return Vector(this->x*arg, this->y*arg, this->z*arg);
 }

 Vector Vector::operator+(Vector v) {
 	return Vector(v.x + this->x, v.y + this->y, v.z + this->z);
 }

 Vector Vector::operator-(Vector v) {
 	return Vector(v.x - this->x, v.y - this->y, v.z - this->z);
 }
 
 Vector Vector::operator/(double arg) {
   return Vector(this->x / arg, this->y / arg, this->z / arg);
 }
 
 bool Vector::operator==(Vector x) {
   return (x.getX() == this->x) && (x.getY() == this->y) && (x.getZ() == this->z);
 }

double Vector::getX() {
	return this->x;
}

double Vector::getY() {
	return this->y;
}

double Vector::getZ() {
	return this->z;
}

void Vector::setX(double x) {
	this->x = x;
}

void Vector::setY(double y) {
	this->y = y;
}

void Vector::setZ(double z) {
	this->z = z;
}

Vector Vector::crossProduct(Vector a, Vector b) {

	double x = (a.y * b.y) - (a.z * b.z);
	double y = (a.z * b.x) - (a.x * b.z);
	double z = (a.x * b.y) - (a.y * b.x);

	return Vector(x, y, z);
}

double Vector::dotProduct(Vector a, Vector b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

double Vector::length() {
	return sqrt(x * x + y * y + z * z);
}

void Vector::normalize() {
	double len = this->length();

	if(len == 0)
		return;

	if(x != 0 || y != 0 || z != 0) {
		this->x = x / len;
		this->y = y / len;
		this->z = z / len;
	}
}

void Vector::print() {
  printf("%.2f %.2f %.2f\n", x, y, z);
}

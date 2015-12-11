#include "Circle.h"
#include <sstream>

using std::stringstream;

Circle::Circle(int cx, int cy, int radius)
	: Shape("circle"), centerX(cx), centerY(cy), radius(radius){
	generateBoundingBox();
}

string Circle::print() {
	std::ostringstream oss;
	oss << name() << "(" << centerX << "," << centerY << "," << radius << ")";
	return oss.str();
}

void Circle::generateBoundingBox(){
	_boundingBox = BoundingBox(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
}

int Circle::area() const {
	return 3 * radius * radius;
}

string Circle::describe() {
	stringstream ss;

	ss << "C(" << centerX << "," << centerY << "," << radius << ")" ;

	return ss.str();
}

void Circle::recalculateBoundingBox() {
    this->generateBoundingBox();
}

void Circle::translation(QPoint translationLength) {
    this->centerX += translationLength.x();
    this->centerY += translationLength.y();
    this->generateBoundingBox();
}

QPoint Circle::getPosition() {
	return QPoint(this->centerX,this->centerY);
}

void Circle::setPosition(QPoint position) {
	this->centerX = position.x();
	this->centerY = position.y();
}

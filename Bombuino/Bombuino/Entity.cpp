// 
// 
// 

#include "Entity.h"


const int& Entity::getX() const {
	return _x;
}

void Entity::setX(const int& x) {
	_x = x;
}

const int& Entity::getY() const {
	return _y;
}

void Entity::setY(const int& y) {
	_y = y;
}

const int& Entity::getWidth() const {
	return _width;
}

void Entity::setWidth(const int& width) {
	_width = width;
}

const int& Entity::getHeight() {
	return _height;
}

void Entity::setHeight(const int& height) {
	_height = height;
}

const TypeEntity& Entity::getTypeEntity() {
	return _typeEntity;
}
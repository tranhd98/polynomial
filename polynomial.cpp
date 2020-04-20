// Name: Hung Duc Tran
// Class: CSC2431
// Project: Polynomial functions
// Description: create function with Arithmetic operators such as sum, subtract, divide, multiple, evaluate, derive, integrate. And create destructor.
// Date: 04/19/2020
#include "polynomial.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cfloat>
#include<cmath>

using std::istream;
using std::ostream;
using std::string;
using std::stringstream;
using std::fixed;
using std::setprecision;
using std::showpos;

Polynomial::Polynomial(size_t degree) : _degree(degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = 0.0;
	}
}
Polynomial::Polynomial(size_t degree, const float* coefficients): _degree(degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = coefficients[i];
	}
}
Polynomial::Polynomial(const Polynomial& polynomial): _degree(polynomial._degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = polynomial._coefficients[i];
	}
}
Polynomial::~Polynomial(){
	if(_coefficients != nullptr)
	    delete [] _coefficients;
	}

const Polynomial Polynomial::Sum(const Polynomial& rhs)const{
    // check _degree
    size_t tempDegree;
    if(_degree >= rhs._degree)
        tempDegree = _degree;
    else
        tempDegree = rhs._degree;
    Polynomial retVal(tempDegree);
    for (size_t i = 0; i < tempDegree + 1; i++) {
        size_t rhsLim = rhs._degree + 1;
        size_t selfLim = _degree + 1;
        float r = 0.0f, l = 0.0f;
        if(i < rhsLim) { // check if i > rhsLim -> memory leak
            r = rhs._coefficients[i];
        }
        else {
            r = 0.0;
        }
        if(i < selfLim){ // check if i > thisLim -> memory leak
            l = _coefficients[i];
        }
        else{
            l = 0.0;
        }
        retVal._coefficients[i] = l + r; // sum of _coefficients and rhs _coefficients
    }
    return retVal;
}
const Polynomial Polynomial::Subtract(const Polynomial& rhs)const{
    size_t tempDegree;
    if(_degree > rhs._degree)
        tempDegree = _degree;
    else
        tempDegree = rhs._degree;
    Polynomial retVal(tempDegree);
    for (size_t i = 0; i < tempDegree + 1; i++) {
        size_t rhsLim = rhs._degree + 1;
        size_t selfLim = _degree + 1;
        float r = 0.0f, l = 0.0f;
        if (i < rhsLim) { // check if i > rhsLim -> memory leak
            r = rhs._coefficients[i];
        }
        else {
            r = 0.0f;
        }
        if (i < selfLim) { // check if i > thisLim -> memory leak
            l = _coefficients[i];
        }
        else {
            l = 0.0;
        }
        retVal._coefficients[i] = l - r; // subtract of _coefficients and rhs _coefficients
    }
    return retVal;
}
const Polynomial Polynomial::Minus()const{
	Polynomial retVal(*this);
	for (size_t i = 0; i < _degree + 1; i++) {
		retVal._coefficients[i] *= -1;
	}
	return retVal;
}
const Polynomial Polynomial::Multiply(const Polynomial& rhs)const{
    size_t tempDegree;
    tempDegree = _degree + rhs._degree;
    Polynomial retVal(tempDegree);
    for (size_t i = 0; i <= _degree; i++) {
        for (size_t j = 0; j <= rhs._degree; j++) {
            retVal._coefficients[i + j] += _coefficients[i] * rhs._coefficients[j];
        }
    }
    return retVal;
}
const Polynomial Polynomial::Divide(const Polynomial& rhs)const{
    if(_degree < rhs._degree) // check if _degree < rhs._degree
	    return Polynomial(0); // return value 0 with degree 0
    size_t degree = _degree - rhs._degree;
	Polynomial retVal(degree);
    size_t i = degree;
    for(int j = _degree; j > 0; j--){
        for(int z = rhs._degree; z > 0; z--){
            if (rhs._coefficients[z] != 0)
            {
                retVal._coefficients[i] = _coefficients[j] / rhs._coefficients[z];
                _coefficients[j - 1] -= retVal._coefficients[i] * rhs._coefficients[z - 1];
            }
        }
        i--;
    }
    return retVal;
}
const Polynomial Polynomial::Derive()const{
    Polynomial retVal(_degree - 1);
    for(size_t i = 0; i < _degree ;i++){
        size_t tempDegree = i + 1;
        retVal._coefficients[i] = _coefficients[tempDegree] * tempDegree;
    }
    return retVal;
}
float Polynomial::Evaluate(float x)const{
    float numberReturn = 0.0f;
    for(size_t i = 0; i <= _degree; i++){
        numberReturn += _coefficients[i] * pow(x, i); // using pow function from cmath
    }
    return numberReturn;
}
float Polynomial::Integrate(float start, float end)const{
	float numberReturn = 0.0f;
	Polynomial retVal(_degree + 1);
	for(size_t i = 0; i <= _degree; i++){
        retVal._coefficients[i + 1] = _coefficients[i] * 1 / (i + 1);
	}
	numberReturn = retVal.Evaluate(end) - retVal.Evaluate(start);
}

const Polynomial& Polynomial::operator=(const Polynomial& rhs){
	if (&rhs == this){
		return *this;
	}
	if (_degree != rhs._degree){
		if (_coefficients){
			delete[] _coefficients;
		}
		_degree = rhs._degree;
		_coefficients = new float[_degree + 1];
	}
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = rhs._coefficients[i];
	}
	return *this;
}
bool Polynomial::Equals(const Polynomial& rhs)const{
	if (_degree != rhs._degree){
		return false;
	}
	for (size_t i=0; i < _degree; i++){
		if (abs(_coefficients[i] - rhs._coefficients[i]) > 0.0001){
			return false;
		}
	}
	return true;
}
string Polynomial::ToString()const{
	stringstream ss;
	for (size_t i = _degree; i > 0; i--) {
		ss << showpos << fixed << setprecision(2) << _coefficients[i] << "x^" << i << " ";
	}
	ss << showpos << fixed << setprecision(2) << _coefficients[0];
	return ss.str();
}
ostream& Polynomial::Write(ostream& output)const{
	output << _degree << " ";
	for (size_t i = 0; i < _degree + 1; i++) {
		output << _coefficients[i] << " ";
	}
	return output;
}
istream& Polynomial::Read(istream& input){
	size_t degree;
	input >> degree;
	if (input.fail()){
		return input;
	}
	float* coefficients = new float[degree + 1];
	for (size_t i = 0; i < degree + 1; i++) {
		input >> coefficients[i];
		if (input.fail()){
			delete[] coefficients;
			return input;
		}
	}

	if (degree != _degree){
		if (_coefficients){
			delete[] _coefficients;
		}
		_degree = degree;
		_coefficients = coefficients;
	}else{
		for (size_t i = 0; i < _degree + 1; i++) {
			_coefficients[i] = coefficients[i];
		}
		delete[] coefficients;
	}
	return input;
}

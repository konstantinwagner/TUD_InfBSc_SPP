//
// Created by vincent on 25.11.17.
//

#include "komplex.h"
#include <iostream>
#include <cmath>


komplex::komplex(double re, double im) {
    this->re = re;
    this->im = im;
}

komplex::~komplex() = default;

double komplex::getRe() {
    return this->re;
}

double komplex::getIm() {
    return this->im;
}

void komplex::setRe(double re) {
    this->re = re;
}

void komplex::setIm(double im) {
    this->im = im;
}

void komplex::add(komplex * zahl) {
    re += zahl->getRe();
    im += zahl->getIm();
}

void komplex::mult(komplex * zahl) {
    double tmp_re = re * zahl->getRe() - im * zahl->getIm();
    double tmp_im = re * zahl->getIm() + im * zahl->getRe();
    re = tmp_re;
    im = tmp_im;
}

int komplex::norm() {
    return (int) sqrt(pow(re, 2)+pow(im, 2));
}

// Zusatz-Methoden
void komplex::print() {
    std::cout << "(" << re << ", " << im << ")"<< std::endl;
}

void komplex::printNorm() {
    std::cout << norm() << std::endl;
}
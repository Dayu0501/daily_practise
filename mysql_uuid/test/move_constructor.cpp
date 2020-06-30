//
// Created by yulichao on 2020/6/30.
//

#pragma once
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

class IntArray {
public:
    //constructor
    explicit IntArray(size_t len) : _length(len), _element(new int[len]) {
        cout << "In Constructor: _length=" << len << endl;
    }

    IntArray()
            : _length(0)
            , _element(nullptr) {

    }

    // deconstructor
    ~IntArray() {
        if (_element != nullptr) {
            cout << "Deconstructor - Delete element......" << endl;
            delete[] _element;
            _length = 0;
        }
    }

    // copy constructor
    IntArray(const IntArray& other) :_length(other._length) , _element(new int[other.length()]) {
        cout << "In Copy Constructor!!" << endl;

        memcpy(_element, other._element, _length);
    }

    // copy assignment operator
    IntArray& operator=(const IntArray& other) {
        cout << "In Copy Assignment operator!" << endl;

        if (this != &other) {
            delete[] _element;
            _length = other._length;
            _element = new int[_length];
            memcpy(_element, other._element, _length);
        }

        return *this;
    }

    IntArray(IntArray&& other) noexcept : _length(0), _element(nullptr) {
        _length = other._length;
        _element = other._element;

        other._length = 0;
        other._element = nullptr;
    }

    IntArray& operator=(IntArray&& other) noexcept {
        if (this != &other) {
            if (!_element)
                delete[] _element;

            _element = other._element;
            _length = other._length;

            other._length = 0;
            other._element = nullptr;
        }

        return *this;
    }

    size_t length() const {
        return _length;
    }
    int * element() const {
        return _element;
    }
public:
    size_t _length;
    int * _element;
};




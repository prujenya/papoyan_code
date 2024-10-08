// Definition of vector i/o functions

#ifndef VECTORIO_H
#define VECTORIO_H

//---------------------------------------------------------------------------

//#include <stdlib.h>

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

//---------------------------------------------------------------------------

template <class T>
ostream & operator<< (ostream &os, const vector< vector<T> > &v)
{
	if ( v.size()==0 ) return os << "{}";
	os << "{" << endl << v[0];
	for (unsigned int i = 1; i < v.size(); i++) os << ", " << endl << v[i] ;
	os << endl << "}";
	return os;
};

template <class T>
ostream & operator<< (ostream &os, const vector<T> &v)
{
	if ( v.size()==0 ) return os << "{}";
	os << "{" << v[0];
	for (int i = 1; i < v.size(); i++) os  << ", " << v[i];
	os << "}";
	return os;
};

#endif

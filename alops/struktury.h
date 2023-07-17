#pragma once
/**
@file struktury.h
*/

#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <map>
#include <vector>
#include <string>

/** 
@brief Struktura reprezentuje element i jego wartosci.
Struktura przechowuje informacje o elemencie ukladu:
- typ (rezystor, zrodlo SEM, zrodlo SPM)
- umiejscowienie (wezel poczatkowy, wezel koncowy)
- wartosc
- odlozone napiecie
- prad przeplywajacy przez element
- moc wydzielona
*/
struct element
{
	char typ;
	std::pair<int, int> umiejscowienie;
	double wartosc, napiecie, prad, moc;
};

typedef
std::vector<std::vector<double>> macierz;


//class element 
//{
//	std::pair<int, int> umiejscowienie;
//	std::complex<double> wartosc;
//	std::complex<double> napiecie;
//	std::complex<double> prad;
//	std::complex<double> moc; 
//	virtual double wyznacz_I();
//};
//
//class E : public element
//{
//	public:
//	std::complex<double> wyznacz_I() override;
//};
//class R : public element
//{
//	public:
//	std::complex<double> wyznacz_I() override;
//};

#endif

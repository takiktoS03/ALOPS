#pragma once
/**
@file funkcje.h
*/

// DECLARATIONS (HEADERS) OF FUNCTIONS 

#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <string>
#include <vector>
#include <set>
#include <unordered_map>

#include "struktury.h"

/**
@brief Funkcja glowna programu
@return int
@param [in] liczba_param Liczba parametrow
@param [in] param[] Tablica parametrow
*/
int main(int liczba_param, char* param[]);

/** 
@brief Funkcja odczytuje elementy z pliku tekstowego.
@details na podstawie wprowadzonych danych w formacie <typ>,<wezel poczatkowy>,<wezel koncowy>,<wartosc>.
@return std::vector<element> Wektor elementow
@param [in] nazwa_pliku Nazwa pliku wejsciowego
*/
std::vector<element> odczyt_wejscia(const std::string& nazwa_pliku);

//void wypisz_elementy(const std::vector<element>& elementy);

/**
@brief Funkcja tworzy kontener unikalnych wezlow z obwodu
@details wpisujac kazdy wezel elementu w sposob posortowany od najmniejszych do najwiekszych wartosci.
@return  Kontener wezlow obwodu
@param [in] elementy Wektor elementow
*/
std::set<int> wektor_wezlow(const std::vector<element>& elementy);

/**
@brief Funkcja dodaje niwelujace sie rezystory na galaz z SEM.
@details Funkcja dodaje rezystor o wartosci -1 obok galezi ze zrodlem elektromotorycznym, aby pozniej traktowac galaz z SEM jako galaz z opornoscia 1 om.
@return std::vector<element> Wektor elementow z nowymi ujemnymi rezystorami
@param [in] elementy Wektor elementow
*/
std::vector<element> dodaj_rez_obok_sem(std::vector<element>& elementy, const std::set<int>& wezly);

/**
@brief Funkcja tworzy macierz (uklad rownan) za pomoca metody Coltriego.
@details Funkcja wprowadza do macierzy wspolczynniki kazdego potencjalu uzywajac metody potencjalow wezlowych.
Napotkane galezie ze zrodlem elektromotorycznym traktuje jako galezie z opornoscia 1 om.
Funkcja tworzy takze mape wezlow na podstawie kontenera tworzonego w wektor_wezlow(), tak aby zaczynaly sie od 0 do n.
@return std::pair<macierz, std::unordered_map<int, int>> Para macierzy (wektora wektorow) i mapy stare2nowe
@param [in] elementy Wektor elementow
@param [in] wezly Kontener wezlow z obwodu
*/
std::pair<macierz, std::unordered_map<int, int>> coltri(const std::vector<element>& elementy, const std::set<int>& wezly);

//void wypisz(const macierz& potencjaly);

/**
@brief Funkcja oblicza macierz za pomoca metody eliminacji Gaussa-Jordana-Crouta.
@details Funkcja sprowadza macierz do postaci trojkatnej (uzyskuje zero nad i pod przekatna macierzy).
Zamienia wiersze (rownanie) z innym wierszem, w ktorym wystepuje wiekszy wspolczynnik w kolumnie.
Metoda ta sprowadza macierz rozszerzona ukladu rownan do postaci bazowej (macierzy jednostkowej).
Z tej postaci mozna wprost odczytac potencjaly w wezlach.
@return std::unordered_map<int, double> Mapa potencjalow w wezlach
@param [in] uklad_rownan_i_mapa Para macierzy i mapy stare2nowe
@param [in] wezly Kontenera wezlow obwodu
*/
std::unordered_map<int, double> gauss(const std::pair<macierz, std::unordered_map<int, int>>& uklad_rownan_i_mapa, const std::set<int>& wezly);

/**
@brief Funkcja oblicza prad na kazdym elemencie.
@details Wykorzystuje do tego obliczone wczesniej potencjaly w kazdym wezle obwodu.
Jesli prad jest dodatni, to plynie od wezla poczatkowego do koncowego elementu. Jesli ujemny, to na odwrot.
@param [in] elementy Wektor elementow
@param [in] potencjaly Mapa potencjalow wezlowych
@param [out] Zwraca wektor elementow uzupelniony o prad dla kazdego elementu
*/
void licz_prady(std::vector<element>& elementy, std::unordered_map<int, double>& potencjaly);

/**
@brief Funkcja oblicza odlozone napiecie na kazdym elemencie.
@details Wykorzystuje do tego obliczony wczesniej prad (dla rezystora) lub mape potencjalow wezlowych dla zrodel.
@param [in] elementy Wektor elementow
@param [in] potencjaly Mapa potencjalow wezlowych
@param [out] Zwraca wektor elementow uzupelniony o odlozone dla kazdego elementu
*/
void licz_napiecia(std::vector<element>& elementy, std::unordered_map<int, double>& potencjaly);

/**
@brief Funkcja oblicza moc wydzielona na kazdym elemencie i bilans obwodu.
@details Wykorzystuje do tego obliczone wczesniej prad i napiecie na kazdym elemencie obwodu.
Jesli moc jest dodatnia, to znaczy, ze element pobiera energie. Jesli ujemna, to znaczy, ze ja oddaje.
Funkcja oblicza bilans mocy na podstawie mocy oddanej lub pobranej dla kazdego elementu.
@param [in] elementy Wektor elementow
@param [out] Zwraca wektor elementow uzupelniony o moc dla kazdego elementu
*/
void licz_moce(std::vector<element>& elementy);

/**
@brief Funkcja wypisuje wszystkie elementy obwodu, ich parametry i bilans obwodu.
@details Funkcja wypisuje do pliku wyjscia charakterystyke kazdego elementu.
Funkcja oblicza bilans mocy na podstawie mocy oddanej lub pobranej dla kazdego elementu.
@param [in] nazwa_pliku Nazwa pliku wyjsciowego
@param [in] elementy Wektor elementow
*/
void zapis_wyjscia(const std::string& nazwa_pliku, const std::vector<element>& elementy);

#endif

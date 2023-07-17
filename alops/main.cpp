/**
@file main.cpp
*/

#include <iostream>
#include <string>
#include <map>


#include "struktury.h"
#include "funkcje.h"

int main(int liczba_param, char * param[])
{
	std::string plik_wejscia, plik_wyjscia;
//	std::cout << std::endl;
//	std::cout << "Liczba parametrow: " << ilosc_param << std::endl;
//	std::cout << "Nazwa programu: " << param[0] << std::endl;
	for (std::size_t i = 0; i < liczba_param; i++)
	{
		//std::cout << "[" << i << "] " << param[i] << std::endl;
		if (std::string(param[i]) == "-i")
		{
			if (i + 1 < liczba_param)
			{
				plik_wejscia = param[i + 1];	// -i plik wejściowy z obwodem
			}
		}
		else if (std::string(param[i]) == "-o")
		{
			if (i + 1 < liczba_param)
			{
				plik_wyjscia = param[i + 1];	// -o plik wyjściowy z wyliczonymi wartościami
			}
		}
	}
	if (liczba_param == 5 && !plik_wejscia.empty() && !plik_wyjscia.empty())
	{
		std::vector<element> elementy = odczyt_wejscia(plik_wejscia);
		if (elementy.empty())
			return 0; // nie ma czego liczyc
		
		std::set<int> wezly = wektor_wezlow(elementy);
		elementy = dodaj_rez_obok_sem(elementy, wezly);
		//wypisz_elementy(elementy);
		wezly = wektor_wezlow(elementy);
		std::pair<macierz, std::unordered_map<int, int>> uklad_rownan_i_mapa = coltri(elementy, wezly);
		std::unordered_map<int, double> potencjaly = gauss(uklad_rownan_i_mapa, wezly);
		licz_prady(elementy, potencjaly);
		licz_napiecia(elementy, potencjaly);
		licz_moce(elementy);
		zapis_wyjscia(plik_wyjscia, elementy);
		/*std::cout << std::endl << "numery wezlow (stare + dodane rez): ";
		for (auto& i : wezly)
		{
			std::cout << i << " ";
		}
		std::cout << std::endl << "napiecia na wezlach: ";
		for (auto& i : potencjaly)
		{
			std::cout << i.first << ": " << i.second << "V ";
		}*/
	}
	else
	{
		std::cout << "///////////////ALOPS///////////////" << std::endl
			<< "Program sluzy do analizy liniowych obwodow pradu stalego" << std::endl
			<< "Sposob uzycia:" << std::endl
			<< "./alops [-i]  nazwa_pliku_wejsciowego [-o] nazwa_pliku_wyjsciowego" << std::endl
			<< "Po przelaczniku (-i lub -o) nalezy wpisac sciezke do pliku wejscia/wyjscia" << std::endl;
	}
	return 0;
}

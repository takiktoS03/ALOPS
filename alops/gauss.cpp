/**
@file gauss.cpp
*/

#include <iostream>
#include <unordered_map>
#include <set>
#include <cmath>
#include "struktury.h"
#include "funkcje.h"

std::unordered_map<int, double> gauss(const std::pair<macierz, std::unordered_map<int, int>>& uklad_rownan_i_mapa, const std::set<int>& wezly)
{
	macierz gauss = uklad_rownan_i_mapa.first;
	std::unordered_map<int, double> nowe2stare;
	std::unordered_map<int, int> stare2nowe = uklad_rownan_i_mapa.second;
	double a;
	std::size_t n = gauss.size();
	/*std::vector<int> nr_wiersza;
	for (int i = 0; i < n; i++)
	{
		nr_wiersza.push_back(i);
	}*/
	for (int i = 0; i < n; i++)
	{
		int ielmax = i;// indeks wiersza, w ktorym znajduje sie element max
		double elmax = fabs(gauss[i][i]);// element max to wartosc bezwzgledna z jakiegos* elementu w kolumnie
		for (int j = i; j < n; j++)
		{// *jakis, znaczy najwiekszy w kolumnie pod wzgledem modulu
			if (fabs(gauss[j][i]) > elmax)
			{
				elmax = fabs(gauss[j][i]);
				ielmax = j;
			}
		}
		if (elmax == 0)
		{
			std::cout << "Macierz osobliwa (wyznacznik = 0), nie da sie obliczyc zmiennych\n";
			return nowe2stare;
		}
		if (ielmax != i)
		{// Zamiana wierszy (r�wna�) "i" z "ielmax"
			std::vector<double> temp = gauss[i];
			gauss[i] = gauss[ielmax];
			gauss[ielmax] = temp;
			/*int temp2 = nr_wiersza[i];
			nr_wiersza[i] = nr_wiersza[ielmax];
			nr_wiersza[ielmax] = temp2;*/
		}
		for (int j = i + 1; j < n; j++)
		{// postepowanie proste gaussa
			a = gauss[j][i] / gauss[i][i];
			gauss[j][i] = 0;
			for (int k = i + 1; k <= n; k++)
			{
				gauss[j][k] -= a * gauss[i][k];
			}
		}
	}
	if (gauss[n - 1][n - 1] == 0)
	{
		//std::cout << "Macierz osobliwa, nie da sie obliczyc zmiennych\n"; // Nie mieszamy logiki aplikacji z interfejsem uzytkownika
		return nowe2stare;
	}
	for (int i = n - 1; i > 0; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{// postepowanie odwrotne gaussa
			a = gauss[j][i] / gauss[i][i];
			for (int k = n; k >= 0; k--)
			{
				gauss[j][k] -= a * gauss[i][k];
			}
		}
	}
	for (int w = 0; w < n; w++)
	{// normalizowanie wierszy
		if (gauss[w][w] != 1)
		{
			a = 1 / gauss[w][w];
			for (int j = 0; j <= n; j++)
			{
				gauss[w][j] *= a;
			}
		}
	}
	//wypisz(gauss);
	//std::cout << std::endl;
	std::vector<double> napiecia{ 0 };
	for (int i = 0; i < n; i++)
	{
		napiecia.push_back(gauss[i][n]);
	}
	for (auto iter = stare2nowe.begin(); iter != stare2nowe.end(); iter++)
	{
		nowe2stare[iter->first] = napiecia[iter->second];
	}
	return nowe2stare;
}

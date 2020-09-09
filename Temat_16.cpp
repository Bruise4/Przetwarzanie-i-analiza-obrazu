/*
Przetwarzanie i Analiza Obrazu

Projekt:
16.ZnajdŸ i zaznacz obwód trójek na zdjêciu. Policz liczbê czarnych symboli i je zaznacz.
Zidentyfikuj karty 7 kier i 3 trefl oraz po³¹cz ich œrodki.

Etap II

MATEUSZ GUZEK
GUZEK.MATEUSZ.4@GMAIL.COM

*/

#include "Temat_16.h"

void Mono(Image3CH& rgbImg, Image1CH& grayImg) //Przyk³ad 
{
	using namespace std;
	//Sprawdzenie rozmiarów
	if (rgbImg.width() == grayImg.width() && rgbImg.height() == grayImg.height())
	{
		for (int i = 0; i < rgbImg.width(); i++)
			for (int j = 0; j < rgbImg.height(); j++)
			{
				// I = (1/3)*(R+G+B) (i,j) - (number of row, number of col)
				grayImg(i, j).Intensity() = (rgbImg(i, j).Red() + rgbImg(i, j).Green() + rgbImg(i, j).Blue()) / 3;
			}
	}
	else
	{
		cerr << "Rozmiary obrazow roznia sie!" << endl;
		return;
	}
}

void Maksimum1CH(Image1CH& we, Image1CH& wy, int okno_rozmiar)
{
	using namespace std;

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					//Wpisanie do wektora okna czêœci pikseli obrazu wejœciowego
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Intensity();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Intensity() = okno[okno_rozmiar_kwadrat - 1]; //Wpisanie maksymalnej wartoœci intensywnoœci z wektora
				}
				else
				{
					wy(i, j).Intensity() = we(i, j).Intensity();	//Filtracja ramki jest niewymagana przy danych zdjêciach
				}
			}
		}
		delete[] okno;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void Maksimum3CH(Image3CH& we, Image3CH& wy, int okno_rozmiar)
{
	using namespace std;

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					//Red
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Red();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Red() = okno[okno_rozmiar_kwadrat - 1]; //Wpisanie maksymalnej wartoœci intensywnoœci z wektora

					//Green
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Green();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Green() = okno[okno_rozmiar_kwadrat - 1]; //Wpisanie maksymalnej wartoœci intensywnoœci z wektora

					//Blue
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Blue();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Blue() = okno[okno_rozmiar_kwadrat - 1]; //Wpisanie maksymalnej wartoœci intensywnoœci z wektora

				}
				else
				{
					//Filtracja ramki jest niewymagana przy danych zdjêciach
					wy(i, j).Red() = we(i, j).Red();
					wy(i, j).Green() = we(i, j).Green();
					wy(i, j).Blue() = we(i, j).Blue();
				}
			}
		}
		delete[] okno;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void Minimum1CH(Image1CH& we, Image1CH& wy, int okno_rozmiar)
{
	using namespace std;

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					//Wpisanie do wektora okna czêœci pikseli obrazu wejœciowego
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Intensity();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Intensity() = okno[0]; //Wpisanie minimalnej wartoœci intensywnoœci z wektora
				}
				else
				{
					wy(i, j).Intensity() = we(i, j).Intensity();	//Filtracja ramki jest niewymagana przy danych zdjêciach
				}
			}
		}
		delete[] okno;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void Minimum3CH(Image3CH& we, Image3CH& wy, int okno_rozmiar)
{
	using namespace std;

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					//Red
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Red();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Red() = okno[0]; //Wpisanie minimalnej wartoœci intensywnoœci z wektora

					//Green
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Green();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Green() = okno[0]; //Wpisanie minimalnej wartoœci intensywnoœci z wektora

					//Blue
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Blue();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Blue() = okno[0]; //Wpisanie minimalnej wartoœci intensywnoœci z wektora

				}
				else
				{
					//Filtracja ramki jest niewymagana przy danych zdjêciach
					wy(i, j).Red() = we(i, j).Red();
					wy(i, j).Green() = we(i, j).Green();
					wy(i, j).Blue() = we(i, j).Blue();
				}
			}
		}
		delete[] okno;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void Medianowy1CH(Image1CH& we, Image1CH& wy, int okno_rozmiar)
{
	using namespace std;

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna
		int polowa_wektora_okna = (okno_rozmiar_kwadrat - 1) / 2; //D³ugoœæ woktora zawsze nieparzysta

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					//Wpisanie do wektora okna czêœci pikseli obrazu wejœciowego
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Intensity();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Intensity() = okno[polowa_wektora_okna]; //Wpisanie mediany
				}
				else
				{
					wy(i, j).Intensity() = we(i, j).Intensity();	//Filtracja ramki jest niewymagana przy danych zdjêciach
				}
			}
		}
		delete[] okno;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void Medianowy3CH(Image3CH& we, Image3CH& wy, int okno_rozmiar)
{
	using namespace std;

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna
		int polowa_wektora_okna = (okno_rozmiar_kwadrat - 1) / 2; //D³ugoœæ woktora zawsze nieparzysta

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					//Red
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Red();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Red() = okno[polowa_wektora_okna]; //Wpisanie mediany

					//Green
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Green();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Green() = okno[polowa_wektora_okna]; //Wpisanie mediany

					//Blue
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Blue();
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co
					wy(i, j).Blue() = okno[polowa_wektora_okna]; //Wpisanie minimalnej wartoœci intensywnoœci z wektora

				}
				else
				{
					//Filtracja ramki jest niewymagana przy danych zdjêciach
					wy(i, j).Red() = we(i, j).Red();
					wy(i, j).Green() = we(i, j).Green();
					wy(i, j).Blue() = we(i, j).Blue();
				}
			}
		}
		delete[] okno;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void Niskopasmowy1CH(Image1CH& we, Image1CH& wy, int tryb)
{
	/*
	Tryb 1:
	1	1	1
	1	1	1
	1	1	1

	Tryb 2:
	1	1	1	1	1
	1	1	1	1	1
	1	1	1	1	1
	1	1	1	1	1
	1	1	1	1	1
	*/

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int okno_rozmiar;
		if (tryb == 1)
			okno_rozmiar = 3;
		else if (tryb == 2)
			okno_rozmiar = 5;

		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna
		int* okno_filtr = new int[okno_rozmiar_kwadrat]; //Wektor z liczb okna filtra

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					//Wpisanie do wektora okna czêœci pikseli obrazu wejœciowego
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Intensity();
						}
					}

					double suma_intensywnosci = 0;
					int suma_okna = 0;

					switch (tryb)
					{
					case 1:
						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
							okno_filtr[k] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Intensity() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
							okno_filtr[k] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Intensity() = suma_intensywnosci / double(suma_okna);
						break;
					}
				}
				else
				{
					wy(i, j).Intensity() = we(i, j).Intensity();	//Filtracja ramki jest niewymagana przy danych zdjêciach
				}
			}
		}
		delete[] okno;
		delete[] okno_filtr;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void Niskopasmowy3CH(Image3CH& we, Image3CH& wy, int tryb)
{
	/*
	Tryb 1:
	1	1	1
	1	1	1
	1	1	1

	Tryb 2:
	1	1	1	1	1
	1	1	1	1	1
	1	1	1	1	1
	1	1	1	1	1
	1	1	1	1	1
	*/

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int okno_rozmiar;
		if (tryb == 1)
			okno_rozmiar = 3;
		else if (tryb == 2)
			okno_rozmiar = 5;

		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna
		int* okno_filtr = new int[okno_rozmiar_kwadrat]; //Wektor z liczb okna filtra

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					double suma_intensywnosci = 0;
					int suma_okna = 0;

					//Red
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Red();
						}
					}

					switch (tryb)
					{
					case 1:
						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
							okno_filtr[k] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Red() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
							okno_filtr[k] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Red() = suma_intensywnosci / double(suma_okna);
						break;
					}

					//Green
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Green();
						}
					}

					suma_intensywnosci = 0;
					suma_okna = 0;

					switch (tryb)
					{
					case 1:
						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
							okno_filtr[k] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Green() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
							okno_filtr[k] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Green() = suma_intensywnosci / double(suma_okna);
						break;
					}

					//Blue
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Blue();
						}
					}

					suma_intensywnosci = 0;
					suma_okna = 0;

					switch (tryb)
					{
					case 1:
						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
							okno_filtr[k] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Blue() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
							okno_filtr[k] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Blue() = suma_intensywnosci / double(suma_okna);
						break;
					}

				}
				else
				{
					//Filtracja ramki jest niewymagana przy danych zdjêciach
					wy(i, j).Red() = we(i, j).Red();
					wy(i, j).Green() = we(i, j).Green();
					wy(i, j).Blue() = we(i, j).Blue();
				}
			}
		}
		delete[] okno;
		delete[] okno_filtr;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void Wysokopasmowy1CH(Image1CH& we, Image1CH& wy, int tryb)
{
	/*
	Tryb 1:
	-1	-1	-1
	-1	8	-1
	-1	-1	-1

	Tryb 2:
	-1	-2	-1
	-2	12	-2
	-1	-2	-1
	*/

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int okno_rozmiar = 3;
		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna
		int* okno_filtr = new int[okno_rozmiar_kwadrat]; //Wektor z liczb okna filtra

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					//Wpisanie do wektora okna czêœci pikseli obrazu wejœciowego
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Intensity();
						}
					}

					double suma_intensywnosci = 0;
					//int suma_okna = 0;

					switch (tryb)
					{
					case 1:
						okno_filtr[0] = -1;
						okno_filtr[1] = -1;
						okno_filtr[2] = -1;
						okno_filtr[3] = -1;
						okno_filtr[4] = 8;
						okno_filtr[5] = -1;
						okno_filtr[6] = -1;
						okno_filtr[7] = -1;
						okno_filtr[8] = -1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci;
							//suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Intensity() = suma_intensywnosci; //wy(i, j).Intensity() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						okno_filtr[0] = -1;
						okno_filtr[1] = -2;
						okno_filtr[2] = -1;
						okno_filtr[3] = -2;
						okno_filtr[4] = 12;
						okno_filtr[5] = -2;
						okno_filtr[6] = -1;
						okno_filtr[7] = -2;
						okno_filtr[8] = -1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci;
							//suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Intensity() = suma_intensywnosci; //wy(i, j).Intensity() = suma_intensywnosci / double(suma_okna);
						break;
					}
				}
				else
				{
					wy(i, j).Intensity() = we(i, j).Intensity();	//Filtracja ramki jest niewymagana przy danych zdjêciach
				}
			}
		}
		delete[] okno;
		delete[] okno_filtr;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void Wysokopasmowy3CH(Image3CH& we, Image3CH& wy, int tryb)
{
	/*
	Tryb 1:
	-1	-1	-1
	-1	8	-1
	-1	-1	-1

	Tryb 2:
	-1	-2	-1
	-2	12	-2
	-1	-2	-1
	*/

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int okno_rozmiar = 3;
		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna
		int* okno_filtr = new int[okno_rozmiar_kwadrat]; //Wektor z liczb okna filtra

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					double suma_intensywnosci = 0;
					//int suma_okna = 0;

					//Red
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Red();
						}
					}

					switch (tryb)
					{
					case 1:
						okno_filtr[0] = -1;
						okno_filtr[1] = -1;
						okno_filtr[2] = -1;
						okno_filtr[3] = -1;
						okno_filtr[4] = 8;
						okno_filtr[5] = -1;
						okno_filtr[6] = -1;
						okno_filtr[7] = -1;
						okno_filtr[8] = -1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							//suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Red() = suma_intensywnosci; //wy(i, j).Red() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						okno_filtr[0] = -1;
						okno_filtr[1] = -2;
						okno_filtr[2] = -1;
						okno_filtr[3] = -2;
						okno_filtr[4] = 12;
						okno_filtr[5] = -2;
						okno_filtr[6] = -1;
						okno_filtr[7] = -2;
						okno_filtr[8] = -1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							//suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Red() = suma_intensywnosci; //wy(i, j).Red() = suma_intensywnosci / double(suma_okna);
						break;
					}

					//Green
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Green();
						}
					}

					suma_intensywnosci = 0;
					//suma_okna = 0;

					switch (tryb)
					{
					case 1:
						okno_filtr[0] = -1;
						okno_filtr[1] = -1;
						okno_filtr[2] = -1;
						okno_filtr[3] = -1;
						okno_filtr[4] = 8;
						okno_filtr[5] = -1;
						okno_filtr[6] = -1;
						okno_filtr[7] = -1;
						okno_filtr[8] = -1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							//suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Green() = suma_intensywnosci; //wy(i, j).Green() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						okno_filtr[0] = -1;
						okno_filtr[1] = -2;
						okno_filtr[2] = -1;
						okno_filtr[3] = -2;
						okno_filtr[4] = 12;
						okno_filtr[5] = -2;
						okno_filtr[6] = -1;
						okno_filtr[7] = -2;
						okno_filtr[8] = -1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							//suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Green() = suma_intensywnosci; //wy(i, j).Green() = suma_intensywnosci / double(suma_okna);
						break;
					}

					//Blue
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Blue();
						}
					}

					suma_intensywnosci = 0;
					//suma_okna = 0;

					switch (tryb)
					{
					case 1:
						okno_filtr[0] = -1;
						okno_filtr[1] = -1;
						okno_filtr[2] = -1;
						okno_filtr[3] = -1;
						okno_filtr[4] = 8;
						okno_filtr[5] = -1;
						okno_filtr[6] = -1;
						okno_filtr[7] = -1;
						okno_filtr[8] = -1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							//suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Blue() = suma_intensywnosci; //wy(i, j).Blue() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						okno_filtr[0] = -1;
						okno_filtr[1] = -2;
						okno_filtr[2] = -1;
						okno_filtr[3] = -2;
						okno_filtr[4] = 12;
						okno_filtr[5] = -2;
						okno_filtr[6] = -1;
						okno_filtr[7] = -2;
						okno_filtr[8] = -1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							//suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Blue() = suma_intensywnosci; //wy(i, j).Blue() = suma_intensywnosci / double(suma_okna);
						break;
					}

				}
				else
				{
					//Filtracja ramki jest niewymagana przy danych zdjêciach
					wy(i, j).Red() = we(i, j).Red();
					wy(i, j).Green() = we(i, j).Green();
					wy(i, j).Blue() = we(i, j).Blue();
				}
			}
		}
		delete[] okno;
		delete[] okno_filtr;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void RozmycieGaussa1CH(Image1CH& we, Image1CH& wy, int tryb)
{
	/*
	Tryb 1:
	1	2	1
	2	4	2
	1	2	1

	Tryb 2:
	1	1	2	1	1
	1	2	4	2	1
	2	4	8	4	2
	1	2	4	2	1
	1	1	2	1	1
	*/

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int okno_rozmiar;
		if (tryb == 1)
			okno_rozmiar = 3;
		else if (tryb == 2)
			okno_rozmiar = 5;

		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna
		int* okno_filtr = new int[okno_rozmiar_kwadrat]; //Wektor z liczb okna filtra

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					//Wpisanie do wektora okna czêœci pikseli obrazu wejœciowego
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Intensity();
						}
					}

					double suma_intensywnosci = 0;
					int suma_okna = 0;

					switch (tryb)
					{
					case 1:
						okno_filtr[0] = 1;
						okno_filtr[1] = 2;
						okno_filtr[2] = 1;
						okno_filtr[3] = 2;
						okno_filtr[4] = 4;
						okno_filtr[5] = 2;
						okno_filtr[6] = 1;
						okno_filtr[7] = 2;
						okno_filtr[8] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci;
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Intensity() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						okno_filtr[0] = 1;
						okno_filtr[1] = 1;
						okno_filtr[2] = 2;
						okno_filtr[3] = 1;
						okno_filtr[4] = 1;
						okno_filtr[5] = 1;
						okno_filtr[6] = 2;
						okno_filtr[7] = 4;
						okno_filtr[8] = 2;
						okno_filtr[9] = 1;
						okno_filtr[10] = 2;
						okno_filtr[11] = 4;
						okno_filtr[12] = 8;
						okno_filtr[13] = 4;
						okno_filtr[14] = 2;
						okno_filtr[15] = 1;
						okno_filtr[16] = 2;
						okno_filtr[17] = 4;
						okno_filtr[18] = 2;
						okno_filtr[19] = 1;
						okno_filtr[20] = 1;
						okno_filtr[21] = 1;
						okno_filtr[22] = 2;
						okno_filtr[23] = 1;
						okno_filtr[24] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci;
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Intensity() = suma_intensywnosci / double(suma_okna);
						break;
					}
				}
				else
				{
					wy(i, j).Intensity() = we(i, j).Intensity();	//Filtracja ramki jest niewymagana przy danych zdjêciach
				}
			}
		}
		delete[] okno;
		delete[] okno_filtr;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void RozmycieGaussa3CH(Image3CH& we, Image3CH& wy, int tryb)
{
	/*
	Tryb 1:
	1	2	1
	2	4	2
	1	2	1

	Tryb 2:
	1	1	2	1	1
	1	2	4	2	1
	2	4	8	4	2
	1	2	4	2	1
	1	1	2	1	1
	*/

	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		int okno_rozmiar;
		if (tryb == 1)
			okno_rozmiar = 3;
		else if (tryb == 2)
			okno_rozmiar = 5;

		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double* okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna
		int* okno_filtr = new int[okno_rozmiar_kwadrat]; //Wektor z liczb okna filtra

		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹
				{
					double suma_intensywnosci = 0;
					int suma_okna = 0;

					//Red
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Red();
						}
					}

					switch (tryb)
					{
					case 1:
						okno_filtr[0] = 1;
						okno_filtr[1] = 2;
						okno_filtr[2] = 1;
						okno_filtr[3] = 2;
						okno_filtr[4] = 4;
						okno_filtr[5] = 2;
						okno_filtr[6] = 1;
						okno_filtr[7] = 2;
						okno_filtr[8] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Red() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						okno_filtr[0] = 1;
						okno_filtr[1] = 1;
						okno_filtr[2] = 2;
						okno_filtr[3] = 1;
						okno_filtr[4] = 1;
						okno_filtr[5] = 1;
						okno_filtr[6] = 2;
						okno_filtr[7] = 4;
						okno_filtr[8] = 2;
						okno_filtr[9] = 1;
						okno_filtr[10] = 2;
						okno_filtr[11] = 4;
						okno_filtr[12] = 8;
						okno_filtr[13] = 4;
						okno_filtr[14] = 2;
						okno_filtr[15] = 1;
						okno_filtr[16] = 2;
						okno_filtr[17] = 4;
						okno_filtr[18] = 2;
						okno_filtr[19] = 1;
						okno_filtr[20] = 1;
						okno_filtr[21] = 1;
						okno_filtr[22] = 2;
						okno_filtr[23] = 1;
						okno_filtr[24] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Red() = suma_intensywnosci / double(suma_okna);
						break;
					}

					//Green
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Green();
						}
					}

					suma_intensywnosci = 0;
					suma_okna = 0;

					switch (tryb)
					{
					case 1:
						okno_filtr[0] = 1;
						okno_filtr[1] = 2;
						okno_filtr[2] = 1;
						okno_filtr[3] = 2;
						okno_filtr[4] = 4;
						okno_filtr[5] = 2;
						okno_filtr[6] = 1;
						okno_filtr[7] = 2;
						okno_filtr[8] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Green() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						okno_filtr[0] = 1;
						okno_filtr[1] = 1;
						okno_filtr[2] = 2;
						okno_filtr[3] = 1;
						okno_filtr[4] = 1;
						okno_filtr[5] = 1;
						okno_filtr[6] = 2;
						okno_filtr[7] = 4;
						okno_filtr[8] = 2;
						okno_filtr[9] = 1;
						okno_filtr[10] = 2;
						okno_filtr[11] = 4;
						okno_filtr[12] = 8;
						okno_filtr[13] = 4;
						okno_filtr[14] = 2;
						okno_filtr[15] = 1;
						okno_filtr[16] = 2;
						okno_filtr[17] = 4;
						okno_filtr[18] = 2;
						okno_filtr[19] = 1;
						okno_filtr[20] = 1;
						okno_filtr[21] = 1;
						okno_filtr[22] = 2;
						okno_filtr[23] = 1;
						okno_filtr[24] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Green() = suma_intensywnosci / double(suma_okna);
						break;
					}

					//Blue
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = we(x + i - ramka, y + j - ramka).Blue();
						}
					}

					suma_intensywnosci = 0;
					suma_okna = 0;

					switch (tryb)
					{
					case 1:
						okno_filtr[0] = 1;
						okno_filtr[1] = 2;
						okno_filtr[2] = 1;
						okno_filtr[3] = 2;
						okno_filtr[4] = 4;
						okno_filtr[5] = 2;
						okno_filtr[6] = 1;
						okno_filtr[7] = 2;
						okno_filtr[8] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Blue() = suma_intensywnosci / double(suma_okna);
						break;

					case 2:
						okno_filtr[0] = 1;
						okno_filtr[1] = 1;
						okno_filtr[2] = 2;
						okno_filtr[3] = 1;
						okno_filtr[4] = 1;
						okno_filtr[5] = 1;
						okno_filtr[6] = 2;
						okno_filtr[7] = 4;
						okno_filtr[8] = 2;
						okno_filtr[9] = 1;
						okno_filtr[10] = 2;
						okno_filtr[11] = 4;
						okno_filtr[12] = 8;
						okno_filtr[13] = 4;
						okno_filtr[14] = 2;
						okno_filtr[15] = 1;
						okno_filtr[16] = 2;
						okno_filtr[17] = 4;
						okno_filtr[18] = 2;
						okno_filtr[19] = 1;
						okno_filtr[20] = 1;
						okno_filtr[21] = 1;
						okno_filtr[22] = 2;
						okno_filtr[23] = 1;
						okno_filtr[24] = 1;

						for (int k = 0; k < okno_rozmiar_kwadrat; k++)
						{
							suma_intensywnosci = okno[k] * okno_filtr[k] + suma_intensywnosci; //suma_intensywnosci = suma_intensywnosci + okno[k];
							suma_okna = suma_okna + okno_filtr[k];
						}
						wy(i, j).Blue() = suma_intensywnosci / double(suma_okna);
						break;
					}
				}
				else
				{
					//Filtracja ramki jest niewymagana przy danych zdjêciach
					wy(i, j).Red() = we(i, j).Red();
					wy(i, j).Green() = we(i, j).Green();
					wy(i, j).Blue() = we(i, j).Blue();
				}
			}
		}
		delete[] okno;
		delete[] okno_filtr;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void Binaryzacja1CH(Image1CH& we, Image1CH& wy, double prog)
{
	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		/*
		//////////////Algorytm z wyk³adu///////////////////
		//1) Wartoœæ pocz¹tkowa progu
		double sumaIntensity = 0;
		int histogramIlosc = 256;
		double histogram[256];
		for (int i = 0; i < histogramIlosc; i++)	histogram[i] = 0;

		int piksel = 0;
		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				sumaIntensity += we(i, j).Intensity();
				//cout << "Piksel: " << piksel << endl;
				piksel++;
				int histogramIndex = 0;
				while (we(i, j).Intensity() > ( (1/double(histogramIlosc)) * histogramIndex) )
				{
					histogramIndex++;
					//cout << "Histogram indeks" << histogramIndex << endl;
				}
				histogram[histogramIndex]++;
			}
		}

		double srednia = sumaIntensity / piksel;
		cout << "Prog poczatkowy: " << srednia << endl;
		*/


		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (we(i, j).Intensity() > prog)
					wy(i, j).Intensity() = 1;
				else
					wy(i, j).Intensity() = 0;

				//cout << we(i, j).Intensity() << endl;
				//cout << wy(i, j).Intensity() << endl;
			}
		}
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void BinaryzacjaSektorowa1CH(Image1CH& we, Image1CH& wy, int okno_rozmiar, double odciecie)
{
	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		//Z filtra
		int ramka = (okno_rozmiar - 1) / 2; //Gruboœæ ramki w pikselach
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				//Sprawdzenie odciêcia - skrajne wartoœci - przyœpiesza ca³oœæ
				if (we(i, j).Intensity() < odciecie)
				{
					wy(i, j).Intensity() = 0;
				}
				else if (we(i, j).Intensity() > 1 - odciecie)
				{
					wy(i, j).Intensity() = 1;
				}
				else if (i >= ramka && i < we.width() - ramka && j >= ramka && j < we.height() - ramka) // Czy jest poza ramk¹			
				{
					//Próg jakos wartoœæ œrednia z sektora/okna pikseli
					double suma = 0;
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							suma += we(x + i - ramka, y + j - ramka).Intensity();
						}
					}

					double progSredniaSektor = suma / okno_rozmiar_kwadrat;

					if (we(i, j).Intensity() < progSredniaSektor)
					{
						wy(i, j).Intensity() = 0;
					}
					else
					{
						wy(i, j).Intensity() = 1;
					}
				}
				else
				{
					wy(i, j).Intensity() = we(i, j).Intensity();	//Filtracja ramki jest niewymagana przy danych zdjêciach
				}
			}
		}
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}

void SegmentacjaKart1CH(Image1CH& we)  //Zwraca ilosc segmentow
{
	using namespace std;

	//Segmentacja 4 kart
	int segmentId = 1;

	//1 krok
	for (int i = 0; i < SZER; i++)
	{
		for (int j = 0; j < WYS; j++)
		{
			if (we(i, j).Intensity() == 1)
			{
				EtykietyKart[i][j] = segmentId;
				segmentId++;
			}
			else
			{
				EtykietyKart[i][j] = 0;
			}
		}
	}

	//2krok - w jedn¹ stronê   		//Z filtra
	int okno_rozmiar = 3;
	int ramka = (okno_rozmiar - 1) / 2; //Odleg³oœæ od œrodka ramki
	int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
	int* okno = new int[okno_rozmiar_kwadrat]; //Wektor z pikseli okna
	for (int i = 0; i < SZER; i++)
	{
		for (int j = 0; j < WYS; j++)
		{
			if (EtykietyKart[i][j] != 0)
			{
				if (i >= ramka && i < SZER - ramka && j >= ramka && j < WYS - ramka) // Czy jest poza ramk¹
				{
					//Wpisanie do wektora okna czêœci etykiet
					//Z filtra minimum...
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = EtykietyKart[x + i - ramka][y + j - ramka];
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co

					//Minimalne nie 0
					int index = 0;
					while (okno[index] == 0)
						index++;
					EtykietyKart[i][j] = okno[index]; //Wpisanie minimalnej wartoœci z wektora
				}
			}
		}
	}

	//2krok - w drug¹ stronê   	
	for (int i = (SZER - 1); i >= 0; i--)
	{
		for (int j = (WYS - 1); j >= 0; j--)
		{
			if (EtykietyKart[i][j] != 0)
			{
				if (i >= ramka && i < SZER - ramka && j >= ramka && j < WYS - ramka) // Czy jest poza ramk¹
				{
					//Wpisanie do wektora okna czêœci etykiet
					//Z filtra minimum...
					for (int x = 0; x < okno_rozmiar; x++)
					{
						for (int y = 0; y < okno_rozmiar; y++)
						{
							okno[okno_rozmiar * y + x] = EtykietyKart[x + i - ramka][y + j - ramka];
						}
					}
					sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co

					//Minimalne nie 0
					int index = 0;
					while (okno[index] == 0)
						index++;
					EtykietyKart[i][j] = okno[index]; //Wpisanie minimalnej wartoœci z wektora

				}
			}
		}
	}
	delete[] okno;
}

int LiczEtykietyKart()
{
	int* etykiety = new int[SZER * WYS]; //Wektor na wszystkie etykiety
	int liczbaEtykiet = 0;
	for (int i = 0; i < SZER; i++)
	{
		for (int j = 0; j < WYS; j++)
		{
			etykiety[WYS * i + j] = EtykietyKart[i][j];
		}
	}
	std::sort(etykiety, WYS * SZER + etykiety); //Sortowanie rosn¹co

	//int licznik = 0;
	//bool czyDoliczonoEtykiete = false;
	for (int i = 0; i < WYS * SZER - 1; i++)
	{
		if (etykiety[i] != etykiety[i + 1])
		{
			liczbaEtykiet++;
			//licznik = 0;
		}
		//else
			//licznik++;
	}

	delete[] etykiety;
	return liczbaEtykiet;
}

/*
void SegmentacjaKart1CH(Image1CH we, Image1CH& wy)  //Zwraca ilosc segmentow
{
	//Sprawdzenie rozmiarów
	if (we.width() == wy.width() && we.height() == wy.height())
	{
		//Segmentacja 4 kart
		int segmentId = 0;

		//1 krok - dzia³a ;)
		for (int i = 0; i < we.width(); i++)
		{
			for (int j = 0; j < we.height(); j++)
			{
				if (we(i, j).Intensity() == 1)
				{
					wy(i, j).Intensity() = double(segmentId) / 1024 / 1024; // Mo¿e przesuniêcia bitowe coœ optymalizuj¹
					segmentId++;
				}
				else
				{
					wy(i, j).Intensity() = 0;
				}
			}
		}

		//2krok - w jedn¹ stronê
		int okno_rozmiar = 3;
		int ramka = (okno_rozmiar - 1) / 2; //Odleg³oœæ od œrodka ramki
		int okno_rozmiar_kwadrat = okno_rozmiar * okno_rozmiar;
		double *okno = new double[okno_rozmiar_kwadrat]; //Wektor z pikseli okna
		for (int i = 0; i < wy.width(); i++)
		{
			for (int j = 0; j < wy.height(); j++)
			{
				if (wy(i, j).Intensity() != 0)
				{
					if (i >= ramka && i < wy.width() - ramka && j >= ramka && j < wy.height() - ramka) // Czy jest poza ramk¹
					{
						//Z filtra minimum...
						//Wpisanie do wektora okna czêœci pikseli obrazu wejœciowego
						for (int x = 0; x < okno_rozmiar; x++)
						{
							for (int y = 0; y < okno_rozmiar; y++)
							{
								okno[okno_rozmiar * y + x] = wy(x + i - ramka, y + j - ramka).Intensity();
							}
						}
						sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co

						//Minimalne nie 0
						int index = 0;
						while (okno[index] == 0)
							index++;
						wy(i, j).Intensity() = okno[index]; //Wpisanie minimalnej wartoœci intensywnoœci z wektora
					}
					else
					{
						wy(i, j).Intensity() = 0; // Zbêdne
					}

				}
			}
		}
		//delete[] okno;

		//2krok - w drug¹ stronê
		for (int i = (wy.width() - 1) ; i >= 0; i--)
		{
			for (int j = (wy.height() - 1); j >= 0 ; j--)
			{
				if (wy(i, j).Intensity() != 0)
				{
					if (i >= ramka && i < wy.width() - ramka && j >= ramka && j < wy.height() - ramka) // Czy jest poza ramk¹
					{
						//Z filtra minimum...
						//Wpisanie do wektora okna czêœci pikseli obrazu wejœciowego
						for (int x = 0; x < okno_rozmiar; x++)
						{
							for (int y = 0; y < okno_rozmiar; y++)
							{
								okno[okno_rozmiar * y + x] = wy(x + i - ramka, y + j - ramka).Intensity();
							}
						}
						sort(okno, okno + okno_rozmiar_kwadrat); //Sortowanie rosn¹co

						//Minimalne nie 0
						int index = 0;
						while (okno[index] == 0)
							index++;
						wy(i, j).Intensity() = okno[index]; //Wpisanie minimalnej wartoœci intensywnoœci z wektora
					}
					else
					{
						wy(i, j).Intensity() = 0; // Zbêdne
					}
				}
			}
		}
		delete[] okno;
	}
	else
	{
		std::cerr << "Rozmiary obrazow roznia sie!" << std::endl;
		return;
	}
}*/

void MinimalizacjaEtykietKart()
{
	using namespace std;

	int* etykietyZredukowane = new int[LiczEtykietyKart()]; //Wektor na kilka etykiet
	int indeksEtykiety = 0;

	//Przepisanie do wektora 
	int* etykiety = new int[SZER * WYS]; //Wektor na wszystkie etykiety
	for (int i = 0; i < SZER; i++)
	{
		for (int j = 0; j < WYS; j++)
		{
			etykiety[WYS * i + j] = EtykietyKart[i][j];
		}
	}
	sort(etykiety, WYS * SZER + etykiety); //Sortowanie rosn¹co

	//Zapisanie wartoœci pocz¹tkowych etykiet
	for (int i = 0; i < WYS * SZER - 1; i++)
	{
		if (etykiety[i] != etykiety[i + 1]) //Szukanie przeskoków
		{
			etykietyZredukowane[indeksEtykiety] = etykiety[i + 1];
			cout << "Etykieta: " << etykietyZredukowane[indeksEtykiety] << endl;
			indeksEtykiety++;
		}
	}
	//system("pause");

	//Redukcja wartosci etykiet
	for (int i = 0; i < SZER; i++)
	{
		for (int j = 0; j < WYS; j++)
		{
			if (EtykietyKart[i][j] != 0)
			{
				indeksEtykiety = 0;
				while (EtykietyKart[i][j] != etykietyZredukowane[indeksEtykiety]) // Musi byæ taka wartoœæ
				{
					indeksEtykiety++;
				}
				EtykietyKart[i][j] = indeksEtykiety + 1; //Etykiety od 1
			}
		}
	}
	//Zredokowane wartoœci etykiety


	//Sprawdzenie
	//Przepisanie do wektora
	for (int i = 0; i < SZER; i++)
	{
		for (int j = 0; j < WYS; j++)
		{
			etykiety[WYS * i + j] = EtykietyKart[i][j];
		}
	}
	sort(etykiety, WYS * SZER + etykiety); //Sortowanie rosn¹co

	indeksEtykiety = 0;
	for (int i = 0; i < WYS * SZER - 1; i++)
	{
		if (etykiety[i] != etykiety[i + 1])
		{
			etykietyZredukowane[indeksEtykiety] = etykiety[i + 1];
			cout << "Etykieta: " << etykietyZredukowane[indeksEtykiety] << endl;
			indeksEtykiety++;
		}
	}
	system("pause");


	delete[] etykiety;
	delete[] etykietyZredukowane;
}

void EtykietyNa1CH(Image1CH& wy, double min, double max)
{
	using namespace std;

	int EtykietaMax = 0;
	for (int i = 0; i < wy.width(); i++)
	{
		for (int j = 0; j < wy.height(); j++)
		{
			wy(i, j).Intensity() = 0;	//Zerowanie pikseli
			if (EtykietyKart[i][j] > EtykietaMax) 	//Szukanie Maksymalnej Etykiety
				EtykietaMax = EtykietyKart[i][j];
		}
	}

	//MozliwaLiczbaEtykietKart = EtykietaMax;  //Test..
	cout << "Etykieta Maks: " << EtykietaMax << endl;
	//system("pause");

	//Skalowanie wartoœci intensywnosci na zakres min - max
	for (int i = 0; i < wy.width(); i++)
	{
		for (int j = 0; j < wy.height(); j++)
		{
			if (EtykietyKart[i][j] != 0)
				wy(i, j).Intensity() = min + EtykietyKart[i][j] * ((max - min) / EtykietaMax);
		}
	}
}

void RozciagniecieHistogramu1CH(Image1CH& wy, double min, double max)
{
	using namespace std;

	double IntensityMax = 0;

	//Znajdz maksimum
	for (int i = 0; i < wy.width(); i++)
	{
		for (int j = 0; j < wy.height(); j++)
		{
			if (wy(i, j).Intensity() > IntensityMax)
				IntensityMax = wy(i, j).Intensity();
		}
	}

	cout << "Maks: " << IntensityMax << endl;
	system("pause");

	//Skalowanie wartoœci intensywnosci na zakres min - max
	for (int i = 0; i < wy.width(); i++)
	{
		for (int j = 0; j < wy.height(); j++)
		{
			if (wy(i, j).Intensity() != 0)
				wy(i, j).Intensity() = min + wy(i, j).Intensity() * ((max - min) / IntensityMax);
		}
	}
}

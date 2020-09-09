#include "Temat_16.h"
#include <iostream>


int main()
{
	using std::cin;
	using std::cout;
	using std::endl;

	int obraz_numer = 0;	bool wczytano_obraz = false;
	int obraz_kolor = 0;	bool wybrano_kolor = false;   bool czy_RGB = 1;
	int filtr_numer = 0;	bool wybrano_filtr_sposob = false;
	int filtr_tryb = 0;		bool wybrano_tryb = false;

	Image3CH ColourImage(SZER, WYS); // Create new image Image3CH - three channels image (width,height)
	Image1CH GrayscaleImage(SZER, WYS); //Load image, (path, flag), default flag is LPL_LOAD_FITTED, no need to pass it every time

	//Wyjœciowe
	Image3CH ColourImageOut(SZER, WYS);
	Image1CH GrayscaleImageOut(SZER, WYS);

	//Wybór obrazu
	cout << "Podaj numer obrazu do wczytania (1 - 4) " << endl;
	cin >> obraz_numer;
	do
	{
		switch (obraz_numer)
		{
		case 1:
			ColourImage.LoadImage("img\\1.jpg", LPL_LOAD_FITTED);
			system("cls");
			cout << "Wczytano obraz " << obraz_numer << endl;
			wczytano_obraz = true;
			break;

		case 2:
			ColourImage.LoadImage("img\\2.jpg", LPL_LOAD_FITTED);
			system("cls");
			cout << "Wczytano obraz " << obraz_numer << endl;
			wczytano_obraz = true;
			break;

		case 3:
			ColourImage.LoadImage("img\\3.jpg", LPL_LOAD_FITTED);
			system("cls");
			std::cout << "Wczytano obraz " << obraz_numer << std::endl;
			wczytano_obraz = true;
			break;

		case 4:
			ColourImage.LoadImage("img\\4.jpg", LPL_LOAD_FITTED);
			system("cls");
			std::cout << "Wczytano obraz " << obraz_numer << std::endl;
			wczytano_obraz = true;
			break;

		default:
			system("cls");
			std::cout << "Prosze wybrac ponownie (1 - 4)" << std::endl;
			std::cin >> obraz_numer;
			break;
		}
	} while (!wczytano_obraz);


	/*
	//Wyór filtra
	std::cout << std::endl << "Wybierz sposob filtrowania (1 - 6) " << std::endl;
	std::cout << "1.Rozmycie Gaussa" << std::endl;
	std::cout << "2.Niskopasmowy" << std::endl;
	std::cout << "3.Wysokopasmowy" << std::endl;
	std::cout << "4.Maksimum" << std::endl;
	std::cout << "5.Minimum" << std::endl;
	std::cout << "6.Mediana" << std::endl;
	std::cin >> filtr_numer;
	do
	{
		switch (filtr_numer)
		{
		case 1:
			system("cls");
			std::cout << "Wybrano " << filtr_numer << ". Rozmycie Gaussa" << std::endl;
			wybrano_filtr_sposob = true;
			break;

		case 2:
			system("cls");
			std::cout << "Wybrano " << filtr_numer << ". Niskopasmowy" << std::endl;
			wybrano_filtr_sposob = true;
			break;

		case 3:
			system("cls");
			std::cout << "Wybrano " << filtr_numer << ". Wysokopasmowy" << std::endl;
			wybrano_filtr_sposob = true;
			break;

		case 4:
			system("cls");
			std::cout << "Wybrano " << filtr_numer << ". Maksimum" << std::endl;
			wybrano_filtr_sposob = true;
			break;

		case 5:
			system("cls");
			std::cout << "Wybrano " << filtr_numer << ". Minimum" << std::endl;
			wybrano_filtr_sposob = true;
			break;

		case 6:
			system("cls");
			std::cout << "Wybrano " << filtr_numer << ". Mediana" << std::endl;
			wybrano_filtr_sposob = true;
			break;

		default:
			system("cls");
			std::cout << "Prosze wybrac ponownie (1 - 6)" << std::endl;
			std::cout << "1.Rozmycie Gaussa" << std::endl;
			std::cout << "2.Niskopasmowy" << std::endl;
			std::cout << "3.Wysokopasmowy" << std::endl;
			std::cout << "4.Maksimum" << std::endl;
			std::cout << "5.Minimum" << std::endl;
			std::cout << "6.Mediana" << std::endl;
			std::cin >> filtr_numer;
			break;
		}
	} while (!wybrano_filtr_sposob);

	//Wybór okna/maski
	switch (filtr_numer)
	{
	case 1:
		do
		{
			system("cls");
			std::cout << "Wybierz rodzaj okna/maski filtra (1 - 2) " << std::endl;
			std::cout << "---1---" << endl << endl;
			std::cout << "1  1  1" << endl;
			std::cout << "2  4  2" << endl;
			std::cout << "1  2  1" << endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "------2------" << endl << endl;
			std::cout << "1  1  2  1  1" << endl;
			std::cout << "1  2  4  2  1" << endl;
			std::cout << "2  4  8  4  2" << endl;
			std::cout << "1  2  4  2  1" << endl;
			std::cout << "1  1  2  1  1" << endl;
			std::cin >> filtr_tryb;
			system("cls");
			if (filtr_tryb >= 1 && filtr_tryb <= 2)
				wybrano_tryb = true;
		} while (!wybrano_tryb);
		break;

	case 2:
		do
		{
			system("cls");
			std::cout << "Wybierz rodzaj okna/maski filtra (1 - 2) " << std::endl;
			std::cout << "---1---" << endl << endl;
			std::cout << "1  1  1" << endl;
			std::cout << "1  1  1" << endl;
			std::cout << "1  1  1" << endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "------2------" << endl << endl;
			std::cout << "1  1  1  1  1" << endl;
			std::cout << "1  1  1  1  1" << endl;
			std::cout << "1  1  1  1  1" << endl;
			std::cout << "1  1  1  1  1" << endl;
			std::cout << "1  1  1  1  1" << endl;
			std::cin >> filtr_tryb;
			system("cls");
			if (filtr_tryb >= 1 && filtr_tryb <= 2)
				wybrano_tryb = true;
		} while (!wybrano_tryb);
		break;

	case 3:
		do
		{
			system("cls");
			std::cout << "Wybierz rodzaj okna/maski filtra (1 - 2) " << std::endl;
			std::cout << "---1---" << endl << endl;
			std::cout << "-1 -1 -1" << endl;
			std::cout << "-1  8 -1" << endl;
			std::cout << "-1 -1 -1" << endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "----2---" << endl << endl;
			std::cout << "-1 -2 -1" << endl;
			std::cout << "-2 12 -2" << endl;
			std::cout << "-1 -2 -1" << endl;
			std::cin >> filtr_tryb;
			system("cls");
			if (filtr_tryb >= 1 && filtr_tryb <= 2)
				wybrano_tryb = true;
		} while (!wybrano_tryb);
		break;

	case 4:
		do
		{
			system("cls");
			std::cout << "Podaj rozmiar okna (liczba nieparzysta)" << std::endl;
			std::cin >> filtr_tryb;
			if(filtr_tryb % 2)
				wybrano_tryb = true;
		}while (!wybrano_tryb);
		break;

	case 5:
		do
		{
			system("cls");
			std::cout << "Podaj rozmiar okna (liczba nieparzysta)" << std::endl;
			std::cin >> filtr_tryb;
			if (filtr_tryb % 2)
				wybrano_tryb = true;
		} while (!wybrano_tryb);
		break;

	case 6:
		do
		{
			system("cls");
			std::cout << "Podaj rozmiar okna (liczba nieparzysta)" << std::endl;
			std::cin >> filtr_tryb;
			if (filtr_tryb % 2)
				wybrano_tryb = true;
		} while (!wybrano_tryb);
		break;

	default:
		system("cls");
		std::cout << "Prosze wybrac ponownie (1 - 6)" << std::endl;
		std::cout << "1.Rozmycie Gaussa" << std::endl;
		std::cout << "2.Niskopasmowy" << std::endl;
		std::cout << "3.Wysokopasmowy" << std::endl;
		std::cout << "4.Maksimum" << std::endl;
		std::cout << "5.Minimum" << std::endl;
		std::cout << "6.Mediana" << std::endl;
		std::cin >> filtr_numer;
		break;
	}

	//Wybór kolorów
	system("cls");
	std::cout << "Wybierz sposob przetwarzania (1 - 2) " << std::endl;
	std::cout << "1.RGB" << std::endl;
	std::cout << "2.Mono" << std::endl;
	std::cin >> obraz_kolor;
	do
	{
		switch (obraz_kolor)
		{
		case 1:
			system("cls");
			std::cout << "Wbrano " << obraz_kolor << ".RGB" << std::endl;
			wybrano_kolor = true;
			break;

		case 2:
			system("cls");
			std::cout << "Wbrano " << obraz_kolor << ".Mono" << std::endl;
			wybrano_kolor = true;
			break;

		default:
			system("cls");
			std::cout << "Prosze wybrac ponownie (1 - 2)" << std::endl;
			std::cout << "1.RGB" << std::endl;
			std::cout << "2.Mono" << std::endl;
			std::cin >> obraz_kolor;
			break;
		}
	} while (!wybrano_kolor);


	if (obraz_kolor == 1)
		czy_RGB = true;
	else if (obraz_kolor == 2)
	{
		czy_RGB = false;
		Mono(ColourImage, GrayscaleImage);
	}

	system("cls");
	std::cout << "Trwa filtrowanie..." << std::endl;

	//Wywo³anie filtra
	switch (filtr_numer) //Filtr
	{
	case 1: //Gaussa
		if (czy_RGB)
			RozmycieGaussa3CH(ColourImage, ColourImageOut, filtr_tryb);
		else
			RozmycieGaussa1CH(GrayscaleImage, GrayscaleImageOut, filtr_tryb);
		break;

	case 2: //Niskopasmowy
		if (czy_RGB)
			Niskopasmowy3CH(ColourImage, ColourImageOut, filtr_tryb);
		else
			Niskopasmowy1CH(GrayscaleImage, GrayscaleImageOut, filtr_tryb);
		break;

	case 3: //Wysokopasmowy
		if (czy_RGB)
			Wysokopasmowy3CH(ColourImage, ColourImageOut, filtr_tryb);
		else
			Wysokopasmowy1CH(GrayscaleImage, GrayscaleImageOut, filtr_tryb);
		break;

	case 4: //Maksimum
		if (czy_RGB)
			Maksimum3CH(ColourImage, ColourImageOut, filtr_tryb);
		else
			Maksimum1CH(GrayscaleImage, GrayscaleImageOut, filtr_tryb);
		break;

	case 5: //Minimum
		if (czy_RGB)
			Minimum3CH(ColourImage, ColourImageOut, filtr_tryb);
		else
			Minimum1CH(GrayscaleImage, GrayscaleImageOut, filtr_tryb);
		break;

	case 6: //Mediana
		if (czy_RGB)
			Medianowy3CH(ColourImage, ColourImageOut, filtr_tryb);
		else
			Medianowy1CH(GrayscaleImage, GrayscaleImageOut, filtr_tryb);
		break;
	}


	*/
	/*
	Mono(ColourImage, GrayscaleImage);
	Maksimum1CH(GrayscaleImage, GrayscaleImageOut, 3);
	GrayscaleImageOut.SaveImage("img\\Maksimum_Mono.jpg");
	Maksimum3CH(ColourImage, ColourImageOut, 3);
	ColourImageOut.SaveImage("img\\Maksimum_RGB.jpg");
	Minimum1CH(GrayscaleImage, GrayscaleImageOut, 3);
	GrayscaleImageOut.SaveImage("img\\Minimum_Mono.jpg");
	Minimum3CH(ColourImage, ColourImageOut, 3);
	ColourImageOut.SaveImage("img\\Minimum_RGB.jpg");
	Medianowy1CH(GrayscaleImage, GrayscaleImageOut, 3);
	GrayscaleImageOut.SaveImage("img\\Medianowy_Mono.jpg");
	Medianowy3CH(ColourImage, ColourImageOut, 3);
	ColourImageOut.SaveImage("img\\Medianowy_RGB.jpg");
	Niskopasmowy1CH(GrayscaleImage, GrayscaleImageOut, 2);
	GrayscaleImageOut.SaveImage("img\\Niskopasmowy_Mono.jpg");
	Niskopasmowy3CH(ColourImage, ColourImageOut, 2);
	ColourImageOut.SaveImage("img\\Niskopasmowy_RGB.jpg");
	Wysokopasmowy1CH(GrayscaleImage, GrayscaleImageOut, 1);
	GrayscaleImageOut.SaveImage("img\\Wysokopasmowy_Mono.jpg");
	Wysokopasmowy3CH(ColourImage, ColourImageOut, 1);
	ColourImageOut.SaveImage("img\\Wysokopasmowy_RGB.jpg");
	RozmycieGaussa1CH(GrayscaleImage, GrayscaleImageOut, 2);
	GrayscaleImageOut.SaveImage("img\\Gaussa_Mono.jpg");
	RozmycieGaussa3CH(ColourImage, ColourImageOut, 2);
	ColourImageOut.SaveImage("img\\Gaussa_RGB.jpg");

	Wysokopasmowy3CH(ColourImage, ColourImageOut, 1);
	ColourImageOut.SaveImage("img\\Wysokopasmowy_RGB.jpg");
	*/

	ColourImage.ShowImage("Przed"); //Show image
	Mono(ColourImage, GrayscaleImage);


	//Rozmycie Gaussa
	RozmycieGaussa1CH(GrayscaleImage, GrayscaleImageOut, 2);
	GrayscaleImageOut.ShowImage("Filtr rozmycie Gaussa");
	GrayscaleImageOut.SaveImage("img\\Analiza_Gaussa.jpg");

	/*
	//Medianowy
	GrayscaleImage = GrayscaleImageOut;
	Medianowy1CH(GrayscaleImage, GrayscaleImageOut, 3);
	GrayscaleImageOut.ShowImage("Filtr medianowy");
	GrayscaleImageOut.SaveImage("img\\Analiza_Medianowy.jpg");
	*/

	//Maksymalny
	GrayscaleImage = GrayscaleImageOut;
	Maksimum1CH(GrayscaleImage, GrayscaleImageOut, 3);
	GrayscaleImageOut.ShowImage("Filtr maksymalny");
	GrayscaleImageOut.SaveImage("img\\Analiza_Maksymalny.jpg");

	//Minimalmny
	GrayscaleImage = GrayscaleImageOut;
	Minimum1CH(GrayscaleImage, GrayscaleImageOut, 3);
	GrayscaleImageOut.ShowImage("Filtr minimalny");
	GrayscaleImageOut.SaveImage("img\\Analiza_Minimalny.jpg");


	//Binaryzacja
	GrayscaleImage = GrayscaleImageOut;
	BinaryzacjaSektorowa1CH(GrayscaleImage, GrayscaleImageOut, 15, 0.5);
	GrayscaleImageOut.SaveImage("img\\Analiza_Binaryzacja.jpg");
	GrayscaleImageOut.ShowImage("Po binaryzacji");
	//GrayscaleImage.ShowHistogram();
	//GrayscaleImageOut.ShowHistogram();



	//Maksymalny
	//GrayscaleImage = GrayscaleImageOut;
	//Maksimum1CH(GrayscaleImage, GrayscaleImageOut, 5);
	//GrayscaleImageOut.ShowImage("Filtr maksymalny");Mono
	//GrayscaleImageOut.SaveImage("img\\Analiza_Maksymalny.jpg");

	//Minimalmny
	//GrayscaleImage = GrayscaleImageOut;
	//Minimum1CH(GrayscaleImage, GrayscaleImageOut, 5);
	//GrayscaleImageOut.ShowImage("Filtr minimalny"); 
	//GrayscaleImageOut.SaveImage("img\\Analiza_Minimalny.jpg");



	GrayscaleImage = GrayscaleImageOut;
	SegmentacjaKart1CH(GrayscaleImage);

	MinimalizacjaEtykietKart();

	EtykietyNa1CH(GrayscaleImageOut, 0.5, 1);
	//RozciagniecieHistogramu1CH(GrayscaleImageOut,0.5,1);
	GrayscaleImageOut.ShowImage("Po segmentacji kart");
	GrayscaleImageOut.SaveImage("img\\Analiza_Segmentacja.jpg");
	cout << "Liczba etykiet: " << LiczEtykietyKart() << endl;
	system("pause");

	return 0;
}
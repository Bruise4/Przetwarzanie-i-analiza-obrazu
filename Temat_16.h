#pragma once

#include <iostream>
#include "lipa.h"
#include <algorithm> //Sortowanie

//Wymiary obrazu
#define SZER 1024
#define WYS 768
int EtykietyKart[SZER][WYS];

//Funkcje
void Mono(Image3CH& rgbImg, Image1CH& grayImg);
void Maksimum1CH(Image1CH& we, Image1CH& wy, int okno_rozmiar);
void Maksimum3CH(Image3CH& we, Image3CH& wy, int okno_rozmiar);
void Minimum1CH(Image1CH& we, Image1CH& wy, int okno_rozmiar);
void Minimum3CH(Image3CH& we, Image3CH& wy, int okno_rozmiar);
void Medianowy1CH(Image1CH& we, Image1CH& wy, int okno_rozmiar);
void Medianowy3CH(Image3CH& we, Image3CH& wy, int okno_rozmiar);
void Niskopasmowy1CH(Image1CH& we, Image1CH& wy, int tryb);
void Niskopasmowy3CH(Image3CH& we, Image3CH& wy, int tryb);
void Wysokopasmowy1CH(Image1CH& we, Image1CH& wy, int tryb);
void Wysokopasmowy3CH(Image3CH& we, Image3CH& wy, int tryb);
void RozmycieGaussa1CH(Image1CH& we, Image1CH& wy, int tryb);
void RozmycieGaussa3CH(Image3CH& we, Image3CH& wy, int tryb);
void Binaryzacja1CH(Image1CH& we, Image1CH& wy, double prog);
void BinaryzacjaSektorowa1CH(Image1CH& we, Image1CH& wy, int okno_rozmiar, double odciecie);
void SegmentacjaKart1CH(Image1CH& we);  //Zwraca ilosc segmentow
int LiczEtykietyKart();
void MinimalizacjaEtykietKart();
void EtykietyNa1CH(Image1CH& wy, double min, double max);
void RozciagniecieHistogramu1CH(Image1CH& wy, double min, double max);
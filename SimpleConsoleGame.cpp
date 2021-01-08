/****************************************************************************
**							SAKARYA �N�VERS�TES�
**			         B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�
**						 B�LG�SAYAR M�HEND�SL��� B�L�M�
**				          PROGRAMLAMAYA G�R��� DERS�
**
**				�DEV NUMARASI�...:Proje �devi
**				��RENC� ADI...............:O�ulcan Hami G�l
**				��RENC� NUMARASI.:B181210017
**				DERS GRUBU����:B
****************************************************************************/
#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;

const int genislik = 80;

const int yukseklik = 20;

char sahne[genislik][yukseklik];

char tuslar[256];

const int ucakkaraktersayisi=5;

int mermisayaci = 0;

const int mermihakki = 1000;

const int dusmansayisi = 5000;

int dusmansayaci = 0;

const int zorlukseviyesi = 15;

int i = 0;

//U�a��n hareketi ve ba�ka yerlerde kullanmak i�in bir veri tipi tasarlad�k.
enum Yon
{
	Yon_Yukar�=1,
	Yon_Asag�=2,
	Yon_Yok=3,
	tusabas�ld�=4
};
//Mermi ve d��man�n ortak kullanaca�� yap�y� tasarlad�k.
struct mermivedusman
{
	int x;
	int y;
	Yon yon;
	int dusmanaynimi;
};

mermivedusman mermi[mermihakki];

mermivedusman dusman[dusmansayisi];

//U�a��m�z i�in bir yap� tasarlad�k.
struct Ucakhucre
{
	int x;
	int y;
	char karakter;
	Yon yon;
};

Ucakhucre Ucak[ucakkaraktersayisi];


void kursoruGizle()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void sahneyiCiz()
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			cout << sahne[x][y];
		}

		cout << endl;
	}
}

void sahneyiTemizle()
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			sahne[x][y] = ' ';
		}

	}
}


void sinirlariOlustur()
{
	for (int x = 0; x < genislik; x++)
	{
		sahne[x][0] = 219;
		sahne[x][yukseklik - 1] = 219;
	}

	for (int y = 0; y < yukseklik; y++)
	{
		sahne[0][y] = 219;
		sahne[genislik - 1][y] = 219;
	}

}

void klavyeOku(char tuslar[])
{
	for (int x = 0; x < 256; x++)
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
}

void mermiat() 
{
	mermi[mermisayaci].x = Ucak[2].y;
	mermi[mermisayaci].y = Ucak[2].x + 1;
	mermi[mermisayaci].yon = tusabas�ld�;
}

void mermiyiyerlestir()
{
	//Mermi dizisinin tu�a bas�l�p bas�lmamas�na g�re karakter atamas�.
	for (int i = 0; i < mermihakki; i++)
	{
		if (mermi[i].yon == tusabas�ld�)
		{
			if (mermi[i].y < 80 && mermi[i].x < 20)
			{
				sahne[mermi[i].y][mermi[i].x] = 254;
			}
		}
	}
}

void mermihareket() 
{
	//Merminin hareketi i�in kulland���m�z d�ng�.
	for (int i = 0; i < mermihakki; i++)
	{
		if (mermi[i].yon == tusabas�ld�)
		{
			mermi[i].y++;
		}
	}
}

void klavyeKontrol()
{
	klavyeOku(tuslar);
	//Tu�lara g�re u�a��n y�n�n� ayarlad�k.
	if (tuslar['W'] != 0)
	{
		Ucak[0].yon = Yon_Yukar�;
		Ucak[1].yon = Yon_Yukar�;
		Ucak[2].yon = Yon_Yukar�;
		Ucak[3].yon = Yon_Yukar�;
		Ucak[4].yon = Yon_Yukar�;
	}
	if (tuslar['S'] != 0)
	{
		Ucak[0].yon = Yon_Asag�;
		Ucak[1].yon = Yon_Asag�;
		Ucak[2].yon = Yon_Asag�;
		Ucak[3].yon = Yon_Asag�;
		Ucak[4].yon = Yon_Asag�;
	}
	//space e bas�l�rsa mermiat() fonksiyonunu �a��rd�k.
	if (tuslar[32] != 0)
	{
		mermiat();
		mermisayaci++;
	}
	
}



void Ucakolustur() 
{
	Ucak[0].karakter = 219;
	Ucak[1].karakter = 219;
	Ucak[2].karakter = 219;
	Ucak[3].karakter = 219;
	Ucak[4].karakter = 219;
	Ucak[0].x = 1;
	Ucak[1].x = 2;
	Ucak[2].x = 3;
	Ucak[3].x = 2;
	Ucak[4].x = 1;
	Ucak[0].y = 7;
	Ucak[1].y = 8;
	Ucak[2].y = 9;
	Ucak[3].y = 10;
	Ucak[4].y = 11;

}


void Ucagisahneyeyerlestir() 
{
	//U�a�� sahnede uygun bir yere yerle�tiriyoruz.
	for (int i = 0; i < ucakkaraktersayisi; i++)
	{
		int x = Ucak[i].x;
		int y = Ucak[i].y;
		sahne[x][y] = Ucak[i].karakter;
	}
}

void Ucag�hareketettir() 
{
	for (int i = 0; i < ucakkaraktersayisi; i++) 
	{
		//U�a��n y�n�ne g�re hangi de�erinin art�p azalaca��na karar verilen k�s�m.
		switch (Ucak[i].yon)
		{
		case Yon_Yukar�:
			if (Ucak[0].y != 1)
			{
				Ucak[i].y--;
			}
			break;
		case Yon_Asag�:
			if (Ucak[4].y != 18)
			{
				Ucak[i].y++;
			}
			break;
		}
	}
	Ucak[0].yon = Yon_Yok;
	Ucak[1].yon = Yon_Yok;
	Ucak[2].yon = Yon_Yok;
	Ucak[3].yon = Yon_Yok;
	Ucak[4].yon = Yon_Yok;

	int a = Ucak[0].y;
	Ucak[1].y = a + 1;
	Ucak[2].y = a + 2;
	Ucak[3].y = a + 3;
	Ucak[4].y = a + 4;

}

void dusmanolustur() 
{
	//Dusman�n rastgele ��kmas� i�in rand() kulland�k.
	int y = rand() % 17;
	while (y == 0) 
	{
		y = rand() % 17;
	}
		
	
	if (dusmansayaci % zorlukseviyesi == 0)
	{
		dusman[dusmansayaci].x = genislik - 4;
		dusman[dusmansayaci].y = y;
		dusman[dusmansayaci].yon = tusabas�ld�;
		dusman[dusmansayaci].dusmanaynimi =i ;
		dusman[dusmansayaci + 1].x = genislik - 3;
		dusman[dusmansayaci + 1].y = y;
		dusman[dusmansayaci + 1].yon = tusabas�ld�;
		dusman[dusmansayaci + 1].dusmanaynimi = i;
		dusman[dusmansayaci + 2].x = genislik - 2;
		dusman[dusmansayaci + 2].y = y;
		dusman[dusmansayaci + 2].yon = tusabas�ld�;
		dusman[dusmansayaci + 2].dusmanaynimi=i;
		dusman[dusmansayaci + 3].x = genislik - 4;
		dusman[dusmansayaci + 3].y = y + 1;
		dusman[dusmansayaci + 3].yon = tusabas�ld�;
		dusman[dusmansayaci + 3].dusmanaynimi=i;
		dusman[dusmansayaci + 4].x = genislik - 3;
		dusman[dusmansayaci + 4].y = y + 1;
		dusman[dusmansayaci + 4].yon = tusabas�ld�;
		dusman[dusmansayaci + 4].dusmanaynimi=i;
		dusman[dusmansayaci + 5].x = genislik - 2;
		dusman[dusmansayaci + 5].y = y + 1;
		dusman[dusmansayaci + 5].yon = tusabas�ld�;
		dusman[dusmansayaci + 5].dusmanaynimi=i;
		dusman[dusmansayaci + 6].x = genislik - 4;
		dusman[dusmansayaci + 6].y = y + 2;
		dusman[dusmansayaci + 6].yon = tusabas�ld�;
		dusman[dusmansayaci + 6].dusmanaynimi=i;
		dusman[dusmansayaci + 7].x = genislik - 3;
		dusman[dusmansayaci + 7].y = y + 2;
		dusman[dusmansayaci + 7].yon = tusabas�ld�;
		dusman[dusmansayaci + 7].dusmanaynimi=i;
		dusman[dusmansayaci + 8].x = genislik - 2;
		dusman[dusmansayaci + 8].y = y + 2;
		dusman[dusmansayaci + 8].yon = tusabas�ld�;
		dusman[dusmansayaci + 8].dusmanaynimi=i;
		i++;

	}
}

void dusmanyoket()
{
	//Merminin bir ilerisinde  d��man var m� diye kontrol ediyoruz.
	for (int i = 0; i < mermisayaci; i++) 
	{
		if (sahne[mermi[i].y + 1][mermi[i].x] == 14)
		{
			//Merminin bir ilerisinde ki d��man�n d��man dizisinin ka��nc� eleman� oldu�unu buluyoruz.
			for (int j = 0; j < dusmansayisi; j++) 
			{
				if (dusman[j].x == mermi[i].y + 1 && dusman[j].y == mermi[i].x) 
				{
					//D��man dizisinin merminin �arpt��� eleman�n�n yan�ndaki elemanlar�n y�n�n� de�i�tiriyoruz ��nk� sahneye yerle�tirme i�lemini tusabas�ld� y�n�ne g�re ayarlad�k.
					for (int l = 0; l < dusmansayisi; l++) 
					{
						if (dusman[l].dusmanaynimi == dusman[j].dusmanaynimi)
						{
							dusman[l].yon = Yon_Yok;
						}
					}
				}
			}
		}
	}


}


void dusmaniyerlestir() 
{
	//Dusman� sahneye yerle�tiriyoruz.
	for (int i = 0; i < dusmansayisi; i++)
	{
		if (dusman[i].yon == tusabas�ld�)
		{
			if (dusman[i].x > 0)
			{
				sahne[dusman[i].x][dusman[i].y] = 14;
			}
		}

	}
}



void dusmanhareket()
{
	//Dusman�n x ini artt�rarak hareket ettiriyoruz.
	for (int i = 0; i < dusmansayisi; i++)
	{
		if (dusman[i].yon == tusabas�ld�)
		{
			dusman[i].x--;
		}
	}
}

int main()
{
	Ucakolustur();

	kursoruGizle();

	srand(time(0));

	while (true) 
	{
		//S�rekli tekrar i�in fonksiyonlar�m�z� while(true) d�ng�s�ne sokuyoruz.
		sahneyiTemizle();
		sinirlariOlustur();
		Ucagisahneyeyerlestir();
		klavyeKontrol();
		Ucag�hareketettir();
		mermiyiyerlestir();
		mermihareket();
		dusmanolustur();
		dusmanyoket();
		dusmaniyerlestir();
		dusmanhareket();
		dusmanyoket();
		dusmansayaci++;
		gotoxy(0, 0);
		sahneyiCiz();

	}
	return 0;
}
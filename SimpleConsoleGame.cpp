/****************************************************************************
**							SAKARYA ÜNÝVERSÝTESÝ
**			         BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**						 BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**				          PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI…...:Proje Ödevi
**				ÖÐRENCÝ ADI...............:Oðulcan Hami Gül
**				ÖÐRENCÝ NUMARASI.:B181210017
**				DERS GRUBU…………:B
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

//Uçaðýn hareketi ve baþka yerlerde kullanmak için bir veri tipi tasarladýk.
enum Yon
{
	Yon_Yukarý=1,
	Yon_Asagý=2,
	Yon_Yok=3,
	tusabasýldý=4
};
//Mermi ve düþmanýn ortak kullanacaðý yapýyý tasarladýk.
struct mermivedusman
{
	int x;
	int y;
	Yon yon;
	int dusmanaynimi;
};

mermivedusman mermi[mermihakki];

mermivedusman dusman[dusmansayisi];

//Uçaðýmýz için bir yapý tasarladýk.
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
	mermi[mermisayaci].yon = tusabasýldý;
}

void mermiyiyerlestir()
{
	//Mermi dizisinin tuþa basýlýp basýlmamasýna göre karakter atamasý.
	for (int i = 0; i < mermihakki; i++)
	{
		if (mermi[i].yon == tusabasýldý)
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
	//Merminin hareketi için kullandýðýmýz döngü.
	for (int i = 0; i < mermihakki; i++)
	{
		if (mermi[i].yon == tusabasýldý)
		{
			mermi[i].y++;
		}
	}
}

void klavyeKontrol()
{
	klavyeOku(tuslar);
	//Tuþlara göre uçaðýn yönünü ayarladýk.
	if (tuslar['W'] != 0)
	{
		Ucak[0].yon = Yon_Yukarý;
		Ucak[1].yon = Yon_Yukarý;
		Ucak[2].yon = Yon_Yukarý;
		Ucak[3].yon = Yon_Yukarý;
		Ucak[4].yon = Yon_Yukarý;
	}
	if (tuslar['S'] != 0)
	{
		Ucak[0].yon = Yon_Asagý;
		Ucak[1].yon = Yon_Asagý;
		Ucak[2].yon = Yon_Asagý;
		Ucak[3].yon = Yon_Asagý;
		Ucak[4].yon = Yon_Asagý;
	}
	//space e basýlýrsa mermiat() fonksiyonunu çaðýrdýk.
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
	//Uçaðý sahnede uygun bir yere yerleþtiriyoruz.
	for (int i = 0; i < ucakkaraktersayisi; i++)
	{
		int x = Ucak[i].x;
		int y = Ucak[i].y;
		sahne[x][y] = Ucak[i].karakter;
	}
}

void Ucagýhareketettir() 
{
	for (int i = 0; i < ucakkaraktersayisi; i++) 
	{
		//Uçaðýn yönüne göre hangi deðerinin artýp azalacaðýna karar verilen kýsým.
		switch (Ucak[i].yon)
		{
		case Yon_Yukarý:
			if (Ucak[0].y != 1)
			{
				Ucak[i].y--;
			}
			break;
		case Yon_Asagý:
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
	//Dusmanýn rastgele çýkmasý için rand() kullandýk.
	int y = rand() % 17;
	while (y == 0) 
	{
		y = rand() % 17;
	}
		
	
	if (dusmansayaci % zorlukseviyesi == 0)
	{
		dusman[dusmansayaci].x = genislik - 4;
		dusman[dusmansayaci].y = y;
		dusman[dusmansayaci].yon = tusabasýldý;
		dusman[dusmansayaci].dusmanaynimi =i ;
		dusman[dusmansayaci + 1].x = genislik - 3;
		dusman[dusmansayaci + 1].y = y;
		dusman[dusmansayaci + 1].yon = tusabasýldý;
		dusman[dusmansayaci + 1].dusmanaynimi = i;
		dusman[dusmansayaci + 2].x = genislik - 2;
		dusman[dusmansayaci + 2].y = y;
		dusman[dusmansayaci + 2].yon = tusabasýldý;
		dusman[dusmansayaci + 2].dusmanaynimi=i;
		dusman[dusmansayaci + 3].x = genislik - 4;
		dusman[dusmansayaci + 3].y = y + 1;
		dusman[dusmansayaci + 3].yon = tusabasýldý;
		dusman[dusmansayaci + 3].dusmanaynimi=i;
		dusman[dusmansayaci + 4].x = genislik - 3;
		dusman[dusmansayaci + 4].y = y + 1;
		dusman[dusmansayaci + 4].yon = tusabasýldý;
		dusman[dusmansayaci + 4].dusmanaynimi=i;
		dusman[dusmansayaci + 5].x = genislik - 2;
		dusman[dusmansayaci + 5].y = y + 1;
		dusman[dusmansayaci + 5].yon = tusabasýldý;
		dusman[dusmansayaci + 5].dusmanaynimi=i;
		dusman[dusmansayaci + 6].x = genislik - 4;
		dusman[dusmansayaci + 6].y = y + 2;
		dusman[dusmansayaci + 6].yon = tusabasýldý;
		dusman[dusmansayaci + 6].dusmanaynimi=i;
		dusman[dusmansayaci + 7].x = genislik - 3;
		dusman[dusmansayaci + 7].y = y + 2;
		dusman[dusmansayaci + 7].yon = tusabasýldý;
		dusman[dusmansayaci + 7].dusmanaynimi=i;
		dusman[dusmansayaci + 8].x = genislik - 2;
		dusman[dusmansayaci + 8].y = y + 2;
		dusman[dusmansayaci + 8].yon = tusabasýldý;
		dusman[dusmansayaci + 8].dusmanaynimi=i;
		i++;

	}
}

void dusmanyoket()
{
	//Merminin bir ilerisinde  düþman var mý diye kontrol ediyoruz.
	for (int i = 0; i < mermisayaci; i++) 
	{
		if (sahne[mermi[i].y + 1][mermi[i].x] == 14)
		{
			//Merminin bir ilerisinde ki düþmanýn düþman dizisinin kaçýncý elemaný olduðunu buluyoruz.
			for (int j = 0; j < dusmansayisi; j++) 
			{
				if (dusman[j].x == mermi[i].y + 1 && dusman[j].y == mermi[i].x) 
				{
					//Düþman dizisinin merminin çarptýðý elemanýnýn yanýndaki elemanlarýn yönünü deðiþtiriyoruz çünkü sahneye yerleþtirme iþlemini tusabasýldý yönüne göre ayarladýk.
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
	//Dusmaný sahneye yerleþtiriyoruz.
	for (int i = 0; i < dusmansayisi; i++)
	{
		if (dusman[i].yon == tusabasýldý)
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
	//Dusmanýn x ini arttýrarak hareket ettiriyoruz.
	for (int i = 0; i < dusmansayisi; i++)
	{
		if (dusman[i].yon == tusabasýldý)
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
		//Sürekli tekrar için fonksiyonlarýmýzý while(true) döngüsüne sokuyoruz.
		sahneyiTemizle();
		sinirlariOlustur();
		Ucagisahneyeyerlestir();
		klavyeKontrol();
		Ucagýhareketettir();
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
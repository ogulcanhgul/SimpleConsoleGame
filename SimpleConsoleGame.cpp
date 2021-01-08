
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

//Uçağın hareketi ve başka yerlerde kullanmak için bir veri tipi tasarladık.
enum Yon
{
	Yon_Yukarı=1,
	Yon_Asagı=2,
	Yon_Yok=3,
	tusabasıldı=4
};
//Mermi ve düşmanın ortak kullanacağı yapıyı tasarladık.
struct mermivedusman
{
	int x;
	int y;
	Yon yon;
	int dusmanaynimi;
};

mermivedusman mermi[mermihakki];

mermivedusman dusman[dusmansayisi];

//Uçağımız için bir yapı tasarladık.
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
	mermi[mermisayaci].yon = tusabasıldı;
}

void mermiyiyerlestir()
{
	//Mermi dizisinin tuşa basılıp basılmamasına göre karakter ataması.
	for (int i = 0; i < mermihakki; i++)
	{
		if (mermi[i].yon == tusabasıldı)
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
	//Merminin hareketi için kullandığımız döngü.
	for (int i = 0; i < mermihakki; i++)
	{
		if (mermi[i].yon == tusabasıldı)
		{
			mermi[i].y++;
		}
	}
}

void klavyeKontrol()
{
	klavyeOku(tuslar);
	//Tuşlara göre uçağın yönünü ayarladık.
	if (tuslar['W'] != 0)
	{
		Ucak[0].yon = Yon_Yukarı;
		Ucak[1].yon = Yon_Yukarı;
		Ucak[2].yon = Yon_Yukarı;
		Ucak[3].yon = Yon_Yukarı;
		Ucak[4].yon = Yon_Yukarı;
	}
	if (tuslar['S'] != 0)
	{
		Ucak[0].yon = Yon_Asagı;
		Ucak[1].yon = Yon_Asagı;
		Ucak[2].yon = Yon_Asagı;
		Ucak[3].yon = Yon_Asagı;
		Ucak[4].yon = Yon_Asagı;
	}
	//space e basılırsa mermiat() fonksiyonunu çağırdık.
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
	//Uçağı sahnede uygun bir yere yerleştiriyoruz.
	for (int i = 0; i < ucakkaraktersayisi; i++)
	{
		int x = Ucak[i].x;
		int y = Ucak[i].y;
		sahne[x][y] = Ucak[i].karakter;
	}
}

void Ucagıhareketettir() 
{
	for (int i = 0; i < ucakkaraktersayisi; i++) 
	{
		//Uçağın yönüne göre hangi değerinin artıp azalacağına karar verilen kısım.
		switch (Ucak[i].yon)
		{
		case Yon_Yukarı:
			if (Ucak[0].y != 1)
			{
				Ucak[i].y--;
			}
			break;
		case Yon_Asagı:
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
	//Dusmanın rastgele çıkması için rand() kullandık.
	int y = rand() % 17;
	while (y == 0) 
	{
		y = rand() % 17;
	}
		
	
	if (dusmansayaci % zorlukseviyesi == 0)
	{
		dusman[dusmansayaci].x = genislik - 4;
		dusman[dusmansayaci].y = y;
		dusman[dusmansayaci].yon = tusabasıldı;
		dusman[dusmansayaci].dusmanaynimi =i ;
		dusman[dusmansayaci + 1].x = genislik - 3;
		dusman[dusmansayaci + 1].y = y;
		dusman[dusmansayaci + 1].yon = tusabasıldı;
		dusman[dusmansayaci + 1].dusmanaynimi = i;
		dusman[dusmansayaci + 2].x = genislik - 2;
		dusman[dusmansayaci + 2].y = y;
		dusman[dusmansayaci + 2].yon = tusabasıldı;
		dusman[dusmansayaci + 2].dusmanaynimi=i;
		dusman[dusmansayaci + 3].x = genislik - 4;
		dusman[dusmansayaci + 3].y = y + 1;
		dusman[dusmansayaci + 3].yon = tusabasıldı;
		dusman[dusmansayaci + 3].dusmanaynimi=i;
		dusman[dusmansayaci + 4].x = genislik - 3;
		dusman[dusmansayaci + 4].y = y + 1;
		dusman[dusmansayaci + 4].yon = tusabasıldı;
		dusman[dusmansayaci + 4].dusmanaynimi=i;
		dusman[dusmansayaci + 5].x = genislik - 2;
		dusman[dusmansayaci + 5].y = y + 1;
		dusman[dusmansayaci + 5].yon = tusabasıldı;
		dusman[dusmansayaci + 5].dusmanaynimi=i;
		dusman[dusmansayaci + 6].x = genislik - 4;
		dusman[dusmansayaci + 6].y = y + 2;
		dusman[dusmansayaci + 6].yon = tusabasıldı;
		dusman[dusmansayaci + 6].dusmanaynimi=i;
		dusman[dusmansayaci + 7].x = genislik - 3;
		dusman[dusmansayaci + 7].y = y + 2;
		dusman[dusmansayaci + 7].yon = tusabasıldı;
		dusman[dusmansayaci + 7].dusmanaynimi=i;
		dusman[dusmansayaci + 8].x = genislik - 2;
		dusman[dusmansayaci + 8].y = y + 2;
		dusman[dusmansayaci + 8].yon = tusabasıldı;
		dusman[dusmansayaci + 8].dusmanaynimi=i;
		i++;

	}
}

void dusmanyoket()
{
	//Merminin bir ilerisinde  düşman var mı diye kontrol ediyoruz.
	for (int i = 0; i < mermisayaci; i++) 
	{
		if (sahne[mermi[i].y + 1][mermi[i].x] == 14)
		{
			//Merminin bir ilerisinde ki düşmanın düşman dizisinin kaçıncı elemanı olduğunu buluyoruz.
			for (int j = 0; j < dusmansayisi; j++) 
			{
				if (dusman[j].x == mermi[i].y + 1 && dusman[j].y == mermi[i].x) 
				{
					//Düşman dizisinin merminin çarptığı elemanının yanındaki elemanların yönünü değiştiriyoruz çünkü sahneye yerleştirme işlemini tusabasıldı yönüne göre ayarladık.
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
	//Dusmanı sahneye yerleştiriyoruz.
	for (int i = 0; i < dusmansayisi; i++)
	{
		if (dusman[i].yon == tusabasıldı)
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
	//Dusmanın x ini arttırarak hareket ettiriyoruz.
	for (int i = 0; i < dusmansayisi; i++)
	{
		if (dusman[i].yon == tusabasıldı)
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
		//Sürekli tekrar için fonksiyonlarımızı while(true) döngüsüne sokuyoruz.
		sahneyiTemizle();
		sinirlariOlustur();
		Ucagisahneyeyerlestir();
		klavyeKontrol();
		Ucagıhareketettir();
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

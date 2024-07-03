#include "Wybor.h"

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczaæ pomiêdzy #ifdef a #endif.
*/

#ifdef Kol_2

class Wlasciciel {

};

//1
enum stan {
	dopuszczony = 1,
	niedopuszczony = 2,
};
class Samochod {
protected:
	char rejestracja[9];
	int licznik;
	stan stany;
	Wlasciciel* w;
	static Samochod* wzorzec;
	double warpocz;
public:
	//2
	void setstany(stan s) {
		stany = s;
	}
	stan getstan() {
		return stany;
	}
	void setLicznik(int a) {
		if (a <= 0) {
			throw invalid_argument("ujelny licznik");
		}
		licznik = a;
	}
	
	int getLicznik() {
		return licznik;
	}
	static void setWzorzec(Samochod* wzorzec) {
		Samochod::wzorzec = wzorzec;
	}
	static Samochod* getWzorzec() {
		if (wzorzec == nullptr) {
			throw invalid_argument("nie ma wozroca");

		}
		return wzorzec;
	}
	void setNrrejestrcji(const char* rej) {
		if (strlen(rej) != 9) {
			throw invalid_argument("Numer rejestracyjny powinien sk³adaæ siê z 9 znakow.");
		}
		strncpy_s(this->rejestracja, sizeof(this->rejestracja), rej, _TRUNCATE);
	}
	void setWlasciel(Wlasciciel* wa) {
		w = wa;
	}
	void setwarpocz(double a) {
		warpocz = a;
	}
	//konstruktory 3
	Samochod(const char* rej, int l, stan s, Wlasciciel* wa, double warpocz ) {
		setNrrejestrcji(rej);
		setLicznik(l);
		setstany(s);
		setWlasciel(wa);
		setwarpocz(a);
	}
	Samochod() {
		Samochod(this->getWzorzec()->rejestracja, this->getWzorzec()->licznik, this->getWzorzec()->stany, this->getWzorzec()->w, this->getWzorzec()->warpocz);
	}
	//5
	virtual double zasieg() const {
		if (stany == niedopuszczony) {
			throw invalid_argument("nie dopuszczony");
		}
		return 800;
	}
	///7
	bool operator!=(const Samochod& b) const {
		if (abs(licznik - b.licznik) > 20 || stany != b.stany) {
			return true;
		}
		
		return false;
	}

	//6
	virtual double obliczWartosc() const {
		double WSP_SPARW;
		if (stany == dopuszczony) {
			WSP_SPARW = 1;
		}
		else {
			WSP_SPARW = 0.2;
		}
		
		double wartosc = (warpocz - 0.1 * licznik) * WSP_SPARW;
		if (wartosc < 400.0) {
			wartosc = 400.0;
		}
		return wartosc;
	}

	virtual operator double() const {
		return this->obliczWartosc();
	}

};
//4
class SamochodElektryczny : public Samochod {
private:
	int stanBateri;

public:
	void setStanBaterii(int s) {
		if (s < 0 || s > 100) {
			throw invalid_argument("Zla wartosc");
		}
		else {
			stanBateri = s;
		}
	}


	SamochodElektryczny(Samochod a, int s) :Samochod(a) {
		setStanBaterii(s);
	}
	//5
	double zasieg() const override {
		if (stany==niedopuszczony) {
			throw invalid_argument("nie dopuszczony");
		}
		return stanBateri * 2.5;
	}
	//6
	operator double() const override {
		if (this->obliczWartosc() * 0.7 >= 400) {
			return this->obliczWartosc() * 0.7;
		}
		return 400;
	}
};
Samochod* Samochod::wzorzec = nullptr;

int main()
{
	Wlasciciel wlasciciel1;
	Samochod samochod1("ABC123456", 50000,dopuszczony, &wlasciciel1, 10000);
	Samochod samochod2("ABC123456", 500000, dopuszczony, &wlasciciel1, 10000);
	if (samochod1 != samochod2) {
		cout << "true";
	}
	else {
		cout << "false";
	}
	samochod1.setWzorzec(&samochod1);
	SamochodElektryczny(samochod1, 50);

}

#endif

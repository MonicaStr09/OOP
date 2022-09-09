#include<iostream>
#include<fstream>
using namespace std;

class ExceptieCustomAngajat :public exception {
public:
	const char* what()const throw() {
		return "Varsta angajatului trebuie sa fie >0 si <55";
	}
};

class Angajat {
protected:
	char* nume;
	string telefon;
	int varsta;
	double salariu;

public:

	//implementare metoda virtuala
	virtual void marireSalariu() {
		if (salariu > 0) {
			salariu = salariu + 200;
		}
	}

	//constructor default
	Angajat() {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	//constructor cu 3 parametrii dati
	Angajat(string telefon, int varsta, double salariu) {
		this->telefon = telefon;
		this->varsta = varsta;
		this->salariu = salariu;
	}

	//constructor de copiere
	Angajat(const Angajat& a) {
		this->nume = new char[strlen(a.nume) + 1];
		strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
		this->telefon = a.telefon;
		this->varsta = a.varsta;
		this->salariu = a.salariu;
	}

	//operator =
	Angajat& operator=(const Angajat& a) {
		if (this != &a) {

			if (this->nume != nullptr) {
				delete[] this->nume;
			}
			if (a.nume != nullptr) {
				this->nume = new char[strlen(a.nume) + 1];
				strcpy_s(this->nume, strlen(a.nume) + 1, a.nume);
			}
			else {
				this->nume = nullptr;
			}

			this->telefon = a.telefon;
			this->varsta = a.varsta;
			this->salariu = a.salariu;
		}

		return *this;
	}

	//constructor cu toti parametrii
	Angajat(const char* nume, string telefon, int varsta, double salariu) {
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);

		this->telefon = telefon;
		this->varsta = varsta;
		this->salariu = salariu;
	}

	//destructor
	~Angajat() {
		if (this->nume != nullptr) {
			delete[] this->nume;
		}
	}

	//getteri si setteri 
	char* getNume() {
		return nume;
	}

	string getTelefon() {
		return telefon;
	}

	int getVarsta() {
		return varsta;
	}

	double getSalariu() {
		return salariu;
	}

	void setNume(const char* nume) {
		if (nume != nullptr) {
			delete[] this->nume;

			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			throw new exception("Numele este null.");
		}
	}

	void setTelefon(string telefon) {
		if (telefon.empty()) {
			throw new exception("Telefonul este gol.");
		}
		this->telefon = telefon;
	}

	void setVarsta(int varsta) {
		if (varsta < 0 || varsta>55) {
			throw  ExceptieCustomAngajat();
		}
		else {
			this->varsta = varsta;
		}
	}
	//operator ==
	bool operator==(Angajat a) {
		return strcmp(nume, a.nume) == 0 && varsta == a.varsta && salariu == a.salariu && telefon == a.telefon;
	}

	//operator <<
	friend ostream& operator<<(ostream& out, const Angajat& a) {
		cout << "Angajatul se numeste: " << a.nume << " cu telefonul: " << a.telefon << " are varsta de: "
			<< a.varsta << " si salariul: " << a.salariu << endl << endl;

		return out;
	}

	//operator >>
	friend istream& operator>>(istream& in, Angajat& a) {
		char aux[100];
		cout << "Nume:"; in >> aux;

		if (a.nume != nullptr) {
			delete[] a.nume;
		}

		a.nume = new char[strlen(aux) + 1];
		strcpy_s(a.nume, strlen(aux) + 1, aux);

		cout << "Telefon:"; in >> a.telefon;
		cout << "Varsta:"; in >> a.varsta;
		cout << "Salariu:"; in >> a.salariu;

		return in;
	}

	//op<<(fisier)
	friend ofstream& operator<<(ofstream& out, const Angajat& a) {
		out << a.nume << endl << a.telefon << endl << a.varsta << endl << a.salariu << endl;

		return out;
	}

	//op>>(fisier)
	friend ifstream& operator>>(ifstream& in, Angajat& a) {
		in >> a.telefon;
		in >> a.varsta;
		in >> a.salariu;

		char aux[100];
		in >> aux;

		if (a.nume != nullptr) {
			delete[] a.nume;
		}

		a.nume = new char[strlen(aux) + 1];
		strcpy_s(a.nume, strlen(aux) + 1, aux);

		return in;
	}

};

class Frizer : public Angajat {
private:
	bool esteCunoscut;
	int tarif;
public:

	//implementare metoda virtuala
	virtual void marireSalariu() {
		if (salariu > 0) {
			salariu = salariu + 500;
		}
	}

	//constructor default
	Frizer() :Angajat("Stirbescu", "0745902146", 22, 3000) {
		this->esteCunoscut = true;
		this->tarif = tarif;
	}

	//constructor cu toti parametrii
	Frizer(const char* nume, string telefon, int varsta, double salariu, bool esteCunoscut, int tarif) :Angajat(nume, telefon, varsta, salariu) {
		this->esteCunoscut = esteCunoscut;
		this->tarif = tarif;
	}

	//constructor de copiere
	Frizer(const Frizer& f) : Angajat(f) {
		this->esteCunoscut = f.esteCunoscut;
		this->tarif = f.tarif;
	}

	//operator=
	Frizer& operator=(const Frizer& f) {
		if (this != &f) {
			Angajat::operator=(f);
			this->esteCunoscut = f.esteCunoscut;
			this->tarif = f.tarif;
		}
		return *this;
	}

	//operator <<
	friend ostream& operator<<(ostream& out, const Frizer& f) {

		out << (Angajat)f;
		out << "Este cunoscut " << f.esteCunoscut << endl;
		out << "Tarif: " << f.tarif << endl;
		return out;
	}

	//operator >>
	friend istream& operator>>(istream& in, Frizer& f) {
		char aux[100];
		cout << "Nume:"; in >> aux;

		if (f.nume != nullptr) {
			delete[] f.nume;
		}

		f.nume = new char[strlen(aux) + 1];
		strcpy_s(f.nume, strlen(aux) + 1, aux);

		cout << "Telefon:"; in >> f.telefon;
		cout << "Varsta:"; in >> f.varsta;
		cout << "Salariu:"; in >> f.salariu;
		cout << "Este cunoscut"; in >> f.esteCunoscut;
		cout << "Tarif"; in >> f.tarif;

		return in;
	}

	//op<<(fisier)
	friend ofstream& operator<<(ofstream& out, const Frizer& f) {
		out << f.nume << endl << f.telefon << endl << f.varsta << endl << f.salariu << endl << f.esteCunoscut << endl << f.tarif << endl;;

		return out;
	}

	//op>>(fisier)
	friend ifstream& operator>>(ifstream& in, Frizer& f) {
		in >> f.telefon;
		in >> f.varsta;
		in >> f.salariu;
		in >> f.esteCunoscut;
		in >> f.tarif;

		char aux[100];
		in >> aux;

		if (f.nume != nullptr) {
			delete[] f.nume;
		}

		f.nume = new char[strlen(aux) + 1];
		strcpy_s(f.nume, strlen(aux) + 1, aux);

		return in;
	}


};

class Ministru : public Angajat {
private:
	bool esteCorupt;
	bool arePensieSpeciala;
public:

	//implementare metoda virtuala
	virtual void marireSalariu() {
		if (salariu > 0) {
			salariu = salariu + 7000;
		}
	}

	//constructor default
	Ministru() :Angajat("Chirita", "0712345678", 27, 2000) {
		this->esteCorupt = true;
		this->arePensieSpeciala = true;
	}

	//constructor cu toti parametrii
	Ministru(const char* nume, string telefon, int varsta, double salariu, bool esteCorupt, bool arePensieSpeciala) :Angajat(nume, telefon, varsta, salariu) {
		this->esteCorupt = esteCorupt;
		this->arePensieSpeciala = arePensieSpeciala;
	}

	//constructor de copiere
	Ministru(const Ministru& m) : Angajat(m) {
		this->esteCorupt = m.esteCorupt;
		this->arePensieSpeciala = m.arePensieSpeciala;
	}

	//operator=
	Ministru& operator=(const Ministru& m) {
		if (this != &m) {
			Angajat::operator=(m);
			this->esteCorupt = m.esteCorupt;
			this->arePensieSpeciala = m.arePensieSpeciala;
		}
		return *this;
	}

	//operator <<
	friend ostream& operator<<(ostream& out, const Ministru& m) {

		out << (Angajat)m;
		out << "Este corupt " << m.esteCorupt << endl;
		out << "Are pensie speciala: " << m.arePensieSpeciala << endl;
		return out;
	}

	//operator >>
	friend istream& operator>>(istream& in, Ministru& m) {
		char aux[100];
		cout << "Nume:"; in >> aux;

		if (m.nume != nullptr) {
			delete[] m.nume;
		}

		m.nume = new char[strlen(aux) + 1];
		strcpy_s(m.nume, strlen(aux) + 1, aux);

		cout << "Telefon:"; in >> m.telefon;
		cout << "Varsta:"; in >> m.varsta;
		cout << "Salariu:"; in >> m.salariu;
		cout << "Este corupt"; in >> m.esteCorupt;
		cout << "Are pensie speciala"; in >> m.arePensieSpeciala;

		return in;
	}

	//op<<(fisier)
	friend ofstream& operator<<(ofstream& out, const Ministru& m) {
		out << m.nume << endl << m.telefon << endl << m.varsta << endl << m.salariu << endl << m.esteCorupt << endl << m.arePensieSpeciala << endl;;

		return out;
	}

	//op>>(fisier)
	friend ifstream& operator>>(ifstream& in, Ministru& m) {
		in >> m.telefon;
		in >> m.varsta;
		in >> m.salariu;
		in >> m.esteCorupt;
		in >> m.arePensieSpeciala;

		char aux[100];
		in >> aux;

		if (m.nume != nullptr) {
			delete[] m.nume;
		}

		m.nume = new char[strlen(aux) + 1];
		strcpy_s(m.nume, strlen(aux) + 1, aux);

		return in;
	}
};

class InterfataICompanie {
public:
	virtual void adaugaAngajat(Angajat*) = 0;
	virtual void stergeAngajat(Angajat*) = 0;
};
class Companie : public InterfataICompanie {
private:
	string denumire;
	int nrAngajati;
	Angajat** angajati;
public:

	//constructor default
	Companie() {
		this->angajati = nullptr;
		nrAngajati = 0;
		denumire = "";
	}

	//constructor cu toti parametrii
	Companie(string denumire, int nrAngajati, Angajat** angajati) {
		this->denumire = denumire;

		this->angajati = new Angajat * [nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			this->angajati[i] = new Angajat(*angajati[i]);
		}

		this->nrAngajati = nrAngajati;
	}

	//constructor de copiere
	Companie(const Companie& c) {
		this->denumire = c.denumire;

		this->angajati = new Angajat * [c.nrAngajati];
		for (int i = 0; i < c.nrAngajati; i++) {
			this->angajati[i] = new Angajat(*c.angajati[i]);
		}

		this->nrAngajati = c.nrAngajati;
	}

	//operator=
	Companie& operator=(const Companie& c) {
		if (this != &c) {
			if (this->angajati != nullptr) {
				delete[] this->angajati;
			}

			this->denumire = c.denumire;

			this->angajati = new Angajat * [c.nrAngajati];
			for (int i = 0; i < c.nrAngajati; i++) {
				this->angajati[i] = new Angajat(*c.angajati[i]);
			}

			this->nrAngajati = c.nrAngajati;

		}
		return *this;
	}

	//destructor
	~Companie() {
		if (this->angajati != nullptr) {
			delete[] this->angajati;
		}
	}

	//getteri si setteri
	string getDenumire() {
		return denumire;
	}

	int getNrAngajati() {
		return nrAngajati;
	}

	void setDenumire(string denumire) {
		if (denumire.empty()) {
			throw new exception("Denumirea este goala.");
		}
		this->denumire = denumire;
	}

	void setNrAngajati(int nrAngajati) {
		if (nrAngajati < 0) {
			throw new exception("Nr angajatilor este incorect introdus.");
		}
		else {
			this->nrAngajati = nrAngajati;
		}
	}

	//implementare metoda din interfata
	//adauga angajat
	virtual void adaugaAngajat(Angajat* a) {
		Angajat** aux = new Angajat * [nrAngajati];
		for (int i = 0; i < nrAngajati; i++) {
			aux[i] = new Angajat(*angajati[i]);
		}
		delete[] angajati;
		angajati = new Angajat * [nrAngajati + 1];
		for (int i = 0; i < nrAngajati; i++) {
			angajati[i] = new Angajat(*aux[i]);
		}
		angajati[nrAngajati] = a;
		nrAngajati++;
		delete[] aux;
	}

	//implementare metoda din interfata
	//sterge angajat
	virtual void stergeAngajat(Angajat* a) {
		int nrDuplicate = 0;
		for (int i = 0; i < nrAngajati; i++) {
			if (*angajati[i] == *a) {
				nrDuplicate++;
			}
		}

		if (nrDuplicate > 0) {
			for (int i = 0; i < nrAngajati; i++) {
				if (*angajati[i] == *a) {
					for (int j = i; j < nrAngajati - 1; j++) {
						this->angajati[j] = angajati[j + 1];
					}
					nrAngajati--;
				}
			}

			Angajat** aux = new Angajat * [nrAngajati];
			for (int i = 0; i < nrAngajati; i++) {
				aux[i] = angajati[i];
			}

			delete[] angajati;
			angajati = aux;
		}

	}

	//operator[]
	Companie& operator[](int index) {
		if (index >= 0 && index < nrAngajati) {
			//return angajati[index];
		}
		else {
			throw new exception("eroare in [] ");
		}
	}

	//operator <<
	friend ostream& operator<<(ostream& out, Companie& c) {
		out << "Denumire companie: " << c.denumire << endl;
		out << "Numar de angajati disponibili: " << c.nrAngajati << endl;

		for (int i = 0; i < c.nrAngajati; i++) {
			Angajat* angajat = c.angajati[i];
			out << *angajat;
		}
		return out;
	}

	//operator >>
	friend istream& operator>>(istream& in, Companie& c) {
		char aux[100];
		cout << "Angajati:"; in >> aux;

		if (c.angajati != nullptr) {
			delete[] c.angajati;
		}

		for (int i = 0; i < c.nrAngajati; i++) {
			//aux[i] = *c.angajati[i];
		}

		cout << "Denumire companie: "; in >> c.denumire;
		cout << "Numar de angajati disponibili: "; in >> c.nrAngajati;

		return in;
	}


};

template<typename T> void afisareTemplate(T a, T b) {
	cout << a << " " << b << endl;
}


int main()
{
	Angajat a1("Ionescu", "0736491259", 30, 2100);
	a1.setVarsta(56);
	Angajat a2("Nimic", "", 0, 0.0);
	Angajat a3 = a1;
	cout << a1 << endl;
	cout << a3 << endl;
	a3 = a2;
	a1.marireSalariu();
	cout << a1 << endl;
	cin >> a2;
	cout << a2 << endl;


	cout << "\n\na2.getNume(): " << a2.getNume();

	Frizer f1("Georgescu", "07987654321", 22, 1900, true, 35);
	Frizer f2("", "", 0, 0.0, 0, 0);
	Frizer f3 = f1;
	cout << f1 << endl;
	cout << f3 << endl;
	f3 = f2;
	f1.marireSalariu();
	cout << f1 << endl;
	cout << f1 << endl;
	cin >> f2;
	cout << f2 << endl;


	Ministru m1("Draganescu", "07987654390", 28, 5000, false, false);
	Ministru m2("", "", 0, 0.0, 0, 0);
	Ministru m3 = m1;
	cout << m1 << endl;
	cout << m3 << endl;
	m3 = m2;
	m1.marireSalariu();
	cout << m1 << endl;
	cout << m1 << endl;
	cin >> m2;
	cout << m2 << endl;


	Angajat* angajati[] = { &a1, &a2, &a3 };
	Companie c1("Orange", 3, angajati);
	Angajat* angajati2[] = { &a1, &a2 };
	Companie c2("Flanco", 2, angajati2);
	Companie c3 = c1;
	cout << c3;
	c3 = c2;
	cout << c3;
	c1.adaugaAngajat(&a1);
	cout << c1;
	c1.stergeAngajat(&a1);
	cout << c1;
	afisareTemplate<int>(2, 5);

	try {
		m1.setVarsta(100);
	}
	catch (ExceptieCustomAngajat e) {
		cout << e.what() << endl;
	}

	ofstream fisTextOut1("angajatiOut.txt");
	if (fisTextOut1.is_open()) {
		fisTextOut1 << a1;

		fisTextOut1.close();
	}
	else {
		cout << "Fisierul angajatiOut.txt nu poate fi deschis pentru scriere\n";
	}

	ofstream fisTextOut2("frizeriOut.txt");
	if (fisTextOut2.is_open()) {
		fisTextOut2 << f1;

		fisTextOut2.close();
	}
	else {
		cout << "Fisierul frizeriOut.txt nu poate fi deschis pentru scriere\n";
	}

	ofstream fisTextOut3("ministriOut.txt");
	if (fisTextOut3.is_open()) {
		fisTextOut3 << m1;

		fisTextOut3.close();
	}
	else {
		cout << "Fisierul ministriOut.txt nu poate fi deschis pentru scriere\n";
	}


	Angajat a4("Iliescu", "0798786543", 22, 1900);
	Frizer f4("Mihai", "0984754823", 33, 4500, true, 50);
	Ministru m4("Andrei", "02938453842", 54, 25000, true, true);

	ifstream fisTextIn1("angajatiOut.txt");
	if (fisTextIn1.is_open()) {
		fisTextIn1 >> a4;

		cout << "\n\n a4 \n\n" << a4 << endl;

		fisTextIn1.close();
	}
	else {
		cout << "Fisierul angajatiOut.txt nu poate fi deschis pentru scriere\n";
	}

	ifstream fisTextIn2("frizeriOut.txt");
	if (fisTextIn2.is_open()) {
		fisTextIn2 >> f4;

		cout << "\n\n f4 \n\n" << f4 << endl;

		fisTextIn2.close();
	}
	else {
		cout << "Fisierul frizeriOut.txt nu poate fi deschis pentru scriere\n";
	}

	ifstream fisTextIn3("ministriOut.txt");
	if (fisTextIn3.is_open()) {
		fisTextIn3 >> m4;

		cout << "\n\n m4 \n\n" << m4 << endl;

		fisTextIn3.close();
	}
	else {
		cout << "Fisierul ministriOut.txt nu poate fi deschis pentru scriere\n";
	}

}
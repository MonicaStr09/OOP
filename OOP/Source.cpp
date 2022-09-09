#include<iostream>
#include<fstream>
#include<ctime>
#include <vector>
using namespace std;

#define _CRT_SECURE_NO_WARNINGS

class ExceptieCustomProdus1 :public exception {
public:
	const char* what()const throw() {
		return "Pretul produsului trebuie sa fie intre 0 si 500 de lei";
	}
};

class ExceptieCustomProdus2 :public exception {
public:
	const char* what()const throw() {
		return "Numarul stocului unui produs nu trebuie sa depaseasca 200 bucati";
	}
};

class InterfataCalorii {
public:
	virtual string catTrebuieSaConsumi() = 0;
};


class Produs :public InterfataCalorii
{
private:
	char* denumireProdus;
	double pret;
	int nrStoc;
	double* stoc;
public:

	//constructor default
	Produs()
	{
		this->denumireProdus = new char[strlen("necunoscut") + 1];
		strcpy_s(this->denumireProdus, strlen("necunoscut") + 1, "necunoscut");
		this->pret = 0.0;
		this->nrStoc = 0.0;
		this->stoc = nullptr;

	}

	//constructor cu toti parametrii
	Produs(const char* denumireProdus, double pret, int nrStoc, double* stoc)
	{
		if (denumireProdus != nullptr) {
			this->denumireProdus = new char[strlen(denumireProdus) + 1];
			strcpy_s(this->denumireProdus, strlen(denumireProdus) + 1, denumireProdus);
		}
		else {
			this->denumireProdus = new char[strlen("necunoscut") + 1];
			strcpy_s(this->denumireProdus, strlen("necunoscut") + 1, "necunoscut");

		}

		if (pret > 0.0) {
			this->pret = pret;
		}
		else {
			this->pret = 0.0;
		}

		if (nrStoc > 0) {
			this->nrStoc = nrStoc;
		}
		else {
			this->nrStoc = 0.0;
		}

		if (stoc != nullptr) {
			this->stoc = new double[nrStoc];
			for (int i = 0; i < nrStoc; i++) {
				this->stoc[i] = stoc[i];
			}
		}
		else {
			this->stoc = nullptr;
		}

	}

	//constructor de copiere
	Produs(const Produs& p) {
		if (p.denumireProdus != nullptr) {
			this->denumireProdus = new char[strlen(p.denumireProdus) + 1];
			strcpy_s(this->denumireProdus, strlen(p.denumireProdus) + 1, p.denumireProdus);
		}
		else {
			this->denumireProdus = nullptr;
		}

		if (p.pret != 0.0) {
			this->pret = p.pret;
		}
		else {
			this->pret = 0.0;
		}

		if (p.nrStoc != 0) {
			this->nrStoc = p.nrStoc;
		}
		else {
			this->nrStoc = 0;
		}

		if (p.stoc != nullptr) {
			this->stoc = new double[p.nrStoc];
			for (int i = 0; i < p.nrStoc; i++) {
				this->stoc[i] = p.stoc[i];
			}
		}
		else this->stoc = nullptr;
	}

	//op =
	Produs& operator=(const Produs p) {
		if (this != &p) {
			if (this->denumireProdus != nullptr) {
				delete[] this->denumireProdus;
			}
			if (this->stoc != nullptr) {
				delete[] this->stoc;
			}

			if (p.denumireProdus != nullptr) {
				this->denumireProdus = new char[strlen(p.denumireProdus) + 1];
				strcpy_s(this->denumireProdus, strlen(p.denumireProdus) + 1, p.denumireProdus);
			}
			else {
				this->denumireProdus = nullptr;
			}
			this->pret = p.pret;
			this->nrStoc = p.nrStoc;

			if (p.stoc != nullptr) {
				this->stoc = new double[p.nrStoc];
				for (int i = 0; i < p.nrStoc; i++) {
					this->stoc[i] = p.stoc[i];
				}
			}
		}
		return *this;
	}

	//destructor
	~Produs() {
		if (this->denumireProdus != nullptr) {
			delete[] this->denumireProdus;
		}

		if (this->stoc != nullptr) {
			delete[] this->stoc;
		}
	}

	char* getDenumireProdus() {
		return denumireProdus;
	}

	double getPret() {
		return pret;
	}

	int getNrStoc() {
		return nrStoc;
	}

	double* getStoc() {
		return stoc;
	}

	void setPret(double pret) {
		if (pret < 0 || pret>500) {
			throw new ExceptieCustomProdus1();
		}
		else {
			this->pret = pret;
		}
	}

	void setNrStoc(int nrStoc) {
		if (nrStoc < 0 || nrStoc>200) {
			throw new ExceptieCustomProdus2();
		}
		else {
			this->nrStoc = nrStoc;
		}
	}

	//implementare metoda din interfata
	string catTrebuieSaConsumi() {
		return "O persoana trebuie sa consume o gama diversificata de produse! ";
	}

	//operator ++ (pre-incrementare)
	const Produs& operator++() {
		nrStoc++;
		return *this;
	}

	//operator + (cout<<p2+2)
	int operator+(int x) {
		return nrStoc + x;
	}

	//operator += (p3+=3)
	void operator+=(int x) {
		nrStoc += x;
	}

	//op= (int)
	Produs& operator=(int a)
	{
		this->nrStoc = a;
		return *this;
	}

	//op!=
	bool operator!=(Produs p)
	{
		if (strcmp(this->denumireProdus, p.denumireProdus) == 0)
			if (this->pret == p.pret && nrStoc == p.nrStoc && stoc == p.stoc)
				return 0;
		return 1;
	}

	//operator + (cout<10+p3)
	friend int operator+(int x, Produs& p) {
		return x + p.nrStoc;
	}

	//op cast - implicit sau explicit
	operator int() {
		return nrStoc;
	}

	//op ==
	bool operator==(Produs& p) {
		if (this == &p) {
			return true;
		}

		return strcmp(denumireProdus, p.denumireProdus) == 0 && pret == p.pret && nrStoc == p.nrStoc && stoc == p.stoc;
	}

	//op <<
	friend ostream& operator<<(ostream& out, const Produs& p) {
		cout << "Denumirea produsului este: " << p.denumireProdus << " cu pretul unitar pe bucata de: " << p.pret << " nr stocurilor fiind de: " << p.nrStoc << " si stocurile ";
		for (int i = 0; i < p.nrStoc; i++) {
			out << p.stoc[i] << " ";
		}
		out << endl;

		return out;
	}

	//op >>
	friend istream& operator>>(istream& in, Produs& p) {
		char aux[100];
		cout << "Denumire:"; in >> aux;

		if (p.denumireProdus != nullptr) {
			delete[] p.denumireProdus;
		}

		p.denumireProdus = new char[strlen(aux) + 1];
		strcpy_s(p.denumireProdus, strlen(aux) + 1, aux);

		cout << "Pret: "; in >> p.pret;
		cout << " Nr stocurilor: "; in >> p.nrStoc;

		if (p.stoc != nullptr) {
			delete[] p.stoc;
		}
		p.stoc = new double[p.nrStoc];
		for (int i = 0; i < p.nrStoc; i++) {
			in >> p.stoc[i];
		}

		return in;
	}
	void scriebin(fstream& f)
	{
		int lg;
		lg = strlen(this->denumireProdus) + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->denumireProdus, lg);
		f.write((char*)&this->pret, sizeof(double));
		f.write((char*)&this->nrStoc, sizeof(int));
		for (int i = 0; i < this->nrStoc; i++)
			f.write((char*)&this->stoc[i], sizeof(double));
	}
	void citirebin(fstream& f)
	{
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* s = new char[lg];
		f.read(s, lg);
		strcpy_s(this->denumireProdus, lg, s);
		f.read((char*)&this->pret, sizeof(double));
		f.read((char*)&this->nrStoc, sizeof(int));
		for (int i = 0; i < this->nrStoc; i++)
			f.read((char*)&this->stoc[i], sizeof(double));
	}

};

class Ciocolata :private Produs {
private:
	double gramaj;
	string marca;

public:
	void  stareExpirare() {
		cout << "Exista o mica probabilitate de expirare";
	}

	//constructor default
	Ciocolata() :Produs() {
		this->gramaj = 0.0;
		this->marca = " ";
	}

	//constructor cu toti parametrii
	Ciocolata(const char* denumireProdus, double pret, int nrStoc, double* stoc, double gramaj, string marca) :Produs(denumireProdus, pret, nrStoc, stoc) {
		if (gramaj > 0.0) {
			this->gramaj = gramaj;
		}
		else {
			this->gramaj = 0.0;
		}
		if (marca.empty()) {
			this->marca = " ";
		}
		else {
			this->marca = marca;
		}
	}

	//constructor de copiere
	Ciocolata(const Ciocolata& c) :Produs(c) {
		this->gramaj = c.gramaj;
		this->marca = c.marca;
	}

	//op=
	Ciocolata& operator=(const Ciocolata& c) {
		if (this != &c) {
			Produs::operator=(c);

			this->gramaj = c.gramaj;
			this->marca = c.marca;

		}
		return *this;
	}

	//implementare metoda din interfata
	string catTrebuieSaConsumi() {
		return "O persoana trebuie sa consume maxim 3 bucati de ciocolata zilnic! ";
	}

	friend ostream& operator<<(ostream& out, const Ciocolata& c) {

		out << (Produs)c;
		out << "Gramaj " << c.gramaj << endl;
		out << "Marca " << c.marca << endl;
		return out;
	}
};

class Briosa :private Produs {
private:
	bool areCiocolata;
	bool esteFacutaAstazi;
public:

	//constructor default
	Briosa() :Produs() {
		this->areCiocolata = false;
		this->esteFacutaAstazi = true;
	}

	//constructor cu toti parametrii
	Briosa(const char* denumireProdus, double pret, int nrStoc, double* stoc, bool areCiocolata, bool esteFacutaAstazi) :Produs(denumireProdus, pret, nrStoc, stoc) {
		this->areCiocolata = areCiocolata;
		this->esteFacutaAstazi = esteFacutaAstazi;
	}

	//constructor de copiere
	Briosa(const Briosa& b) :Produs(b) {
		this->areCiocolata = b.areCiocolata;
		this->esteFacutaAstazi = b.esteFacutaAstazi;
	}

	//op=
	Briosa& operator=(const Briosa& b) {
		if (this != &b) {
			Produs::operator=(b);

			this->areCiocolata = b.areCiocolata;
			this->esteFacutaAstazi = b.esteFacutaAstazi;

		}
		return *this;
	}

	//implementare metoda din interfata
	string catTrebuieSaConsumi() {
		return "O persoana trebuie sa consume maxim o briosa zilnic! ";
	}

	friend ostream& operator<<(ostream& out, const Briosa& b) {

		out << (Produs)b;
		out << "Are ciocolata " << b.areCiocolata << endl;
		out << "Este facuta astazi " << b.esteFacutaAstazi << endl;
		return out;

	}
	void scriebi(fstream& f)
	{
		Produs::scriebin(f);
		f.write((char*)&this->areCiocolata, sizeof(bool));
		f.write((char*)&this->esteFacutaAstazi, sizeof(bool));
	}
	void citirebi(fstream& f)
	{
		Produs::citirebin(f);
		f.read((char*)&this->areCiocolata, sizeof(bool));
		f.read((char*)&this->esteFacutaAstazi, sizeof(bool));
	}
};

class GamaDeBriose {
private:
	string denumire;
	Briosa* briose;
	int nrBriose;

public:
	//constructor cu toti parametrii
	GamaDeBriose(string denumire, Briosa* briose, int nrBriose) {
		this->denumire = denumire;

		this->briose = new Briosa[nrBriose];
		for (int i = 0; i < nrBriose; i++) {
			this->briose[i] = briose[i];
		}

		this->nrBriose = nrBriose;
	}

	//constructor de copiere toti param
	GamaDeBriose(const GamaDeBriose& gama) {
		this->denumire = gama.denumire;

		this->briose = new Briosa[gama.nrBriose];
		for (int i = 0; i < nrBriose; i++) {
			this->briose[i] = gama.briose[i];
		}

		this->nrBriose = gama.nrBriose;
	}

	//destructor
	~GamaDeBriose() {
		if (briose != nullptr) {
			delete[] briose;
		}
	}

	//op=
	GamaDeBriose& operator=(const GamaDeBriose& gama) {
		if (this != &gama) {
			if (this->briose != nullptr) {
				delete[] this->briose;
			}

			this->denumire = gama.denumire;

			this->briose = new Briosa[gama.nrBriose];
			for (int i = 0; i < nrBriose; i++) {
				this->briose[i] = gama.briose[i];
			}

			this->nrBriose = gama.nrBriose;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, GamaDeBriose& gama) {
		out << "Denumirea gamei de briose: " << gama.denumire << endl;
		out << "Numarul componentelor gamei disponibile: " << gama.nrBriose << endl;
		for (int i = 0; i < gama.nrBriose; i++) {
			out << gama.briose[i];
		}
		return out;
	}
	void scriebin(fstream& f)
	{
		int lg = this->denumire.size() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->denumire.data(), lg);
		f.write((char*)&this->nrBriose, sizeof(int));
		for (int i = 0; i < this->nrBriose; i++)
			this->briose[i].scriebi(f);
	}
	void citirebin(fstream& f)
	{
		int lg;
		f.read((char*)&lg, sizeof(int));
		char* s = new char[lg];
		f.read(s, lg);
		this->denumire = s;
		f.read((char*)&this->nrBriose, sizeof(int));
		for (int i = 0; i < this->nrBriose; i++)
			this->briose[i].citirebi(f);
	}
};

class Ofertabriose {
	string denumire;
	vector<Briosa> ofertabriose;
	int nrBriose;

public:
	//constructor cu toti parametrii
	Ofertabriose(string denumire, vector<Briosa> briose, int nrBriose) {
		if (denumire.size() > 0)
			this->denumire = denumire;
		else
			this->denumire = "a";
		if (nrBriose > 0 && !briose.empty()) {
			this->nrBriose = nrBriose;
			this->ofertabriose = briose;
		}
		else
		{
			this->ofertabriose.clear();
			this->nrBriose = 0;
		}
	}

	//constructor de copiere toti param
	Ofertabriose(const Ofertabriose& gama) {
		this->denumire = gama.denumire;
		this->ofertabriose = gama.ofertabriose;
		this->nrBriose = gama.nrBriose;
	}

	//destructor
	~Ofertabriose() {}
	Ofertabriose& operator+(Briosa& b)
	{
		this->ofertabriose.push_back(b);
		return *this;
	}

	Ofertabriose& operator-()
	{
		this->ofertabriose.pop_back();
		return *this;
	}

	friend ostream& operator<<(ostream& out, Ofertabriose& of)
	{
		out << "\nDenumire" << of.denumire << endl;
		out << "\n Numar de briose" << of.nrBriose << endl;
		vector<Briosa>::iterator it;
		for (it = of.ofertabriose.begin(); it != of.ofertabriose.end(); it++)
			out << *it;
		return out;
	}

};

int main() {

	double v1[] = { 3,5,7 };
	Produs p1("Paine", 2, 3, v1);
	cout << p1 << endl;
	double v2[] = { 1,2,3,4.0, 5 };
	Produs p2("Ciocolata", 4, 5, v2);
	cout << p1 << endl;
	Produs p3("Zahar", 3, 3, v1);
	cout << p1 << endl;
	//
	////op=
	p3 = p2 = p1;
	cout << p3;
	//
	p3.getDenumireProdus();
	//
	////operator pre-incrementare
	cout << ++p2;
	//
	////op +
	cout << p1 + 2 << endl;

	////op+d
	cout << 3 + p2 << endl;

	////op+=
	p3 += 1;
	cout << p3 << endl;;

	////op +=
	p2 += 1;
	cout << p2 << endl << endl;

	////op cast explicit
	cout << "(int)p2=" << (int)p2 << endl << endl;

	////op ==
	if (p1 == p2) {
		cout << "p1==p2" << endl << endl;
	}
	else {
		cout << "p1!=p2" << endl << endl;
	}

	Ciocolata c1;
	cout << c1;

	double v3[] = { 1,2,3 };
	Ciocolata c2("Ciocolata", 4, 3, v3, 100, "Milka");
	cout << c2 << endl;

	Briosa b1;
	cout << b1 << endl;

	double v4[] = { 2,5,9 };
	Briosa b2("Briosa", 11, 3, v4, true, true);
	cout << b2 << endl;

	Briosa bb[2];
	bb[0] = b1;
	bb[1] = b2;
	GamaDeBriose gb("Briosele", bb, 2);
	cout << gb << endl;
	fstream f("fisierbinar.txt", ios::out | ios::binary);
	gb.scriebin(f);
	f.close();
	fstream g("fisierbinar.txt", ios::in | ios::binary);
	gb.citirebin(g);
	cout << gb;

	//early binding
	cout << "\n Early binding" << endl;
	cout << p1.catTrebuieSaConsumi() << endl;
	cout << b2.catTrebuieSaConsumi() << endl;
	cout << c2.catTrebuieSaConsumi() << endl;



	//late binding
	cout << "\n Late binding:" << endl;
	Produs* p;
	Briosa* b;
	Ciocolata* c;
	InterfataCalorii* ic;
	p = &p1;
	cout << p->catTrebuieSaConsumi() << endl;
	b = &b1;
	cout << b->catTrebuieSaConsumi() << endl;
	c = &c1;
	cout << c->catTrebuieSaConsumi() << endl;
	ic = p;
	cout << ic->catTrebuieSaConsumi() << endl;

	vector<Briosa> gama;
	gama.push_back(b1);
	gama.push_back(b2);
	vector<Briosa>::iterator it;
	for (it = gama.begin(); it != gama.end(); it++)
		cout << *it << endl;

	//cele 2 exceptii
	try {
		p1.setPret(-1);
	}
	catch (ExceptieCustomProdus1* ex)
	{
		cout << ex->what() << endl;
	}
	try {
		p1.setNrStoc(-1);
	}
	catch (ExceptieCustomProdus2* ex1)
	{
		cout << ex1->what() << endl;
	}
	//clasa ce contine vectorul STL
	Ofertabriose of("Oferta", gama, 2);
	cout << of;
	of.operator+(*b);
	cout << of;
}
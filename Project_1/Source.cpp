#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include<string>
using namespace std;

enum class GEN { FEMEIE = 1, BARBAT = 2, NECUNOSCUT = 3 };

class Sectie {
private:
	const int cod;//a
	static int nrAngajati;//b
	char* nume;//c
	string prenume;//d
	float* ture; //  turele din ultimele nrZile  //e
	int nrZile;//f
	bool concediu; //0- a avut ; 1- nu a avut//g
	GEN gen;//h

public:
	//2.Constructor pentru clasa Sectie 
	Sectie(string prenume, float* ture, int nrZile, GEN gen) :cod(0) {

		if (!prenume.empty())
			this->prenume = prenume;
		else
			throw new exception("Prenumele este gol");

		if (nrZile >= 0)
			this->nrZile = nrZile;
		else
			throw new exception("numarul de zile trebuie sa fie mai mare sau egal cu 0");

		if (ture != nullptr) {
			this->ture = new float[nrZile];
			for (int i = 0; i < nrZile; i++)
				this->ture[i] = ture[i];
		}
		else
			throw new exception("Turele au valoarea nullptr");

		if (gen == GEN::FEMEIE || gen == GEN::BARBAT || gen == GEN::NECUNOSCUT)
			this->gen = gen;
		else
			throw new exception("Genul este invalid");

		nume = new char[strlen("Anonim") + 1];
		strcpy_s(nume, strlen("Anonim") + 1, "Anonim");
	}


	//3.Constructor de copiere
	Sectie(const Sectie& s) :cod(s.cod) {
		nrAngajati++;
		this->nume = new char[strlen(s.nume) + 1];
		strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);

		this->prenume = s.prenume;
		this->nrZile = s.nrZile;

		this->ture = new float[s.nrZile];
		for (int i = 0; i < s.nrZile; i++)
			this->ture[i] = s.ture[i];

		this->concediu = s.concediu;
		this->gen = s.gen;
	}

	//Operator =
	Sectie& operator=(const Sectie& s) {
		if (this != &s) {
			s.nrAngajati++;

			if (this->nume != nullptr) {
				delete[] this->nume;
			}
			if (this->ture != nullptr) {
				delete[] this->ture;
			}

			this->nume = new char[strlen(s.nume) + 1];
			strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);

			this->prenume = s.prenume;
			this->nrZile = s.nrZile;

			this->ture = new float[nrZile];
			for (int i = 0; i < s.nrZile; i++)
				this->ture[i] = s.ture[i];

			this->concediu = s.concediu;
			this->gen = s.gen;
		}
		return *this;
	}
	//4.Constructor default
	Sectie() :cod(0) {
		nrAngajati++;
		nume = new char[strlen("Anonim") + 1];
		strcpy_s(nume, strlen("Anonim") + 1, "Anonim");

		prenume = "Anonim";
		nrZile = 28;
		ture = new float[nrZile];

		for (int i = 0; i < nrZile; i++)
			ture[i] = 0;

		concediu = 1;
		gen = GEN::NECUNOSCUT;

	}

	//Destructor
	~Sectie() {
		if (this->nume != nullptr)
			delete[] this->nume;

		if (this->ture != nullptr)
			delete[] this->ture;
		cout << "\nDESTRUCTOR.";
	}

	//5. 4 getteri

	char* getNume() {
		return nume;
	}
	int getGEN() {
		return (int)gen;
	}
	bool getConcediu() {
		return concediu;
	}
	int getNrZile() {
		return nrZile;
	}

	//6. 4 setteri cu validãri pe variabilele primite ca input
	void setNume(const char* nume) {
		if (nume != nullptr) {
			delete[] this->nume;
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else
			throw new exception("Numele este invalid, null!");
	}
	void setPrenume(string prenume) {
		if (!prenume.empty())
			this->prenume = prenume;
		else
			throw new exception("Prenumele este gol!");
	}
	void setConcediu(bool concediu) {
		if (concediu == 0 || concediu == 1)
			this->concediu = concediu;
		else
			throw new exception("Concediul a fost introdus gresit: 0 - a avut concediu; 1 - nu a avut concediu");
	}
	void setVanzari(float* ture) {
		if (ture != nullptr) {
			delete[] this->ture;
			this->ture = new float[nrZile];
			for (int i = 0; i < nrZile; i++)
				this->ture[i] = ture[i];
		}
		else
			throw new exception("Turele lucrate au valoarea nullptr");
	}

	//7. Operatorul >>
	friend istream& operator>>(istream& in, Sectie& s) {
		cout << "\n\nIntroduceti datele: ";
		char aux[100];
		cout << "Nume: "; in >> aux;
		if (s.nume != nullptr) {
			delete[] s.nume;
		}
		if (s.ture != nullptr) {
			delete[] s.ture;
		}
		s.nume = new char[strlen(aux) + 1];
		strcpy_s(s.nume, strlen(aux) + 1, aux);

		cout << "Prenume: "; in >> s.prenume;
		cout << "Nr zile: "; in >> s.nrZile;
		s.ture = new float[s.nrZile];

		for (int i = 0; i < s.nrZile; i++) {
			cout << "Ture in ziua " << i << ": ";
			in >> s.ture[i];
		}

		cout << "Concediu(1=disponibil, 0=utilizat): "; in >> s.concediu;
		cin.get();
		int x;
		cout << "Gen(1=femeie, 2=barbat, 3=necunoscut): "; in >> x;
		switch (x) {
		case 1: s.gen = GEN::FEMEIE; break;
		case 2: s.gen = GEN::BARBAT; break;
		case 3: s.gen = GEN::NECUNOSCUT; break;
		}
		return in;
	}

	// Opetatorul <<
	friend ostream& operator<<(ostream& out, Sectie& s) {
		out << "Cod: " << s.cod << ", Nume: " << s.nume << ", Prenume: " << s.prenume;
		switch (s.getGEN()) {
		case 1: out << "\nGen: FEMEIE "; break;
		case 2: out << "\nGen: BARBAT "; break;
		case 3: out << "\nGen: NECUNOSCUT "; break;
		}
		switch (s.concediu) {
		case 0: out << ", Concediu: epuizat"; break;
		case 1: out << ", Concediu: disponibil"; break;
		}
		out << ", Nr zile: " << s.nrZile;
		out << "\nTure: ";
		for (int i = 0; i < s.nrZile; i++)
		{
			out << "\nin ziua " << i << ": " << s.ture[i];
		}
		return out;
	}

	//8. Operatorul --(post-decrementat)
	Sectie operator--(int) {
		if (ture[nrZile - 1] > 1) {
			Sectie aux(*this);
			float* auxiliar = new float[nrZile];
			for (int i = 0; i < nrZile - 1; i++)
				auxiliar[i] = ture[i];
			auxiliar[nrZile - 1] = ture[nrZile - 1] - 1;
			delete[] this->ture;
			this->ture = auxiliar;
			return aux;
		}
		else
			return *this;
	}
	//Operatorul index[]
	float& operator[](int index) {
		if (index >= 0 && index < nrZile) {
			return ture[index];
		}
		else {
			cout << "Eroare";
			//throw new exception("Eroare: nrZile");
		}
	}
	//Operatorul !
	bool operator!() {
		return !concediu;
	}

	//9. Stergere
	void stergereElement(float elem) {
		int index = -1;
		float* aux = new float[nrZile - 1];
		for (int i = 0; i < nrZile; i++) {
			if (elem == ture[i]) {
				index = i;
				break;
			}
			aux[i] = this->ture[i];
		}
		if (index != -1) {
			this->nrZile--;
			for (int i = index; i < nrZile; i++)
				aux[i] = this->ture[i + 1];
			delete[] this->ture;
			this->ture = aux;
		}

	}

	//Adaugare
	void adaugareElement(float elem) {
		float* aux = new float[nrZile + 1];
		for (int i = 0; i < nrZile; i++)
			aux[i] = ture[i];
		aux[nrZile] = elem;
		nrZile++;
		delete[] this->ture;
		this->ture = aux;

	}
	//10. Calcul nr de elem poz , nr de elem neg
	int calcul()
	{
		int i, cate = 0;
		for (i = 0; i < this->nrZile; i++)
			if (this->ture[i] > 0)
				cate++;
		return cate;
	}
};
int Sectie::nrAngajati = 0;
int main()
{

	float vector[] = { 10,11,12 };
	//2:
	Sectie s1("Ionescu", vector, 2, GEN::BARBAT);
	cout << "\n\n Cerinta2: " << "\nS-a executat linia: \nSectie s1(""Ionescu"", vector, 2, GEN::BARBAT)";
	cout << "\ns1: " << s1;


	//Cerinta 3, 4 si 7::
	cout << "\n\n Cerintele 3, 4 si 7: " << "\nSe executa urmatoarele linii de cod: "
		<< "\nSectie s2(s1), s3;\ns3 = s2;\nSectie s4;";

	Sectie s2(s1), s3;
	s3 = s2;
	Sectie s4;
	cout << "\ns1: " << s1;
	cout << "\ns2: " << s2;
	cout << "\ns3: " << s3;
	cout << "\ns4: " << s4;

	cout << "\n\ntest operator >>: ";
	Sectie s5;
	cin >> s5;
	cout << s5;


	//(cerinta 5)-getteri:
	cout << "\n\n getteri:";
	cout << "\ns1.getNume(): " << s1.getNume();
	cout << "\ns1.getNrZile(): " << s1.getNrZile();
	cout << "\ns1.getGEN(): ";
	switch (s1.getGEN()) {
	case 1: cout << "FEMEIE"; break;
	case 2: cout << "BARBAT"; break;
	case 3: cout << "NECUNOSCUT"; break;
	}
	cout << "\ns1.getConcediu(): ";
	switch (s1.getConcediu()) {
	case 0: cout << "\nConcediu: indisponibil"; break;
	case 1: cout << "\nConcediu: disponibil";
	}


	//(cerinta 6)-setteri:
	cout << "\n\n  setteri: ";
	cout << "\nSe executa urmatoarele linii de cod:\ns1.setNume(""Stirbescu"");\ns1.setConcediu(1);\ns1.setTure(vector2);\ns1.setPrenume(""Monica""); ";
	float vector2[] = { 2,5,15 };
	s1.setNume("Stirbescu");
	s1.setConcediu(0);
	s1.setVanzari(vector2);
	s1.setPrenume("Monica");
	cout << "\ns1: " << s1;


	//Cerinta 8:
	cout << "\n\n Cerinta 8: ";
	cout << "\ns1: " << s1;
	cout << "\nSe afiseaza s1 negat(! - neaga concediul): " << !s1;
	s1--;
	cout << "\nSe executa s1--(s1-- -> scade nr de ture in ultima zi):\n " << s1;
	cout << "\nop index: s1[2]= " << s1[2];


	//Cerinta 9:
	cout << "\n\nCerinta 9: ";
	cout << "\nSe executa: \ns1.stergereElement(2);\ns1.adaugareElement(2);";
	s1.stergereElement(2);
	s1.adaugareElement(2);
	cout << "\n" << s1;

	//Cerinta 10:
	cout << "\n\nCerinta 10: ";
	cout << "Nr de elem pozitive ";
	cout << s1.calcul() << endl;
	cout << "Nr de elem negative ";
	cout << s1.getNrZile() - s1.calcul() << endl;

};







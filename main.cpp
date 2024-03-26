#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;
class medicament{
	char nume[30];
	int pret;
	public:
		medicament()
			{
				strcpy(nume, "Medicament");
				pret=1;
             }
         int Pret() const
         {
             return pret;
         }
         void schimbarepret(int x)
         {
             pret=x;
         }
         void citeste()
         	{
         		cout<<"Denumire: ";
         		cin.get();
         		cin.getline(nume,30);
         		cout<<"Pret: ";
         		cin>>pret;
         	}
         friend ostream & operator << (ostream & out , const medicament & med)
        {
            out<<med.nume<<" : "<<med.pret<<" de lei."<<endl;
            return out;
        }
        ~medicament(){
         }
        medicament(const medicament &a);
        medicament & operator = (const medicament & med)
        {
        	pret=med.pret;
        	strcpy(nume,med.nume);
        	return *this;
        }

};
medicament::medicament(const medicament &a)
{
	strcpy(nume,a.nume);
	pret=a.pret;
}
class pacient{
	char nume[30];
	int nrmed;
	medicament a[10];
	public:
		pacient()
		{
			strcpy(nume,"Pacient");
			nrmed=0;
		}
		int costuri() const
		{
			int s=0;
			for (int i=0;i<nrmed;i++)
			{
				s=s+a[i].Pret();
			}
			return s;
		}
		void setNrmed(int x);
		int getNrmed();
		void citeste()
		{
			cin.getline(nume,30);
		}
		void setMed(medicament m, int i);
		 friend ostream & operator << (ostream & out , const pacient & p)
        {
            for(int i=0;i<p.nrmed;i++)
        		out<<p.a[i];
        	out<<"Ele costa in total "<<p.costuri()<<" lei"<<endl;
            return out;
        }
        void getnume(char s[30]) const
        {
        	strcpy(s,nume);
        }
        void citescnume()
        {
        	cin.getline(nume,30);
        }
        void meniu()
        {
        	cout<<"0. Intoarceti-va\n";
        	cout<<"1. Prescrieti un medicament.\n";
        	cout<<"2. Vizualizati lista de medicamente.\n";
        	cout<<"3. Schimbati un medicament\n";
        	cout<<"4. Copie medicament\n";
        	int buton;
        	cin>>buton;
        	if(buton==0)
        		;
        	else
                if(buton==1)
                {
                    (*this).prescriere();
                    (*this).meniu();
                }
                else
                    if(buton==2)
                    {
                        cout<<*this;
                        (*this).meniu();
                    }
                    else
                        if(buton==3)
                        {
                            medicament x;
                            (*this).setMed(x,0);
                            cout<<x;
                            (*this).meniu();
                        }
                        else
                        {
                            medicament x(a[0]);
                            cout<<x;
                            (*this).meniu();
                        }
        }
        void prescriere()
        {
        	nrmed++;
        	a[nrmed-1].citeste();
        }
};
void pacient::setNrmed(int x)
{
	nrmed=x;
}
void pacient::setMed(medicament m, int i)
{
	a[i]=m;
}
int pacient::getNrmed()
{
	return nrmed;
}
class medic{
	char nume[30];
	int nrpacienti;
	pacient pacienti[20];
	int program[5][8];
	int salariu;
	char specializare[30];
	public:
		medic()
		{
			strcpy(nume,"Medic");
			nrpacienti=0;
			for(int i=0;i<5;i++)
				for(int j=0;j<8;j++)
					program[i][j]=0;
			strcpy(specializare,"Medic de familie");
		}
		friend ostream & operator << (ostream &out, const medic &medik)
		{
			char s[30];
			for(int i=0;i<medik.nrpacienti;i++)
			{
				medik.pacienti[i].getnume(s);
				out<<i+1<<". "<<s<<endl;
			}
			return out;
		}
		bool ocupat(int x,int y)
		{
			if (program[x-1][y-9]==1)
				return true;
			return false;
		}
		void getnume(char s[30]) const
		{
			strcpy(s,nume);
		}
		void citire()
		{
			cin.get();
			cout<<"Nume: ";
			cin.getline(nume,30);
			cout<<"Specializare: ";
			cin.getline(specializare,30);
		}
		void meniu()
		{
			int buton;
			cout<<"Nume: "<<nume<<endl;
			cout<<"Specializare: "<<specializare<<endl;
			cout<<"1. Faceti programare."<<endl;
			cout<<"2. Vizualizati lista pacientilor."<<endl;
			cout<<"3. Intoarceti-va\n";
			cin>>buton;
			if(buton==1)
			{
				(*this).programare();
				(*this).meniu();
			}
			else if(buton==2)
			{
				(*this).vizualizare();
				(*this).meniu();
			}
			else ;
		}
		bool liber()
		{
			bool x=false;
			for(int i=0;i<5;i++)
				for(int j=0;j<8;j++)
					if(program[i][j]==0)
					{
						x=true;
						break;
					}
			return x;
		}
		void vizualizare()
		{
			int buton;
			char s[30];
			cout<<"0. Intoarceti-va.\n";
			cout<<*this;
			cin>>buton;
			if(buton==0)
				;
			else
            {
				pacienti[buton-1].meniu();
				cout<<"Ne intoarcem"<<endl;
				(*this).vizualizare();
            }
		}
		void programare()
		{
			if(!(*this).liber())
			{
				cout<<"Programul medicului este plin pe saptamana asta. Incercati saptamana viitoare.";
			}
			else
			{
				cout<<"Alegeti ziua:"<<endl;
				cout<<"1.Luni\n2.Marti\n3.Miercuri\n4.Joi\n5.Vineri\n";
				int buton1,buton2;
				cin>>buton1;
				cout<<"Alegeti o ora de la 9 la 16.\n";
				cin>>buton2;
				if(program[buton1-1][buton2-9]==0)
				{
					cout<<"Introduceti numele pacientului.\n";
					cin.get();
					nrpacienti++;
					pacienti[nrpacienti-1].citescnume();
					program[buton1-1][buton2-9]=1;
					cout<<"Ne intoarcem la meniul doctorului.\n";
				}
				else
				{
					cout<<"Domnul doctor este ocupat in acea zi si la acea ora. Incercati alta data.\n";
				}
			}
		}

};
class spital
{
	char nume[30];
	medic medici[5];
	int nrmedici;
	public:
		spital()
		{
			nrmedici=0;
			strcpy(nume,"Spital");
		}
		friend ostream & operator << (ostream &out, const spital &hospital)
		{
			char s[30];
			out<<"0. Reveniti la ecranul principal."<<endl;
            for(int i=0;i<hospital.nrmedici;i++)
            {
                hospital.medici[i].getnume(s);
                out<<i+1<<"."<<s<<endl;
            }
			return out;
		}
		void vizualizare()
		{
			if(nrmedici==0)
			{
				cout<<"Spitalul inca nu a angajat medici. Alegeti alta varianta.\n";
			}
			else
			{
				char s[30];
				int buton;
				cout<<"0. Reveniti la ecranul principal."<<endl;
				for(int i=0;i<nrmedici;i++)
				{
					medici[i].getnume(s);
					cout<<i+1<<"."<<s<<endl;
				}
				cin>>buton;
				if(buton==0)
					;
				else
                {
					medici[buton-1].meniu();
					(*this).vizualizare();
                }
			}
		  }
		void angajare()
		{
			nrmedici++;
			medici[nrmedici-1].citire();
			cout<<"Ne intoarcem la meniul principal\n";
		}
		void setNrmed(int x)
		{
		    nrmedici=x;
		}
		void gestiune()
		{
			int buton;
			cout<<"1. Vizualizare"<<endl;
			cout<<"2. Angajare"<<endl;
			cout<<"3. Inchidere"<<endl;
			cout<<"4. Schimbare numar medici"<<endl;
			cin>>buton;
			if(buton==1)
			{
				(*this).vizualizare();
				(*this).gestiune();
			}
			else
                if(buton==2)
                {
                    (*this).angajare();
                    (*this).gestiune();
                }
				else
                    if(buton==4)
                    {
                        int x;
                        cin>>x;
                        setNrmed(x);
                        cout<<"Sunt "<<x<<" medici."<<endl;
                        (*this).gestiune();
                    }
                    else
                        ;

		}
};
int main()
{
	spital x;
	x.gestiune();
	return 0;
}

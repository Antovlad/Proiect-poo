#include <iostream>
#include <cmath>
using namespace std;
class Geoset
{
    protected:
        char nume[10];
        int nrdimensiuni;
    public:
        static int nrmultimi;
        Geoset()
        {
        }
        Geoset(int i)
        {
            nrdimensiuni=i;
            nrmultimi++;
        }
        static int getnr()
        {
            return nrmultimi;
        }
};
int Geoset::nrmultimi=0;
class Forma:public Geoset
{
    public:
        static int nrforme;
        static int getnrforme()
        {
            return nrforme;
        }
        Forma():Geoset()
        {
            nrdimensiuni=2;
        }
        virtual double perimetru()=0;
        virtual double arie()=0;

};
int Forma::nrforme=0;
struct coord
{
    double x,y;
};
class Dreptunghi:public Forma
{
    protected:
        coord colt;
        double lungime;
        double latime;
    public:
        static int nrdreptunghiuri;
        Dreptunghi():Forma(){}
        Dreptunghi(coord xy, double L, double l):Forma()
        {
            colt=xy;
            lungime=L;
            latime=l;
            nrdreptunghiuri++;
        }
        double perimetru()
        {
            return 2*(lungime+latime);
        }
        double arie()
        {
            return lungime*latime;
        }
    protected:
        double getlatime()
        {
            return latime;
        }
};
int Dreptunghi::nrdreptunghiuri=0;
class Patrat:public Dreptunghi
{
    double latura;
    public:
        static int nrpatrate;
        Patrat():Dreptunghi(){}
        Patrat(coord xy,double x):Dreptunghi(xy,x,x)
        {
            colt=xy;
            lungime=x;
            latime=x;
            latura=x;
            nrpatrate++;
        }
        double getlatura()
        {
            return (*this).getlatime();
        }
};
int Patrat::nrpatrate=0;
class Elipsa:public Forma
{
    protected:
        coord centru;
        double raza1,raza2;
    public:
        static int nrelipse;
        Elipsa():Forma(){}
        Elipsa(coord xy, double r1, double r2):Forma()
        {
            centru=xy;
            raza1=r1;
            raza2=r2;
            nrelipse++;
        }
        double perimetru()
        {
            double h=((raza1-raza2)*(raza1-raza2))/((raza1+raza2)*(raza1+raza2));
            return M_PI*(raza1+raza2)*(1+(3*h)/(10+sqrt(4-3*h)));
        }
        double arie()
        {
            return M_PI*raza1*raza2;
        }
};
int Elipsa::nrelipse=0;
class Cerc:public Elipsa
{
    double raza;
public:
    static int nrcercuri;
    Cerc():Elipsa(){}
    Cerc(coord xy, double r):Elipsa(xy,r,r)
    {
        nrcercuri++;
    }
};
int Cerc::nrcercuri=0;
int main()
{
    int tasta;
    cout<<"1.Creati o multime de puncte neregulata\n";
    cout<<"2.Afisati numarul de multimi de puncte.\n";
    cout<<"3.Creati o forma neregulata.\n";
    cout<<"4.Afisati numarul de forme create.\n";
    cout<<"5.Creati un dreptunghi si determinati perimetrul si aria.\n";
    cout<<"6.Creati un patrat si determinati perimetrul si aria.\n";
    cout<<"7.Creati o elipsa si determinati perimetrul si aria.\n";
    cout<<"8.Creati un cerc si determinati perimetrul si aria.\n";
    cin>>tasta;
    if(tasta==1)
    {
        int a;
        cout<<"Numar de dimensiuni:";
        cin>>a;
        Geoset x(a);
    }
    else
        if(tasta==2)
        {
            cout<<Geoset::nrmultimi;
        }
        else
            if(tasta==3)
            {
                cout<<"Ati creat o forma.";
            }
            else
                if(tasta==4)
                {
                    cout<<Forma::nrforme;
                }
                else
                    if(tasta==5)
                    {
                        cout<<"Coordonate:\n";
                        cout<<"x=";
                        double k,l;
                        cin>>k;
                        cout<<"y=";
                        cin>>l;
                        double lg,lt;
                        cout<<"Lungime:";
                        cin>>lg;
                        cout<<"Latime:";
                        cin>>lt;
                        coord punct;
                        punct.x=k;
                        punct.y=l;
                        Dreptunghi dreptunghi(punct,lg,lt);
                        Forma* primu=&dreptunghi;
                        cout<<"Perimetru "<<primu->perimetru()<<endl;
                        cout<<"Arie "<<primu->arie()<<endl;//am folosit functii virtuale, polimorfism si si upcasting
                    }
                    else
                        if(tasta==6)
                        {
                            cout<<"Coordonate:\n";
                            cout<<"x=";
                            double k1,l1;
                            cin>>k1;
                            cout<<"y=";
                            cin>>l1;
                            double lat;
                            cout<<"Latura:";
                            cin>>lat;
                            coord punct2;
                            punct2.x=k1;
                            punct2.y=l1;
                            Patrat patrat(punct2,lat);
                            cout<<"Perimetrul este "<<4*lat;
                            cout<<"Aria este "<<lat*lat;
                            cout<<"Patratul are latura de:"<<patrat.getlatura()<<endl;
                        }
                        else
                            if(tasta==7)
                            {
                                cout<<"Coordonate:\n";
                                cout<<"x=";
                                double k2,l2;
                                cin>>k2;
                                cout<<"y=";
                                cin>>l2;
                                coord punct3;
                                punct3.x=k2;
                                punct3.y=l2;
                                double r3,r4;
                                cout<<"Prima raza:";
                                cin>>r3;
                                cout<<"A doua raza:";
                                cin>>r4;
                                Elipsa elipsa(punct3,r3,r4);
                                Forma* adouas=&elipsa;
                                cout<<"Perimetru "<<adouas->perimetru()<<endl;
                                cout<<"Arie "<<adouas->arie()<<endl;//am folosit functii virtuale, polimorfism si si upcasting
                            }
                            else
                                if(tasta==8)
                            {
                                cout<<"Coordonate:\n";
                                cout<<"x=";
                                double k4,l4;
                                cin>>k4;
                                cout<<"y=";
                                cin>>l4;
                                coord punct6;
                                punct6.x=k4;
                                punct6.y=l4;
                                double radius;
                                cout<<"Raza:";
                                cin>>radius;
                                Cerc cerc(punct6,radius);
                                cout<<"Perimetrul:"<<2*M_PI*radius;
                                cout<<"Aria:"<<radius*radius*M_PI;
                            }


    return 0;
}

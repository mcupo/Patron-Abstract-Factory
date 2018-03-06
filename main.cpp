#include <iostream>

using namespace std;

enum Direccion {Norte, Sur, Este, Oeste};

class LugarDelMapa

{

    public:

        virtual void Entrar()=0;

};

class Habitacion : public LugarDelMapa

{

    private:

        LugarDelMapa*    _lados[4];

        int                _numeroHabitacion;

    public:

        Habitacion(int numHabitacion){}

        LugarDelMapa* ObtenerLado(Direccion) const{}

        void EstablecerLado(Direccion, LugarDelMapa*){}

        virtual void Entrar(){}

};

class Pared : public LugarDelMapa

{

    public:

        Pared(){}

        virtual void Entrar(){}

};

class Puerta : public LugarDelMapa

{

    private:

        Habitacion* _habitacion1;

        Habitacion* _habitacion2;

        bool        _estaAbierta;

    public:

        Puerta(Habitacion* =0, Habitacion* =0){}

        virtual void Entrar(){}

        Habitacion* OtroLadoDe(Habitacion*){}

};

class Laberinto

{

    private:

        //...

    public:

        Laberinto(){}

        void AnadirHabitacion(Habitacion*){}

        Habitacion* NumeroDeHabitacion(int) const{}

};

//No es más que una colección de métodos de fabricación. Al no ser una clase abstracta, hace tanto de FabricaAbstracta como de FabricaConcreta

class FabricaDeLaberintos

{

    public:

        FabricaDeLaberintos(){cout<<"Uso la fabrica FabricaDeLaberintos\n";}

        virtual Laberinto* HacerLaberinto() const{return new Laberinto;}

        virtual Pared* HacerPared() const{return new Pared;}

        virtual Habitacion* HacerHabitacion(int n) const {return new Habitacion(n);}

        virtual Puerta* HacerPuerta(Habitacion* h1, Habitacion* h2) const {return new Puerta(h1,h2);}

};

class Hechizo{};

class HabitacionEncantada : public Habitacion

{

    public:

        HabitacionEncantada(int numHabitacion,Hechizo*):Habitacion(numHabitacion){}

};

class PuertaQueNecesitaHechizo : public Puerta

{

    public:

        PuertaQueNecesitaHechizo(Habitacion* h1, Habitacion* h2):Puerta(h1,h2){}

};

class FabricaDeLaberintosEncantados : public FabricaDeLaberintos

{

    protected:

        Hechizo* Hechizar() const{return new Hechizo;}

    public:

        FabricaDeLaberintosEncantados(){cout<<"Uso la fabrica FabricaDeLaberintosEncantados\n";}

        Habitacion* HacerHabitacion(int n) const {return new HabitacionEncantada(n, Hechizar());}

        Puerta* HacerPuerta(Habitacion* h1, Habitacion* h2) const {return new PuertaQueNecesitaHechizo(h1,h2);}

};

class JuegoDelLaberinto

{

    public:

        Laberinto* CrearLaberinto(FabricaDeLaberintos& fabrica);

};

Laberinto* JuegoDelLaberinto::CrearLaberinto(FabricaDeLaberintos &fabrica)

{

    Laberinto* unLaberinto    = fabrica.HacerLaberinto();

    Habitacion* h1            = fabrica.HacerHabitacion(1);

    Habitacion* h2            = fabrica.HacerHabitacion(2);

    Puerta* unaPuerta        = fabrica.HacerPuerta(h1, h2);

    unLaberinto->AnadirHabitacion(h1);

    unLaberinto->AnadirHabitacion(h2);

    h1->EstablecerLado(Norte, fabrica.HacerPared());

    h1->EstablecerLado(Este, unaPuerta);

    h1->EstablecerLado(Sur, fabrica.HacerPared());

    h1->EstablecerLado(Oeste, fabrica.HacerPared());

    h1->EstablecerLado(Norte, fabrica.HacerPared());

    h1->EstablecerLado(Este, fabrica.HacerPared());

    h1->EstablecerLado(Sur, fabrica.HacerPared());

    h1->EstablecerLado(Oeste, unaPuerta);

    return unLaberinto;

}

void main()

{

    JuegoDelLaberinto juego;

    FabricaDeLaberintosEncantados fabrica;

    //Crear laberinto puede recibir igualmente una instancia de FabricaDeLaberintos, u otras fábricas para construir laberintos

    juego.CrearLaberinto(fabrica);

    cin.get();

}

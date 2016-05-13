#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;
struct player//player information, currently hard coded into the source, in future builds will hopefully be loaded from files
{
double HP = 200;
double END = 200;
double STR = 30;

};
struct enemy//this and the player struct are fairly simple, I will add more attributes and stats soon
{
string enemy_name;
double HP;
double END;
double STR;
};
struct weapon//same with this one
{
string name;
double PWR;
double FTG;
};

void Fight_Display( string n, double x, double y)//displays the health of each party involved in the fight
{
    cout << "The "<<(n)<<" has "<< (x)<<"HP. You have"<<(y)<<"Hp"<<endl;
}
void load_weapon(weapon& x, string y, double s, double f)
{
    x.name = y;
    x.PWR = s;
    x.FTG = f;
}

void choose_weapon(weapon& w)
{
cout << "Please a choose a weapon (enter a number between (0-3)"<<endl;
int input;
char confirm;
cin>>input;
if (input == 0)
{
load_weapon (w, "Fists", 5, 5);
}

if (input == 1)
{
load_weapon (w, "Axe", 20, 25);
}

if (input == 2)
{
load_weapon (w, "Sword", 15, 15);//each weapon data also hard coded, like with the player info I hope to load this from file soon
}

if (input == 3)
{
load_weapon (w, "Staff", 10, 5);
}
cout<<"Is this the weapon you want? (type y or n)"<<endl;
cin >> confirm;

if (confirm == 'n')
{
    choose_weapon(w);
}
}

void load_enemy(enemy& x, string n, int eh, int ee, int es)
{
    x.enemy_name = n;
    x.HP = eh;
    x.END = ee;
    x.STR = es;
}
void choose_eneme(enemy& thing)
{
    int enemyinput;
    char confirm;
    cout << "Please choose an enemy (enter a number between 1-3)"<<endl;
    cin >> enemyinput;
{
if (enemyinput == 1)
{
    load_enemy(thing, "Ogre", 500, 200, 150);
}
if (enemyinput == 2)
{
    load_enemy(thing, "Wolf",250,400,75);
}
if (enemyinput == 3)
{
    load_enemy(thing, "Chicken", 5000, 5000, 5000);
}

}
cout << "You have chosen "<<thing.enemy_name<<". Is this the enemy you want? (type y or n)"<<endl;
cin >> confirm;
if (confirm == 'n')
{
    choose_eneme(thing);
}
}
int main()
{
int input, enemyinput;
double damage = 1.2;//the damage value will not be stuck at 1.2, lol. I will use a random number generator for this
weapon myWeapon;
enemy Theenemy;
player Me;

choose_weapon(myWeapon);
choose_eneme(Theenemy);

double pDamage;
double eDamage;
while( Theenemy.HP >0 && Me.HP >0)//the "Battle block" so to speak. Uses simple math calculations to determine damage done and stamina lost to each party
{
Fight_Display(Theenemy.enemy_name, Theenemy.HP, Me.HP);
pDamage = ((Me.STR + myWeapon.PWR)*(1.00+(Me.END/100)));
eDamage = (Theenemy.STR *(1.00+Theenemy.END/100));
Theenemy.HP -= pDamage;
Me.HP -= eDamage;
Me.END -= myWeapon.FTG;
Theenemy.END -= Theenemy.STR/35;
cout << Me.HP<<"\t"<<Me.END<<endl;
cout << Theenemy.HP<<"\t"<<Theenemy.END<<endl;
}
if (Me.HP<=0.0)//the bad ending
{
    cout<<"You died. Game over! :("<<endl;
}

if (Theenemy.HP <=0.0)//the good ending
{
    cout<<"The "<<Theenemy.enemy_name<<" died. You win!"<<endl;
}

system("PAUSE");
return 0;
}

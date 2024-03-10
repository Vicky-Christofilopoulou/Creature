#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class Creature;

class creature_society
{
    public:
        creature_society(int n, int i, int good, int bad, creature_society *p);
        ~creature_society();
        void Beat(int i);
        void Bless(int i);
        void clone_next(int i);
        void clone_zombies(int i);
        int no_of_good();
        int no_of_zombies();

    private:
        int N;      //number of creatures
        creature_society *cs;
        Creature **Array;
};

class Creature
{
    public:
        Creature(string n, int L,int p, int good, int bad, creature_society *dp);
        virtual ~Creature();
        bool is_a_zombie(){return zombie_flag;}
        virtual bool is_a_good()=0;
        void Clone(Creature *old, Creature *next);
        void Bless(); 
        void Beat();
    protected:
        string name;
        creature_society *cs;
        int Life;
        int pos;
        bool zombie_flag;
        int good_thrsh;
        int bad_thrsh;
};

class good_creature : public Creature
{
    public:
        good_creature(string n, int L,int p, int good, int bad, creature_society *dp);
        virtual ~good_creature(){};
        bool is_a_good(){return true;}
        void Bless();   
};

class bad_creature: public Creature
{
    public:
        bad_creature(string n, int L,int p, int good, int bad, creature_society *dp);
        virtual ~bad_creature(){};
        bool is_a_good(){return false;}
        void Bless();
};


int main(int argc, char *argv[])
{
    int N;              //Number of Creatures
	int M;              //used in main
    int L;             //Life of creatures
    int good_thrsh;
    int bad_thrsh;
    int num;
    int action;
    
    if (argc !=6)
    {
        cout<<"Wrong number of arguments. You must type 5 arguments."<<endl;
        exit(1);
    }
    N= atoi(argv[1]);
    M=atoi(argv[2]);
    L=atoi(argv[3]);
    good_thrsh=atoi(argv[4]);
    bad_thrsh=atoi(argv[5]);


    creature_society Society(N,L,good_thrsh, bad_thrsh, &Society);

    for (int i=0; i<M; i++)
    {
        num=rand() % N;
        action= rand() % 2-1; //0== bless , 1==beat
        if (action == 0 )
        {
            cout <<"Bless creature in position "<< num << endl;
            Society.Bless(num);
        }
        else
        {
            cout <<"Beat creature in position "<< num << endl;
            Society.Beat(num);
        }
    }

    if (Society.no_of_good() == N)
    {
        cout<<"Good Dominates in the World!"<< endl;
    }
    else if (Society.no_of_zombies() == N)
    {
        cout<<"This is a dead society"<<endl;
    }
    else
    {
        cout<<"Try again to improve the world"<<endl;
    }
    return 0;
}


//Functions for Creature
Creature::Creature(string n, int L,int p, int good, int bad, creature_society *dp) : name(n), Life(L), pos(p), good_thrsh(good), bad_thrsh(bad), cs(dp)
{
    cout<<"Constructing a creature."<< endl;
    zombie_flag=false;
}

Creature::~Creature()
{
    cout<<"Destructing a creature."<< endl;
}

void Creature:: Clone(Creature *old, Creature *next)
{
    delete next;
    if (old ->is_a_good())
    {
        good_creature *next= new good_creature(old->name, old->Life, old->pos +1, good_thrsh, bad_thrsh, cs);
    }
    else
    {
        bad_creature *next= new bad_creature(old->name, old->Life,old->pos +1, good_thrsh, bad_thrsh, cs);
    }
}

void Creature::Bless()
{
    if (zombie_flag==false)
    {
        Life++;
        cout<<"The creature was blessed."<<endl<<endl;;
    }
}

void Creature::Beat()
{
    if (Life == 0)
    {
        zombie_flag=true;
        cout<<"The creature is zombie."<<endl<<endl;
    }
    if (zombie_flag==false)
    {
        Life--;
        cout<<"The creature was beaten."<<endl<<endl;
    }
    
}

//Functions for good_creature
good_creature::good_creature(string n, int L,int p, int good, int bad, creature_society *dp) : 
        Creature(n, L,p,good,bad,dp){}

void good_creature::Bless()
{
    if (Life > good_thrsh)
    {
        cs->clone_next(pos);
    }
}

//Functions for bad_creature
bad_creature::bad_creature(string n, int L,int p, int good, int bad, creature_society *dp) :  
        Creature(n, L,p,good,bad,dp){}

void bad_creature::Bless()
{
    if (Life > bad_thrsh)
    {
        cs->clone_zombies(pos);
    }
}

//Functions for creature_society
creature_society::creature_society(int n,int l, int good, int bad,creature_society *dp) : N(n),cs(dp)
{
    cout<<"Constucting a creature society."<<endl;
    Array= new Creature*[N];
    if (!Array)
    {
        cout<<"Error allocating memory!"<< endl;
        exit(1);
    }

    int behavior;
    for (int i=0; i<N; i++)
    {
        behavior = rand() % 2 -1 ; //random way to choose between good (0) or bad (1)
        string n;
        const char* names_good[8]= {"Aurora","Maya","Galahad","Arachne","Elmir","Ziri","Keira","Artemis"};
	    const char* names_bad[8]= {"Daredevil","Xesha","Faceless","Phobos","Astaroth","Satori","Orion","Morrigan"};
        int k=rand()%8;
        
        if (behavior == 0)
        {
            n=names_good[k] + to_string(i);
            Array[i]= new good_creature(n,l,i,good,bad,cs);
            cout<<"Name:"<< n << " Life:" << l << " Position:" << i << " Good Creature."<< endl<< endl;
        }
        else 
        {
            n=names_bad[k]+ to_string(i);
            Array[i]= new bad_creature(n,l,i,good,bad,cs);
            cout<<"Name:"<< n << " Life:" << l << " Position:" << i << " Bad Creature."<< endl<< endl;
        }
        
    }
}

creature_society::~creature_society()
{
    cout<<"Destructing a creature_society."<< endl;
    for (int i=0; i<N; i++)
        delete Array[i];
    delete[] Array;
}

void creature_society:: Beat(int i)
{
    Array[i]->Beat();
}

void creature_society::Bless(int i)
{
    Array[i]->Bless();
}

void creature_society::clone_next(int i)
{
    if (i== N-1) //last creature
    {
        Array[0]-> Clone(Array[i], Array[0]);
    }
    else
    {
        Array[i+1]->Clone(Array[i], Array[i+1]);
    }
}

void creature_society::clone_zombies(int i)
{
    if (i != N) //if i==N last creature -> no clone
    {
        for (int j=i; j<N-1; j++)
        {
            if (Array[j+1]-> is_a_zombie() == true)
            {
                Array[j+1]-> Clone(Array[j], Array[j+1]);
            }
            else 
            {
                break;
            }
        }
    }
}

int creature_society::no_of_good()
{
    int n=0;
    for (int i=0; i<N; i++)
    {
        if (Array[i]->is_a_good() == true)
        {
            n++;
        }
    }
    return n;
}

int creature_society:: no_of_zombies()
{
    int n=0;
    for (int i=0; i<N; i++)
    {
        if (Array[i]->is_a_zombie() == true)
        {
            n++;
        }
    }
    return n;
}
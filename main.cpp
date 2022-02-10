#include <bits/stdc++.h>
#include <unistd.h>
#define CLRSCR "\e[2J\e[H";
#define RED "\x1b[31m";
#define GREEN "\x1b[32m";
#define BLUE "\x1b[34m";
#define MAGENTA "\x1b[35m";
#define WHITE "\x1b[37m";
using namespace std;

int introChoice;
string charName;
bool mapFound = false, sword = false, shield = false, armour = false, bow = false;
int e1 = 0, e2 = 0, e3 = 0, e4 = 0,b1 = 0, p1 = 0;
bool critHits = false, block = false, lifeSteal = false, rDmg = false;
void levelSelect();
void gamePlay(int,int);

class BaseClass{
  public:
  int health,meleeDmg;

  void setHealth(int h){
    health = h;
  }
  int getHealth(){
    return health;
  }

  virtual int Damage() = 0;
  virtual void takeDamage(int) = 0; 
};

class Player : public BaseClass{
  private:
  int rangedDmg;

  public:
  Player(){
    if(armour)
      setHealth(250);
    else
      setHealth(200);
  }

  int Damage(){
    srand(time(NULL));
    int meleeDmg = rand() % (25 - 20 + 1) + 25; 
    int crit = rand() % 4 + 1;
    if(critHits && crit > 2){
      meleeDmg += 30;
      cout<<GREEN;
      cout<<"OH WOW! Its a Critical Damage: "<<meleeDmg<<endl<<RED;
    }
    return meleeDmg;
  }

  void takeDamage(int d){
    health -= d;
    if(health <= 0){
      health = 0;
    }
    setHealth(health);
  }

  int rangedDamage(){
    srand(time(NULL));
    int rangedDmg = rand() % (45 - 40 + 1) + 40; 
    int crit = rand() % 4 + 1;
    if(critHits && crit > 2){
      rangedDmg += 40;
      cout<<GREEN;
      cout<<"OH WOW! Its a Critical Damage: "<<rangedDmg<<endl<<RED;
    }
    return rangedDmg;
  }

  void lifeStealHealing(int h){
    health += h;
    cout<<GREEN;
    cout<<charName<<" used Life Steal Ability and recovers his health by "<<h<<endl;
    if(health >= 200){
      health = 200;
    }
    cout<<charName<<"'s Health: "<<health<<endl<<endl<<RED;
  }

  int Healing(){
    srand(time(NULL));
    int h = rand() % (30 - 25 + 1) + 25;
    if(health < 200){
      health += h;
      cout<<GREEN;
      cout<<charName<<" used Healing Portion and increased his health by: "<<h<<endl<<RED;
      if(health >= 200){
        health = 200;
      }
    }
    else if(health == 200){
      cout<<GREEN;
      cout<<"Can't use Health Potion! Health is already Full "<<endl<<RED;
    }
    return h;
  }
};

class Enemy: public BaseClass{
  public:
  Enemy(){
    setHealth(100);
  }

  int Damage(){
    srand(time(NULL));
    int meleeDmg = rand() % (7 - 5 + 1) + 5; 
    return meleeDmg;
  }

  void takeDamage(int d){
    health -= d;
    if(health <= 0){
      health = 0;
    }
    setHealth(health);
  }

  int AttackorBlock(){
    srand(time(NULL));
    return (rand() % 4 + 1);
  }
};

class Boss : public BaseClass{
  public:
  Boss(){
    setHealth(300);
  }

  int Damage(){
    srand(time(NULL));
    int meleeDmg = rand() % (15 - 10 + 1) + 10; 
    return meleeDmg;
  }

  void takeDamage(int d){
    health -= d;
    if(health <= 0){
      health = 0;
    }
    setHealth(health);
  }

  void bossHealthRegen(int h){
    health += h;
    cout<<RED;
    cout<<"Murlocs recovers his health by "<<h<<endl<<endl<<GREEN;
    if(health >= 300){
      health = 300;
    }
  }

  int groundSlash(){
    srand(time(NULL));
    cout<<RED;
    cout<<"Murlocs used his Ground Slash Ability! "<<endl<<endl<<GREEN;
    int meleeDmg = rand() % (25 - 20 + 1) + 20; 
    return meleeDmg;
  }

  int groundSlashOrBlock(){
    srand(time(NULL));
    return (rand() % 6 + 1);
  }
};

void printStars(){
  cout<<"*********************************************************************************************************************"<<endl<<endl;
  sleep(1);
}

void levelCompleted(int levelNumber){
  cout<<"\t\t *************** Level "<<levelNumber<<" Completed *************** "<<endl<<WHITE;
  sleep(3);
  cout<<CLRSCR;
}

void lockLevel(){
  cout<<"\n\n\t ******* Complete Previous Level to unlock this level! ******* "<<endl
      <<"\t\t\t\t\t\t   Please Wait... "<<endl<<endl;
  sleep(2);
  cout<<CLRSCR;
  levelSelect();
}

void levelUnlocked(int level){
  if(level == 5)
    cout<<"************** BOSS LEVEL UNLOCKED *************** "<<endl;
  else
    cout<<"********** LEVEL "<<level+1<<" UNLOCKED ********** "<<endl;
  cout<<WHITE;
  sleep(4);
  cout<<CLRSCR;
}

void gameOver(){
  cout<<CLRSCR;
  cout<<"\t\t\t******************** GAME OVER! ********************"<<endl;
  cout<<"\t\t\t************ YOU FAILED TO DEFEAT MURLOC ***********"<<endl;
}

int selectEnemy(int levelNumber){
  cout<<WHITE;
  int choice;
  switch(levelNumber){
    case 1:{
      while(e1 == 0){
        if(p1 == 0){
          cout<<"Select which Enemy you want to Attack "<<endl<<endl;
          cout<<"1. Enemy 1"<<endl<<endl;
          cin>>choice;
          if(choice != 1)
            cout<<"Please select a valid option! "<<endl<<endl;
          else
            gamePlay(choice,levelNumber);
        }      
      }
      if(e1 == 1){
        e1 = 0;
        levelCompleted(levelNumber);
        levelSelect();
      }
      else if( p1 == 1){
        gameOver();
      }
      break;
    }
    case 4:
    case 2:{
      while(e1 == 0 || e2 == 0){
        if(p1 == 0){
          cout<<"Select which Enemy you want to Attack "<<endl<<endl;
          cout<<"1. Enemy 1"<<endl;
          cout<<"2. Enemy 2"<<endl<<endl;
          cin>>choice;  
          if((choice == 1 && e1 == 1) || (choice == 2 && e2 == 1))
            cout<<"This Enemy is already Defeated! "<<endl;
          else if(choice == 1 || choice == 2)
            gamePlay(choice,levelNumber);
          else
            cout<<"Please select a valid option! "<<endl<<endl;
        }
      }
      if(e1 == 1 && e2 == 1){
        e1 = e2 = 0;
        levelCompleted(levelNumber);
        levelSelect();
      }
      else if( p1 == 1){
        gameOver();
      }
      break;
    }
    case 3:{
      while(e1 == 0 || e2 == 0 || e3 == 0){
        if(p1 == 0){
          cout<<"Select which Enemy you want to Attack "<<endl<<endl;
          cout<<"1. Enemy 1"<<endl;
          cout<<"2. Enemy 2"<<endl;
          cout<<"3. Enemy 3"<<endl<<endl;
          cin>>choice;  
          if((choice == 1 && e1 == 1) || (choice == 2 && e2 == 1)|| (choice == 3 && e3 == 1))
            cout<<"This Enemy is already Defeated! "<<endl;
          else if(choice == 1 || choice == 2 || choice == 3)
            gamePlay(choice,levelNumber);
          else 
            cout<<"Please select a valid option! "<<endl<<endl;
        }
      }
      if(e1 == 1 && e2 == 1 && e3 == 1){
        e1 = e2 = e3 = 0;
        levelCompleted(levelNumber);
        levelSelect();
      }
      else if( p1 == 1){
        gameOver();
      }
      break;
    }
    case 5:{
      while(e1 == 0 || e2 == 0 || e3 == 0 || e4 == 0){
        if(p1 == 0){                   
          cout<<"Select which Enemy you want to Attack "<<endl<<endl;
          cout<<"1. Enemy 1"<<endl;
          cout<<"2. Enemy 2"<<endl;
          cout<<"3. Enemy 3"<<endl;
          cout<<"4. Enemy 4"<<endl<<endl;
          cin>>choice;  
          if((choice == 1 && e1 == 1) || (choice == 2 && e2 == 1)|| (choice == 3 && e3 == 1) || (choice == 4 && e4 == 1))
            cout<<"This Enemy is already Defeated! "<<endl;
          else if(choice == 1 || choice == 2 || choice == 3 || choice == 4)
            gamePlay(choice,levelNumber);
          else 
            cout<<"Please select a valid option! "<<endl<<endl;
        }
      }
      if(e1 == 1 && e2 == 1 && e3 == 1 && e4 == 1){
        e1 = e2 = e3 = e4 = 0;                                                
        levelCompleted(levelNumber);
        levelSelect();
      }
      else if( p1 == 1){
        gameOver();
      }
      break;
    }
    case 6:{
      while(b1 == 0){
        if(p1 == 0){
          int choice;
          cout<<"Select which Enemy you want to Attack "<<endl<<endl;
          cout<<"1. MURLOCS (Boss) "<<endl<<endl;
          cin>>choice;
          if(choice != 1)
            cout<<"Please select a valid option! "<<endl<<endl;
          else
            gamePlay(choice,levelNumber);
        }
      }
      if(b1 == 1){
        b1 = 0;
        levelCompleted(levelNumber);
        cout<<"******************** GAME COMPLETED! ******************** "<<endl<<endl;
        cout<<"****************** YOU DEFEATED MURLOC ****************** "<<endl;
      }
      else if( p1 == 1){
        gameOver();
      }
      break;
    }
    default:
      cout<<"Level Doesn't Exist!! "<<endl;
  }
  return choice;
}

int bossAttack(int healRegenorGrndSlsh,int *bossSpclAtck,int plyrAtck,int plyrRngd,bool bossTurn,Player &p,Boss &b){
  cout<<RED;
  int bossAtck;
  while(b.getHealth() > 0 && !bossTurn){
    if(b.groundSlashOrBlock() == 6 && (plyrAtck == 1 || plyrRngd == 1)){
      int h = rand() % (15 - 10 + 1) + 10;
      b.takeDamage(0);
      cout<<"MURLOC's Turn: "<<endl;
      cout<<"OH NO! MURLOC Blocked Your Attack and use his special ability of Health Regenration!"<<endl;
      b.bossHealthRegen(h);
      cout<<"MURLOC's Health: "<<b.getHealth()<<endl;
    }
    else if(b.groundSlashOrBlock() == 5 && (plyrAtck == 1 || plyrRngd == 1)){
      int dmg = p.Damage();
      b.takeDamage(dmg);
      cout<<"MURLOC fails to block the attack "<<endl<<GREEN;
      cout<<charName<<" deals a damage of: "<<dmg<<" to MURLOC! "<<endl<<RED;
      cout<<"MURLOC's Health: "<<b.getHealth()<<endl<<endl;
      cout<<"MURLOC's Turn: "<<endl;
      cout<<"MURLOC is trying to use Ground Slash Ability! "<<endl;
      *bossSpclAtck = 1;
    }
    else if(b.groundSlashOrBlock() <= 4){
      if(plyrAtck == 1 && lifeSteal){
        int dmg = p.Damage();
        b.takeDamage(dmg);
        cout<<"MURLOC fails to block the attack "<<endl<<GREEN;
        cout<<charName<<" deals a damage of: "<<dmg<<" to MURLOC! "<<endl<<RED;
        cout<<"MURLOC's Health: "<<b.getHealth()<<endl<<endl;
        p.lifeStealHealing(dmg - 5);
      }
      if(plyrRngd == 1 && rDmg){
        int dmg = p.rangedDamage();
        b.takeDamage(dmg);
        cout<<"MURLOC fails to block the Ranged Attack "<<endl<<GREEN;
        cout<<charName<<" deals a damage of: "<<dmg<<" to MURLOC! "<<endl<<RED;
        cout<<"MURLOC's Health: "<<b.getHealth()<<endl<<endl;
      }
      cout<<"MURLOC's Turn: "<<endl;
      cout<<"MURLOC is trying to Attack! "<<endl;
      bossAtck = 1;
    }
    else{
      cout<<"MURLOC's Turn: "<<endl;
      cout<<"MURLOC is trying to Attack! "<<endl;
      bossAtck = 1;
    }
    bossTurn = true;
  }
  cout<<WHITE;
  return bossAtck;
}

int enemyAttack(int attackorblock,int plyrAtck,int plyrRngd,bool enemyTurn,Player &p,Enemy &e,int enemyNumber){
  cout<<RED;
  int enmyAtck;
  while(e.getHealth()>0 && !enemyTurn){
    if(e.AttackorBlock() == 4 && (plyrAtck == 1 || plyrRngd == 1)){
      e.takeDamage(0);
      cout<<"Enemy "<<enemyNumber<<"'s Turn: "<<endl;
      cout<<"OH NO! Enemy "<<enemyNumber<<" Blocked Your Attack "<<endl
          <<"Enemy "<<enemyNumber<<"'s Health: "<<e.getHealth()<<endl<<endl;
      cout<<"Enemy "<<enemyNumber<<"'s Turn: "<<endl;
      cout<<"Enemy "<<enemyNumber<<" is trying to Attack! "<<endl;
      enmyAtck = 1;
    }
    else if(e.AttackorBlock() <= 3){
      if(plyrAtck == 1 && !lifeSteal && !rDmg){
        int dmg = p.Damage();
        e.takeDamage(dmg);
        cout<<"Enemy "<<enemyNumber<<" fails to block the attack "<<endl<<GREEN;
        cout<<charName<<" deals a damage of: "<<dmg<<" to Enemy "<<enemyNumber<<"! "<<endl<<RED;
        cout<<"Enemy "<<enemyNumber<<"'s Health: "<<e.getHealth()<<endl<<endl;
      }
      if(plyrAtck == 1 && lifeSteal){
        int dmg = p.Damage();
        e.takeDamage(dmg);
        cout<<"Enemy "<<enemyNumber<<" fails to block the attack "<<endl<<GREEN;
        cout<<charName<<" deals a damage of: "<<dmg<<" to Enemy "<<enemyNumber<<"! "<<endl<<RED;
        cout<<"Enemy "<<enemyNumber<<"'s Health: "<<e.getHealth()<<endl<<endl;
        p.lifeStealHealing(dmg - 5);
      }
      if(plyrRngd == 1 && rDmg){
        int dmg = p.rangedDamage();
        e.takeDamage(dmg);
        cout<<"Enemy "<<enemyNumber<<" fails to block the Ranged Attack "<<endl<<GREEN;
        cout<<charName<<" deals a damage of: "<<dmg<<" to Enemy "<<enemyNumber<<"! "<<endl<<RED;
        cout<<"Enemy "<<enemyNumber<<"'s Health: "<<e.getHealth()<<endl<<endl;
      }
      cout<<"Enemy "<<enemyNumber<<"'s Turn: "<<endl;
      cout<<"Enemy "<<enemyNumber<<" is trying to Attack! "<<endl;
      enmyAtck = 1;
    }
    enemyTurn = true;
  }
  cout<<WHITE;
  return enmyAtck;
}

void playerAttack(Player &p,Enemy &e,Boss &b, int *plyrAtck,int *plyrRngd,int enmyAtck,int bossAtck,int bossSpclAtck,int enemyNumber){
  cout<<GREEN;
  char playerInput;
  int dmg = 0;
  while(p.getHealth()>0 &&(tolower(playerInput)!='h' && tolower(playerInput)!='a' && tolower(playerInput)!='b' && tolower(playerInput)!='r')){
    cout<<charName<<"'s Turn: "<<endl<<WHITE;
    if(!block)
      cout<<"Press H to use Healing Potion or A to Attack the opponent "<<endl;
    else if(block && !rDmg)
      cout<<"Press H to use Healing Potion or A to Attack the opponent or B to Block the Opponent's Attack "<<endl;
    else if(block && rDmg)
      cout<<"Press H to use Healing Potion or A to Attack the opponent or B to Block the Opponent's Attack or R to use Ranged Attack "<<endl;
    cin>>playerInput;
    cout<<GREEN;
    switch(tolower(playerInput)){
      case 'h':{
        if(enmyAtck == 1){
          dmg = e.Damage();
          p.Healing();
          cout<<RED;
          cout<<"Enemy "<<enemyNumber<<" deals a damage of: "<<dmg<<" to "<<charName<<"! "<<endl<<GREEN;
          p.takeDamage(dmg);
          cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
        }
        else if(bossAtck == 1){
          dmg = b.Damage();
          p.Healing();
          cout<<RED;
          cout<<"MURLOC deals a damage of: "<<dmg<<" to "<<charName<<"! "<<endl<<GREEN;
          p.takeDamage(dmg);
          cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
        }
        else if(bossSpclAtck == 1){
          dmg = b.groundSlash();
          p.Healing();
          cout<<RED;
          cout<<"MURLOC deals a damage of: "<<dmg<<" to "<<charName<<"! "<<endl<<GREEN;
          p.takeDamage(dmg);
          cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
        }
        else{
          p.Healing();
          cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
        }
        break;
      }
      case 'a':{
        if(enmyAtck == 1){
          dmg = e.Damage();
          p.takeDamage(dmg);
          cout<<charName<<" fails to block the Enemy "<<enemyNumber<<"'s attack "<<endl<<RED;
          cout<<"Enemy "<<enemyNumber<<" deals a damage of: "<<dmg<<" to "<<charName<<"! "<<endl<<GREEN;
          cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
        }
        else if(bossAtck == 1){
          dmg = b.Damage();
          p.takeDamage(dmg);
          cout<<charName<<" fails to block the MURLOC's attack "<<endl<<RED;
          cout<<"MURLOC deals a damage of: "<<dmg<<" to "<<charName<<"! "<<endl<<GREEN;
          cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
        }
        else if(bossSpclAtck == 1){
          dmg = b.groundSlash();
          p.takeDamage(dmg);
          cout<<charName<<" fails to block the MURLOC's Special Attack "<<endl<<RED;
          cout<<"MURLOC deals a damage of: "<<dmg<<" to "<<charName<<"! "<<endl<<GREEN;
          cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
        }

        cout<<charName<<" is trying to attack the Enemy ! "<<endl;
        *plyrAtck = 1;
        break;
      }
      case 'b':{
        if(block){
          if(enmyAtck == 1 || bossAtck == 1){
            cout<<charName<<" Blocked the Opponent's Attack ! "<<endl;
          }
          else if(bossSpclAtck == 1){
            cout<<charName<<" can't Block the MURLOC's Special Attack! "<<endl;
            dmg = b.groundSlash();
            p.takeDamage(dmg);
            cout<<RED;
            cout<<"MURLOC deals a damage of: "<<dmg<<" to "<<charName<<"! "<<endl<<GREEN;
            cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
          }
          else if(enmyAtck == 0 || bossAtck == 0 || bossSpclAtck == 0)
            cout<<"Enemy is not Attacking! You can't use Block! "<<endl;
        }
        else if(!block){
          cout<<"Block is Not Unlocked Yet! "<<endl;
        }
        break;
      }
      case 'r':{
        if(rDmg){
          if(enmyAtck == 1){
            int dmg = e.Damage();
            p.takeDamage(dmg);
            cout<<charName<<" fails to block the Enemy "<<enemyNumber<<"'s attack "<<endl<<RED;
            cout<<"Enemy "<<enemyNumber<<" deals a damage of: "<<dmg<<" to "<<charName<<"! "<<endl<<GREEN;
            cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
          }
          if(bossAtck == 1){
            dmg = b.Damage();
            p.takeDamage(dmg);
            cout<<charName<<" fails to block the MURLOC's attack "<<endl<<RED;
            cout<<"MURLOC deals a damage of: "<<dmg<<" to "<<charName<<"! "<<endl<<GREEN;
            cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
          }
          else if(bossSpclAtck == 1){
            dmg = b.groundSlash();
            p.takeDamage(dmg);
            cout<<charName<<" fails to block the MURLOC's attack "<<endl<<RED;
            cout<<"MURLOC deals a damage of: "<<dmg<<" to "<<charName<<"! "<<endl<<GREEN;
            cout<<charName<<"'s Health: "<<p.getHealth()<<endl<<endl;
          }
          cout<<charName<<" is trying to use Ranged Attack ! "<<endl;
          *plyrRngd = 1;
        }
        else if(!rDmg){
          cout<<"Ranged Attack is Not Unlocked Yet! "<<endl;
          *plyrRngd = 0;
        }
        break;
      }
      default:{
        cout<<"Invalid Input! Please choose a valid option! "<<endl;
        break;
      }
    }
  }
  cout<<WHITE;
}

void gamePlay(int enemyNumber,int level){
  cout<<CLRSCR;
  char playerInput;
  int plyrAtck,plyrRngd,bossSpclAtck;
  int enmyAtck = 0,bossAtck = 0;
  Enemy e;
  Player p;
  Boss b;
  while(p.getHealth() > 0 && e.getHealth() > 0){
    bool enemyTurn = false;
    playerAttack(p,e,b,&plyrAtck,&plyrRngd,enmyAtck,bossAtck,bossSpclAtck,enemyNumber);
    if(p.getHealth() <= 0){
      cout<<WHITE;
      cout<<"\n\n\t\t\t******************* YOU ARE DEAD! ******************"<<endl<<endl;
      p1 = 1;
      e1 = e2 = e3 = e4 = b1 =2;
      sleep(3);
      break;
    }
    else{
      enmyAtck = 0;
      bossAtck = 0;
      bossSpclAtck = 0;
      playerInput = 'x';
      printStars();
      if(level == 6)
        bossAtck = bossAttack(b.groundSlashOrBlock(),&bossSpclAtck,plyrAtck,plyrRngd,enemyTurn,p,b);
      else
        enmyAtck = enemyAttack(e.AttackorBlock(),plyrAtck,plyrRngd,enemyTurn,p,e,enemyNumber);
      plyrAtck = 0;
      plyrRngd = 0;
      printStars();
    }
  }
  if(e.getHealth() <= 0 || b.getHealth() <= 0){
    cout<<RED;
    cout<<"Enemy "<<enemyNumber<<" Defeated! "<<endl<<endl<<WHITE;
    switch(enemyNumber){
      case 1: 
        e1 = 1; b1 = 1; break;
      case 2: 
        e2 = 1; break;
      case 3: 
        e3 = 1; break;
      case 4: 
        e4 = 1; break;
    }
    if(level == 1 && e1 == 1){
      cout<<MAGENTA;
      cout<<charName<<" got a MAP! "<<endl<<endl;
      mapFound = true;
      levelUnlocked(level);
    }
    if(level == 2  && e1 == 1 && e2 == 1){
      cout<<MAGENTA;
      cout<<charName<<" got a SWORD! "<<endl<<endl;
      sword = true;
      critHits = true;
      cout<<charName<<" can now give Critical Hits to the Enemies "<<endl<<endl;
      levelUnlocked(level);
    }
    if(level == 3 && e1 == 1 && e2 == 1 && e3 == 1){
      cout<<MAGENTA;
      cout<<charName<<" got a SHIELD! "<<endl<<endl;
      shield = true;
      block = true;
      cout<<charName<<" can now Block the Enemy Attacks "<<endl<<endl;
      levelUnlocked(level);
    }
    if(level == 4 && e1 == 1 && e2 == 1){
      cout<<MAGENTA;
      cout<<charName<<" got a ARMOUR! "<<endl<<endl;
      armour = true;
      lifeSteal = true;
      cout<<charName<<" Unlocks the ability of Life Steal "<<endl<<endl;
      levelUnlocked(level);
    }
    if(level == 5 && e1 == 1 && e2 == 1 && e3 == 1 && e4 == 1){
      cout<<MAGENTA;
      cout<<charName<<" got a BOW! "<<endl<<endl;
      bow = true;
      rDmg = true;
      cout<<charName<<" can now perform Ranged Attacks "<<endl<<endl;
      levelUnlocked(level);
    }
    if(level == 6 && b1 == 1){
      cout<<MAGENTA;
      cout<<CLRSCR;
      cout<<"You have defeated the MURLOC (Boss)! "<<endl;
      sleep(4);
    }
    selectEnemy(level);
    cout<<WHITE;
  }
}

void loadLevel(int levelNumber){
  if(levelNumber == 6)
    cout<<"\n\n\t\t\t **************** LOADING BOSS LEVEL *****************"<<endl<<endl;
  else 
    cout<<"\n\n\t\t\t ********** LOADING LEVEL "<<levelNumber<<" **********"<<endl<<endl;
  sleep(3);
  cout<<CLRSCR;
  selectEnemy(levelNumber);
}

void levelSelect(){
  cout<<WHITE;
  int ls;
  cout<<"Select a Level! "<<endl<<endl;
  cout<<"1. LEVEL 1 "<<endl;
  cout<<"2. LEVEL 2 "<<endl;
  cout<<"3. LEVEL 3 "<<endl;
  cout<<"4. LEVEL 4 "<<endl;
  cout<<"5. LEVEL 5 "<<endl;
  cout<<"6. BOSS LEVEL "<<endl<<endl;
  cin>>ls;
  switch(ls){
    case 1:{
      loadLevel(1);
      break;
    }
    case 2:{
      if(mapFound)
        loadLevel(2);
      else
        lockLevel();
      break;
    }
    case 3:{
      if(sword)
        loadLevel(3);
      else
        lockLevel();
      break;
    }
    case 4:{
       if(shield)
        loadLevel(4);
      else
        lockLevel();
      break;
    }
    case 5:{
       if(armour)
        loadLevel(5);
      else
        lockLevel();
      break;
    }
    case 6:{
       if(bow)
        loadLevel(6);
      else
        lockLevel();
      break;
    }
    default:{
      cout<<"Please enter correct Level Number! "<<endl;
      break;
    }
  }
}

void Story(){
  cout<<MAGENTA;
  bool a = true;
  char reply;
  cout<<"After many years of exploring magical items in deep and dark caves full of monsters. Now you are returning to your Clover Kingdom!"<<endl
      <<"While returning from your Journey, you met a man. He is afraid and running from something."<<endl
      <<"Their are many injury marks on his body "<<endl
      <<"That man is from the Diamond Kingdom! "<<endl
      <<charName<<" asked him \"What Happened\" "<<endl
      <<"That man told the story of how a Demon King named MURLOC has captured the kingdom and has taken all the citizens captive."<<endl
      <<"Their is no one in the kingdom capable of defeating that evil Demon King"<<endl
      <<"That man asked \" Please Help Us? \" "<<endl<<endl;
  while(a){
    cout<<"Would you like to help him? (Y/N) "<<endl
        <<charName<<" replied - "<<endl;
    cin>>reply;
    cout<<endl;
    if(tolower(reply) == 'y'){
      cout<<WHITE;
      cout<<"You are a true Wizard! "<<endl<<endl<<MAGENTA;
      a = false;
    }
    else{
      cout<<WHITE;
      cout<<"Don't be a coward Help him! "<<endl<<endl<<MAGENTA;
    }
  }
  cout<<"That man replied - THANK YOU SO MUCH! "<<endl
      <<"But you will need some magical items - MAP, SWORD, SHIELD, ARMOUR, BOW in order to defeat the Demon King!"<<endl
      <<"And you have to complete the 5 Levels to reach the Demon King, which are full of Demons "<<endl
      <<"You will get magical items once you complete a level, which will help you to defeat the Demon King "<<endl<<endl;
  cout<<"Now Your New Journey Begins! "<<endl;
  sleep(10);
  cout<<WHITE;
}

void intro(){
  cout << CLRSCR;
  cout<<"Please Select: "<<endl<<endl
      <<"1. Start Game "<<endl
      <<"2. Rules "<<endl
      <<"3. Exit "<<endl<<endl;
  cin>>introChoice;
  switch(introChoice){
    case 1:{
      cout<<CLRSCR;
      cout<<"Enter Your Character's Name: "<<endl;
      cin>>charName;
      cout<<CLRSCR;
      Story();
      cout<<CLRSCR;
      levelSelect();
      break;
    }
    case 2:{
      bool ret = true;
      char back;
      while(ret){
        cout << CLRSCR;
        cout<<"-------------------- RULES -------------------- "<<endl
            <<"1) There are total 6 levels in the game."<<endl
            <<"2) There are multiple Enemies in each levels and you have to defeat all of them to complete the level."<<endl
            <<"3) If the health of the player reaches 0, then the player will lose and the game will end."<<endl
            <<"4) Player have many special abilities like critical damage, life steal, block, ranged attacks."<<endl
            <<"5) Each special abilities will get unlock after completing a level."<<endl
            <<"6) You can't block special attacks of enemies "<<endl
            <<"7) You have to defeat the MURLOCK (Boss) to complete the game!"<<endl<<endl;
        cout<<"Press B to go back to the Main Menu!!! "<<endl;
        cin>>back;
        if(tolower(back) == 'b'){
          intro(); 
          ret = false;
        }
        else{
          cout<<"Please enter a valid option! "<<endl;
          sleep(2);
          cout<<CLRSCR;
        }
      }
      break;
    } 
    case 3:{
      char e;
      cout<<"Do you want to leave the game!!! ( Y/N )"<<endl;
      cin>>e;
      if(e == 'y' || e == 'Y'){
        cout<<"Game is closing"<<endl;
        sleep(2);
        exit(0);
      }
      else if(e == 'n' || e == 'N'){
        cout<<"Taking you back to the main menu"<<endl
            <<"Wait for some time"<<endl;
        sleep(2);
        intro();
      }
    }
    default:{
      cout<<"Please enter a valid option! "<<endl;
      break;
    }
  }
}

int main(){
  cout << CLRSCR;
  cout<<"\t\t\t\t******************************************************************************************** "<<endl
      <<"\t\t\t\t*                                                                                           *"<<endl
      <<"\t\t\t\t*                   Welcome to the Text-Based RPG Adventure Game!!!                         *"<<endl
      <<"\t\t\t\t*                                                                                           *"<<endl
      <<"\t\t\t\t*********************************************************************************************"<<endl<<endl<<endl;
  cout<<"\t\t\t\t                         ( PLEASE WAIT! GAME IS LOADING....)                                "<<endl<<endl<<endl;
  sleep(4);
  cout<<CLRSCR;
  intro();
}
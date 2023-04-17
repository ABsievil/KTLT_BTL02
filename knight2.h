#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

class BaseBag;
class BaseOpponent;
class BaseKnight;
class ArmyKnights;
class BaseItem;
class Events;
class KnightAdventure;
// #define DEBUG

enum ItemType {ANTIDOTE=0,PHOENIXDOWNI,PHOENIXDOWNII,PHOENIXDOWNIII,PHOENIXDOWNIV, NULLITEMTYPE};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

class Node {
public:
    ItemType data;
    Node* next;
    Node() {
        next = NULL;
    }
    Node(ItemType value) {
        data = value;
        next = NULL;
    }
};

class BaseBag {
protected:
    int a,b;    //phoenixdownI and antidote
    int limit;
    int size;

    BaseKnight *bagofknight;    
    Node *head;
    Node *lastHead;
public:
    virtual ~BaseBag(){}
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    virtual bool addFirst(ItemType value);
    
    /* LIST: */
    Node *getHead(){return head;}
    Node *getLastHead(){return lastHead;}
    void deleteFirst() {
        if (head != NULL) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
        }
    }
    bool find(ItemType value) {
        Node* current = head;
        while (current != NULL) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    void swapWithFirst(ItemType value) {
        Node* current = head;
        while (current != NULL) {
            if (current->data == value) {
                ItemType temp = head->data;
                head->data = current->data;
                current->data = temp;
            }
            current = current->next;
        }
    }
    void delete3Item(){
        if(size>=3){
           deleteFirst();
           deleteFirst();
           deleteFirst();
        }
        else if(size==2){
            deleteFirst();
            deleteFirst();
        }
        else if(size==1){
            deleteFirst();
        }
    }
    ItemType findPhoenixdown(Node* startNode){
        Node* current = startNode;
        if(current==head) lastHead=NULL;
        while (current != NULL) {
            if (current->data == PHOENIXDOWNI || 
                current->data == PHOENIXDOWNII || 
                current->data == PHOENIXDOWNIII || 
                current->data == PHOENIXDOWNIV ) {
                if (current->next != NULL) {
                    lastHead = current->next;
                } 
                else {
                    lastHead = NULL;
                }    
                return current->data;
            }
            current = current->next;
        }
        return NULLITEMTYPE;  //tìm không thấy thì trả về itemType này
    }
    void destructorList();
    void setBag();
};
class BagOfPaladin:public BaseBag{
public:
    ~BagOfPaladin();
    BagOfPaladin(int a,int b,BaseKnight* knight);
    bool addFirst(ItemType value) override;
};
class BagOfLancelot:public BaseBag{
public:
    ~BagOfLancelot();
    BagOfLancelot(int a,int b,BaseKnight* knight);
};
class BagOfDragon:public BaseBag{
public:
    ~BagOfDragon();
    BagOfDragon(int a,int b,BaseKnight* knight);
    bool addFirst(ItemType value) override;
};
class BagOfNormal:public BaseBag{
public:
    ~BagOfNormal();
    BagOfNormal(int a,int b,BaseKnight* knight);
};

class BaseOpponent{  //lớp trừu tượng của đối thủ
protected:
    int levelO;
public:
    int getLevelO(){return levelO;}   

};
class Monster_1to5:public BaseOpponent{
public:
     Monster_1to5(int i,int event);
     int gilMonster(int);
     int BaseDamage(int);

};
class Monster_6and7:public BaseOpponent{
public:
     Monster_6and7(int i,int event);
};
class Monster_99:public BaseOpponent{
private:
     int HP=5000;
public:     
      void setHP(int HP){this->HP=HP;}
      int getHP(){return HP;}
};

class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;
    int phoenixdownI;
    bool poisonAntidote=false;
public:
    BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    ~BaseKnight();
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        BaseKnight *ptr=new BaseKnight(id,maxhp,level,gil,antidote,phoenixdownI);
        return ptr;
    }
    void setBaseBag(BaseKnight *knight);

    string toString() const;
 
    /*check type knight first game*/
    int set_KnightType(int HP);
    bool check_Snt(int );
    bool check_NumPythagoras(int HP);
    
    /* GET SET: */
    int getMaxHp() const { return maxhp; }
    int getHp() const {return hp;}
    int getLevel() const { return level; }
    int getGil() const { return gil; }
    int getAntidote() const { return antidote; }
    int getPhoenixDownI() const { return phoenixdownI; }
    KnightType getKnightType(){return knightType;}
    BaseBag* getBag(){return bag;}
    bool getPoisonAntidote(){return poisonAntidote;}

    void setHp(int newHp) { 
        hp=newHp; 
        if(hp>maxhp) hp=maxhp;
    }
    void setLevel(int newLevel) { 
        level = newLevel; 
        if(level>10) level=10;
    }
    void setGil(int newGil) { 
        gil = newGil; 
        if(gil>999) gil=999;
    }
    float setKnightBaseDamage(KnightType knightType);
    void setPoisonAntidote(bool logic){
        this->poisonAntidote=logic;
    }
};

class ArmyKnights {
private:
    int n;
    int countArmy;
    int idLastKnight;
    BaseKnight **knight; 
    bool paladinShield=0,
    lancelotSpear=0,
    guinevereHair=0,
    excaliburSword=0;  
    int numTreasure=0;  
    bool passOmegaWeapon=0, 
    passHades=0;
    int eventPresent;

public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight ( BaseOpponent *opponent );
    bool adventure (Events * events);

    BaseKnight * lastKnight() const;
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    
    int count() const { return countArmy; }
    void printInfo() const;
    void printResult(bool win) const;

    bool setEvent_1to5(int level,int levelO,BaseOpponent *opponent,BaseKnight *access);
    void increaseGil(Monster_1to5 *monster,BaseKnight *access);
    bool HPrecovery(BaseKnight *access);
    bool setEvent_6(int level,int levelO,BaseOpponent *opponent,BaseKnight *access);
    void setEvent_7(int level,int levelO,BaseOpponent *opponent,BaseKnight *access);
    void increaseGil(BaseKnight *access);
    void setEvent_8(BaseKnight *access);
    bool setEvent_10(BaseKnight *access);
    bool setEvent_11(BaseKnight *access);
    bool setEvent_99(BaseOpponent *opponent);
    void setEventPhoenixdown(BaseItem *item,BaseKnight *access); 
};

class BaseItem {
protected:
        ItemType type;    
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    virtual ItemType getType()=0;
};
class Antidote: public BaseItem{   
public:
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
    ItemType getType();    
};
class PhoenixDownI: public BaseItem{
public:
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
    ItemType getType();
};
class PhoenixDownII: public BaseItem{
public:
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
    ItemType getType();
};
class PhoenixDownIII: public BaseItem{
public:
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
    ItemType getType();
};
class PhoenixDownIV: public BaseItem{
public:
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
    ItemType getType();
};

class Events {
private:  
    int e;
    int *arrEvent;    
public:
    Events(const string &file_events);
    ~Events();
    int count() const;
    int get(int i) const;
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;
    string file_armyknights, file_events;
public:
    KnightAdventure();
    ~KnightAdventure();
 
    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__
#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
void BaseBag::setBag(){
    head = NULL;
    lastHead= NULL;
    size = 0;
    if(bagofknight->getKnightType()==LANCELOT) limit=16;
    else if(bagofknight->getKnightType()==DRAGON) limit=14;
    else if(bagofknight->getKnightType()==NORMAL) limit=19;
    if(a>0){
        for(int i=0;i<a;i++){
            addFirst(PHOENIXDOWNI);
        } 
    }
    if(b>0){
        if(bagofknight->getKnightType()!= DRAGON){
            for(int i=0;i<b;i++){
                addFirst(ANTIDOTE);
            }
        }
    }
}
bool BaseBag::addFirst(ItemType value) {
    if (size < limit) {
        Node* newNode = new Node(value);
        newNode->next = head;   //gán địa chỉ node đầu tiên lúc trước vào newNode để newNode có thể trỏ đến node đó
        head = newNode;         //gán địa chỉ của newNode vào head để head lưu địa chỉ của newNode  
        size++;
        return true;
    }
    else return false;
}
bool BaseBag::insertFirst(BaseItem * item){ 
    if( addFirst(item->getType()) ==true ) return true;   
    else return false;
    //do túi đồ của Paladin là unlimit
}    
BaseItem *BaseBag::get(ItemType itemType) {
    if(find(itemType)){
        switch (itemType) {
            case ANTIDOTE:
                return new Antidote();
            case PHOENIXDOWNI:
                return new PhoenixDownI();
            case PHOENIXDOWNII:
                return new PhoenixDownII();
            case PHOENIXDOWNIII:
                return new PhoenixDownIII();
            case PHOENIXDOWNIV:
                return new PhoenixDownIV();
            default:
                return NULL;
        }
    }
    else {
        return NULL;
    }
}
string BaseBag::toString() const {
    // Bag[count=<c>;<list_items>]
    string Antidote="Antidote", 
    PhoenixI="PhoenixI",
    PhoenixII="PhoenixII", 
    PhoenixIII="PhoenixIII", 
    PhoenixIV="PhoenixIV";
    string s("Bag[count=");
    s=s+to_string(size)+";";
    Node* current = head;
    int num=0;
    while(current != NULL){
    if(num>0) s+=",";
        if(current->data==ANTIDOTE) s+=Antidote;
        else if(current->data==PHOENIXDOWNI) s+=PhoenixI;
        else if(current->data==PHOENIXDOWNII) s+=PhoenixII;
        else if(current->data==PHOENIXDOWNIII) s+=PhoenixIII;
        else if(current->data==PHOENIXDOWNIV) s+=PhoenixIV;
        // di chuyển đến nút tiếp theo
        current = current->next;
        num++;
    }
    s+="]";
    return s;
}
void BaseBag::destructorList(){
        Node* current = head;
        while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
        }
    }

BagOfPaladin::BagOfPaladin(int a,int b,BaseKnight *knight){
    this->a=a;
    this->b=b;
    this->bagofknight=knight;
    setBag();
}
bool BagOfPaladin::addFirst(ItemType value){
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    size++;
    return true;
}
BagOfPaladin::~BagOfPaladin(){
    destructorList();
}

BagOfLancelot::BagOfLancelot(int a,int b,BaseKnight *knight){
    this->a=a;
    this->b=b;
    this->bagofknight=knight;
    setBag();
}
BagOfLancelot::~BagOfLancelot(){
    destructorList();
}

BagOfDragon::BagOfDragon(int a,int b,BaseKnight *knight){
    this->a=a;
    this->b=b;
    this->bagofknight=knight;
    setBag();
}
bool BagOfDragon::addFirst(ItemType value) {
    if(value != ANTIDOTE){
        if (size < limit) {
            Node* newNode = new Node(value);
            newNode->next = head;   //gán địa chỉ node đầu tiên lúc trước vào newNode để newNode có thể trỏ đến node đó
            head = newNode;         //gán địa chỉ của newNode vào head để head lưu địa chỉ của newNode  
            size++;
            return true;
        }
        else return false;
    }
    else return false;
}
BagOfDragon::~BagOfDragon(){
    destructorList();
}

BagOfNormal::BagOfNormal(int a,int b,BaseKnight *knight){
    this->a=a;
    this->b=b;
    this->bagofknight=knight;
    setBag();
}
BagOfNormal::~BagOfNormal(){
    destructorList();
}
/* * * END implementation of class BaseBag * * */


/* * * BEGIN implementation of class BaseItem * * */
//Antidote:
    bool Antidote::canUse(BaseKnight *knight){
         return true;
    }
    void Antidote::use(BaseKnight *knight){
         knight->getBag()->swapWithFirst(ANTIDOTE);
         knight->getBag()->deleteFirst();
         // edit propeties knight
         knight->setPoisonAntidote(false);
    }
    ItemType Antidote::getType(){
        type=ANTIDOTE;
        return type;
    }

//PhoenixdownI:
    bool PhoenixDownI::canUse(BaseKnight *knight){
         if(knight->getHp()<=0) return true;
         else return false;
    }
    void PhoenixDownI::use(BaseKnight *knight){
        knight->getBag()->swapWithFirst(PHOENIXDOWNI);
        knight->getBag()->deleteFirst();
        // edit propeties knight
        knight->setHp(knight->getMaxHp());
        knight->setPhoenixDownI((knight->getPhoenixDownI()-1));
    }
    ItemType PhoenixDownI::getType(){
        type=PHOENIXDOWNI;
        return type;
    }

//PhoenixdownII:
    bool PhoenixDownII::canUse(BaseKnight *knight){
        int aQuaterOfmaxHP= (knight->getMaxHp())/4;
        if((knight->getHp())<aQuaterOfmaxHP){
                return true;
        }
        else return false;
    }
    void PhoenixDownII::use(BaseKnight *knight){
        knight->getBag()->swapWithFirst(PHOENIXDOWNII);
        knight->getBag()->deleteFirst();
        // edit propeties knight
        knight->setHp(knight->getMaxHp());
    }
    ItemType PhoenixDownII::getType(){
        type=PHOENIXDOWNII;
        return type;
    }

//PhoenixdownIII:
    bool PhoenixDownIII::canUse(BaseKnight *knight){
        int aThirdOfmaxHP= (knight->getMaxHp())/3;
        if( (knight->getHp()) < aThirdOfmaxHP ){
                return true;
        }
        else return false;
    }
    void PhoenixDownIII::use(BaseKnight *knight){
        knight->getBag()->swapWithFirst(PHOENIXDOWNIII);
        knight->getBag()->deleteFirst();
         // edit propeties knight
         if( (knight->getHp())<=0 ){
            int aThirdOfmaxHP= (knight->getMaxHp())/3;
            knight->setHp(aThirdOfmaxHP);
         }
         else{
            int aQuaterOfmaxHP= (knight->getMaxHp())/4;
            knight->setHp( (knight->getHp()) + aQuaterOfmaxHP );
         }
    }
    ItemType PhoenixDownIII::getType(){
        type=PHOENIXDOWNIII;
        return type;
    }

//PhoenixdownIV:
    bool PhoenixDownIV::canUse(BaseKnight *knight){
        int halfOfmaxHP=( knight->getMaxHp())/2;
        if( (knight->getHp()) < halfOfmaxHP ){
            return true;
        }
        else return false;
    }
    void PhoenixDownIV::use(BaseKnight *knight){
        knight->getBag()->swapWithFirst(PHOENIXDOWNIV);
        knight->getBag()->deleteFirst();
         // edit propeties knight
         if( (knight->getHp())<=0 ){
            int halfOfmaxHP=( knight->getMaxHp())/2;
            knight->setHp(halfOfmaxHP);
         }
         else{
            int oneFifthOfmaxHP = (knight->getMaxHp())/5;
            knight->setHp( (knight->getHp()) + oneFifthOfmaxHP );
         }
    }
    ItemType PhoenixDownIV::getType(){
        type=PHOENIXDOWNIV;
        return type;
    }

/* * * END implementation of class BaseItem * * */


/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

BaseKnight::BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    this->id=id;
    this->hp=maxhp;
    this->maxhp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->phoenixdownI=phoenixdownI;
    this->knightType=static_cast<KnightType>(set_KnightType(maxhp));
}
BaseKnight::~BaseKnight(){
    delete bag;
}
void BaseKnight::setBaseBag(BaseKnight *knight){
    if(knightType==PALADIN) bag= new BagOfPaladin(phoenixdownI,antidote,knight); 
    else if(knightType==LANCELOT) bag=new BagOfLancelot(phoenixdownI,antidote,knight); 
    else if(knightType==DRAGON) bag= new BagOfDragon(phoenixdownI,antidote,knight); 
    else if(knightType==NORMAL) bag= new BagOfNormal(phoenixdownI,antidote,knight); 
    phoenixdownI=0;antidote=0;
}

int BaseKnight::set_KnightType(int HP){
    if(check_Snt(HP)==1) return 0;
    else if(HP==888) return 1;
    else if(check_NumPythagoras(HP)==1) return 2;
    else return 3;
}
bool BaseKnight::check_Snt(int n){
    int count=0;
     for(int i=1;i<=n;i++){
        if(n%i==0) count++;
     }
     if(count==2) return true;
     else return false;
}
bool BaseKnight::check_NumPythagoras(int HP){
    if(100<=HP && HP<=999){
        int a=HP%10;  HP /= 10;
        int b=HP%10;  HP /= 10;
        int c=HP%10;  HP /= 10;
        if(a>0 && b>0 && c>0){
            if(a*a+b*b==c*c || 
               a*a+c*c==b*b ||
               b*b+c*c==a*a ){ 
            return true;
            }
        }
    }
    return false;
}
float BaseKnight::setKnightBaseDamage(KnightType knightType){
    if(knightType==LANCELOT) return 0.05;
    else if(knightType==PALADIN) return 0.06;
    else if(knightType==DRAGON) return 0.075;
}

/* * * END implementation of class BaseKnight * * */



/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string &file_armyknights){
     ifstream file;
     file.open(file_armyknights);
     file>>n;
     knight=new BaseKnight*[n];
     idLastKnight=n-1;
     countArmy=n;
     string line;
     getline(file,line);
     for(int i=0;i<n;i++){
        getline(file,line);
        stringstream ss(line);
        int id=i+1, maxhp, level, gil, antidote, phoenixdownI;
        ss>>maxhp>>level>>phoenixdownI>>gil>>antidote;
        knight[i]=BaseKnight::create(id,maxhp,level,gil,antidote,phoenixdownI);
        knight[i]->setBaseBag(knight[i]);
     }
}
ArmyKnights::~ArmyKnights(){
    for (int i = 0; i < n; i++) {
        delete knight[i];   
    }
    delete[] knight;
}
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50,'-') << endl;
}
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
BaseKnight * ArmyKnights::lastKnight() const{
    if(count()>=1) return knight[idLastKnight];
    else return NULL;
}

bool ArmyKnights::setEvent_1to5(int level,int levelO,BaseOpponent *opponent,BaseKnight *access){
    Monster_1to5 *monster= static_cast<Monster_1to5*>(opponent);
    if(level>=levelO || (access->getKnightType()== LANCELOT) || (access->getKnightType()== PALADIN) ){ 
         increaseGil(monster,access); 
         return true; 
    }
    else { 
        int HP=(access->getHp())-(monster->BaseDamage(eventPresent))*(levelO-level);
        access->setHp(HP);
        if(HPrecovery(access)) return true;
        else return false;   
    }
}
void ArmyKnights::increaseGil(Monster_1to5 *monster,BaseKnight *access){
    if( (access->getGil()+monster->gilMonster(eventPresent))>999 ){
        int change=access->getGil()+monster->gilMonster(eventPresent)-999;  //tính tiền thừa
        access->setGil(access->getGil()+ monster->gilMonster(eventPresent));  // cộng tiền vào
        int i=2;
        while(change>0 && count()-i>=0){
            BaseKnight *access2= knight[count()-i];
            if( (access2->getGil()+change)>999){
                    int change2=access2->getGil()+ change -999; // do hàng dưới nên k thể uploat change trực tiếp
                    access2->setGil(access2->getGil()+change);
                    change=change2;
                    i++;
            }
            else{
                access2->setGil(access2->getGil()+change);
                change=0;
            }
        }
    }
    else{
        access->setGil(access->getGil()+ monster->gilMonster(eventPresent));
    }
}
bool ArmyKnights::HPrecovery(BaseKnight *access){
    //bước 1: 
    Node *start= access->getBag()->getHead();
    bool valueCanUse= false;
    BaseItem *item=nullptr;
    do{    
        if(item !=NULL){delete item;item=nullptr;} 
        ItemType findPhoenixdown = access->getBag()->findPhoenixdown(start);  //find fist phoenixdown
        if(findPhoenixdown != NULLITEMTYPE) {
            item= access->getBag()->get(findPhoenixdown);  // create new item in function get of class BaseBag 
            valueCanUse=item->canUse(access); 
        }       
        if( item!=NULL && (valueCanUse== true) ){ 
            item->use(access);
        }
        start= access->getBag()->getLastHead();
    }while( item !=NULL && (valueCanUse == false) && (start!=NULL) ); // nếu tìm thấy thuốc nhưng ko sử dụng được và thuốc đấy không phải là viên cái cuối cùng trong linkedlist thì tìm tiếp
    if(item !=NULL) {delete item;item=nullptr;}
        
    //bước 2:
    if( ((access->getHp()<=0 )) && (access->getGil()>=100) ){
        access->setGil((access->getGil()-100));
        access->setHp((access->getMaxHp()/2));
    }
    if(access->getHp()<=0 ) { return false;}
  return true;  
}

bool ArmyKnights::setEvent_6(int level,int levelO,BaseOpponent *opponent,BaseKnight *access){
    if(level>=levelO){
          access->setLevel(access->getLevel()+1);
    }
    else{
        if(access->getKnightType()== DRAGON) return true;
        else access->setPoisonAntidote(true);
        //GIẢI ĐỘC:
        BaseItem *item= access->getBag()->get(ANTIDOTE);
        if(item!=NULL && item->canUse(access) ){  //Item của Antidote
            item->use(access); //giải độc
        }
        if(item !=NULL){delete item;item=nullptr;} 
        //NẾU KHÔNG GIẢI ĐƯỢC ĐỘC:
        if(access->getPoisonAntidote()==true){
            access->getBag()->delete3Item();
            access->setHp(access->getHp()-10);
            if(HPrecovery(access)) return true;
            else return false;  
        }
    }
  return true;  
}

void ArmyKnights::setEvent_7(int level,int levelO,BaseOpponent *opponent,BaseKnight *access){
    if(level>=levelO){
        increaseGil(access);
    }
    else{
        if( access->getKnightType()!=PALADIN ) access->setGil((access->getGil())/2);
    }
}
void ArmyKnights::increaseGil(BaseKnight *access){
    if( ((access->getGil())*2)>999 ){
        int change=access->getGil()*2-999;  //tính tiền thừa
        access->setGil(access->getGil()*2);  // cộng tiền vào
        int i=2;
        while(change>0 && count()-i>=0){
            BaseKnight *access2= knight[count()-i];
            if( (access2->getGil()+change)>999){
                int change2=access2->getGil()+ change -999; // do hàng dưới using change nên k thể uploat change trực tiếp
                access2->setGil(access2->getGil()+change);
                change=change2;
                i++;
            }
            else{
                access2->setGil(access2->getGil()+change);
                change=0;
            }
        }
    }
    else{
        access->setGil(access->getGil()*2);
    }
}

void ArmyKnights::setEvent_8(BaseKnight *access){
    if( access->getKnightType()==PALADIN ){
        int aThirdOfmaxHP=(access->getMaxHp())/3; 
         if( (access->getHp())<aThirdOfmaxHP ){
            int oneFifthOfmaxHP=(access->getMaxHp())/5;
            access->setHp(access->getHp()+ oneFifthOfmaxHP);
         }
    }
    else if(access->getGil()>=50){ 
        int aThirdOfmaxHP=(access->getMaxHp())/3;     // 1/3 maxHP
        if( (access->getHp())<aThirdOfmaxHP ){
            access->setGil(access->getGil()-50);
            int oneFifthOfmaxHP=(access->getMaxHp())/5;
            access->setHp(access->getHp()+ oneFifthOfmaxHP);
        }
    }
}

bool ArmyKnights::setEvent_10(BaseKnight *access){
    if( ( (access->getLevel()==10) && (access->getHp()==access->getMaxHp()) ) 
       || (access->getKnightType()==DRAGON) ){
        access->setLevel(10);
        access->setGil(999);
        passOmegaWeapon=1;
        return true;
    }
    else{ 
        access->setHp(0);
        if(HPrecovery(access)) return true;
        else return false;   
    }
}

bool ArmyKnights::setEvent_11(BaseKnight *access){
    if( ( (access->getKnightType()==PALADIN) && (access->getLevel()>=8) ) 
       || (access->getLevel()==10) ){
        if(paladinShield==0){
            paladinShield=1;
            numTreasure++;
        }
        passHades=1;  
        return true;
    }
    else{ 
        access->setHp(0);
        if(HPrecovery(access)) return true;
        else return false;   
    }
}

bool ArmyKnights::setEvent_99(BaseOpponent *opponent){
    Monster_99 *monster= static_cast<Monster_99*>(opponent);
    if(excaliburSword==1 ) return true;
    if(numTreasure==3){
        int i=1;
        int ct_count = count();
        while(ct_count-i>=0){
            if( knight[ct_count-i]->getKnightType()==PALADIN ||
                knight[ct_count-i]->getKnightType()==LANCELOT ||
                knight[ct_count-i]->getKnightType()==DRAGON){ 
                  BaseKnight *access= knight[ct_count-i]; 
                  int level=access->getLevel();
                  int damage= (access->getHp())*level*(access->setKnightBaseDamage(access->getKnightType()));
                  monster->setHP( (monster->getHP())-damage );// cout<<"HP NU HOANG:"<<monster->getHP()<<endl;
                  if(monster->getHP()<=0 ) return true; 
                  access->setHp(0);
                  
                  if(ct_count-i==count()-1) {idLastKnight--;}
                  countArmy--;                   
                }
            i++;    
        }
        //NẾU ĐI HẾT VÒNG WHILE MÀ CHƯA WIN THÌ ĐỘI QUÂN CHẾT
        countArmy=0;
        return false;
    }
    //NẾU KHÔNG ĐỦ 3 ITEM
    else {  
    countArmy=0;
    return false;
    }
}

bool ArmyKnights::setEventPhoenixdown(BaseItem *newitem,BaseKnight *access){
     if( access->getBag()->insertFirst(newitem) ==false ){
         int i=2;
         while(count()-i>=0){
              BaseKnight *access2= knight[count()-i];
              if(access2->getBag()->insertFirst(newitem)) break;
              else i++;
         }
     }
}

bool ArmyKnights::fight(BaseOpponent *opponent){
    BaseKnight *access=knight[count()-1];
    int level=access->getLevel();
    if( eventPresent==1 ||
        eventPresent==2 ||
        eventPresent==3 ||
        eventPresent==4 ||
        eventPresent==5 ){  
        int levelO=opponent->getLevelO();
        if(setEvent_1to5(level,levelO,opponent,access)==false) return false;
    }
    //event 6: gặp ma Tornbery
    else if(eventPresent==6){   
        int levelO=opponent->getLevelO();
        if(setEvent_6(level,levelO,opponent,access)==false) return false;
    }
    //event 7: gặp nữ hoàng cờ bạc Queen of Cards
    else if(eventPresent==7){   
        int levelO=opponent->getLevelO();
        setEvent_7(level,levelO,opponent,access);
    }
    //event 8: gặp lái buôn vui tính Nina de Rings
    else if(eventPresent==8){
        setEvent_8(access);
    }
    //event 9:gặp vườn sầu riêng
    else if(eventPresent==9){
        access->setHp(access->getMaxHp());
    }
    //event 10: gặp OmegaWeapon
    else if(eventPresent==10 && passOmegaWeapon==0){
            if(setEvent_10(access)==false) return false;
    }
    //event 11: gặp Hades
    else if(eventPresent==11 && passHades==0){
        if(setEvent_11(access)==false) return false; //ham tra ve true nghia la ko co knight chet
    }
    else if(eventPresent==95 && paladinShield==0) {
        paladinShield=1;
        numTreasure++;
    }
    else if(eventPresent==96 && lancelotSpear==0) {
        lancelotSpear=1;
        numTreasure++;
    }
    else if(eventPresent==97 && guinevereHair==0) {
        guinevereHair=1;
        numTreasure++;
    }
    else if(eventPresent==98 && numTreasure==3 && excaliburSword==0){
        excaliburSword=1;
    }
    else if(eventPresent==99){
        if(setEvent_99(opponent)==false) return false;
    }
    else if(eventPresent==112){
        BaseItem *newitem= new PhoenixDownII;
        setEventPhoenixdown(newitem,access);
        delete newitem;
    }
    else if(eventPresent==113){
        BaseItem *newitem= new PhoenixDownIII;
        setEventPhoenixdown(newitem,access);
        delete newitem;
    }
    else if(eventPresent==114){
        BaseItem *newitem= new PhoenixDownIV;
        setEventPhoenixdown(newitem,access);
        delete newitem;
    }

  return true;  
}

bool ArmyKnights::adventure (Events * events){
    for(int i=0;i<events->count();i++){  //cout<<i+1<<" "<<events->get(i)<<"  "; //NHỚ XÓA
        eventPresent=events->get(i);
        BaseOpponent *opponent=nullptr; 
        if( events->get(i)==1 ||
            events->get(i)==2 ||
            events->get(i)==3 ||
            events->get(i)==4 ||
            events->get(i)==5 )    {opponent= new Monster_1to5(i,events->get(i));}
        else if(events->get(i)==6 ||
                events->get(i)==7 ){opponent= new Monster_6and7(i,events->get(i));}
        else if(events->get(i)==99){opponent= new Monster_99;}
        
        //RUN CODE:
        if(events->get(i)== 99){
            fight(opponent);
        }
        else{
            while( fight(opponent) ==false ){
                if(count()>1){
                    idLastKnight--;
                    countArmy--;
                    continue;
                }
                else{
                    idLastKnight--;
                    countArmy--;
                    break;
                }
            }
        }

        printInfo();
        if (opponent != nullptr) { 
            delete opponent;
            opponent = nullptr; 
        }
        if(count()==0) {  //nếu knight cuối cùng chết
            break;
        }
    }
    if(count()>0) return true;
    else return false;
}
/* * * END implementation of class ArmyKnights * * */



/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure(){
    delete events;
    delete armyKnights;
}
void KnightAdventure::loadArmyKnights(const string &file_armyknights){
    this->file_armyknights=file_armyknights;
}
void KnightAdventure::loadEvents(const string &file_events){
    this->file_events=file_events;
}
void KnightAdventure::run(){
    armyKnights=new ArmyKnights(file_armyknights);
    events=new Events(file_events);
    armyKnights->printResult(armyKnights->adventure(events));
}
/* * * END implementation of class KnightAdventure * * */



/* * * BEGIN implementation of class Events * * */
Events::Events(const string & file_events){
    ifstream file;
    file.open(file_events);
    file>>e;
    arrEvent= new int[e];
    string line;
    getline(file,line);
    getline(file,line);
    stringstream ss(line);
    int num; 
    int i=0;
    while(ss>>num){
        arrEvent[i]=num;
        i++;
    }
}
Events::~Events(){
    delete[] arrEvent;
}         
int Events::count() const{
    return e;
}
int Events::get(int i) const{
    return arrEvent[i];
}
/* * * END implementation of Events * * */


/* * * BEGIN implementation of class BaseOpponent * * */
Monster_1to5::Monster_1to5(int i, int event){
    this->levelO=(i+event)%10+1;
}
int Monster_1to5::gilMonster(int eventNum) {
    if (eventNum == 1) {
        return 100;
    }
    else if (eventNum == 2) {
        return 150;
    }
    else if (eventNum == 3) {
        return 450;
    }
    else if (eventNum == 4) {
        return 750;
    }
    else if (eventNum == 5) {
        return 800;
    }
}
int Monster_1to5::BaseDamage(int eventNum) {
    if (eventNum == 1) {
        return 10;
    }
    else if (eventNum == 2) {
        return 15;
    }
    else if (eventNum == 3) {
        return 45;
    }
    else if (eventNum == 4) {
        return 75;
    }
    else if (eventNum == 5) {
        return 95;
    }
}

Monster_6and7::Monster_6and7(int i,int event){
    this->levelO=(i+event)%10+1;
}
/* * * END implementation of class BaseOpponent * * */
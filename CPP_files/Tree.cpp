#include "Tree.h"
#include "TreeNode.h"
#include <fstream>
#include <vector>
using namespace std;



TreeNode* Tree::FindByID(int ID){
    //cout<<"ELements size"<<Elements.size()<<endl;
    
    for(int i=0;i<Elements.size();i++){//postoji vektor Elemenata te tako mozemo da proverimo kad stignemo do onog sa ID koji nam treba da bi povezali
        //cout << "i za ID : " << i << endl;
        if((Elements.at(i)->getID())==ID){ return Elements[i];}
    }
}
Tree::Tree(const string& filepath){
    int NumElem;
    int Id;
    int Type;
    fstream inputFile(filepath, ios::in);
    inputFile >> Time;
    inputFile >> NumElem;

    Elements.resize(NumElem);
    
    //cout<<"Uneli ste redom Vreme "<<Time<<"us i Broj Elemenata "<<NumElem<<endl;
    int br=0;
    for(int i=0;i<NumElem;i++){
        inputFile>>Id;
        inputFile>>Type;
        switch (Type) {
        case 0:{
            //cout<<"Sonda"<<endl;//kreiraj sondu
            Sonda* sonda= new Sonda(Id,Type,1);
            Elements[i] = sonda;
            SondeID.push_back(sonda);
            break;
            }
        case 1:{
            
            double Frequency;
            inputFile>>Frequency;
            FrequencySource* FrequencySources= new FrequencySource(Id,Type,0,Frequency,Time);
            //cout<<"Izvor takta je izabran i vrednost takta je "<<Frequency <<endl;
            Elements[i] = FrequencySources;
            for(int i=0;i<(FrequencySources->GetMomentsOfChangeFS()).size();i++){
                //cout<<"Moments u case1 Vreme: "<<(FrequencySources->GetMomentsOfChangeFS())[i].Vreme;
                MinimumsOfTime.push_back((FrequencySources->GetMomentsOfChangeFS())[i].Vreme);
            }
            break;
            
        }
        case 2:{
            vector<float> promene;
            while(inputFile.peek()!='\n'){
                int vreme;
                inputFile>> vreme;
                promene.push_back(vreme);
                
            }            
            //cout<<"Izvor takta podesivi"<<endl;
            SeterSource* SeterSources=new SeterSource(Id,Type,0,promene);
            /*list <float> :: iterator it; //ovde pocinje ispis liste
            for(it = promene.begin(); it != promene.end(); ++it) 
                cout << '\t' << *it; 
            cout << '\n';//ovo zakomentarisi*/
            Elements.push_back(SeterSources);
            for(int i=0;i<(SeterSources->GetMomentsOfChangeSS()).size();i++){
                //cout<<"Moments u case1 Vreme: "<<(SeterSources->GetMomentsOfChangeFS())[i];
                MinimumsOfTime.push_back((SeterSources->GetMomentsOfChangeSS())[i]);
            }
            //MinimumsOfTime.push_back(SeterSources->GetMin());
            break;
            
        }
        case 3:{
            
            NOT* Not= new NOT(Id,Type);
            
            Elements[i] = Not;
            // cout<<" NE"<< Not->getID()<<endl;
            break;
        }
        case 4:{
            int GatesAnd=2;
            //if(inputFile.peek()!='\n'){
                inputFile>>GatesAnd;
            //}
            AND* And= new AND(Id,Type,GatesAnd);
            //cout<<"Element je AND i ima"<<GatesAnd<<" ulaza"<<endl;
            Elements[i]=And;
            break;
        }
        case 5:{
            int GatesOr=2;
            if(inputFile.peek()!='\n'){
                inputFile>>GatesOr;
            }
            OR* Or= new OR(Id,Type,GatesOr);
            //cout<<"Element je OR i ima "<<GatesOr<<" ulaza"<<endl;
            Elements[i]=Or;
            break;
        }
        default:
            //cout<<"Doslo je do greske";
            break;
            //throw exception("Jedan od elemenata je zadat a nije u osegu od 0 do 5");
        }
        //cout<<"identifikator ovog elementa je bio"<<Id<<endl;
    }
    cout << "Broj Elemenata: ";// << Elements.size();
    
    while(inputFile.peek() != EOF){
        int input;
        int output;
        int port;


        inputFile>>output>>input>>port;
        cout<<output<<input<<port;
        // cout << FindByID(input)->getID();
        FindByID(input)->SetNChild(port,FindByID(output));
        
    }
    inputFile.close();
    

}

void Tree::calc(double time){
    vrednosti.resize(SondeID.size());
     int x=0;
    for (int sl = 0; sl < SondeID.size() ; sl++){//za svaku sondu
        
        TreeNode* trenutnicvor=SondeID[sl];    
        Stek.push(trenutnicvor);
        for (int  elem = 0; elem < Elements.size(); elem++)
        {
            Elements[elem]->setObradjen(0);

        }//postavlja sve na 0 da bi moglo da se izvrsava dalje
        bool prethodni=SondeID[sl]->getState();
        bool promenjen;
        while(!Stek.empty()){//prolazak stabla
            trenutnicvor=Stek.top();
            if((Stek.top())->JelObradjen()){
                trenutnicvor->calculate(time);
                Stek.pop();
            }else {
                for(int i=0;i<trenutnicvor->GetNumberOfChilds();i++){
                    Stek.push(trenutnicvor->GetNChild(i));
                }
                trenutnicvor->setObradjen(1);
            }
           promenjen=SondeID[sl]->getState();
        }
        // if(prethodni!=promenjen){
        vrednosti[x].Prethodno=prethodni;
        vrednosti[x].Promenjeno=promenjen;
        vrednosti[x].Vreme=time;
        //cout<<vrednosti[x].Vreme;
        vrednosti[x].Sonda=SondeID[sl]->getID();
        // cout<<(bool)prethodni<<" -> "<<promenjen<<" : "<<time<<"us "<<endl;
        x++;
        // }    
    }
}
float Tree::CalcStep(){
    float result = MinimumsOfTime[0];
    for (int i = 1; i < MinimumsOfTime.size(); i++)
    {
        result=NZDS(result,MinimumsOfTime[i]);
    }
    return result;
}
float Tree::NZDS(float a, float b) {
    if (a == 0){ 
       return b; 
    }else if (b == 0){ 
       return a; 
    }else if ((a-b)<1e-4){ 
        return a; 
    } else if(a>b){
         NZDS(a-b, b); 
    } else{
         NZDS(a, b-a); 
    }
    }
    Tree::~Tree(){
    for (int i = 0; i < Elements.size(); i++)
        delete Elements[i];
    }
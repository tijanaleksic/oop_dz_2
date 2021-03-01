#include "TreeNode.h"
#include <iostream>
using namespace std;

TreeNode::TreeNode() {};


void FrequencySource::MomentsOfChange(){//ovo ce kreirati listu Prelomi koja sadrzi svaki trenutak i vrednost kada se promena izvrsila
    double TrajanjeCetvrtke=1.0/(2*Frequency_);//pola perioda[us]
    int BrojClanovaListe=TimeDuration_/TrajanjeCetvrtke;//broj clanova {eventualno dodati +1 za 0 clan ili staviti <=}
    cout<<"Broj clanova je : "<<BrojClanovaListe<<endl;
    cout<<"Time Duration : "<<TimeDuration_;
    cout<<"Trajanje cetvrtke je : "<<TrajanjeCetvrtke<<endl;
    cout<<"Frequency clanova je : "<<Frequency_<<endl;
    VremeVrednost Trenutno;
    Trenutno.Vreme=0;//postavljamo da pocinje simulacija od 0
    Trenutno.Vrednost=0;//pocetna vrednost je 0 po tekstu zadatka
    for(int i=0;i<=BrojClanovaListe;i++){
        cout<< "uso "<< i;
        Moments_.push_back(Trenutno);
        //ubacuje na kraj liste Prelomi element koji sadrzi vreme i vrednost u promeni
        Trenutno.Vreme+=TrajanjeCetvrtke;//dodaje vreme koje treba da prodje do sledece promene
        Trenutno.Vrednost=!Trenutno.Vrednost;//izvrce vrednost
        
    } 

}
void SeterSource::NapraviPrelome(){
    VremeVrednost trenutno;
    trenutno.Vreme=0;
    trenutno.Vrednost=0;//proveri da  l ima dobra kolckna vrednosti
    for (int i = 0; i < Changes_.size(); i++){
        MomVal.push_back(trenutno);
        trenutno.Vreme+=Changes_[i];
        trenutno.Vrednost=!trenutno.Vrednost;
    }
    
    
}

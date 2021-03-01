#ifndef TREE_NODE_H
#define TREE_NODE_H
//#include "NZD.cpp"
#include <iostream>
#include <stdlib.h>
#include <list>
#include <vector>
#include <math.h>
using namespace std;
/*struct nTreeNode
{
     TreeNode *childArray[];
     ValType val;
     int childNum;
};

void reparentTo(nTreeNode *parent, nTreeNode *child)
{
     
     nTreeNode **_temp, *childArray[] = new nTreeNode*[parent->ChildNum+1];
     memcpy(childArray, parent->childArray, sizeof(nTreeNode*)*(parent->childNum));
     childArray[parent->ChildNum] =  child;
     _temp = parent->childArray;
     parent->childArray = childArray;
     parent->childNum++;
     delete[] _temp;     
     return;
}*/
typedef struct vremevrednost{
     double Vreme;
     double Vrednost;
 } VremeVrednost;
 
class TreeNode {
public:
    TreeNode();
	TreeNode(const TreeNode&) = delete;
	TreeNode(TreeNode&&) = delete;
     virtual void calculate(double Now) = 0;
	int getID(){return ID_;}
	int GetElementType() const { return ElementType_; }
	int GetNumberOfChilds()const { return NumberOfChilds_;}
	TreeNode* GetNChild(int n) const { return Array_.at(n); }
	bool JelObradjen(){return Obradjen;}
	bool getState(){return State;}
	void setObradjen(bool o){Obradjen=o;}
	float NZD(float a, float b) {
    if (a == 0){ 
       return b; 
    }else if (b == 0){ 
       return a; 
    }else if ((a-b)<1e-4){ 
        return a; 
    } else if(a>b){
         NZD(a-b, b); 
    } else{
         NZD(a, b-a); 
    }    
}
	
	

	void SetNChild(int n,TreeNode* nChild) { Array_[n] = nChild; }
protected:
     int NumberOfChilds_;
     int ID_;
     double  TimeDuration_;
     int ElementType_;
     list <float> ChangingTimes_;
	 bool Obradjen=0;
	 bool State=0;
	 vector <TreeNode*> Array_;
	 vector <VremeVrednost> Moments_;//ovo si menjala
private:     
	
};

class Sonda : public TreeNode {
public:
	Sonda(int ID,int ElementType,int NumberOfChilds){
          ID_=ID;
          ElementType_=ElementType;
          NumberOfChilds_=NumberOfChilds;
		  this->Array_.resize(1);

	};
	virtual void calculate(double Now)  override{
        this->State=(GetNChild(0)->getState());
		//cout<<"Sondu ste namestili na "<<ID_<<endl;
		
	}
	int ReutrnID(){return ID_;}
	private:
	
};


class  FrequencySource : public TreeNode {
public:
	FrequencySource(int ID,int ElementType,int NumberOfChilds,double Frequency,double TimeDuration):Frequency_(Frequency){
		NumberOfChilds_=NumberOfChilds;
        ID_=ID;
        TimeDuration_=TimeDuration;	
		this->Array_.resize(NumberOfChilds_);	
		
		MomentsOfChange();
	}
	float GetMin(){return 1.0/(2*Frequency_);	}
	virtual void calculate(double Now) override{
		int now=round(Now*10000);
		for (int i = 0; i < Moments_.size()-1; i++){
			if(now>=round(Moments_[i].Vreme*10000)&&(now<=round(Moments_[i+1].Vreme*10000))){
				State=Moments_[i].Vrednost;
			}
			//else if(round(now)==0){
			//	State=Moments_[0].Vreme;
			//}
		}
	}
	void MomentsOfChange();
	
	vector <VremeVrednost> GetMomentsOfChangeFS(){
		return Moments_;}


private:
	double Frequency_;
	//vector <VremeVrednost> Moments_;//ovo treba unistiti kad se na kraju pravi
	int LastVal;
};
class SeterSource: public TreeNode{
	public:
	SeterSource(int ID,int ElementType,int NumberOfChilds,vector <float> Changes ){
		NumberOfChilds_=NumberOfChilds;
		ID_=ID;
		Changes_=Changes;
		this->Array_.resize(NumberOfChilds_);
		NapraviPrelome();
	}
	virtual void calculate(double Now) override{
		for (int i = 0; i < MomVal.size()-1; i++){
			if((Now>=MomVal[i].Vreme)&&(Now<MomVal[i+1].Vreme)){
				State=MomVal[i].Vrednost;
			}
		}
	}
	void NapraviPrelome();
	float GetMin(){
		float result=MomVal[0].Vreme;
		for (int i = 0; i < MomVal.size(); i++){	
			result=NZD(result,MomVal[i].Vreme);
			
		}
		
		return result; }
	vector<float> GetMomentsOfChangeSS(){return Changes_;}


private:
	int Frekvencija_;
	int VremeTrajanja_;
	vector <float> Changes_;
	vector <VremeVrednost> MomVal;//ovo treba unistiti kad se na kraju pravi
	int PrethodnaVrednost;

};
class NOT:public TreeNode{
	public:
	NOT(int ID,int ElementType){
		ElementType_=ElementType;
          ID_=ID;
          NumberOfChilds_=1;
		  this->Array_.resize(NumberOfChilds_);
		//ulaz=this->povezan?
	}
     //int GetInput(){return input;    }
	virtual void  calculate(double Now) override{
		this->State=!(GetNChild(0)->getState());
	}
	private:
	


};
class AND:public TreeNode{
	public:
	AND(int ID,int ElementType,int GatesAnd){
		NumberOfChilds_=GatesAnd;
        ID_=ID;
        ElementType_=ElementType;
		this->Array_.resize(NumberOfChilds_);
          //ulaz=this->povezan?
	}
	virtual void calculate(double Now) override{
		bool ulazni=1;
		for (int i = 0; i < this->NumberOfChilds_; i++){
			ulazni=GetNChild(i)->getState();
			State=State && ulazni;		
		}				
	}
	private:
	int brojulaza=2;
	

};
class OR:public TreeNode{
	public:
	OR(int ID,int ElementType,int GatesOr){
		NumberOfChilds_=GatesOr;
          ID_=ID;
          ElementType_=ElementType;
		  this->Array_.resize(NumberOfChilds_);
          //ulaz=this->povezan?
	}
	virtual void calculate(double Now) override{
		
		for (int i = 0; i < this->NumberOfChilds_; i++){
			bool ulazni;
			ulazni=GetNChild(i)->getState();
			State=State || ulazni;		
		}				
	}
	private:
	int brojulaza=2;
	int* niz=new int[brojulaza];

};


#endif


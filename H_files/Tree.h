#pragma once

#include "TreeNode.h"
#include <string>
#include <vector>
#include <stack>
class TreeNode;
class Tree;
typedef struct preposlevremesonda{
    bool Prethodno;
    bool Promenjeno;
    float Vreme;
    int Sonda;
} PrePosleVremeSonda;
using namespace std;
class Tree
{
public:
    Tree(const string& filepath);
    void calc(double time);
    TreeNode* FindByID(int ID);
    float CalcStep();
    float NZDS(float a, float b);
    vector <PrePosleVremeSonda> getVrednosti(){return vrednosti;}
    vector <float> getMOT(){ 
        int minind;
        for (int i = 0; i < MinimumsOfTime.size()-1; i++)
        {
            

            for (int j = i+1; j < MinimumsOfTime.size(); j++)
            {
                if(MinimumsOfTime[j]<MinimumsOfTime[minind]){ minind=j;}
                float s= MinimumsOfTime[minind];
                MinimumsOfTime[minind]=MinimumsOfTime[i];
                MinimumsOfTime[i]=s;
                
            }
            
            
            //ovde ubaci da sortiras i izbacujes sve dupled
        }//sortirano
        
        for (int i=0;i<MinimumsOfTime.size();i++){
            if(MinimumsOfTime[i]==MinimumsOfTime[i+1]){
                MinimumsOfTime.erase(MinimumsOfTime.begin()+i);
            }
        }//ovo vrv ne radi proveri
        

        
        return MinimumsOfTime;
    }
    vector <TreeNode*> getSonde(){return SondeID;}
    
    ~Tree();
private:

    float Time;
    vector <PrePosleVremeSonda> vrednosti;
    vector <TreeNode*> Elements;
    vector <TreeNode*> SondeID;
    stack <TreeNode*> Stek;
    vector <float> MinimumsOfTime;

};



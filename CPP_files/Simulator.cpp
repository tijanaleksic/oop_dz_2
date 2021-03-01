#include "Simulator.h"
#include "TreeNode.h"
#include "Tree.h"

#include<fstream>
#include <iostream>
#include <list>
#include <string>
#include <math.h>
using namespace std;
Simulator::Simulator(){};

void Simulator::loadCircuit(const string& filepath){
    //cout << "Init circuit!";
    fstream inputFile(filepath);
    inputFile >> Time;
    inputFile.close();
    circuit=new Tree(filepath);
    //cout << "Init circuit!";
}
void Simulator::simulate(const string& filepath){
    //vector <TreeNode*> sondeid;
    
    // vector <float> MOT;
     
    // MOT=circuit->getMOT();
    // cout << "MOT: " << MOT.size()<< endl;
    // vector <PrePosleVremeSonda> vrs;
    // int sonda;
    // for(int i= 0;i<MOT.size();i++){
    //     // cout<<"usoi MOT[i] je "<< MOT[i];
        
    //     circuit->calc(MOT[i]);
    //     vrs=circuit->getVrednosti();
    //     // cout<<"vrs.size()"<<vrs.size()<< endl;
    //     for (int vr = 0; vr < vrs.size(); vr++){
    //         sonda= vrs[vr].Sonda;
    //         if (vrs[vr].Prethodno != vrs[vr].Promenjeno) {
    //             fstream outputFile("output_"+to_string(sonda),ios_base::app);
    //             // outputFile.open("output_"+sonda);
    //             outputFile<<vrs[vr].Prethodno<<" -> "<<vrs[vr].Promenjeno<<" : "<<vrs[vr].Vreme<<endl;
    //             cout<<vrs[vr].Prethodno<<" -> "<<vrs[vr].Promenjeno<<" : "<<vrs[vr].Vreme<<endl;
    //             outputFile.close();
    //         }
    //     }
    // }
    
    
    double Step =0.01;
    vector <PrePosleVremeSonda> vrs;
    int sonda;
    
    for (double time = 0; time<Time;){ 
        circuit->calc(time);vrs=circuit->getVrednosti();
        // cout<<"vrs.size()"<<vrs.size()<< endl;
        for (int vr = 0; vr < vrs.size(); vr++){
            sonda= vrs[vr].Sonda;
            if (vrs[vr].Prethodno != vrs[vr].Promenjeno) {
                fstream outputFile("output_"+to_string(sonda),ios_base::app);
                // outputFile.open("output_"+sonda);
                outputFile<<vrs[vr].Prethodno<<" -> "<<vrs[vr].Promenjeno<<" : "<<vrs[vr].Vreme<<endl;
                cout<<vrs[vr].Prethodno<<" -> "<<vrs[vr].Promenjeno<<" :"<<vrs[vr].Vreme<<"us"<<endl;
                outputFile.close();
                
            }
        }
         time+=Step;

    }
}
Simulator::~Simulator(){
    delete circuit;
}
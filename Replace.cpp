//
// Created by shaon on 2018/6/6.
//Élitiste/Remplacement des stratégies d'évolution    meme taille
///remplacer les individus de TabEnfant dans la population (en
///préservant la meilleure solution !)
///exemple : garder dans Popul « les MaxPopul meilleure individus »
///parmi les(MaxPopul+NbEnfant)individus
bool Replace(vector<solution> &pop,vector<solution> &enfant){
    vector<solution> ExpPop;
    int num=pop.size();
    for(int i=0;i<enfant.size()/2;i++){
        ExpPop.push_back(enfant[i]);
    }
    for(int i=0;i<pop.size();i++){
        ExpPop.push_back(pop[i]);
    }
    MergeSort(ExpPop);
    vector<solution>().swap(pop);
    for(int j=0;j<num;j++){
        pop.push_back(ExpPop[j]);
    }
//    int k=0;
//    int debut=0;
//    if (enfant[0].Fitness<pop[0].Fitness){k++; ExpPop.push_back(enfant[0]);debut=1;}
//    while (k<num) {
//        ExpPop.push_back(pop[k]);
//        k++;
//        for (int i = debut; i < enfant.size(); ++i) {
//            if (pop[k].Fitness<enfant[i].Fitness and pop[k+1].Fitness>enfant[i].Fitness){
//                ExpPop.push_back(enfant[i]);
//            k++;}
//                //cout<<"Remplacement effectué"<<endl;
//                //break;
//            }
//
//        }
//    pop=ExpPop;
    return true;
}

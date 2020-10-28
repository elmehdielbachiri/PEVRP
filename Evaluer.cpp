//// ************************************************************************************************************** ////
//// ******************************************  Calculer distence   ********************************************** ////
//// ************************************************************************************************************** ////
//// * Calculer les distences entre les clients
#include <math.h>
#define Pi  4.0*atan(1.0)
#define radiusOfEarth  4182.45

double GetDistence(cdp client1, cdp client2) {
    double lat1 = client1.latitude;
    double lat2 = client2.latitude;
    double lon1 = client1.longitude;
    double lon2 = client2.longitude; // radius== 4182.44949; // miles, 6371km;
    double dLat = (lat2-lat1)* Pi/ 180;
    double dLon = (lon2-lon1)* Pi/ 180;
    double a = pow(sin(dLat/2.0),2.0) +cos(lat1* (Pi/ 180)) * cos(lat2* (Pi/ 180)) * pow(sin(dLon/2.0),2.0) ;
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double distance = radiusOfEarth * c;
    return distance;}
//// * Calculer les dis

//// * Calculer les distense de un sequence de client

double GetSegmentDistence(vector<int> &V, int a, int b, double D[][500]){
    double dis=0;
    for(int i=a;i<b;i++){
        dis=dis+D[V[i]][V[i+1]];
    }
    return dis;
}
//// *  Chercher les points de recharge available dans le circle dont le rayon=R
//// *  R/100 presente le distence avec R pour cent energie

bool FindPointRecharge(double R, vector<int> &PRDisponible, double Dmax, cdp client, cdp CDP[], vector<int> &availablePR,int numClient) {
    for(int i=0;i<PRDisponible.size();i++) {
        if (GetDistence(client,CDP[PRDisponible[i]])<(R/100.0)*Dmax){
            availablePR.push_back(PRDisponible[i]);
        }
    }
    return true;
}
//// ************************************************************************************************************** ////
//// *******************************************  CheckEnergy   *************************************************** ////
//// ************************************************************************************************************** ////
//// * Verifier la faisabilite de route avec la solution de reparer Ins
//// * Si chaque route de cette tournee est inferieur a Dmax, le solution Ins est utile pour reparer la tournee infaisable
//// * D vector de distence avant/apres le point de recharge
//// * a,b 不能是分割点
bool CheckEnergy(solution &sol, int a, int b, solution &Ins,double Dis[][500], double Dmax, double Tmax, double Vrecharge, double Vmoy, vector<double> &D) {
    double Time = 0;//完成这个循环所用的时间
    vector<double>().swap(D);
    double d = 0;
    // ERREUR ICI POUR a=0 b=3
    // et Ins.Pointer[0]=0 (Point de recharge avant le c)
    // Pointer de solution d'insertion indique l'element qui le suit, cad si pointer=k, la station de recharge est
    // place avant sol.chromosome[k]; si pointer=b+1 solution place apres chromosome[b+1]
    if (Ins.Pointer[0]==a){
    d = Dis[0][Ins.Chromosome[0]] ;}
    else{
    d = Dis[0][sol.Chromosome[a]] + GetSegmentDistence(sol.Chromosome, a, Ins.Pointer[0]-1 , Dis) +
        Dis[sol.Chromosome[Ins.Pointer[0]-1]][Ins.Chromosome[0]];}
    D.push_back(d);
    if (d > Dmax) {
        return false;
    }
    //Probleme au cas Ou Ins.Pointer[0]>Ins.Pointer[1]
    if (Ins.Pointer.size() > 1) {
        if(Ins.Pointer[0]>Ins.Pointer[1]){
            reverse(Ins.Pointer.begin(), Ins.Pointer.end());
            reverse(Ins.Chromosome.begin(), Ins.Chromosome.end());}
        for (int i = 0; i < Ins.Pointer.size() - 1; i++) {
            // Tester distance entre stations de recharge inserees
            d = Dis[Ins.Chromosome[i]][sol.Chromosome[Ins.Pointer[i]]] +
                GetSegmentDistence(sol.Chromosome, Ins.Pointer[i], Ins.Pointer[i + 1] - 1, Dis)
                + Dis[sol.Chromosome[Ins.Pointer[i + 1] - 1]][Ins.Chromosome[i + 1]];
            D.push_back(d);
            if (d > Dmax) {
                return false;
            }
        }
    }
    if(Ins.Pointer[Ins.Pointer.size() - 1]!=b+1){
    //ICI on calcule la distance de la derniere station au depot, si la derniere station est avant le dernier noeud
        d = Dis[Ins.Chromosome[Ins.Pointer.size() - 1]][sol.Chromosome[Ins.Pointer[Ins.Pointer.size() - 1]]] +
        GetSegmentDistence(sol.Chromosome, Ins.Pointer[Ins.Pointer.size() - 1], b, Dis) + Dis[sol.Chromosome[b]][0];}
    else{
        //SI station apres dernier noeud
       d=Dis[Ins.Chromosome[Ins.Pointer.size() - 1]][0];
    }

    D.push_back(d);
    if (d > Dmax) {
        return false;
    }

    // Verifier le cout de temps d'insertion
    Time =(Dis[0][sol.Chromosome[a]] +Dis[sol.Chromosome[b]][0]+GetSegmentDistence(sol.Chromosome, a, b, Dis)) / Vmoy;
    Ins.Time = 0.0;
    //for (int i = 0; i < D.size() -1; i++) {
    for (int i = 0; i < D.size()-1 ; i++) {
        Ins.Time = Ins.Time + 0.25;
    }
    Ins.Time = Ins.Time + Ins.Fitness / Vmoy;
    Time = Time + Ins.Time;
    if (Time > Tmax) {
        return false;
    } else {
        //cout<<"Tournee Faisable."<<endl;
        return true;
    }
}/*
bool CheckEnergy(solution &sol, int a, int b, solution &Ins, double Dis[][500], double Dmax, double Tmax, double Vrecharge, double Vmoy, vector<double> &D) {
    double Time = 0;//完成这个循环所用的时间
    vector<double>().swap(D);
    double d=0;
    d=Dis[sol.Chromosome[a]][0]+GetSegmentDistence(sol.Chromosome, a, Ins.Pointer[0]-1, Dis) +Dis[sol.Chromosome[Ins.Pointer[0]-1]][Ins.Chromosome[0]];
    D.push_back(d);
    if (d > Dmax) {
        return false;
    }
    if (Ins.Pointer.size() > 1) {
        for (int i = 0; i < Ins.Pointer.size() - 1; i++) {
            d= Dis[Ins.Chromosome[i]][sol.Chromosome[Ins.Pointer[i]]] +GetSegmentDistence(sol.Chromosome, Ins.Pointer[i], Ins.Pointer[i + 1]-1, Dis)
               +Dis[sol.Chromosome[Ins.Pointer[i + 1]-1]][Ins.Chromosome[i+1]];
            D.push_back(d);
            if (d > Dmax) {
                return false;
            }
        }
    }
    d=Dis[Ins.Pointer[Ins.Pointer.size() - 1]][sol.Chromosome[Ins.Pointer[Ins.Pointer.size() - 1]]]+
      GetSegmentDistence(sol.Chromosome, Ins.Pointer[Ins.Pointer.size() - 1], b, Dis) + Dis[sol.Chromosome[b]][0];

    D.push_back(d);
    if (d > Dmax) {
        return false;
    }

    // Verifier le cout de temps d'insertion
    Time=GetSegmentDistence(sol.Chromosome, a, b, Dis)/Vmoy;
    Ins.Time=0;
    for (int i = 0; i < D.size() - 1; i++) {
        Ins.Time = Ins.Time + Vrecharge;
    }
    Ins.Time = Ins.Time + Ins.cout1 / Vmoy;
    Time = Time + Ins.Time;
    if (Time > Tmax) {
        return false;
    } else {
        //cout<<"Tournee Faisable."<<endl;
        return true;
    }
}
*/
bool CheckEnergyonelement(solution &sol, int b, solution &Ins, double Dis[][500], double Dmax, double Tmax, double Vrecharge, double Vmoy, vector<double> &D,cdp CDP[]) {
    double Time = 0;//完成这个循环所用的时间
    vector<double>().swap(D);
    double d=0;
    if (Ins.Pointer[0]==b+1) {
        d = Dis[0][sol.Chromosome[b]] + Dis[sol.Chromosome[Ins.Pointer[0] - 1]][Ins.Chromosome[0]];
    if (d>Dmax){
        return false;
    }
    if(Dis[Ins.Chromosome[0]][0]>Dmax){
        return false;
    }
        Time=(Dis[Ins.Chromosome[0]][sol.Chromosome[b]]+Dis[sol.Chromosome[b]][0]+Dis[0][Ins.Chromosome[0]])/Vmoy+Vrecharge;
    }
    if (Ins.Pointer[0]==b){
        d = Dis[0][Ins.Chromosome[0]] ;
        if (d>Dmax){
            return false;
        }
        if(Dis[Ins.Chromosome[0]][sol.Chromosome[b]]+Dis[sol.Chromosome[b]][0]>Dmax){
            return false;
        }
        Time=(Dis[Ins.Chromosome[0]][sol.Chromosome[b]]+Dis[sol.Chromosome[b]][0]+Dis[0][Ins.Chromosome[0]])/Vmoy+Vrecharge;}
    if (Time > Tmax) {
        return false;
    } else {
        //cout<<"Tournee Faisable."<<endl;
        return true;
    }

}
//// ************************************************************************************************************** ////
//// *****************************************  CoutInsertion   *************************************************** ////
//// ************************************************************************************************************** ////
//// * Calculer les cout d'insertion
//// * a,b是染色体中的位置,不能是分割点
//// * 每次循环都重新计算插入成本
//// * Dis est la matrice de distence entre les clients et les points de recharge

//// * Optiion 1 - Calculer tous les cout de pr ************************************************************************

bool CoutInsertionOption1(solution &sol,int a, int b,vector<solution> &V,cdp CDP[], double Dis[][500]){
    solution Ins;
    vector<solution>().swap(V);

    for(int j=1;j<CDP[0].APR.size();j++){
        Ins.Name=CDP[0].APR[j];
        Ins.Chromosome.push_back(CDP[0].APR[j]);
        Ins.cout1=Dis[0][CDP[0].APR[j]]+Dis[CDP[0].APR[j]][sol.Chromosome[a]]-Dis[0][sol.Chromosome[a]];
        Ins.cout2=Dis[CDP[0].APR[j]][sol.Chromosome[a]];
        Ins.cout3=0.5*Ins.cout1+0.5*Ins.cout2;
        Ins.Fitness=Ins.cout1;
        Ins.Pointer.push_back(a);
        V.push_back(Ins);
        vector<int>().swap(Ins.Chromosome);
        vector<int>().swap(Ins.Pointer);
    }

    for(int i=a;i<b;i++){
        int k=sol.Chromosome[i];
        for(int j=0;j<CDP[k].APR.size();j++){
            Ins.Name=CDP[k].APR[j];
            Ins.Chromosome.push_back(CDP[k].APR[j]);
            Ins.cout1=Dis[k][CDP[k].APR[j]]+Dis[CDP[k].APR[j]][sol.Chromosome[i+1]] -Dis[sol.Chromosome[i]][sol.Chromosome[i+1]];
            Ins.cout2=Dis[CDP[k].APR[j]][sol.Chromosome[i+1]];
            Ins.cout3=0.5*Ins.cout1+0.5*Ins.cout2;
            Ins.Fitness=Ins.cout1;
            Ins.Pointer.push_back(i+1);
            V.push_back(Ins);
            vector<int>().swap(Ins.Chromosome);
            vector<int>().swap(Ins.Pointer);
        }
    }

    for(int j=1;j<CDP[sol.Chromosome[b]].APR.size();j++){
        Ins.Name=CDP[sol.Chromosome[b]].APR[j];
        Ins.Chromosome.push_back(CDP[sol.Chromosome[b]].APR[j]);
        Ins.cout1=Dis[sol.Chromosome[b]][CDP[sol.Chromosome[b]].APR[j]]+Dis[CDP[sol.Chromosome[b]].APR[j]][0]-Dis[sol.Chromosome[b]][0];
        Ins.cout2=Dis[CDP[sol.Chromosome[b]].APR[j]][0];
        Ins.cout3=0.5*Ins.cout1+0.5*Ins.cout2;
        Ins.Fitness=Ins.cout1;
        Ins.Pointer.push_back(b);
        V.push_back(Ins);
        vector<int>().swap(Ins.Chromosome);
        vector<int>().swap(Ins.Pointer);
    }

    return true;
}
////// * Optiion 2 - Calculer les cout de 2 pr ***************************************************************************

bool CoutInsertionOption2(int a,vector<solution> &V){
    solution Ins;
    Ins.Chromosome.push_back(0);
    Ins.Chromosome.push_back(0);
    Ins.Pointer.push_back(0);
    Ins.Pointer.push_back(0);
    if(V.size()>=a){
        for(int i=0;i<a;i++){// Inserer 2 fois
            for(int j=0;j<a;j++){
                if(i!=j){
                    Ins.Chromosome[0]=V[i].Name;
                    Ins.Chromosome[1]=V[j].Name;
                    Ins.Pointer[0]=V[i].Pointer[0];
                    Ins.Pointer[1]=V[j].Pointer[0];
                    Ins.Fitness=V[i].Fitness+V[j].Fitness;
                    Ins.cout1=V[i].cout1+V[j].cout1;
                    Ins.cout2=V[i].cout2+V[j].cout2;
                    Ins.cout3=V[i].cout3+V[j].cout3;
                    Ins.Time=V[i].Time+V[j].Time;
                    V.push_back(Ins);
                }
            }
        }
    }
    else{
        a=V.size();
        for(int i=0;i<a;i++){// Inserer 2 fois
            for(int j=0;j<a;j++){
                if(i!=j){
                    Ins.Chromosome[0]=V[i].Name;
                    Ins.Chromosome[1]=V[j].Name;
                    Ins.Pointer[0]=V[i].Pointer[0];
                    Ins.Pointer[1]=V[j].Pointer[0];
                    Ins.Fitness=V[i].Fitness+V[j].Fitness;
                    Ins.cout1=V[i].cout1+V[j].cout1;
                    Ins.cout2=V[i].cout2+V[j].cout2;
                    Ins.cout3=V[i].cout3+V[j].cout3;
                    Ins.Time=V[i].Time+V[j].Time;
                    V.push_back(Ins);
                }
            }
        }
    }

    return true;
}
////// * Optiion 3 - Calculer les cout de 3 derniere pr pour repair regarder *********************************************
bool CoutInsertionOption3(solution sol,int a, int b,vector<solution> &V,cdp CDP[], double Dis[][500]){
    solution Ins;
    vector<solution>().swap(V);

    //Insertion d'une station de recharge en partant du depot juste apres depot
    int br=sol.Chromosome[a];
    for(int j=1;j<CDP[br].APR.size();j++){
        Ins.Name=CDP[br].APR[j];
        Ins.Chromosome.push_back(CDP[br].APR[j]);
        Ins.cout1=Dis[0][CDP[br].APR[j]]+Dis[CDP[br].APR[j]][sol.Chromosome[a]]-Dis[0][sol.Chromosome[a]];
        Ins.cout2=Dis[CDP[br].APR[j]][sol.Chromosome[a]];
        Ins.cout3=0.5*Ins.cout1+0.5*Ins.cout2;
        Ins.Fitness=Ins.cout1;
        Ins.Pointer.push_back(a);
        V.push_back(Ins);
        vector<int>().swap(Ins.Chromosome);
        vector<int>().swap(Ins.Pointer);
    }
    //insertions de stations avant i+1 tq i+1 dans [a+1,b+1]
    for(int i=a;i<b;i++) {
        int k = sol.Chromosome[i];
        for (int j = 0; j < CDP[k].APR.size(); j++) {
            Ins.Name = CDP[k].APR[j];
            Ins.Chromosome.push_back(CDP[k].APR[j]);
            Ins.cout1 =
                    Dis[k][CDP[k].APR[j]] + Dis[CDP[k].APR[j]][sol.Chromosome[i + 1]] - Dis[k][sol.Chromosome[i + 1]];
            Ins.cout2 = Dis[CDP[k].APR[j]][sol.Chromosome[i + 1]];
            Ins.cout3 = 0.5 * Ins.cout1 + 0.5 * Ins.cout2;
            Ins.Fitness = Ins.cout1;
            Ins.Pointer.push_back(i + 1);
            V.push_back(Ins);
            vector<int>().swap(Ins.Chromosome);
            vector<int>().swap(Ins.Pointer);
        }
    }
    int br1=sol.Chromosome[b];
    for(int j=1;j<CDP[br1].APR.size();j++){
        Ins.Name=CDP[br1].APR[j];
        Ins.Chromosome.push_back(CDP[br1].APR[j]);
        Ins.cout1=Dis[CDP[br1].APR[j]][0]+Dis[sol.Chromosome[b]][CDP[br1].APR[j]]-Dis[sol.Chromosome[b]][0];
        Ins.cout2=Dis[CDP[br1].APR[j]][sol.Chromosome[b]];
        Ins.cout3=0.5*Ins.cout1+0.5*Ins.cout2;
        Ins.Fitness=Ins.cout1;
        Ins.Pointer.push_back(b+1);
        V.push_back(Ins);
        vector<int>().swap(Ins.Chromosome);
        vector<int>().swap(Ins.Pointer);
    }
    return true;
}
//// ************************************************************************************************************** ////
//// **********************************************    Repair   *************************************************** ////
//// ************************************************************************************************************** ////
//// * Fonction de reparer 2 Option
//// * a,b: La position du début et de la fin du tournee dans le chromosome,不能是分割点
//// * V : vector de cout d'insertion

//// * Option 1 -- 尝试插入2个点但是不尝试所有的点  inserer 2 points de recharge *****************************************

bool RepaireOption1( solution sol, int a, int b, solution &sol_repair, double Dmax, double Tmax, double Vmoy,
                     double Vrecharge,double Dis[][500], cdp CDP[]){
    bool Continue;
    double Time=0;// Le temps total sans insertion pour cette tournee
    vector<double> D; // Le distence total sans insertion pour cette tournee
    vector<solution> V;

    CoutInsertionOption1(sol, a, b, V, CDP, Dis); // Calculer les cout d'insertion
    MergeSort(V); // Trier la solution en fonction de la fitness de la solution
    CoutInsertionOption2(4,V);//取前4个最小的排列组合
    MergeSort(V); // Trier la solution en fonction de la fitness de la solution
//    for(int i=0;i<V.size();i++) {
//        cout<<V[i].cout1<<"       "<<V[i].cout2<<endl;
//    }

    //Juger de la faisabilité de la solution selon l'ordre
    for(int i=0;i<V.size();i++){
        vector<double>().swap(D);
        Continue=CheckEnergy(sol, a, b, V[i], Dis, Dmax, Tmax,Vrecharge, Vmoy, D);
        if(Continue){
            sol_repair.Chromosome.swap(V[i].Chromosome);
            sol_repair.Pointer.swap(V[i].Pointer);
            sol_repair.Time=V[i].Time;
            sol_repair.cout1=V[i].cout1;
            sol_repair.cout2=V[i].cout2;
            sol_repair.cout3=V[i].cout3;
            sol_repair.Fitness=V[i].Fitness;
            // cout<<"La solution de reparer est "<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.Pointer[0]<<endl;
            return true;
        }
    }
    // cout<<"Il n'y a pas de solution de reparer."<<endl;
    return false;
}
//// * Option 2 -- 保留之前的可行的路径并在其基础上再增加点 Regarder *****************************************************

bool RepaireOption2( solution sol, int a, int b, solution &sol_repair, double Dmax, double Tmax, double Vmoy,
                     double Vrecharge, double Dis[][500], cdp CDP[], vector<route> RF){
    bool Continue;
    double Time=0;// Le temps total sans insertion pour cette tournee
    vector<double> D; // Le distence total sans insertion pour cette tournee
    vector<solution> V;

    if(RF[RF.size()-1].repair.Chromosome.size()==0){
        CoutInsertionOption3(sol, b-1, b, V, CDP, Dis); // Calculer les cout d'insertion
        MergeSort(V); // Trier la solution en fonction de la fitness de la solution
        //Juger de la faisabilité de la solution selon l'ordre
        for(int i=0;i<V.size();i++){
            vector<double>().swap(D);
            Continue=CheckEnergy(sol, a, b, V[i], Dis, Dmax,Tmax, Vrecharge, Vmoy,D);
            if(Continue){
                sol_repair.Chromosome.swap(V[i].Chromosome);
                sol_repair.Pointer.swap(V[i].Pointer);
                sol_repair.Time=V[i].Time;
                sol_repair.cout1=V[i].cout1;
                sol_repair.cout2=V[i].cout2;
                sol_repair.cout3=V[i].cout3;
                sol_repair.Fitness=V[i].Fitness;
                // cout<<"La solution de reparer est "<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.Pointer[0]<<endl;
                return true;
            }
        }
    }
    if(RF[RF.size()-1].repair.Chromosome.size()==1){
        vector<double>().swap(D);
        Continue=CheckEnergy(sol, a, b, RF[RF.size()-1].repair, Dis, Dmax,Tmax, Vrecharge, Vmoy,D);
        if(Continue){
            sol_repair.Chromosome.swap(RF[RF.size()-1].repair.Chromosome);
            sol_repair.Pointer.swap(RF[RF.size()-1].repair.Pointer);
            sol_repair.Time=RF[RF.size()-1].repair.Time;
            sol_repair.cout1=RF[RF.size()-1].repair.cout1;
            sol_repair.cout2=RF[RF.size()-1].repair.cout2;
            sol_repair.cout3=RF[RF.size()-1].repair.cout3;
            sol_repair.Fitness=RF[RF.size()-1].repair.Fitness;
            //cout<<"La solution de reparer est "<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.Pointer[0]<<endl;
            return true;
        }
        else{
            CoutInsertionOption3(sol, b-1, b, V, CDP, Dis); // Calculer les cout d'insertion
            MergeSort(V); // Trier la solution en fonction de la fitness de la solution

            for(int i=0;i<V.size();i++){
                vector<double>().swap(D);
                sol_repair.Chromosome.push_back(RF[RF.size()-1].repair.Chromosome[0]);
                sol_repair.Chromosome.swap(V[i].Chromosome);
                sol_repair.Chromosome.push_back(RF[RF.size()-1].repair.Pointer[0]);
                sol_repair.Pointer.swap(V[i].Pointer);
                sol_repair.Time=V[i].Time+RF[RF.size()-1].repair.Time;
                sol_repair.cout1=V[i].cout1+RF[RF.size()-1].repair.cout1;
                sol_repair.cout2=V[i].cout2+RF[RF.size()-1].repair.cout2;
                sol_repair.cout3=V[i].cout3+RF[RF.size()-1].repair.cout3;
                sol_repair.Fitness=V[i].Fitness+RF[RF.size()-1].repair.Fitness;
                Continue=CheckEnergy(sol, a, b, sol_repair, Dis, Dmax,Tmax, Vrecharge, Vmoy,D);
                if(Continue){
                    // cout<<"La solution de reparer est "<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.Pointer[0]<<endl;
                    return true;
                }
            }
        }
    }
    if(RF[RF.size()-1].repair.Chromosome.size()>=2){
        // cout<<"Il n'y a pas de solution de reparer."<<endl;
        return false;
    }
    // cout<<"Il n'y a pas de solution de reparer."<<endl;
    return false;
}
////// * Option 3 -- Consider juste les 2/3 derniere neouds ****************************************************************

bool RepaireOption3( solution sol, int a, int b, solution &sol_repair, double Dmax, double Tmax, double Vmoy,
                     double Vrecharge, double Dis[][500], cdp CDP[], int num){
    bool Continue;
    double Time=0;// Le temps total sans insertion pour cette tournee
    vector<double> D; // Le distence total sans insertion pour cette tournee
    vector<solution> V;

    int c=0;// 确定策略的寻找范围
    if(b-a+1>num){
        c=b-num+1;
        CoutInsertionOption3(sol, c, b, V, CDP, Dis); // Calculer les cout d'insertion
    }
    else{
        CoutInsertionOption1(sol, a, b, V, CDP, Dis); // Calculer les cout d'insertion
    }
    MergeSort(V); // Trier la solution en fonction de la fitness de la solution
    CoutInsertionOption2(4,V);//取前4个最小的排列组合
    MergeSort(V); // Trier la solution en fonction de la fitness de la solution

    //Juger de la faisabilité de la solution selon l'ordre
    for(int i=0;i<V.size();i++){
        vector<double>().swap(D);
        Continue=CheckEnergy(sol, a, b, V[i], Dis, Dmax, Tmax,Vrecharge, Vmoy, D);
        if(Continue){
            sol_repair.Chromosome.swap(V[i].Chromosome);
            sol_repair.Pointer.swap(V[i].Pointer);
            sol_repair.Time=V[i].Time;
            sol_repair.cout1=V[i].cout1;
            sol_repair.cout2=V[i].cout2;
            sol_repair.cout3=V[i].cout3;
            sol_repair.Fitness=V[i].Fitness;

            // cout<<" RRRRRR   "<<sol_repair.Fitness<<"       "<<sol_repair.dis<<endl;
            // cout<<"La solution de reparer est "<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.Pointer[0]<<endl;
            return true;
        }
    }
    // cout<<"Il n'y a pas de solution de reparer."<<endl;
    return false;
}
////// * Option 4 -- insere a partir de noeud l'energie est 50% **********************************************************

bool RepaireOption4( solution sol, int a, int b, solution &sol_repair, double Dmax, double Tmax, double Vmoy,
                     double Vrecharge, double Dis[][500], cdp CDP[]){
    bool Continue;
    double Time=0;// Le temps total sans insertion pour cette tournee
    vector<double> D; // Le distence total sans insertion pour cette tournee
    vector<solution> V;
   //if (a!=b){
      if (a==b) {
      a=a;}
        int i=a;
      double d=Dis[0][sol.Chromosome[i]];
    while(d<0.5*Dmax && i<=b){
        d=d+Dis[sol.Chromosome[i]][sol.Chromosome[i+1]];
        i++;
    }
 // i changé en a;
    CoutInsertionOption3(sol, a, b, V, CDP, Dis); // Calculer les cout d'insertion
    MergeSort(V); // Trier la solution en fonction de la fitness de la solution
/*
    CoutInsertionOption2(4,V);//取前4个最小的排列组合
    MergeSort(V); // Trier la solution en fonction de la fitness de la solution
*/

    for(int i=0;i<V.size();i++){
        vector<double>().swap(D);
        Continue=CheckEnergy(sol, a, b, V[i], Dis, Dmax, Tmax,Vrecharge, Vmoy, D);
        if(Continue) {
            sol_repair.Chromosome.swap(V[i].Chromosome);
            sol_repair.Pointer.swap(V[i].Pointer);
            sol_repair.Time = V[i].Time;
            sol_repair.cout1 = V[i].cout1;
            sol_repair.cout2 = V[i].cout2;
            sol_repair.cout3 = V[i].cout3;
            sol_repair.Fitness = V[i].Fitness;
            // cout<<"La solution de reparer est "<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.Pointer[0]<<endl;
            return true;
        }
    }
    // cout<<"Il n'y a pas de solution de reparer."<<endl;
    return false;
}/*
else{
        CoutInsertionOption3(sol, b, b, V, CDP, Dis); // Calculer les cout d'insertion
        MergeSort(V);
        for(int i=0;i<V.size();i++){
            vector<double>().swap(D);
            Continue=CheckEnergy(sol, b, b, V[i], Dis, Dmax, Tmax,Vrecharge, Vmoy, D);
            if(Continue){
                sol_repair.Chromosome.swap(V[i].Chromosome);
                sol_repair.Pointer.swap(V[i].Pointer);
                sol_repair.Time=V[i].Time;
                sol_repair.cout1=V[i].cout1;
                sol_repair.cout2=V[i].cout2;
                sol_repair.cout3=V[i].cout3;
                sol_repair.Fitness=V[i].Fitness;
                // cout<<"La solution de reparer est "<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.Pointer[0]<<endl;
                return true;
            }
        }*/
//return false;}}
                                                         

//// ************************************************************************************************************** ////
//// ***********************************************     Split  *************************************************** ////
//// ************************************************************************************************************** ////
//// * Fonction de Split : diviser la séquence ordonnée en plusieurs tournee pour calculer la valeur d'aptitude de la solution ---- 3 Options
//// * a,b : La position de l'espaceur pour chaque période
//// * S : Ensemble de solution de réparation
//// * R : Ensemble de tournee
//// * CoutRecharge : cout de ; vector<double> CoutVehicle; distence

//// Option 1 -- regarder pas ******************************************************************************************

bool SplitOption1(solution &sol,int a, int b, cdp CDP[], double Qmax, double Tmax, double Dmax, double Vmoy,
                  double Vrecharge, double CoutRecharge ,double Dis[][500]){

    vector<int> Q;//// 重新构成一个容器
    Q.push_back(0);
    for(int i=a+1;i<=b-1;i++){
        Q.push_back(sol.Chromosome[i]);
    }

    int load=0;
    int cost=0;
    int time=0;
    bool CheckEnergy;
    bool Continue=true;
    double NewV;
    double cd=0;
    double cr=0;
    vector<solution> S;
    vector<vector<int> > R;
    vector<double> V(Q.size(),0); // le coût du plus court chemin de 0 à j
    vector<double> B(Q.size(),0); // le coût du plus court chemin de 0 à j
    solution sol_repair;
    vector<int> r;
    vector<solution> s;
    int fin=Q.size()-1;

    for(int i=1;i<Q.size();i++){
        V[i]=65500;
        //N[i]=0;
    }
    // N[a]=0;

    for(int i=1;i<Q.size();i++){
        load=0;
        cost=0;
        time=0;
        int j=i;
        while(j<Q.size() && load<=Qmax && time<=Tmax ){
            load=load+CDP[Q[j]].Demande;
            if(i==j){
                cost=Dis[0][Q[j]-1]+Dis[Q[j]-1][0];
                time=cost/Vmoy+CDP[Q[j]].ServiceTime+CDP[0].ServiceTime;
            }
            else{
                cost=cost-Dis[Q[j-1]-1][0]+Dis[Q[j-1]-1][Q[j]-1]+Dis[Q[j]-1][0];
                time=cost/Vmoy+CDP[Q[j]].ServiceTime;
            }
            if(load<=Qmax && time<=Tmax){
                if(cost<=Dmax){
                    //cout<<"["<<i<<","<<j<<"]"<<"Tourmee faisable"<<endl;
                    NewV=V[i-1]+cost;
                    Continue=true;
                }
                else {
                    //cout << "[" << i << "," << j << "]" << "Tourmee infaisable" << endl;
                    vector<int>().swap(sol_repair.Chromosome);
                    vector<int>().swap(sol_repair.Pointer);
                    vector<int>().swap(sol_repair.InOut);
                    CheckEnergy = RepaireOption1(sol, i+a, j+a, sol_repair, Dmax, Tmax, Vmoy, Vrecharge, Dis, CDP);
                    if (CheckEnergy) {
                        //cout << "[" << i << "," << j << "]" << " Successful" << " La réparation a réussi" << endl;
                        sol_repair.InOut.push_back(Q[i]);
                        sol_repair.InOut.push_back(Q[j]);
                        NewV = V[i-1] + cost + sol_repair.Fitness;
                        Continue=true;
                        s.push_back(sol_repair);
                    }
                    else{
                        Continue=false;
                        // cout<<"["<<i<<","<<j<<"]"<<" Failed"<<endl;
                        break;
                    }
                }
            }
            if(NewV<V[j] && Continue){//|| (NewV==V[j] && N[i-1]+1 <N[j])
                V[j]=NewV;
                // N[j]=N[i-1]+1;
                B[j]=i-1;
            }
            j++;
        }
    }
//    for(int i=0;i<Q.size();i++){
//        cout<<B[i]<<endl;
//    }
    //Sauvegarder les tournee et les solution d'insertion
    while(fin!=0) {
        r.push_back(Q[B[fin]]);
        r.push_back(Q[fin]);
        cd=cd+Dis[0][Q[B[fin]-1]]+ GetSegmentDistence(Q,B[fin],fin,Dis)+Dis[Q[fin]][0];//该循环的距离长度
        R.push_back(r);
        for(int i=0;i<s.size();i++){
            if(s[i].InOut[0]==Q[B[fin]+1]){
                if(s[i].InOut[1]==Q[fin]){
                    S.push_back(s[i]);
                    //cd=cd+s[i].Fitness;
                }
            }
        }
        vector<int>().swap(r);
        fin = B[fin];
    }
//    for(int i=0;i<S.size();i++){
//        cout<<S[i].cout1<<"    "<<S[i].cout2<<endl;
//    }
    cr=S.size()*CoutRecharge;
    sol.CoutVehicle.push_back(cd);
    sol.CoutRecharge.push_back(cr);
    sol.R.push_back(R);
    sol.S.push_back(S);
    return true;
}
/// Option 2 -- regarder les solution faisable  ***********************************************************************

bool SplitOption2(solution &sol,int a, int b, cdp CDP[], double Qmax, double Tmax, double Dmax, double Vmoy,
                  double Vrecharge, double CoutRecharge, double Dis[][500]){
    vector<int> Q;//// 重新构成一个容器
    Q.push_back(0);
    for(int i=a+1;i<=b-1;i++){
        Q.push_back(sol.Chromosome[i]);
    }

    vector<route> RF; //可行路径的集合
    route rf;//可行路径
    int load=0;
    int cost=0;
    int time=0;
    bool CheckEnergy;
    bool Continue=true;
    double NewV;
    double cd=0;
    double cr=0;
    vector<solution> S;
    vector<vector<int> > R;
    vector<double> V(Q.size(),0); // le coût du plus court chemin de 0 à j
    vector<double> B(Q.size(),0); // le coût du plus court chemin de 0 à j
    //solution sol_repair;
    vector<int> r;
    vector<solution> s;
    int fin=Q.size()-1;

    for(int i=1;i<Q.size();i++){
        V[i]=655000;
        //N[i]=0;
    }
    // N[a]=0;

    //Split
    for(int i=1;i<Q.size();i++){
        load=0;
        cost=0;
        time=0;
        int j=i;
        while(j<Q.size() && load<=Qmax && time<=Tmax ){
            load=load+CDP[Q[j]].Demande;
            if(i==j){
                cost=Dis[0][Q[j]-1]+Dis[Q[j]-1][0];
                time=cost/Vmoy+CDP[Q[j]].ServiceTime+CDP[0].ServiceTime;
            }
            else{
                cost=cost-Dis[Q[j-1]-1][0]+Dis[Q[j-1]-1][Q[j]-1]+Dis[Q[j]-1][0];
                time=cost/Vmoy+CDP[Q[j]].ServiceTime;
            }
            if(load<=Qmax && time<=Tmax){
                if(cost<=Dmax){
                    vector<int>().swap(rf.r);
                    rf.r.push_back(i);
                    rf.r.push_back(j);
                    RF.push_back(rf);
                    //cout<<"["<<i<<","<<j<<"]"<<"Tourmee faisable"<<endl;
                    NewV=V[i-1]+cost;
                    Continue=true;
                }
                else {
                    vector<int>().swap(rf.r);
                    rf.r.push_back(i);
                    rf.r.push_back(j);
                    //cout << "[" << i << "," << j << "]" << "Tourmee infaisable" << endl;
                    vector<int>().swap(rf.repair.Chromosome);
                    vector<int>().swap(rf.repair.Pointer);
                    vector<int>().swap(rf.repair.InOut);
                    CheckEnergy = RepaireOption2(sol, i+a, j+a, rf.repair, Dmax, Tmax, Vmoy, Vrecharge, Dis, CDP, RF);
                    if (CheckEnergy) {
                        //  cout << "[" << i << "," << j << "]" << " Successful" << " La réparation a réussi" << endl;
                        rf.repair.InOut.push_back(Q[i]);
                        rf.repair.InOut.push_back(Q[j]);
                        RF.push_back(rf);
                        NewV = V[i-1] + cost + rf.repair.Fitness;
                        Continue=true;
                        s.push_back(rf.repair);
                    }
                    else{
                        Continue=false;
                        //cout<<"["<<i<<","<<j<<"]"<<" Failed"<<endl;
                        break;
                    }
                }
            }
            if(NewV<V[j] && Continue){//|| (NewV==V[j] && N[i-1]+1 <N[j])
                V[j]=NewV;
                // N[j]=N[i-1]+1;
                B[j]=i-1;
                //cout<<"Predecessur"<<B[j]<<endl;
            }
            j++;
        }
    }
//    for(int i=0;i<Q.size();i++){
//        cout<<B[i]<<endl;
//    }
    //Sauvegarder les tournee et les solution d'insertion
    while(fin!=0) {
        r.push_back(Q[B[fin]]);
        r.push_back(Q[fin]);
        cd=cd+Dis[0][Q[B[fin]]-1]+ GetSegmentDistence(Q,B[fin],fin,Dis)+Dis[Q[fin]][0];
        R.push_back(r);
        for(int i=0;i<s.size();i++){
            if(s[i].InOut[0]==Q[B[fin]]){
                if(s[i].InOut[1]==Q[fin]){
                    S.push_back(s[i]);
                    //cd=cd+s[i].Fitness;
                }
            }
        }
        vector<int>().swap(r);
        fin = B[fin];
    }
    cr=S.size()*CoutRecharge;
    sol.CoutVehicle.push_back(cd);
    sol.CoutRecharge.push_back(cr);
    sol.R.push_back(R);
    sol.S.push_back(S);
    return true;
}
//// Option3*************************************************************************************************************
bool SplitOption3(solution &sol,int a, int b, cdp CDP[], double Qmax, double Tmax, double Dmax, double Vmoy,
                  double Vrecharge, double CoutRecharge, double Dis[][500],int num) {
    vector<int> Q;//// 重新构成一个容器
    Q.push_back(0);
    for (int i = a + 1; i <= b - 1; i++) {
        Q.push_back(sol.Chromosome[i]);
    }

    int load = 0;
    int cost = 0;
    int time = 0;
    bool CheckEnergy;
    bool Continue = true;
    double NewV;
    double cd = 0;
    double cr = 0;
    vector<solution> S;
    vector<vector<int> > R;
    vector<double> V(Q.size(), 0); // le coût du plus court chemin de 0 à j
    vector<double> B(Q.size(), 0); // le coût du plus court chemin de 0 à j
    solution sol_repair;
    vector<int> r;
    vector<solution> s;
    int fin = Q.size() - 1;

    for (int i = 1; i < Q.size(); i++) {
        V[i] = 65500;
        //N[i]=0;
    }
    // N[a]=0;

    //Split
    for (int i = 1; i < Q.size(); i++) {
        load = 0;
        cost = 0;
        time = 0;
        int j = i;
        while (j < Q.size() && load <= Qmax && time <= Tmax) {
            load = load + CDP[Q[j]].Demande;
            if (i == j) {
                cost = Dis[0][Q[j] - 1] + Dis[Q[j] - 1][0];
                time = cost / Vmoy + CDP[Q[j]].ServiceTime + CDP[0].ServiceTime;
            } else {
                cost = cost - Dis[Q[j - 1] - 1][0] + Dis[Q[j - 1] - 1][Q[j] - 1] + Dis[Q[j] - 1][0];
                time = cost / Vmoy + CDP[Q[j]].ServiceTime;
            }
            if (load <= Qmax && time <= Tmax) {
                if (cost <= Dmax) {
                    // cout<<"["<<i<<","<<j<<"]"<<"Tourmee faisable"<<endl;
                    NewV = V[i - 1] + cost;
                    Continue = true;
                } else {
                    //cout << "[" << i << "," << j << "]" << "Tourmee infaisable" << endl;
                    vector<int>().swap(sol_repair.Chromosome);
                    vector<int>().swap(sol_repair.Pointer);
                    vector<int>().swap(sol_repair.InOut);
                    CheckEnergy = RepaireOption3(sol, i + a, j + a, sol_repair, Dmax, Tmax, Vmoy, Vrecharge, Dis, CDP,
                                                 num);

                    if (CheckEnergy) {
                        //cout<<sol_repair.Fitness<<"    "<<sol_repair.dis<<endl;
                        // cout << "[" << i << "," << j << "]" << " Successful" << " La réparation a réussi" << endl;
                        sol_repair.InOut.push_back(Q[i]);
                        sol_repair.InOut.push_back(Q[j]);
                        NewV = V[i - 1] + cost + sol_repair.Fitness;
                        Continue = true;
                        s.push_back(sol_repair);
                    } else {
                        Continue = false;
                        //cout<<"["<<i<<","<<j<<"]"<<" Failed"<<endl;
                        break;
                    }
                }
            }
            if (NewV < V[j] && Continue) {//|| (NewV==V[j] && N[i-1]+1 <N[j])
                V[j] = NewV;
                // N[j]=N[i-1]+1;
                B[j] = i - 1;
                // cout<<"Predecessur"<<B[j]<<endl;
            }
            j++;
        }
    }
//    for(int i=0;i<Q.size();i++){
//        cout<<B[i]<<endl;
//    }
    //Sauvegarder les tournee et les solution d'insertion
    while (fin != 0) {
        r.push_back(Q[B[fin]]);
        r.push_back(Q[fin]);
        cd = cd + Dis[0][Q[B[fin]] - 1] + GetSegmentDistence(Q, B[fin], fin, Dis) + Dis[Q[fin]][0];
        R.push_back(r);
        for (int i = 0; i < s.size(); i++) {
            if (s[i].InOut[0] == Q[B[fin]]) {
                if (s[i].InOut[1] == Q[fin]) {
                    S.push_back(s[i]);
                    //cd=cd+s[i].Fitness;
                }
            }
        }
        vector<int>().swap(r);
        fin = B[fin];
    }
//    cout<<S.size()<<endl;
//    for(int i=0;i<S.size();i++){
//        cout<<S[i].cout1<<"    "<<S[i].cout2<<endl;
//    }
    cr = S.size() * CoutRecharge;
    sol.CoutVehicle.push_back(cd);
    sol.CoutRecharge.push_back(cr);
    sol.R.push_back(R);
    sol.S.push_back(S);
    return true;
}
bool CoutInsertionOption5(solution sol,int a,int b,vector<solution> &V,cdp CDP[], double Dis[][500]){
    solution Ins;
    vector<solution>().swap(V);

    int  k=sol.Chromosome[b];
    for(int j=1;j<CDP[k].APR.size();j++) {
        Ins.Name = CDP[sol.Chromosome[b]].APR[j];
        Ins.Chromosome.push_back(CDP[sol.Chromosome[b]].APR[j]);
        Ins.cout1 = Dis[sol.Chromosome[b]][CDP[sol.Chromosome[b]].APR[j]] + Dis[CDP[sol.Chromosome[b]].APR[j]][0] -
                    Dis[sol.Chromosome[b]][0];
        Ins.cout2 = Dis[CDP[sol.Chromosome[b]].APR[j]][0];
        Ins.cout3 = 0.5 * Ins.cout1 + 0.5 * Ins.cout2;
        Ins.Fitness = Ins.cout1;
        //APRESB
        Ins.Pointer.push_back(b + 1);
        V.push_back(Ins);
        vector<int>().swap(Ins.Chromosome);
        vector<int>().swap(Ins.Pointer);
    }
    for(int j=1;j<CDP[k].APR.size();j++) {
        Ins.Name = CDP[sol.Chromosome[b]].APR[j];
        Ins.Chromosome.push_back(CDP[sol.Chromosome[b]].APR[j]);
        Ins.cout1 = Dis[sol.Chromosome[0]][CDP[sol.Chromosome[b]].APR[j]] + Dis[CDP[sol.Chromosome[b]].APR[j]][sol.Chromosome[b]] -
                    Dis[sol.Chromosome[b]][0];
        Ins.cout2 = Dis[CDP[sol.Chromosome[b]].APR[j]][0];
        Ins.cout3 = 0.5 * Ins.cout1 + 0.5 * Ins.cout2;
        Ins.Fitness = Ins.cout1;
        //
        //Avant B
        Ins.Pointer.push_back(b);
        V.push_back(Ins);
        vector<int>().swap(Ins.Chromosome);
        vector<int>().swap(Ins.Pointer);
    }
    return true;
}
//// Option 4 -- inserer pour  *****************************************************************************************
bool Repaireoneelement( solution sol, int b, solution &sol_repair, double Dmax, double Tmax, double Vmoy,
                        double Vrecharge, double Dis[][500], cdp CDP[]) {
    bool Continue;
    double Time=0;// Le temps total sans insertion pour cette tournee
    vector<double> D; // Le distence total sans insertion pour cette tournee
    vector<solution> V;
    CoutInsertionOption5(sol, b, b, V, CDP, Dis); // Calculer les cout d'insertion
    MergeSort(V);
    for(int i=0;i<V.size();i++) {
        vector<double>().swap(D);
        Continue = CheckEnergyonelement(sol, b, V[i], Dis, Dmax, Tmax, Vrecharge, Vmoy, D,CDP);
        if (Continue) {
            sol_repair.Chromosome.swap(V[i].Chromosome);
            sol_repair.Pointer.swap(V[i].Pointer);
            sol_repair.Time = V[i].Time;
            sol_repair.cout1 = V[i].cout1;
            sol_repair.cout2 = V[i].cout2;
            sol_repair.cout3 = V[i].cout3;
            sol_repair.Fitness = V[i].Fitness;
        return true;}
    }
return false;}

bool SplitOption4(solution &sol,int a, int b, cdp CDP[], double Qmax, double Tmax, double Dmax, double Vmoy,
                  double Vrecharge, double CoutRecharge ,double Dis[][500]) {
    vector<int> Q;//// 重新构成一个容器
    vector<double> traceb;
    Q.push_back(0);
    for (int i = a + 1; i <= b - 1; i++) {
        Q.push_back(sol.Chromosome[i]);
    }
/*    Q.push_back(0);
    Q.push_back(14);
    Q.push_back(4);
    Q.push_back(19);
    Q.push_back(9);
    Q.push_back(6);
    Q.push_back(18);
    Q.push_back(5);
    Q.push_back(17);
    Q.push_back(1);
    Q.push_back(8);
    Q.push_back(10);
    Q.push_back(16);
    Q.push_back(12);
    Q.push_back(11);
    Q.push_back(7);
    Q.push_back(13);
    Q.push_back(3);
    Q.push_back(2);
    Q.push_back(15);
    Q.push_back(20);*/

    double load = 0;
    double cost = 0.00001;
    double time = 0.0;
    bool CheckEnergy;
    bool Continue = true;
    double NewV = 65500.0000000009;
    double cd = 0;
    double cr = 0;
    vector<solution> S;
    vector<vector<int> > R;
    vector<double> V(Q.size(), 0.0); // le coût du plus court chemin de 0 à j
    vector<int> B(Q.size(), 0); // l'arc du plus court chemin de 0 à j
    vector<double> N(Q.size(), 0);
    solution sol_repair;
    vector<int> r;
    vector<solution> s;
    int fin = Q.size() - 1;

    for (int i = 1; i < Q.size(); i++) {
        V[i] = 65500.0000000009;//Parametre a revoir augmenter pour les comparaisons avec la litterature;
    }
    // N[a]=0;
    // revoir les vehicules
    //Split
    for (int i = 1; i < Q.size(); i++) {
        cost = 0.0;
        time = 0.0;
        int j = i;
        //bool Continue2= true;
        while (j < Q.size() && load <= Qmax && time < Tmax) {
            //<= Tmax && Continue2) {
            //add index nbvj meme structure que V
            // dans chaque condition de while ajouter contrainte <numv max
           //load = load + CDP[Q[j]].Demande;
            if (i == j) {
                cost = Dis[0][Q[j]] + Dis[Q[j]][0];
                time = cost / Vmoy + 0.5+0.25; //0.5 depot
            }

                /*  if (load <= Qmax && time <= Tmax) {
                  if (cost <= Dmax) {
                      //cout<<"["<<i<<","<<j<<"]"<<"Tourmee faisable"<<endl;
                      NewV = V[i - 1] + cost;
                      Continue = true;
                  } else {
                      //cout << "[" << i << "," << j << "]" << "Tourmee infaisable" << endl;
                      vector<int>().swap(sol_repair.Chromosome);
                      vector<int>().swap(sol_repair.Pointer);
                      vector<int>().swap(sol_repair.InOut);
                      CheckEnergy = Repaireoneelement(sol, i + a, sol_repair, Dmax, Tmax, Vmoy, Vrecharge, Dis, CDP);


                      if (CheckEnergy) {
                          //cout << "[" << i << "," << j << "]" << " Successful" << " La réparation a réussi" << endl;
                          sol_repair.InOut.push_back(Q[i]);
                          sol_repair.InOut.push_back(Q[j]);
                          NewV = V[i - 1] + cost + sol_repair.Fitness;
                          Continue = true;
                          s.push_back(sol_repair);

                          //cout<<"La solution de reparer est "<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.Pointer[0]<<endl;
                      } else {
                          Continue = false;
                          // cout<<"["<<i<<","<<j<<"]"<<" Failed"<<endl;
                          cout << "ERREUR"<<endl;
                      }
              }}}*/
            else {
                cost = cost - Dis[Q[j - 1]][0] + Dis[Q[j - 1]][Q[j]] + Dis[Q[j]][0];
                time = cost / Vmoy + (j-i+1)*0.5+0.25 ;//(depot)
            }
            if (load <= Qmax && time <= Tmax) {
                if (cost <= Dmax){
                    //cout<<"["<<i<<","<<j<<"]"<<"Tourmee faisable"<<endl;
                    NewV = V[i - 1] + cost;
                    Continue = true;
                } else {
                    //cout << "[" << i << "," << j << "]" << "Tourmee infaisable" << endl;
                    vector<int>().swap(sol_repair.Chromosome);
                    vector<int>().swap(sol_repair.Pointer);
                    vector<int>().swap(sol_repair.InOut);
                    CheckEnergy = RepaireOption4(sol, i + a, j + a, sol_repair, Dmax, Tmax, Vmoy, Vrecharge, Dis, CDP);


                    if (CheckEnergy) {
                        //cout << "[" << i << "," << j << "]" << " Successful" << " La réparation a réussi" << endl;
                        sol_repair.InOut.push_back(Q[i]);
                        sol_repair.InOut.push_back(Q[j]);
//                       int pt = sol_repair.Pointer[0];
//                        if (pt < j && pt > i) {
//                            sol_repair.Fitness =
//                                    Dis[Q[pt]][sol_repair.Chromosome[0]] + Dis[sol_repair.Chromosome[0]][Q[pt + 1]] -
//                                    Dis[Q[pt]][Q[pt + 1]];
//                        }
//                        if (pt == i - 1) {
//                            sol_repair.Fitness = -Dis[0][Q[i]] + Dis[0][sol_repair.Chromosome[0]] +
//                                                 Dis[sol_repair.Chromosome[0]][Q[i]];
//                        }
//                        if (pt == j) {
//                            sol_repair.Fitness = -Dis[Q[j]][0] + Dis[Q[j]][sol_repair.Chromosome[0]] +
//                                                 Dis[sol_repair.Chromosome[0]][0];
//                        }
                        NewV = V[i - 1] + cost + sol_repair.Fitness;
                        Continue = true;
                        s.push_back(sol_repair);
                        time = double(cost+ sol_repair.Fitness) / double(Vmoy) + sol_repair.Chromosome.size()* 0.25 +
                               (j - i + 1) * 0.5+0.25; //Depot
                        //cout<<"La solution de reparer est "<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.Pointer[0]<<endl;
                    } else {
                        Continue = false;
                        // cout<<"["<<i<<","<<j<<"]"<<" Failed"<<endl;
                        break;
                    }
                    //numvehicule ++
                }
            }

                if (NewV < V[j] && Continue && time<=Tmax) {//|| (NewV==V[j] && N[i-1]+1 <N[j])
                    V[j] = NewV;
                    B[j] = i - 1;
                    N[j] = N[i - 1] + 1;
                }
                j++;
            }
    }
    //   for(int i=0;i<Q.size();i++){
    //      cout<<B[i]<<endl;
    //}
    //Sauvegarder les tournee et les solution d'insertion
    //tournee peuvent etre extraite de r.size () ?
    // if V!=0 pour le reinitialiser;
    while (fin!=0) {
        double time2=0;
        r.push_back(fin);
        r.push_back(B[fin]);
        cd=cd+Dis[0][Q[B[fin]+1]]+ GetSegmentDistence(Q,B[fin]+1,fin,Dis)+Dis[Q[fin]][0];
        //time2=GetSegmentDistence(Q,B[fin]+1,fin,Dis)+Dis[Q[fin]][0]+Dis[0][Q[B[fin]+1]];
        R.push_back(r);
        for(int i=0;i<s.size();i++) {
            if (s[i].InOut[0] == Q[B[fin] + 1]) {
                if (s[i].InOut[1] == Q[fin]) {
                    S.push_back(s[i]);
                    cd = cd + s[i].Fitness;
                    //time2=time2+s[i].Fitness;
                    //time2=time2+Vmoy*0.25;
                            //k=k+1;
                        /*    int pt=s[i].Pointer[0];
                            if (pt<fin && pt>B[fin]){
                            cd=cd+Dis[Q[pt]][s[i].Chromosome[0]]+Dis[s[i].Chromosome[0]][Q[pt+1]]-Dis[Q[pt]][Q[pt+1]];
                        }
                        if(pt==B[fin]) {
                            cd = cd - Dis[0][Q[B[fin]]] + Dis[0][s[i].Chromosome[0]] +
                                 Dis[s[i].Chromosome[0]][Q[B[fin]]];
                        }
                            if(pt==fin) {
                                cd = cd - Dis[Q[fin]][0] + Dis[Q[fin]][s[i].Chromosome[0]] + Dis[s[i].Chromosome[0]][0];
                            }
                            if (pt> fin | pt< B[fin] ){
                                cout<<"erreur pointer"<<pt<<endl;
                            }*/
               }
            }
//
//            reverse(r.begin(), r.end());
            //cout<<r<< endl
        }
        //cout <<k<<endl
      //  time2=(time2/Vmoy)+(fin-B[fin])*0.5;
      //  if(time2>Tmax){
       //     cout<<"error time"<<endl;
       // }
        vector<int>().swap(r);
        fin = B[fin];
    }

    //cr = S.size() * CoutRecharge;
    sol.CoutVehicle.push_back(cd);
    sol.CoutRecharge.push_back(cr);
    sol.R.push_back(R);
    sol.S.push_back(S);
    sol.Fitness=cd;
    //sol.Fitness=V[Q.size()-1];
    //  for (int i=0; i<V.size();i++) {
    //cout << V[i] << endl;
    // cout <<B[i]<<endl;
    //}
    //for (int i=0; i<V.size();i++) {
        //cout << V[i] << endl;
        //cout<<N[i]<<endl;
    //}
    //for (int i=0; i<V.size();i++) {
    //    cout << traceb[-i] << endl;// B for the arcs
    //}

    return true;

}



//// ************************************************************************************************************** ////
//// **********************************************     Evaluer   ************************************************* ////
//// ************************************************************************************************************** ////
//// * Fonction d'evluer le Fitness de chaque chromosome
double EvaluerOption1(solution &sol, cdp CDP[], double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
                      double CoutRecharge,double Dis[][500], double alpha, double beta) {
    for (int i = 0; i < sol.Pointer.size() - 1; i++) {
        SplitOption1(sol, sol.Pointer[i], sol.Pointer[i + 1], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge,
                     Dis);
        sol.Fitness = sol.Fitness + alpha * sol.CoutVehicle[i] + beta * sol.CoutRecharge[i];
    }
    return sol.Fitness;
}
////*******************************************************************************************************************
double EvaluerOption2(solution &sol, cdp CDP[], double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
                      double CoutRecharge,double Dis[][500], double alpha, double beta){
    for(int i=0;i<sol.Pointer.size()-1;i++){
        SplitOption2(sol,sol.Pointer[i], sol.Pointer[i+1], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Dis);
        sol.Fitness=sol.Fitness+alpha*sol.CoutVehicle[i]+beta*sol.CoutRecharge[i];
    }
    return sol.Fitness;
}
////*******************************************************************************************************************
double EvaluerOption3(solution &sol, cdp CDP[], double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
                      double CoutRecharge,double Dis[][500], double alpha, double beta, int num){
    for(int i=0;i<sol.Pointer.size()-1;i++){
        SplitOption3(sol,sol.Pointer[i], sol.Pointer[i+1], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Dis,num);
        sol.Fitness=sol.Fitness+alpha*sol.CoutVehicle[i]+beta*sol.CoutRecharge[i];
    }
    return sol.Fitness;
}
////*******************************************************************************************************************
double EvaluerOption4(solution &sol, cdp CDP[], double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
                      double CoutRecharge,double Dis[][500], double alpha, double beta){
    for(int i=0;i<sol.Pointer.size()-1;i++){
        // cout<< "["<<sol.Pointer[i]<<"  "<<sol.Pointer[i+1]<<"     "<<sol.Chromosome[sol.Pointer[i]]<<"   "<<sol.Chromosome[sol.Pointer[i+1]]<<endl;
        SplitOption4(sol,sol.Pointer[i], sol.Pointer[i+1], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Dis);
       //sol.Fitness=sol.CoutVehicle[i];
    }
    return sol.Fitness;
}

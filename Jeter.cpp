//
// 不用的程序
//



//// * Option2
bool RepaireOption2( solution sol, int a, int b,vector<vector<vector<solution> > > &V, solution sol_repair, double Dmax, double Tmax, double Vmoy, double Vrecharge, double Dis[][110]){
 bool Continue=false;
double Time=0;
vector<double> D;
vector<solution> Ins;
//    vector<solution> Ins2;
//    solution rep;

// Inserer 1 fois
for(int i=a;i<b;i++){
for(int j=0;j<V[sol.Chromosome[i]][sol.Chromosome[i+1]-1].size();j++){
V[sol.Chromosome[i]][sol.Chromosome[i+1]-1][j].position.push_back(i+1);
Ins.push_back(V[sol.Chromosome[i]][sol.Chromosome[i+1]-1][j]);
}
}
for(int i=0;i<V[V.size()-1][sol.Chromosome[b]-1].size();i++){
V[V.size()-1][sol.Chromosome[b]-1][i].position.push_back(b+1);
Ins.push_back(V[V.size()-1][sol.Chromosome[b]-1][i]);
}
MergeSort(Ins);

while(!Continue){
for(int i=0;i<Ins.size();i++){

Continue=CheckEnergy(sol, a, b, Ins[i], Dis, Dmax, Vrecharge, D);
if(Continue){
for(int j=0;j<D.size();j++){
Time=Time+D[i]/Vmoy;
}
if(Time+Ins[i].time<=Tmax){
sol_repair.Chromosome.swap(Ins[i].Chromosome);
sol_repair.position.swap(Ins[i].position);
sol_repair.time=Ins[i].time;
sol_repair.distence= Ins[i].distence;
}
cout<<"La solution de reparer est"<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.position[0]<<endl;
return true;
}
}
b--;
}

c=sol_repair.position[0];
for(int i=c-a-1;i<=d-a-1;i++){
for(int j=0;j<V0c[i].size();j++){
Ins2.push_back(V0c[i][j]);
}
}
for(int i=c-a-1;i<=d-a-1-1;i++){
for(int j=0;j<Vcc[i].size();j++){
Ins2.push_back(Vcc[i][j]);
}
}
for(int i=c-a-1;i<=d-a-1;i++){
for(int j=0;j<Vc0[i].size();j++){
Ins2.push_back(Vc0[i][j]);
}
}
MergeSort(Ins2);
for(int i=0;i<Ins2.size();i++){
cf = CheckEnergy(sol, a, b, Ins2[i], CDP, Dmax, Vrecharge);
if (cf) {
if (T + Ins2[i].time <= Tmax) {
sol_repair.Chromosome.push_back(Ins2[i].Chromosome[0]);
sol_repair.position.push_back(Ins2[i].position[0]);
sol_repair.time = sol_repair.time + Ins2[i].time;
sol_repair.distence = sol_repair.time + Ins2[i].distence;
break;
}
}
else{
return false;
}
}
return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Repaire( solution sol, int a, int b, vector<vector<vector<solution> > > &V, solution sol_repair,
double Dmax, double Tmax, double Vmoy, double Vrecharge, double Dis[][110]){
bool Continue;
double Time=0;// Le temps total sans insertion pour cette tournee
vector<double> D; // Le distence total sans insertion pour cette tournee
vector<solution> Ins; // vector de solution d'insertion

// Obtenez les solutions dont vous avez besoin dans le tableau
// Determiner le position d'insertion  de chaque solution
// Inserer 1 fois
for(int i=a;i<b;i++){
for(int j=0;j<V[sol.Chromosome[i]-1][sol.Chromosome[i+1]-1].size();j++){
V[sol.Chromosome[i]-1][sol.Chromosome[i+1]-1][j].position.push_back(i+1);
Ins.push_back(V[sol.Chromosome[i]-1][sol.Chromosome[i+1]-1][j]);
vector<int>().swap(V[sol.Chromosome[i]-1][sol.Chromosome[i+1]-1][j].position);//Ins[Ins.size()-1].position.emplace_back(i+1);
}
//        for(int j=0;j<V[sol.Chromosome[i]-1][sol.Chromosome[i+1]-1].size();j++){
//            V[sol.Chromosome[i]-1][sol.Chromosome[i+1]-1][j].position.push_back(i+1);
//            Ins.insert(Ins.begin(),V[sol.Chromosome[i]-1][sol.Chromosome[i+1]-1][j]);
//            vector<int>().swap(V[sol.Chromosome[i]-1][sol.Chromosome[i+1]-1][j].position);//Ins[Ins.size()-1].position.emplace_back(i+1);
//        }
}
for(int i=0;i<V[V.size()-1][sol.Chromosome[b]-1].size();i++){
V[V.size()-1][sol.Chromosome[b]-1][i].position.push_back(b+1);
Ins.push_back(V[V.size()-1][sol.Chromosome[b]-1][i]);
vector<int>().swap(V[V.size()-1][sol.Chromosome[b]-1][i].position);
//Ins[Ins.size()-1].position.emplace_back(b+1);

}
//    solution rep;
//    // Inserer 2 fois
//    for(int i=0;i<Ins.size();i++){
//        for(int j=0;j<Ins.size();j++){
//            if(i!=j){
//                rep.Chromosome.push_back(Ins[i].Chromosome[0]);
//                rep.Chromosome.push_back(Ins[j].Chromosome[0]);
//                rep.position.push_back(Ins[i].position[0]);
//                rep.position.push_back(Ins[j].position[0]);
//                rep.distence=Ins[i].distence+Ins[i].distence;
//                rep.time=Ins[i].time+Ins[j].time;
//                rep.Fitness=-rep.distence;
//                Ins.push_back(rep);
//                vector<int>().swap(rep.Chromosome);
//                vector<int>().swap(rep.position);
//
//            }
//        }
//    }
MergeSort(Ins); // Trier la solution en fonction de la fitness de la solution
//Juger de la faisabilité de la solution selon l'ordre
for(int i=0;i<Ins.size();i++){
vector<double>().swap(D);
Continue=CheckEnergy(sol, a, b, Ins[i], Dis, Dmax, Vrecharge, D);
if(Continue){
for(int j=0;j<D.size();j++){
Time=Time+D[i]/Vmoy;
}
if(Time+Ins[i].time<=Tmax){
sol_repair.Chromosome.swap(Ins[i].Chromosome);
sol_repair.position.swap(Ins[i].position);
sol_repair.time=Ins[i].time;
sol_repair.distence= Ins[i].distence;
cout<<"La solution de reparer est "<< sol_repair.Chromosome[0]<<" dans la position "<<sol_repair.position[0]<<endl;
return true;
}
}
}
cout<<"Il n'y a pas de solution de reparer."<<endl;
return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// *  Calculer cout d'insertion
//// * ligne: 0+nombre de client + 0  102
//// * colonne: nombre de client 100
//    vector<vector<vector<solution> > > CoutInsertion;
//    vector<vector<solution> > CI;
//    vector<solution> ci;
//    solution Ins;
//    for(int k=0;k<numClient+1;k++){
//        for (int i = 1; i < numClient+1; i++) {
//            for (int j = 0; j < CDP[k].APR.size(); j++) {
//                Ins.Chromosome.push_back(CDP[k].APR[j]);
//                Ins.distence = Distence[k][CDP[k].APR[j]] + Distence[CDP[k].APR[j]][i] - Distence[k][i];
//                Ins.time = Ins.distence / Vmoy;
//                Ins.Fitness = -Ins.distence;
//                ci.push_back(Ins);
//                vector<int>().swap(Ins.Chromosome);
//            }
//            CI.push_back(ci);
//            vector<solution>().swap(ci);
//        }
//        CoutInsertion.push_back(CI);
//        vector<vector<solution> >().swap(CI);
//    }
//    for (int i = 0; i < numClient+1; i++) {
//        for (int j = 0; j < CDP[i].APR.size(); j++) {
//            Ins.Chromosome.push_back(CDP[i].APR[j]);
//            Ins.distence = Distence[i][CDP[i].APR[j]] + Distence[CDP[i].APR[j]][0] - Distence[i][0];
//            Ins.time = Ins.distence / Vmoy;
//            Ins.Fitness = -Ins.distence;
//            ci.push_back(Ins);
//            vector<int>().swap(Ins.Chromosome);
//        }
//        CI.push_back(ci);
//        vector<solution>().swap(ci);
//    }
//    CoutInsertion.push_back(CI);
////for (int i=0;i<CoutInsertion.size();i++){
////    for(int j=0;j<CoutInsertion[i].size();j++){
////        for(int k=0;k<CoutInsertion[i][j].size();k++){
////            cout<<CoutInsertion[i][j][k].Chromosome[0]<<endl;
////        }
////    }
////}
//
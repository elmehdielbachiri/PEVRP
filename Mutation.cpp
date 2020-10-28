////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

void Mmove(solution &sol,  cdp CDP[]) {
    vector<int> chromosome;
    vector<int>::iterator it;
    int b=rand() % sol.Chromosome.size();

    int client=sol.Chromosome[b];
    // ajuster cette partie
    if (client>0 && CDP[client].NumJourCombinaison >= 1) {
        int num = rand() % (CDP[client].NumJourCombinaison-1);
        if(num >= sol.DayChoose[client]){
            num = num+1;
        }
        for(int i=0;i<sol.Chromosome.size();i++){
            if(sol.Chromosome[i]!=sol.Chromosome[b]){
                chromosome.push_back(sol.Chromosome[i]);
            }
            if(sol.Chromosome[i]<0){
                sol.Pointer[-sol.Chromosome[i]]=chromosome.size()-1;
            }
        }

        for (int i = 0; i < CDP[client].Frequence; i++) {
            int day=CDP[client].JourCombinaison[num][i];
            chromosome.insert(chromosome.begin() + sol.Pointer[day+1], client);
            for (int k = day+1; k <sol.Pointer.size(); k++) {  //移动指针
                sol.Pointer[k]++;
            }
        }
        chromosome.swap(sol.Chromosome);
    }
    if (client<0 || CDP[client].NumJourCombinaison== 1){
        Mmove(sol, CDP);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CheckCombinaison(solution &sol,int a, int b, cdp CDP[]){
    int a_choose=sol.DayChoose[sol.Chromosome[a]];
    int b_choose=sol.DayChoose[sol.Chromosome[b]];
    int i=0;
    while(i<CDP[sol.Chromosome[b]].JourCombinaison.size()){
        for(int j=0;j<CDP[sol.Chromosome[b]].Frequence;j++){
            if(CDP[sol.Chromosome[b]].JourCombinaison[i][j]!=CDP[sol.Chromosome[a]].JourCombinaison[a_choose][j]){
                continue;
            }
            else{
                i++;
                break;
            }
        }
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Echange(solution &s1, int a, int inter, cdp CDP[]) {
    bool Continue;
    while(s1.Chromosome[a]<0){
        a++;
    }
    int b=a+inter;
    while(s1.Chromosome[b]<0){
        b++;
    }
    vector<int> chromosome;
    vector<int> pointer;
    pointer.push_back(-1);
    vector<int>::iterator it;
    int client1=s1.Chromosome[a];
    int client2=s1.Chromosome[b];
    int c=s1.DayChoose[client1];
    int d=s1.DayChoose[client2];

    if(CDP[client1].Frequence == CDP[client2].Frequence) {
        Continue = CheckCombinaison(s1, a, b, CDP);
        if (Continue) {
            Continue = CheckCombinaison(s1, b, a, CDP);
            if (Continue) {
                for (int i = 0; i < s1.Chromosome.size(); i++) {
                    if (s1.Chromosome[i] != client1 && s1.Chromosome[i] != client2) {
                        chromosome.push_back(s1.Chromosome[i]);
                        if (s1.Chromosome[i] < 0) {
                            pointer.push_back(chromosome.size()-1);
                        }
                    }
                    if (s1.Chromosome[i] == client1) {
                        chromosome.push_back(client2);
                        s1.DayChoose[client1]=d;
                    }
                    if (s1.Chromosome[i] == client2) {
                        chromosome.push_back(client1);
                        s1.DayChoose[client1]=c;
                    }
                }
                chromosome.swap(s1.Chromosome);
                pointer.swap(s1.Pointer);
//                    for (it = s1.Chromosome.begin(); it != s1.Chromosome.end(); it++) {
//                        cout << *it << endl;
//                    }
            }
            else {
                b++;
                Echange(s1, a, b, CDP);
            }
        }
        else {
            b++;
            Echange(s1, a, b, CDP);
        }
    }
    else{
        b++;
        Echange(s1, a, b, CDP);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MoveNclients(solution &sol, cdp CDP[], int num, int numClient){
    bool Continue=false;
    vector<int> chromosome;
    vector<int> pointer;
    pointer.push_back(-1);


    std::vector<int> RandOrder;
    for (int i=0; i<numClient; ++i) RandOrder.push_back(i);
    auto rng = std::default_random_engine {};

    for(int i=0;i<sol.Chromosome.size();i++) {
        for (int j = 0; j < num; j++) {
            if (RandOrder[j]+1 == sol.Chromosome[i]) {
                Continue = false;
                break;
            }
            else{
                Continue = true;
            }
        };
        if (Continue) {
            chromosome.push_back(sol.Chromosome[i]);
            if (sol.Chromosome[i] < 0) {
                pointer.push_back(chromosome.size()-1);
            }
        }
    }
    for(int i=0;i<num;i++){
        int n=rand() % CDP[RandOrder[i]+1].NumJourCombinaison;
        sol.DayChoose[RandOrder[i]+1]=n;
        for(int h=0;h<CDP[RandOrder[i]+1].Frequence;h++) {
            int day=CDP[RandOrder[i]+1].JourCombinaison[n][h];
            chromosome.insert(chromosome.begin() + pointer[day+1], CDP[RandOrder[i] + 1].Name);
            for (int k = day+1; k <= pointer.size(); k++) {  //移动指针
                pointer[k]++;
            }
        }
    }
    chromosome.swap(sol.Chromosome);
    pointer.swap(sol.Pointer);
}


int destroy(solution &sol, int num_destroy,int num_Client,int tab[]) {
    std::vector<int> Removed;
    for (int i = 0; i < num_Client; ++i) Removed.push_back(0);
    for (int j = 0; j < num_destroy; j++) {
        bool possible = false;
        while (not(possible)) {
            int n = rand() % num_Client;
            if (Removed[n] == 0) {
                possible = true;
                tab[j] = n;
                Removed[n] = 1;
            }
        }
        //cout<<tab[j]<<endl;

    }
    return 0;
}

bool evaluer_capacite_combinaison(solution &s1,cdp CDP[],int client, int num_combinaison, double Qmax) {
    solution sol=s1;
    for(int j=0;j<CDP[client].Frequence;j++){// Ajout du client manquant
        sol.Chromosome.insert(sol.Chromosome.begin()+sol.Pointer[CDP[client].JourCombinaison[num_combinaison][j]+1],client );
        for(int k=CDP[client].JourCombinaison[num_combinaison][j]+1;k<sol.Pointer.size();k++){
            sol.Pointer[k]++;
        }
    }
    for(int i=0;i<sol.Pointer.size()-1;i++){
        vector<int> Q;
        Q.push_back(0);// Copie du chromosome par journée
        for(int j=sol.Pointer[i]+2;j<=sol.Pointer[i+1];j++) {
            Q.push_back(sol.Chromosome[j]);
        }
        int load=0;
        for(int k=1;k<Q.size();k++) {
            load = load + CDP[Q[k]].Demande;
        }
        if (load>Qmax) {return false;};

    }
    return true;
}

bool evaluer_temps_soltuion(solution &sol,cdp CDP[],int client, int num_combinaison, double Tmax,double Dis[][500],double Vmoy) {
    for(int i=0;i<sol.Pointer.size()-1;i++){
        vector<int> Q;
        Q.push_back(0);// Copie du chromosome par journée
        for(int j=sol.Pointer[i]+2;j<=sol.Pointer[i+1];j++) {
            Q.push_back(sol.Chromosome[j]);
        }
        for(int i=1;i<Q.size();i++){
        int cost=0;
        int time=0;
        int j=i;
        while(j<Q.size()){
            if(i==j){// client directement lié au dépot
                cost=Dis[0][Q[j]-1]+Dis[Q[j]-1][0];
                time=cost/Vmoy+CDP[Q[j]].ServiceTime+CDP[0].ServiceTime;
            }
            else{
                cost=cost-Dis[Q[j-1]-1][0]+Dis[Q[j-1]-1][Q[j]-1]+Dis[Q[j]-1][0];
                time=cost/Vmoy+CDP[Q[j]].ServiceTime;
            }
            j++;
        }}
        if (99>Tmax) {return false;};

    }
    return true;
}

int best_solution(int jour,solution sol, int debut, int fin, int client, cdp CDP [], int num_combinaison,double Dis[][500]) {
    int min = 20000;
    int best = debut+1;
    for (int a = debut + 1; a < fin - 1; a++) {
        if (sol.Chromosome[a] > 0 and sol.Chromosome[a + 1] > 0) {
            double cout1 = Dis[client][sol.Chromosome[a]] + Dis[client][sol.Chromosome[a + 1]] -
                        Dis[sol.Chromosome[a + 1]][sol.Chromosome[a]];
            //cout<<"min "<<min<<endl;
            if (cout1 <= min) {
                best = a;
                min = cout1;
                //cout<<min<<endl;

            };
        }
    }
    return best;
}


    void repair_LNS(solution &sol1, cdp CDP[], int num_destroy, int numClient, vector<int> Destroyed, double Qmax,
                    double Tmax, double Dmax, double Vmoy, double Vrecharge, double CoutRecharge, double Dis[][500], double alpha, double beta) {
        for (int i = 0; i < num_destroy; i++) {// parcours de chaque client détruit
            int client = Destroyed[i];
            int best_fitness = 100000;
            solution best_sol;
            for (int choice = 0;
                 choice < CDP[client].NumJourCombinaison; choice++) {// parcours chacune de ses combinaisons
                solution sol = sol1;
                int check_capa = evaluer_capacite_combinaison(sol, CDP, client, choice,
                                                              Qmax);// vérifier la capacité de la combinaison choisie
                //cout<<"client "<<client<<"combi "<<CDP[client].NumJourCombinaison<<"capa "<<check_capa<<endl;
                //cout<<CDP[client].NumJourCombinaison<<endl;
                if (check_capa) {
                    std::vector<int> Order;
                    for (int i = 0; i < CDP[client].JourCombinaison[choice].size(); ++i) Order.push_back(0);
                    for (int k = 0; k < CDP[client].JourCombinaison[choice].size(); k++) {
                        int best_indice = best_solution(0, sol,0,sol.Chromosome.size(), client,
                                                        CDP, choice, Dis);
                        Order[k] = best_indice;
                        //cout<<"indice "<<best_indice<<" client "<<client<<"combi "<<choice<<endl;
                    }
                    for (int a = 0; a < CDP[client].JourCombinaison[choice].size(); a++) {
                        sol.Chromosome.insert(
                                sol.Chromosome.begin() + sol.Pointer[CDP[client].JourCombinaison[choice][a] + 1] -
                                Order[a], client);
                        for (int k = CDP[client].JourCombinaison[choice][a] + 1; k < sol.Pointer.size(); k++) {
                            sol.Pointer[k]++;
                        }
                    }
                    for (int p = 0; p < sol.Chromosome.size() - 1; p++) {
                        cout << sol.Chromosome[p] << endl;
                        //SplitOption1(sol, sol.Pointer[p], sol.Pointer[p + 1], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge,
                        //Dis);
                        //sol.Fitness = sol.Fitness + alpha * sol.CoutVehicle[p] + beta * sol.CoutRecharge[p];
                    }
                    //if (sol.Fitness<best_fitness){best_fitness=sol.Fitness; best_sol=sol;}
                }
            }
            sol1 = best_sol;
        }
    }


void LNS(solution &sol, cdp CDP[], int num_destroy, int numClient){
    std::vector<int> Removed;
    for (int i = 0; i < numClient; ++i) Removed.push_back(0);
    std::vector<int> Destroyed;
    for (int i = 0; i < num_destroy; ++i) Destroyed.push_back(0);
    for (int j = 0; j < num_destroy; j++) {
        bool possible = false;
        while (not(possible)) {
            int n = rand() % numClient;
            if (Removed[n] == 0) {
                possible = true;
                Destroyed[j] = n;
                Removed[n] = 1;
            }
        }

    }
    //repair_LNS(sol,CDP,num_destroy,numClient,Destroyed,3);
}

void remove_client(solution &sol, int client, cdp CDP[]){
}

bool verifier_capa(solution sol,cdp CDP[],double Qmax){
    for(int i=0;i<sol.Pointer.size()-1;i++){
        vector<int> Q;
        Q.push_back(0);// Copie du chromosome par journée
        for(int j=sol.Pointer[i]+1;j<sol.Pointer[i+1]-1;j++) {
            Q.push_back(sol.Chromosome[j]);
        }
        int load=0;
        for(int k=1;k<Q.size();k++) {
            load = load + CDP[Q[k]].Demande;
        }
        if (load>Qmax) {return false;};
    }
    return true;
}


void repair2_LNS(solution &sol1, cdp CDP[], int num_destroy, int numClient, vector<int> Destroyed, double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge, double CoutRecharge,double Dis[][500], double alpha, double beta) {
    //Créer toutes les solutions possibles puis vérifier qu'elles sont réalisables
    for (int i = 0; i < num_destroy; i++) {// parcours de chaque client détruit
        int client = Destroyed[i];
        solution current_sol = sol1;
        int best_fit = 1000000;// parcours chacune de ses combinaisons
        //cout<<"Choix: "<<choice<<endl;
        std::vector<int> Order;
        solution sol;
        sol.Chromosome = sol1.Chromosome;
        sol.Pointer = sol1.Pointer;
        //sol=sol1;
        //cout<<"Taille initiale"<<sol.Chromosome.size()<<endl;
        int best_indice = best_solution(0, sol,
                                        sol.Pointer[0],
                                        sol.Pointer[1] - 1, client, CDP,
                                        0, Dis);
        //cout<<"Jour: "<<CDP[client].JourCombinaison[choice][k]<<" Meilleur indice: "<<best_indice<<endl;


        //cout<<"Insertion"<<endl;
        sol.Chromosome.insert(
                sol.Chromosome.begin() + best_indice,
                client);
        //cout<<"Insertion terminée"<<endl;
        sol.Pointer[1]++;
        sol1=sol;
    }
    solution sol=sol1;
            //sol.Fitness=0;
            // for (int j = 0; j < sol.Chromosome.size(); ++j) {
            //cout<<sol.Chromosome[j]<<endl;
            //}
            sol.Fitness=0;
            EvaluerOption4(sol, CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Dis, alpha, beta);
            //cout <<"Score de:"<<sol.Fitness<<endl;



}

void LNS2(solution &sol, cdp CDP[], int num_destroy, int numClient, double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge
        , double CoutRecharge,double Dis[][500], double alpha, double beta){
    std::vector<int> Removed;
    Removed.clear();
    for (int i = 0; i < numClient; ++i) Removed.push_back(0);
    std::vector<int> Destroyed;
    Destroyed.clear();
    for (int i = 0; i < num_destroy; ++i) Destroyed.push_back(0);
    for (int j = 0; j < num_destroy; j++) {
        bool possible = false;
        while (not(possible)) {
            int n = (rand() % numClient) + 1;
            if (Removed[n - 1] == 0) {
                possible = true;
                Destroyed[j] = n;
                Removed[n - 1] = 1;
                //cout<<"Client retiré "<<n<<endl;
            }
        }
    }
    for (int j = 0; j < num_destroy; j++){
        for (int i = 0; i < sol.Chromosome.size(); i++){
            if (sol.Chromosome[i]==Destroyed[j]){
                sol.Chromosome.erase (sol.Chromosome.begin()+i);
                for(int k=1;k<sol.Pointer.size();k++){
                    if (i<=sol.Pointer[k]){
                        sol.Pointer[k]--;
                    }
                }
            }
        }
    }
    solution to_repair;
    to_repair.Chromosome=sol.Chromosome;// Conservation du chromosome et des pointeurs de la solution détruite
    to_repair.Pointer=sol.Pointer;
    to_repair.R=sol.R;
    to_repair.S=sol.S;
//    to_repair.Fitness=0;
//    to_repair.InOut=sol.InOut;
//    to_repair.cout1=sol.cout1;
//    to_repair.cout2=sol.cout2;
//    to_repair.cout3=sol.cout3;
//    to_repair.Time=sol.Time;
    //cout<<to_repair.Chromosome.size()<<"  SIZE BEFORE REPAIR"<<endl;
    //cout<< CDP[Destroyed[0]].Frequence+CDP[Destroyed[1]].Frequence+CDP[Destroyed[2]].Frequence <<endl;
    //cout<< Destroyed[0]<< "    "<< Destroyed[1] <<"     "<< Destroyed[2] <<endl;
    repair2_LNS(to_repair, CDP, num_destroy, numClient, Destroyed, Qmax,Tmax,Dmax, Vmoy,Vrecharge,CoutRecharge,Dis,alpha,beta);
    //cout<<to_repair.Chromosome.size()<<"    SIZE AFTER REPAIR"<<endl;
    //cout<<"Réparation effectuée"<<endl;
    //for (int i = 0; i < to_repair.Chromosome.size(); i++){
    //cout<<to_repair.Chromosome[i]<<endl;
    //
    // }
    sol=to_repair;
    //to_repair.Fitness=0;
}

void boucle_LNS2(solution &sol, cdp CDP[], int num_destroy, int numClient, double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
                 double CoutRecharge,double Dis[][500], double alpha, double beta){
    solution initiale=sol;
    solution best;
    solution vide;
    for (int i = 0; i < 30; ++i) {
        //cout<<sol.Chromosome.size()<<endl;
        //cout<<"iteration: "<<i<<endl;
        solution initiale=sol;
        //cout<<"Taille avant destruction "<<sol.Chromosome.size()<<endl;
        //cout<<"Score avant destruc*tion "<<sol.Fitness<<endl;
        sol.Fitness=0;
        LNS2(sol, CDP, num_destroy, numClient, Qmax,Tmax,Dmax, Vmoy,Vrecharge,CoutRecharge,Dis,alpha,beta);
        //cout<<sol.Fitness<<endl;
        if (initiale.Fitness>sol.Fitness){
            //cout<<"PAS de MAJ";
            best.Chromosome=sol.Chromosome;
            best.Fitness=sol.Fitness;
            best.Pointer=sol.Pointer;
            best.R=sol.R;
            best.S=sol.S;
            best.InOut=sol.InOut;
            best=sol;
        }
    }
    vide.Chromosome=best.Chromosome;
    vide.Pointer=best.Pointer;
    vide.Fitness=best.Fitness;
    vide.R=best.R;
    vide.S=best.S;
    sol=vide;
    // cout<<"apres LNS "<<sol.Fitness<<endl;

}



//bool repair3_LNS(solution &sol, cdp CDP[],int a,int b, int num_destroy, int numClient, vector<int> Destroyed, double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
                 //double CoutRecharge,double Dis[][500], double alpha, double beta) {
    // Pour chaque client créer toutes les combinaisons possibles avec la meilleure position d'insertion

void improved_LNS2(solution &sol, cdp CDP[], int num_destroy, int numClient, double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
                 double CoutRecharge,double Dis[][500], double alpha, double beta, int num_iteration){
    solution initiale=sol;
    for (int i = 0; i < num_iteration; ++i) {
        solution initiale=sol;
        //LNS2_improved(sol, CDP, num_destroy, numClient, Qmax,Tmax,Dmax, Vmoy,Vrecharge,CoutRecharge,Dis,alpha,beta);
        //cout<<sol.Fitness<<endl;
        if (sol.Fitness>initiale.Fitness){
            //cout<<"PAS de MAJ"
            sol=initiale;
        }

    }
}


void LNS2opt(solution &sol, cdp CDP[], int num_destroy, int numClient, double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
          double CoutRecharge,double Dis[][500], double alpha, double beta) {
    solution best;
    best=sol;
    for (int k = 0; k < 10; ++k) {
        solution copie;
        //cout<<"Iteration "<<k<<endl;
        copie.Chromosome=sol.Chromosome;
        copie.Pointer=sol.Pointer;
        //cout<<"Avant "<<sol.Fitness<<endl;
        for (int i = 0; i < sol.Pointer.size()-1; ++i) {// we apply a 2-opt to each day
            if ((sol.Pointer[i + 1] - sol.Pointer[i]) > 1) {
                int a = rand() % (sol.Pointer[i + 1] - sol.Pointer[i] - 1);
                int b = rand() % (sol.Pointer[i + 1] - sol.Pointer[i] - 1);
                int p = sol.Pointer[i];
                if (a > b) {
                    int r = a;
                    a = b;
                    b = r;
                } //a<b -we exchange a and b
                for (int j = a; j < b + 1; ++j) {//Inversion sur la portion [a-b]
                    copie.Chromosome[j + p + 1] = sol.Chromosome[a + b - j + p + 1];
                }
            }
        }
        copie.Fitness=0;
        EvaluerOption4(copie, CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Dis, alpha, beta);
        //cout<<"Après "<<copie.Fitness<<endl;
        //copie.Chromosome.clear();
        //copie.Pointer.clear();
        if (copie.Fitness<best.Fitness){best=copie;
        //cout<<"MAJ"<<endl;
        }
        }
    sol=best;
    //cout<<"Best Fitness "<<sol.Fitness<<endl;
}

void two_opt(solution &sol, cdp CDP[], int num_destroy, int numClient, double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
             double CoutRecharge,double Dis[][500], double alpha, double beta) {

}

void deux_opt_inversion(solution &sol, cdp CDP[], int debut, int fin, double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
              double CoutRecharge,double Dis[][500], double alpha, double beta) {
    solution copie;
    solution best=sol;
    //cout<<"Fitness sol initiale "<<sol.Fitness<<endl;
    for (int i = debut; i < fin; ++i) {
        for (int k = i+ 1; k < fin; ++k) {
            solution copie;
            copie.Chromosome = best.Chromosome;
            copie.Pointer = best.Pointer;
            //cout<<"INversion"<<endl;
            for (int j = i; j < k + 1; ++j) {
                //cout<<"B"<<endl;
                //cout<<copie.Chromosome[j]<<endl;
                copie.Chromosome[j] = sol.Chromosome[i + k - j];
                //cout<<copie.Chromosome[j]<<endl;
            }
            copie.Fitness=0;
            EvaluerOption4(copie, CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Dis, alpha, beta);
            //cout<<copie.Fitness<<endl;
            if (copie.Fitness<best.Fitness){best=copie;}
        }
    }
    sol=best;
    //cout<<"Fitness sol finale "<<sol.Fitness<<endl;
}
int recherche_position_client(int client, int i,solution sol){
    for (int j = sol.Pointer[i]+1; j < sol.Pointer[i+1]; ++j){
        if (sol.Chromosome[j]==client){return j;}
    }
}

void deux_opt(solution &sol, cdp CDP[], double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
                        double CoutRecharge,double Dis[][500], double alpha, double beta) {
    cout<<sol.Fitness<<endl;
    for (int i = 0; i <sol.Pointer.size()-1 ; ++i) {
        int k=sol.R[i].size()-1;
        //for (int j = sol.Pointer[i]+1; j < sol.Pointer[i+1]; ++j) {//Mélange par journée
            while (k!=0) {
                //cout<<k<<endl;
                int client1=sol.R[i][k][0];
                int client2=sol.R[i][k][1];
                int debut=recherche_position_client(client1,i,sol);
                int fin =recherche_position_client(client2,i,sol)-1;
//                cout<<"CLient1 "<<client1<<endl;
//                cout<<"Position1 "<<debut<<endl;
//                cout<<"CLient2 "<<client2<<endl;
//                cout<<"Position2 "<<fin<<endl;
                if (debut!=fin and client2<120 and client1!=0){
                deux_opt_inversion(sol,  CDP, debut,  fin,  Qmax,  Tmax,  Dmax,  Vmoy,  Vrecharge, CoutRecharge,Dis, alpha,  beta);
                }
                k= (sol.R[i].size()-1<k-1)?sol.R[i].size()-1:k-1;
                //cout<<sol.Fitness<<endl;
            }
            cout<<sol.Fitness<<endl;
        //}
    }
}



int roulette_russe1(vector<double> weight){
    double sum=std::accumulate(weight.begin(),weight.end(),0);
    std::vector<double > proba;
    for (int i = 0; i < weight.size(); ++i) {proba.push_back(weight[i]/sum);}
    double p = (rand() % 101) / 100.0;
    //cout<<"Proba à atteindre "<<p<<endl;
    double current=0;
    int i=0;
    while (i<weight.size()){
        current=proba[i]+current;
        if (p<current){return i;}
        i++;
    }
}

void weight_adjustment1(vector<double> &weight,int choix,vector <solution> pop,solution sol,double poids){
    if (poids<pop[0].Fitness){weight[choix]+=1;}
}

/*void adaptive_LNS_mutations(solution sol,cdp CDP[], vector <solution> &pop, int numClient, double P_mutation,int numRechoose,double P_choose,double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
                            double CoutRecharge,double Dis[][500], double alpha, double beta ){
    std::vector<double> weight;
    for (int i = 0; i < 4; ++i) weight.push_back(1);
    for (int j = 0; j <14 ; ++j) {
        int choix = roulette_russe1(weight);
        cout<<"Choix "<<choix<<endl;
        if (choix == 0) {Mmove(sol, CDP);}
        else if (choix == 1) {MoveNclients(sol, CDP, numRechoose, numClient);}
        else if (choix == 2) {double p = (rand() % 101) / 100.0;
            //cout <<"La probabilite de mutation est " <<p << endl;
            if (p < P_mutation) {
                double p_choose = (rand() % 101) / 100.0;
                if (p_choose >= P_choose) {
                    Mmove(sol, CDP);
                }
                else {
                    MoveNclients(sol, CDP, numRechoose, int(numClient));
                }
            }
        }
        else if (choix == 3) {boucle_LNS2(sol, CDP, 1, numClient, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge,
                                          Dis, alpha, beta);
        }
        double poids = sol.Fitness;
        weight_adjustment1(weight, choix, pop, sol, poids);
    }
    for (int k = 0; k <weight.size() ; ++k) {
        cout<<"Poids "<<weight[k]<<endl;
    }
}*/


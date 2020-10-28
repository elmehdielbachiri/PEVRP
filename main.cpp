#include "PEVRP.h"
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char *argv[]) {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////    Read data and calcul matrix    /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    string instants[] = {"/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-10-N100.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-11-N100.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-12-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-13-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-14-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-15-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-16-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-17-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-18-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-19-N100.txt" ,
//                         "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-10-N100.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-11-N100.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-12-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-13-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-14-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-15-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-16-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-17-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-18-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-19-N100.txt" ,
//                         "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-10-N100.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-11-N100.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-12-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-13-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-14-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-15-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-16-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-17-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-18-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-19-N100.txt" ,
//                         "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-10-N200.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-11-N200.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-12-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-13-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-14-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-15-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-16-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-17-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-18-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-2J/TEST-19-N200.txt" ,
//                         "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-10-N200.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-11-N200.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-12-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-13-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-14-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-15-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-16-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-17-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-18-N200.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-3J/TEST-19-N200.txt" ,
//
//    };
       //string instants[] = {"/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-10-N100.txt"};
//for (int in=1;in<=2;in++){
//for (int kin=1;kin<=5;kin++){
 for (int itern=1;itern<=10;itern++){
     string instants[] = {
             "/Users/mac/Desktop/RESULTS litterature/VA Files/Instances/Large VA Input_300c_21sprocessed.txt"
    };

     //cout<<"instance"<<in<<"run"<<itern<<endl;


    //string instants[]={"/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-10-N100.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-11-N100.txt","/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-12-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-13-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-14-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-15-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-16-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-17-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-18-N100.txt" , "/Users/principal/Desktop/Donnees/PEVRP100/TXT-5J/TEST-19-N100.txt" };
//
    string crossover[] = {"CELOX", "crossover_insertion_optimale", "crossover_combinaisonP2",
                          "croisement_insertion_aléatoire", "crossover_aleatoire", "crossover_adaptative"};
    string mutations[] = {"Mmove", "MoveNClients", "Mélange aléatoire", "LNS(1)", "LNS(3)", "LNS(5)", "LNS(7)",
                          "LNS-2opt"};
//
//    for (int l = 0; l < sizeof(crossover) / sizeof(crossover[0]); ++l) {
//        for (int n = 0; n < sizeof(mutations) / sizeof(mutations[0]); ++n) {
    //ofstream myfile;
    //myfile.open ("/Users/principal/Desktop/Donnees/Test.txt");
    //Nombre de clients retiré dans LNS
ofstream myfile;
    myfile.open ("/Users/mac/Desktop/RESULTS litterature/VA Files/Resultats/Large VA Input_300c_21sprocessed"+to_string(itern)+".txt");
     //myfile<<"Instance "<<in<<"\n";
     //myfile<<"run "<<itern<<"\n";
       //Nombre de clients retiré dans LNS
     //for (int n = 0; n < 3; n++) {
       for (int y = 0; y < 1; y++) {
            //myfile<<"Instance "<<y<<"\n";
            //cout<<"Instance "<<y<<endl;
        const string instant = instants[y];
        const string doc_client = "\\Users\\principal\\Desktop\\Donneess\\doc\\doc_client.txt";//Choisir aleatoirment
        const string doc_parameter = "\\Users\\principal\\Desktop\\Donnees\\doc\\doc_parameter.txt";
        const string doc_pointrecharge = "\\Users\\principal\\Desktop\\Donnees\\doc\\doc_pointrecharge.txt";
        fstream file(doc_pointrecharge, ios::out | ios::trunc);
        fstream(doc_client, ios::out | ios::trunc);
        fstream(doc_parameter, ios::out | ios::trunc);
        //Process(instant, doc_parameter, 3, 3, 11, 11);
        int numParameter = 1;
        double Parameter[1][11];
        //ReadParameter(doc_parameter, Parameter, 1, numParameter);
        double numClient = 300; //Nombre de clients
        double numVehicle = 3; //    Nombre de véhicules
        double numPointRecharge = 22; //    Nombre de points de recharge (depot compris)
        double Vrecharge = 0.25; //    Temps nécessaire pour recharger de 0 à 100%
        double numPeriod = 1; //Nombre de périodes
        //try 296
        double Dmax = 300; //Distance possible avec 100% d'énergie dans le véhicule
        double Vmoy = 40.00000000001;
        double Tmax = 11; //Temps maximum pour une tournée heure
        double Qmax = 4000000;  //Capacité de transport maximale du VE k,
        double CoutRecharge = 0; //Coût fixé de recharge dans une station de recharge externe
        double CoutVehicle = 1; //Coût fixé d’un véhicule électrique chaque jour
        Process(instant, doc_client, 3+int(numPointRecharge), 3+int(numPointRecharge)+ int(numClient)-1 , 4, 4);
        Process(instant, doc_pointrecharge, 2,
                 2+ int(numPointRecharge),
                4,
                4);
        //Definition du client
            std::string type;
            double id[int(numPointRecharge)+int(numClient)+1];
            double latitude[int(numPointRecharge)+int(numClient)+1];
            double longitude[int(numPointRecharge)+int(numClient)+1];
            ifstream file_(doc_client);
            int i=0;
            if (file_.is_open()){
                while( file_ >> id[i] >> type >> longitude[i] >> latitude[i])
                {
                    //cout<< longitude[i] <<endl;
                    //cout<< latitude[i] <<endl;
                    i++;
                }
                file_.close();
            }
            //i-1 nbre de clients faisables
            ifstream file1_(doc_pointrecharge);
            numClient=i;
            int j=i;
            if (file1_.is_open()){
                while( file1_ >> id[j] >> type >> longitude[j] >> latitude[j])
                {
                    //cout<< longitude[j] <<endl;
                    //cout<< latitude[j] <<endl;
                    j++;
                }
                file1_.close();
            }
        //Construction de l'objet Client

        vector<int> Jour;
        cdp CDP[int(numClient + numPointRecharge) + 1];
        CDP[0].Name = 0;
        CDP[0].longitude = longitude[int(numClient)];
        CDP[0].latitude = latitude[int(numClient)];
        CDP[0].ServiceTime = 0.25;
        for (int i = 1; i <= numClient; i++) {
           //CDP[i].Name = id[i-1]+1;
            CDP[i].Name = i;
            CDP[i].longitude =longitude[i-1];
            CDP[i].latitude = latitude[i-1];
            CDP[i].Demande = 10;
            CDP[i].ServiceTime = 0.5;
            CDP[i].Frequence = 1;
            Jour.push_back(1);
            CDP[i].JourCombinaison.push_back(Jour);
            vector<int>().swap(Jour);//清除vector内存
            CDP[i].NumJourCombinaison = CDP[i].JourCombinaison.size();
        }
        vector<int> PRDisponible;
        double R = 10000; // Rayon de cherche les points de recharges,开始可以用100
        for (int i = int(numClient) + 1; i <= numClient + numPointRecharge; i++) {
            /*if (id[i-1]==0){
                CDP[i].Name =numClient+2;
            }
            else{
                CDP[i].Name = id[i-1]+1;
            }*/
            CDP[i].Name=i;
            CDP[i].longitude = longitude[i];
            CDP[i].latitude =latitude[i];
            CDP[i].ServiceTime = 0.25;
            PRDisponible.push_back(CDP[i].Name);
        }
        for (int i = 1; i <= numClient; i++) {
            FindPointRecharge(R, PRDisponible, Dmax, CDP[i], CDP, CDP[i].APR, numClient);
            //////cout<<CDP[i].APR.size()<<endl;
        }
        //// * Definition de la matrice de distance entre les clients et PRs
        //// * ligne: nombre de client + nombre de PRs + depot 100+9+1
        //// * colonne: nombre de client + nombre de PRs + depot  100+9+1
        int m = int(numClient) + int(numPointRecharge) + 1;
       double Distence[500][500] = {0};
        for (int i = 0; i < int(numClient) + int(numPointRecharge) + 1; i++) {
            for (int j = 0; j < int(numClient) + int(numPointRecharge) + 1; j++) {
                Distence[i][j] = GetDistence(CDP[i], CDP[j]);
            }
        }
            vector<int> clientsinfaisables;
            bool Faisable;
            //Procedure de traitement de clients:
            for (int i=1;i<int(numClient)+1;i++){
                Faisable=false;
                if (Distence[0][i]+Distence[i][0]<=Dmax){
                    if ((Distence[0][i]+Distence[i][0])/Vmoy + CDP[i].ServiceTime<=Tmax){
                        Faisable=true;
                    }
                }
                else{
                    for (int j=int(numClient)+1;j< int(numClient) + int(numPointRecharge) + 1;j++) {
                        if (Distence[0][j] < Dmax && Distence[j][i] + Distence[i][0] <= Dmax ||
                            Distence[0][i] + Distence[i][j] < Dmax && Distence[j][0] <= Dmax) {
                            if ((Distence[0][j] + Distence[j][i] + Distence[i][0]) / Vmoy + CDP[i].ServiceTime +
                                CDP[j].ServiceTime <= Tmax) {
                                Faisable = true;
                            }
                            else{
                                for (int k=int(numClient)+1;k< int(numClient) + int(numPointRecharge) + 1;k++){
                                    if (Distence[0][j] <= Dmax && Distence[j][i] + Distence[i][k] < Dmax && Distence[k][0]<=Dmax){
                                        if ((Distence[0][j] + Distence[j][i] + Distence[i][k]+Distence[k][0]) / Vmoy + CDP[i].ServiceTime +
                                            CDP[j].ServiceTime+CDP[k].ServiceTime<= Tmax) {
                                            Faisable = true;
                                        }
                                    }
                                }
                            }
                        }
                    }}
                if (not Faisable){
                    clientsinfaisables.push_back(i);
                }
            }

            ////cout<< "Procédure de lecture terminée " << endl;
        srand((unsigned int) time(NULL));
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////       Parameters a régler      ///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        for (int r = 0; r < 1; r++) {
            //myfile<<"Mutation "<<mutations[l]<<"\n";
            //////cout<<"Mutation "<<mutations[l]<<endl;
            int Iteration = 100000; //Nombre d'itérations, [1000, 50000, 5000, 10000]
            int MaxPopulation = 60; //Taille de la population initiale, [500, 40, 50]
            int numSelection = 5;//Nombre de selection, [2, MaxPopulation/2]
            int numEnfant = numSelection - 1; //
            double P_mutation = 0.2; //Probabilité de mutation []
            double P_choose = 1; //Probabilité de choisir la methode de mutation
            int numRechoose = 10;
            int inter = 500;
            double Alpha = 1;//coefficient de cout1
            double Beta = 1;//coefficient de cout2
            vector<int>::iterator it;
            vector<solution> Pop;//Population initiale
            vector<solution> Pop_initialisation;//Population initiale
            vector<solution> TabSelect;//Individus sélectionnés
            solution enfant;
            vector<solution> Enfant;
            //////////////////////////////////////////     Test Algorithme Génétique      ////////////////////////////////////////////
            const clock_t begin_time = clock();
         /*   Generate_Population(int(numClient), int(numPeriod), int(numPointRecharge), CDP, 60, Pop_initialisation);
            ////cout<< "Evaluation de la population initiale: " << endl;

            for (int i = 0; i <60; i++) {
                EvaluerOption4(Pop_initialisation[i], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Distence,
                               Alpha,
                               Beta);
            }

            //ALNS classique:
            string crossover[] = {"CELOX", "crossover_insertion_optimale", "crossover_combinaisonP2",
                                  "croisement_insertion_aléatoire"};
            string mutations[] = {"Mmove", "MoveNClients", "Mélange aléatoire",  "LNS(3)"};
            //Phase d'évaluation: on prend 5 individus et on applique croisement§mutations et on voit lesquels ont les meilleures scores
            std::vector<double> weight_crossover;
            for (int i = 0; i < sizeof(crossover) / sizeof(crossover[0]); ++i) { weight_crossover.push_back(1); }
            std::vector<double> weight_mutation;
            for (int i = 0; i < sizeof(mutations) / sizeof(mutations[0]); ++i) { weight_mutation.push_back(1); }
            for (int n = 0; n < Pop_initialisation.size() - 1; ++n) {
                int best_croisement;
                int best_mutation;
                solution sol1 = Pop_initialisation[n];
                solution sol2 = Pop_initialisation[n + 1];
                solution p1 = sol1;
                solution p2 = sol2;
                solution enfant1;
                solution enfant2;
                CELOX_rapide_1jr(p1, p2, enfant1, CDP, numClient);
                enfant1.Fitness = 0;
                EvaluerOption4(enfant1, CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Distence,
                               Alpha,
                               Beta);
                Enfant.push_back(enfant1);
                CELOX_rapide_1jr(p2, p1, enfant2, CDP, numClient);
                enfant2.Fitness = 0;
                EvaluerOption4(enfant2, CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Distence,
                               Alpha,
                               Beta);
                Enfant.push_back(enfant2);
                for (int j = 0; j < Enfant.size(); j++) {
                    double p = (rand() % 101) / 100.0;
                    if (p < P_mutation) {
                        boucle_LNS2(Enfant[j], CDP, 3, numClient, Qmax, Tmax, Dmax, Vmoy, Vrecharge,
                                    CoutRecharge,
                                    Distence, Alpha, Beta);
                        solution BB;
                        BB.Name = Enfant[j].Name;
                        BB.Fitness = 0;
                        BB.Pointer = Enfant[j].Pointer;
                        BB.Chromosome = Enfant[j].Chromosome;
                        BB.Time = Enfant[j].Time;
                        Enfant[j] = BB;
                        // }
                        Enfant[j].Fitness = 0;
                        EvaluerOption4(Enfant[j], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Distence,
                                       Alpha,
                                       Beta);
                        //for (int kp=0;kp<AA.Pointer.size();kp++) {
                        ////cout<< AA.Pointer[kp] << endl;
                        ////cout<< AA.Pointer[kp] << endl;
                        ////cout<< AA.Chromosome[AA.Pointer[kp]] << endl;

                        ////cout<< "Test Mutations fini" << endl;
                        // }
                    }
                    //  }
                    //////cout<<"Mutation "<<mutations[l]<< " Croisement "<<crossover[i]<<" Fitness "<<Enfant[j].Fitness<<endl;

                }

                    //////cout<<"Mutation "<<mutations[l]<< " Croisement "<<crossover[i]<<" Fitness "<<Enfant[j].Fitness<<endl;


            }



            //////cout<<"Evaluation terminée"<<endl;
            vector<int>::iterator it1;
            vector<solution> Pop1;//Population initiale
            vector<solution> TabSelect1;//Individus sélectionnés
            solution enfant1;
            vector<solution> Enfant1;
            Pop=Pop1; TabSelect=TabSelect1; enfant=enfant1;Enfant=Enfant1;
*/
            Generate_Population(int(numClient), int(numPeriod), int(numPointRecharge), CDP, MaxPopulation, Pop);


            ////cout<< "Evaluation de la population initiale: " << endl;
            for (int i = 0; i < MaxPopulation; i++) {
                EvaluerOption4(Pop[i], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Distence, Alpha,
                               Beta);
            }
            MergeSort(Pop);
            //cout<< "Pop initiale " << Pop[0].Fitness << endl;
            double a = Pop[0].Fitness;
            //myfile<<""<<Pop[0].Fitness;
            double best_fit=Pop[0].Fitness;
            ////cout<<"best fit before "<<best_fit<<endl;
            int iter = 0;
            vector<float> clockk;

            for (int i = 0; i < Iteration; i++) {
/*                while (Pop[0].Fitness < 1797.49){
                EvaluerOption4(Pop[0], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Distence, Alpha,
                             Beta);}*/
               if (float(clock() - begin_time) / CLOCKS_PER_SEC <= 22600) {
                vector<solution>().swap(Enfant);
                Selection(numSelection, Pop, TabSelect);
                for (int j = 0; j < numSelection - 1; j++) {
                    //int j=0;
                        solution enfant1;
                        CELOX_rapide_1jr(TabSelect[j], TabSelect[j + 1], enfant1, CDP, numClient);
                        enfant1.Fitness = 0;
                        EvaluerOption4(enfant1, CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Distence,
                                   Alpha,
                                   Beta);
                        Enfant.push_back(enfant1);
                        solution enfant2;
                        CELOX_rapide_1jr(TabSelect[j + 1], TabSelect[j], enfant2, CDP, numClient);
                        enfant2.Fitness = 0;
                        EvaluerOption4(enfant2, CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Distence,
                                   Alpha,
                                   Beta);
                        Enfant.push_back(enfant2);
                }
                //////cout<<"Procédure de croisemment terminée. "<<endl;
                for (int j = 0; j < Enfant.size(); j++) {
                    double p = (rand() % 101) / 100.0;
                   if (p < P_mutation) {
                    boucle_LNS2(Enfant[j], CDP, 3, numClient, Qmax, Tmax, Dmax, Vmoy, Vrecharge,
                                CoutRecharge,
                                Distence, Alpha, Beta);
                    solution BB;
                    BB.Name = Enfant[j].Name;
                    BB.Fitness = 0;
                    BB.Pointer = Enfant[j].Pointer;
                    BB.Chromosome = Enfant[j].Chromosome;
                    BB.Time = Enfant[j].Time;
                    Enfant[j] = BB;
                    // }
                    Enfant[j].Fitness = 0;
                    EvaluerOption4(Enfant[j], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Distence,
                                      Alpha,
                                      Beta);
                    //////cout<<"Fitness enfant après mutation "<<Enfant[j].Fitness<<endl;
                }}
                //////cout<<"Procédure de mutation terminée. "<<endl;

                MergeSort(Enfant);
                Replace(Pop, Enfant);
                MergeSort(Pop);
                        //////cout<<"Remplacement réalisé. "<<endl;
                        ////cout<< "Génération " << i << " " << Pop[0].Fitness << endl;
                        if (best_fit!=Pop[0].Fitness){iter=i;}
                        best_fit=Pop[0].Fitness;
                        if (i%50==0) {//myfile<<";"<<Pop[0].Fitness;
                            ////cout<< "Génération " << i << " " << Pop[0].Fitness << endl;
                           }
                    //cout<< "Génération " << i << " " << Pop[0].Fitness << endl;
                clockk.push_back(clock());

                finalei = i;
            }}
            //myfile << "Temps d'exécution :" << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
            ////cout<< "Meilleur score trouvé:" << Pop[0].Fitness << endl;
            ////cout<< "Meilleur iter trouvé:" << iter << endl;
            myfile << "Meilleur score trouvé : " << Pop[0].Fitness << "\n";
            myfile << "Temps d'exécution : " << float(clock() - begin_time) / CLOCKS_PER_SEC << "\n";
            myfile << "Meilleur Iteration : " << iter<< "\n";
            myfile << "Nombre d'iterations : " <<finalei+1<<"\n";
            myfile << "Temps pour meilleur iteration : " << float(clockk[iter] - begin_time) / CLOCKS_PER_SEC << "\n";
            myfile << "Efficacité : " << (a - Pop[0].Fitness) * 100 / a << "\n";

            int nbrereparation = 0;
            vector<int> Posrecharge;
            vector<int> solrech;
            vector<vector<int>> inOutfinal;
            for (int k = 0; k < Pop[0].S.size(); k++) {
                //myfile << " " << "\n";
                //myfile << "_" << k;
                for (int i = Pop[0].S[k].size()-1; i >= 0; i--) {
                    //myfile << "_" << "La solution de reparer est " << Pop[0].S[k][i].Chromosome[0]
                    //  << " dans la position " << Pop[0].S[k][i].Pointer[0];
                    nbrereparation = nbrereparation + 1;
                    Posrecharge.push_back(Pop[0].S[k][i].Pointer[0]);
                    solrech.push_back(Pop[0].S[k][i].Chromosome[0]);
                    inOutfinal.push_back(Pop[0].S[k][i].InOut);
                }
            }

/*
            for (int k = 0; k < solrech.size(); ++k) {
                myfile << "\n" << endl;
                myfile << "_" << solrech[k]<<endl;
            }
            for (int k = 0; k < Posrecharge.size(); ++k) {
                myfile << "_" << Posrecharge[k]<<endl;
            }*/


            vector<int> solfinal;
            // myfile<<"_"<< "La solution finale s'ecrit"
            for (int k = 0; k < 1; k++) {
                //myfile << " " << "\n";
                //myfile << "Jour " << k + 1;
                for (int i = Pop[0].R[k].size() - 1; i > -1; i--) {
                    solfinal.push_back(0);
                    for (int l = Pop[0].R[k][i][1]+1; l <= Pop[0].R[k][i][0]; l++) {
                        //car Q commence par 1
                        for (int j=0;j<inOutfinal.size();j++){
                            if (inOutfinal[j][0]==Pop[0].Chromosome[Pop[0].R[k][i][1]] && inOutfinal[j][1]==Pop[0].Chromosome[Pop[0].R[k][i][0]-1]){
                                if (Posrecharge[j]==l-1){
                                    solfinal.push_back(solrech[j]);
                                }
                            }
                        }
                        solfinal.push_back(Pop[0].Chromosome[l -1]);

                    }
                    //CAs ou insertion avant de retourner au depot
                    for (int j=0;j<inOutfinal.size();j++){
                        if (inOutfinal[j][0]==Pop[0].Chromosome[Pop[0].R[k][i][1]] && inOutfinal[j][1]==Pop[0].Chromosome[Pop[0].R[k][i][1]-1]){
                            if (Posrecharge[j]==Pop[0].R[k][i][0]){
                                solfinal.push_back(solrech[j]);
                            }
                        }
                    }
                    solfinal.push_back(0);
                }
                solfinal.push_back(-(k + 1));
            }
   /*             for (int k = 1; k < numPeriod; k++) {
                    for (int i = Pop[0].Pointer[k]; i < Pop[0].Pointer[k + 1]; k++) {
                        solfinal[i] = solfinal[i] + Pop[0].Pointer[k];
                    }
                }*/
            //myfile<<0<<"\n";
//            int counter=0;
//            vector<int> solfinal2;
//            for (int i = 0; i < solfinal.size(); i++) {
//                if(solfinal[i]>0 || solfinal[i]<0 ){counter++;}
//                for (int j = 0; j < Posrecharge.size(); j++) {
//                    if (counter == Posrecharge[j]) {
//                        solfinal2.push_back(solrech[j]);
//                    }
//                }
//                solfinal2.push_back(solfinal[i]);
//            }

            //myfile<<"\n"<<"   numvehicule jour 1 "<<Pop[0].R[0].size()<<"\n";
            //myfile<<"   numvehicule jour 2 "<<Pop[0].R[1].size()<<"\n";

            //myfile << "Jour 1" << "\n";

            int nbvehic = 0;
            vector<int> numvehic;

            for (int i = 0; i < solfinal.size(); i++) {
                if (solfinal[i] >= 0) {
                    myfile << " " << id[solfinal[i]];
                }
                if (solfinal[i] == 0 && solfinal[i+1] == 0)
                {
                    myfile << " " << "\n";
                    nbvehic++;
                }
                if (solfinal[i] > numClient) {
                    myfile << " " << 0.99;
                }
                if (solfinal[i] < 0 && i != solfinal.size() - 1) {
                    myfile << " " << "\n";
                    nbvehic = 0;
                    myfile << "Jour " << -solfinal[i] + 1 << "\n";
                }
            }


            bool A;
            int nbreclientsnonservis = 0;
            myfile << "\n" << "Clients non servis: ";
            for (int j = 0; j < Pop[0].Chromosome.size(); j++) {
                A = false;
                int i = 0;
                while (i < solfinal.size()) {
                    if (solfinal[i] == Pop[0].Chromosome[j]) {
                        A = true;
                    }
                    i++;
                }
                if (not A) {
                    myfile << " " << Pop[0].Chromosome[j];
                    nbreclientsnonservis++;
                }
            }
            myfile << nbvehic <<"\n";
            myfile <<  nbreclientsnonservis << "\n";
        }
            myfile.close();
        }}}
//}}
        //}

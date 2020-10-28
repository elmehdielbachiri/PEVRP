////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//返回 false 表示有相同的元素，该基因不能用
//返回 true 表示没有相同的元素，该基因可用
bool SameGene(vector<int> a, int num, int start, int end){
    for(int i=start; i<end+1;i++){
        if(num==a[i]){
            return false;
        }
        else{
            continue;
        }
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LOX(vector<int> &p1,vector<int> &p2,vector<int> &e1,vector<int> &e2,int start,int end) {
//    copy(p2.begin()+start, p2.end()+end+1, e1.begin()+start);//将a中元素全部拷贝到b开始的位置中,注意拷贝的区间为a.begin() ~ a.end()的左闭右开的区间*/
//    copy(p1.begin()+start, p1.end()+end+1, e2.begin()+start);;
    // double pcrossover=0;
    //pcrossover=(rand()%101)/100;
    // if(pcrossover<=p){
    int k=0;
    //对于p1来说
    for(int i=0;i<p1.size();i++) {
        if (SameGene(p1, p2[i], start, end) == true){
            e1.push_back(p2[i]);
        }
        if(SameGene(p2, p1[i], start, end) == true){
            e2.push_back(p1[i]);
        }
    }
    for(int i=start;i<=end;i++){
        e1.insert(e1.begin()+i, p1[i]);
        e2.insert(e2.begin()+i, p2[i]);
    }
    vector<int>::iterator it1;
    for (it1 = e1.begin(); it1 != e1.end(); it1++) {
        cout << *it1 << endl;
    }
    vector<int>::iterator it2;
    for (it2 = e2.begin(); it2 != e2.end(); it2++) {
        cout << *it2 << endl;
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Crossover(vector<int> &p1,vector<int> &p2,vector<int> &e1,vector<int> &e2,int start,int end, double p) {
    double pcrossover=(rand()%101)/100.0;
    if(pcrossover<p){
        LOX(p1,p2,e1,e2,start,end);
    }
    cout<<pcrossover<<endl;
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CheckDay(int a,vector<int> pointer){
    int period=0;
    for(int i=1;i<pointer.size();i++){
        if(a>pointer[i]){
            period= i+1;
            cout<<period<<endl;
            break;
        }
    }
    return period;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//bool ELOX(solution p1,solution p2,solution enf,int start,int end, cdp CDP[]){
//    int periode=0;
//    bool exist;
//    for(int i=0;i<p1.Pointer.size();i++){
//        enf.Pointer.push_back(i);
//        if(i!=0){
//            enf.Chromosome.push_back(-i);
//        }
//    }
//    for(int i=start;i<=end;i++){
//        if(p1.Chromosome[i]>0){
//            periode=CheckDay(i,p1.Pointer);
//            enf.Chromosome.insert(enf.Chromosome.begin()+periode,p1.Chromosome[i]);
//            for(int j=periode;j<enf.Pointer.size();j++){
//                enf.Pointer[j]++;
//            }
//        }
//    }
//    for(int i=0;i<p2.Chromosome.size();i++){
//        int choice=0;
//        exist=SameGene(enf.Chromosome, p2.Chromosome[i], start, end);
//        if(exist || CDP[p2.Chromosome[i]].NumJourCombinaison==1 ){
//            choice=CDP[p2.Chromosome[i]].CombinaisonChoose[p2.Name];
//            for(int j=0;j<CDP[p2.Chromosome[i]].Frequence;j++){
//                enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][i]],p2.Chromosome[i] );
//                for(int k=enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][i]];k<enf.Pointer.size();k++){
//                    enf.Pointer[k]++;
//                }
//            }
//        }
//        if(!exist && p2.Chromosome[i]>0){
//            choice=rand()%CDP[p2.Chromosome[i]].NumJourCombinaison-1;
//            if(choice>=CDP[p2.Chromosome[i]].CombinaisonChoose){
//                choice++;
//            }
//
//        }
//    }
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CELOX(solution &p1,solution &p2,solution &enf, cdp CDP[]){
    int start = rand() % p1.Chromosome.size();
    int end= rand() % p1.Chromosome.size();
    while(p1.Chromosome[start]<0){
        start++;
    }
    while(p1.Chromosome[end]<0){
        end++;
    }
    int n=0;
    if(start>end){
        n=start;
        start=end;
        end=n;
    }

    bool exist;
    int choice;
    vector<int>().swap(enf.Chromosome);
    vector<int>().swap(enf.Pointer);
    vector<int>::iterator it;

    for(int i=0;i<p1.Pointer.size();i++){
        enf.Pointer.push_back(i-1);
        if(i!=0){
            enf.Chromosome.push_back(-i);
        }

    }

    for(int i=end-1;i>=start;i--){
        if(p1.Chromosome[i]>0){
            enf.DayChoose[p1.Chromosome[i]]=p1.DayChoose[p1.Chromosome[i]];
            choice=p1.DayChoose[p1.Chromosome[i]];
            for(int j=0;j<CDP[p1.Chromosome[i]].Frequence;j++){
                enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p1.Chromosome[i]].JourCombinaison[choice][j]+1],p1.Chromosome[i] );
                for(int k=CDP[p1.Chromosome[i]].JourCombinaison[choice][j]+1;k<enf.Pointer.size();k++){
                    enf.Pointer[k]++;
                }
            }
        }
    }

    for(int i=p2.Chromosome.size()-1;i>=0;i--){
        exist=SameGene(p1.Chromosome, p2.Chromosome[i], start, end);
        if(exist && p2.Chromosome[i]>0){
            enf.DayChoose[p2.Chromosome[i]]=p2.DayChoose[p2.Chromosome[i]];
            choice=p2.DayChoose[p2.Chromosome[i]];
            for(int j=0;j<CDP[p2.Chromosome[i]].Frequence;j++){
                enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][j]+1],p2.Chromosome[i] );
                for(int k=CDP[p2.Chromosome[i]].JourCombinaison[choice][j]+1;k<enf.Pointer.size();k++){
                    enf.Pointer[k]++;
                }
            }
        }
    }
    return 0;
}




//
//    cout<<"La chromosome d'enfant est"<<endl;
//    for (it = enf.Chromosome.begin(); it != enf.Chromosome.end(); it++) {
//        cout << *it << endl;
//    }


bool croisement1(solution &p1,solution &p2,solution &enf, cdp CDP[]) {
    int start = 1+rand() % p1.Chromosome.size();// points de coupure aléatoires
    int end = rand() % p1.Chromosome.size()-1;

    while (p1.Chromosome[start] < 0) {
        start++;
    }
    while (p1.Chromosome[end] < 0) {
        end++;
    }
    int n = 0;
    if (start > end) {
        n = start;
        start = end;
        end = n;
    }

    // start<end
    bool exist;
    int choice;
    vector<int>().swap(enf.Chromosome);
    vector<int>().swap(enf.Pointer);
    vector<int>::iterator it;
    std::vector<int> inserted;
    for (int i=0; i<30; ++i) inserted.push_back(0);


    for (int i = 0; i < p1.Pointer.size(); i++) {
        enf.Pointer.push_back(i-1);
        if (i != 0) {
            enf.Chromosome.push_back(-i);
        }

    }
    // Ajout des clients de P1 entre start et end et conservation de la combinaison choisie
    for (int i = end ; i >= start; i--) {
        if (p1.Chromosome[i] > 0) {
            //cout<<inserted[p1.Chromosome[i]]<<endl;
            inserted[p1.Chromosome[i]]=1;
            enf.DayChoose[p1.Chromosome[i]] = p1.DayChoose[p1.Chromosome[i]];
            choice = p1.DayChoose[p1.Chromosome[i]];
            for (int j = 0; j < CDP[p1.Chromosome[i]].Frequence; j++) {
                enf.Chromosome.insert(
                        enf.Chromosome.begin() + enf.Pointer[CDP[p1.Chromosome[i]].JourCombinaison[choice][j] + 1],
                        p1.Chromosome[i]);
                for (int k = CDP[p1.Chromosome[i]].JourCombinaison[choice][j] + 1; k < enf.Pointer.size(); k++) {
                    enf.Pointer[k]++;
                }
            }
        }
    }


    for (int i = p2.Chromosome.size() - 1; i >= 0; i--) {
        //exist = SameGene(p1.Chromosome, p2.Chromosome[i], start, end);
        //cout <<exist<<endl;
        //cout<<inserted[p2.Chromosome[i]]<<endl;
        if (inserted[p2.Chromosome[i]]==0 && p2.Chromosome[i] > 0) {
            inserted[p2.Chromosome[i]]=1;
            //cout<<inserted[p2.Chromosome[i]]<<endl;
            enf.DayChoose[p2.Chromosome[i]] = p2.DayChoose[p2.Chromosome[i]];
            choice = p2.DayChoose[p2.Chromosome[i]];
            for (int j = 0; j < CDP[p2.Chromosome[i]].Frequence; j++) {//insertion à modifier ne se fait pas en fin mais en améliorant les arcs
                enf.Chromosome.insert(
                        enf.Chromosome.begin() + enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][j] + 1],
                        p2.Chromosome[i]);
                for (int k = CDP[p2.Chromosome[i]].JourCombinaison[choice][j] + 1; k < enf.Pointer.size(); k++) {
                    enf.Pointer[k]++;
                }
            }
        }
    }
    //for (int i=0; i<100; ++i) {cout<<inserted[i]<<endl ;cout<<p2.Chromosome[i]<<endl;}
    return 0;
}

bool croisement2(solution &p1,solution &p2,solution &enf, cdp CDP[]){
    int start = rand() % p1.Chromosome.size();
    int end=  rand() % p1.Chromosome.size();
    start=start+4;
    end=end-4;
    while(p1.Chromosome[start]<0){
        start++;
    }
    while(p1.Chromosome[end]<0){
        end++;
    }
    int n=0;
    if(start>end){
        n=start;
        start=end;
        end=n;
    }

    bool exist;
    int choice;
    vector<int>().swap(enf.Chromosome);
    vector<int>().swap(enf.Pointer);
    vector<int>::iterator it;
    std::vector<int> numb;
    for (int i=0; i<30; ++i) numb.push_back(0);

    for(int i=0;i<p1.Pointer.size();i++){
        enf.Pointer.push_back(i-1);
        if(i!=0){
            enf.Chromosome.push_back(-i);
        }

    }

    for(int i=end;i>=start;i--){
        if(p1.Chromosome[i]>0){
            enf.DayChoose[p1.Chromosome[i]]=p1.DayChoose[p1.Chromosome[i]];
            choice=p1.DayChoose[p1.Chromosome[i]];
            numb[p1.Chromosome[i]]++;
            //for(int j=0;j<CDP[p1.Chromosome[i]].Frequence;j++){
            enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p1.Chromosome[i]].JourCombinaison[choice][0]+1],p1.Chromosome[i] );
            for(int k=CDP[p1.Chromosome[i]].JourCombinaison[choice][0]+1;k<enf.Pointer.size();k++){
                enf.Pointer[k]++;
                //}
            }
        }
    }

    for(int i=p2.Chromosome.size()-1;i>=0;i--){
        exist=SameGene(p1.Chromosome, p2.Chromosome[i], start, end);
        //cout<<p2.Chromosome[i]<<endl;
        if(p2.Chromosome[i]>0 && exist){
            //cout<<"num"<<numb[p2.Chromosome[i]]<<endl;
            //cout<<"freq"<<CDP[p2.Chromosome[i]].Frequence<<endl;
            if (numb[p2.Chromosome[i]]<CDP[p2.Chromosome[i]].Frequence){
                enf.DayChoose[p2.Chromosome[i]]=p2.DayChoose[p2.Chromosome[i]];
                numb[p2.Chromosome[i]]++;
                choice=p2.DayChoose[p2.Chromosome[i]];
                //for(int j=0;j<CDP[p2.Chromosome[i]].Frequence;j++){
                enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][0]+1],p2.Chromosome[i] );
                for(int k=CDP[p2.Chromosome[i]].JourCombinaison[choice][0]+1;k<enf.Pointer.size();k++){
                    enf.Pointer[k]++;
                    //}
                }}
        }
    }



//
//    cout<<"La chromosome d'enfant est"<<endl;
//    for (it = enf.Chromosome.begin(); it != enf.Chromosome.end(); it++) {
//        cout << *it << endl;
//    }
    //for(int i=0;i<numb.size();i++){ cout<<numb[i]<<endl;}

//cout<<p1.Chromosome[103]<<endl;
    return 0;
}

int current_day(solution &p, int i){
    for(int j=i;j<p.Chromosome.size();j++){
        if (p.Chromosome[j]<0 ){return -p.Chromosome[j];}
    }
    return 1;

}

bool compatible_choices(solution &p1,solution &p2, int client, int choice1,int choice2 , cdp CDP[], vector<vector<int> > journey_inserted){
        //CDP[p2.Chromosome[i]].JourCombinaison[choice2];
        // Journée où le client a été inséré.
        std::vector<int> combi_choice2;
        for (int i = 0; i < CDP[client].Frequence; ++i) combi_choice2.push_back(CDP[client].JourCombinaison[choice2][i]);
        for (int i = 0; i < 10; ++i) {
            bool exist=false;
            for (int j = 0; j < CDP[client].Frequence; ++j) {
                if (combi_choice2[j]==journey_inserted[client][i]){
                    exist=true;
                }

            }
            if (exist=false){return false;}

        }
        return true;
}




bool crois2(solution &p1,solution &p2,solution &enf, cdp CDP[], int NumClient) {
    int start = rand() % p1.Chromosome.size();
    int end = rand() % p1.Chromosome.size();
    while (p1.Chromosome[start] < 0) {
        start++;
    }
    while (p1.Chromosome[end] < 0) {
        end++;
    }
    int n = 0;
    if (start > end) {
        n = start;
        start = end;
        end = n;
    }

    //cout<<"Debut "<<start<<endl;
    //cout<<"Fin "<<end<<endl;

    bool exist;
    int choice;
    vector<int>().swap(enf.Chromosome);
    vector<int>().swap(enf.Pointer);
    vector<int>::iterator it;
    std::vector<int> numb;
    for (int i = 0; i < NumClient+1; ++i) numb.push_back(0);
    std::vector<int> journee;
    for (int i = 0; i < 10; ++i) journee.push_back(0);
    std::vector<vector<int> >Journey_inserted;
    for (int i = 0; i < NumClient+1; ++i) Journey_inserted.push_back(journee);

    for (int i = 0; i < p1.Pointer.size(); i++) {
        enf.Pointer.push_back(i - 1);
        if (i != 0) {
            enf.Chromosome.push_back(-i);
        }

    }

    //cout<<"STEP0"<<endl;
    for (int k = 0; k < enf.Pointer.size(); ++k) {
        //cout<<enf.Pointer[k]<<endl;
    }

    for (int i = end - 1; i >= start; i--) {//Placement des clients de P1 en conservant la journée sans réaliser une copie entière de la combinaison
        if (p1.Chromosome[i] > 0) {
            enf.DayChoose[p1.Chromosome[i]] = p1.DayChoose[p1.Chromosome[i]];
            //choice = p1.DayChoose[p1.Chromosome[i]];//choix de combinaison
            numb[p1.Chromosome[i]]++;
            Journey_inserted[p1.Chromosome[i]][current_day(p1,i)-1]=1;
            enf.Chromosome.insert(
                    enf.Chromosome.begin() + enf.Pointer[current_day(p1,i)],
                    p1.Chromosome[i]);
            for (int k = current_day(p1,i); k < enf.Pointer.size(); k++) {
                enf.Pointer[k]++;
            }

        }
    }
    //cout<<"STEP1"<<endl;
    for (int k = 0; k < enf.Pointer.size(); ++k) {
                //cout<<enf.Pointer[k]<<endl;
            }
    int sum=0;
    for (int l = 0; l <numb.size() ; ++l) {
        sum+=numb[l];
    }

    //cout<<"nb insertion "<<sum<<endl;

    for (int i = p2.Chromosome.size() - 1; i >= 0; i--) {

        if (p2.Chromosome[i] > 0) {
            if (numb[p2.Chromosome[i]] == 0) {// Element n'a pas  encore inséré
                numb[p2.Chromosome[i]] = CDP[p2.Chromosome[i]].Frequence;// On reprend la combinaison de P2
                enf.DayChoose[p2.Chromosome[i]] = p2.DayChoose[p2.Chromosome[i]];
                choice = p2.DayChoose[p2.Chromosome[i]];
                for (int j = 0; j < CDP[p2.Chromosome[i]].Frequence; j++) {
                    enf.Chromosome.insert(
                            enf.Chromosome.begin() + enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][j] + 1],
                            p2.Chromosome[i]);
                    for (int k = CDP[p2.Chromosome[i]].JourCombinaison[choice][j] + 1; k < enf.Pointer.size(); k++) {
                        enf.Pointer[k]++;
                    }
                }
                //cout<<"STEPa2"<<endl;
                for (int k = 0; k < enf.Pointer.size(); ++k) {
                    //cout<<enf.Pointer[k]<<endl;
                }
            } else if (numb[p2.Chromosome[i]] < CDP[p2.Chromosome[i]].Frequence) {// L'elément a été inseré dans la première partie, mais sa fréquence n'a pas été atteinte
                //enf.DayChoose[p2.Chromosome[i]] = p2.DayChoose[p2.Chromosome[i]];// La problématique ici est de trouver une combinaison qui fonctionne
                //choice = p2.DayChoose[p2.Chromosome[i]];
                // Choisir la combinaison adéquate
                int choice2 = p2.DayChoose[p2.Chromosome[i]];
                int choice1 = p1.DayChoose[p2.Chromosome[i]];
                bool compa= compatible_choices(p1,p2, p2.Chromosome[i],  choice1, choice2 ,  CDP, Journey_inserted);
                if (compa){
                    for (int j = 0; j < CDP[p2.Chromosome[i]].Frequence; j++){
                        if (Journey_inserted[p2.Chromosome[i]][CDP[p2.Chromosome[i]].JourCombinaison[choice2][j]]==0){
                            enf.Chromosome.insert(
                                    enf.Chromosome.begin() + enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice2][j] + 1],
                                    p2.Chromosome[i]);
                            for (int k = CDP[p2.Chromosome[i]].JourCombinaison[choice2][j] + 1; k < enf.Pointer.size(); k++) {
                                enf.Pointer[k]++;
                            }
                        }
                    }
                    numb[p2.Chromosome[i]]=CDP[p2.Chromosome[i]].Frequence;

                }
                else {
                        for (int j = 0; j < CDP[p2.Chromosome[i]].Frequence; j++){
                            if (Journey_inserted[p2.Chromosome[i]][CDP[p2.Chromosome[i]].JourCombinaison[choice1][j]]==0){
                                enf.Chromosome.insert(
                                        enf.Chromosome.begin() + enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice1][j] + 1],
                                        p2.Chromosome[i]);
                                for (int k = CDP[p2.Chromosome[i]].JourCombinaison[choice1][j] + 1; k < enf.Pointer.size(); k++) {
                                    enf.Pointer[k]++;
                                }
                            }
                        }
                        numb[p2.Chromosome[i]]=CDP[p2.Chromosome[i]].Frequence;
                    }
                }
            //cout<<"STEPv2"<<endl;
            for (int k = 0; k < enf.Pointer.size(); ++k) {
                //cout<<enf.Pointer[k]<<endl;
            }
            }
        }
    //cout<<"STEP2"<<endl;
    for (int k = 0; k < enf.Pointer.size(); ++k) {
        //cout<<enf.Pointer[k]<<endl;
    }

    for (int m = 0; m < enf.Chromosome.size(); ++m) {
        //cout<<enf.Chromosome[m]<<endl;
    }

    return 0;
    }

int best_position(solution &enf, int a, int b, solution p2, int i) {
//    cout<<"Client "<<p2.Chromosome[i]<<endl;
//    cout<<"Antecedent "<<p2.Chromosome[i-1]<<endl;
//    cout<<"Suivant "<<p2.Chromosome[i+1]<<endl;
        for (int j = a + 1; j < b - 1; j++) {
            //cout<<enf.Chromosome[j]<<endl;
            if (enf.Chromosome[j] == p2.Chromosome[i-1] and p2.Chromosome[i-1]>0) {return j;};
            if (enf.Chromosome[j] == p2.Chromosome[i+1]and p2.Chromosome[i-1]>0) {return (j+1);};
        }
        //cout<<b-1<<endl;
        return b;
    }

bool crossover1(solution &p1, solution &p2, solution &enf, cdp CDP[], int numClient) {//Conservation de la combinaison du parent 1 et insertion optimale avec mémoire du parent 2
        int start = rand() % (p1.Chromosome.size()-1);
        int end = rand() % (p1.Chromosome.size()-1);
        //cout<<start<<endl;
        //cout<<end<<endl;
        while (p1.Chromosome[start] < 0) {
            start++;
        }
        while (p1.Chromosome[end] < 0) {
            end++;
        }
        int n = 0;
        if (start > end) {
            n = start;
            start = end;
            end = n;
        }

        int choice;
        vector<int>().swap(enf.Chromosome);
        vector<int>().swap(enf.Pointer);
        vector<int>::iterator it;
        std::vector<int> inserted;
        for (int i = 0; i < numClient+1; ++i) inserted.push_back(0);

        for (int i = 0; i < p1.Pointer.size(); i++) {
            enf.Pointer.push_back(i - 1);
            if (i != 0) {
                enf.Chromosome.push_back(-i);
            }

        }

        //cout<<"Premier element insere "<<p1.Chromosome[end-1]<<endl;
        //cout<<"Dernier element insere "<<p1.Chromosome[start]<<endl;
        //cout<<"Parent1"<<endl;
    for (int l = 0; l < p1.Chromosome.size(); ++l) {
        //cout<<p1.Chromosome[l]<<endl;
    }

    //cout<<"Parent2"<<endl;
    for (int l = 0; l < p2.Chromosome.size(); ++l) {
        //cout<<p2.Chromosome[l]<<endl;
    }
    //cout<<"Parent1"<<endl;
        for (int i = end - 1; i >= start; i--) {// Conservation de la combinaison du parent 1 et insertion des clients en fin de tournée
            if (inserted[p1.Chromosome[i]] == 0 && p1.Chromosome[i] > 0) {
                inserted[p1.Chromosome[i]] = 1;
                //cout<<p1.Chromosome[i]<<endl;
                enf.DayChoose[p1.Chromosome[i]] = p1.DayChoose[p1.Chromosome[i]];
                choice = p1.DayChoose[p1.Chromosome[i]];
                for (int j = 0; j < CDP[p1.Chromosome[i]].Frequence; j++) {
                    int position1 = best_position(enf, enf.Pointer[CDP[p1.Chromosome[i]].JourCombinaison[choice][j]],enf.Pointer[CDP[p1.Chromosome[i]].JourCombinaison[choice][j] + 1],p1,i);
                    enf.Chromosome.insert(enf.Chromosome.begin() +position1,
                                          p1.Chromosome[i]);
                    for (int k = CDP[p1.Chromosome[i]].JourCombinaison[choice][j] + 1; k < enf.Pointer.size(); k++) {
                        enf.Pointer[k]++;
                    }
                }
            }
        }
    //cout<<"Parent2"<<endl;
        for (int i = p2.Chromosome.size() - 1;
             i >= 0; i--) {//On souhaite garder la combinaison de P2 mais avoir la meilleure insertion
            if (inserted[p2.Chromosome[i]] ==0 && p2.Chromosome[i] > 0) {// Le client n'a pas encore été inséré
                inserted[p2.Chromosome[i]] =1;
                //cout<<p2.Chromosome[i]<<endl;
                enf.DayChoose[p2.Chromosome[i]] = p2.DayChoose[p2.Chromosome[i]];
                choice = p2.DayChoose[p2.Chromosome[i]];// on conserve la même combinaison
                    for (int j = 0; j < CDP[p2.Chromosome[i]].Frequence; j++) {
                        int position1 = best_position(enf, enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][j]],enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][j] + 1],p2,i);
                        enf.Chromosome.insert(enf.Chromosome.begin() +position1,
                                              p2.Chromosome[i]);
                        //cout<<"Position "<<position1<<endl;
                        for (int k = CDP[p2.Chromosome[i]].JourCombinaison[choice][j] + 1;
                             k < enf.Pointer.size(); k++) {
                            enf.Pointer[k]++;
                        }
                    }
                }
            }
    //return 0;
    //cout<<"Enfant"<<endl;
    for (int l = 0; l < enf.Chromosome.size(); ++l) {
        //cout<<enf.Chromosome[l]<<endl;
    }

        }

bool crois_position_aleatoire(solution &p1, solution &p2, solution &enf, cdp CDP[], int numClient) {
    int start = rand() % p1.Chromosome.size();
    int end= rand() % p1.Chromosome.size();
    while(p1.Chromosome[start]<0){
        start++;
    }
    while(p1.Chromosome[end]<0){
        end++;
    }
    int n=0;
    if(start>end){
        n=start;
        start=end;
        end=n;
    }

    int choice;
    vector<int>().swap(enf.Chromosome);
    vector<int>().swap(enf.Pointer);
    vector<int>::iterator it;
    std::vector<int> inserted;
    for (int i = 0; i < numClient+1; ++i) inserted.push_back(0);

    for(int i=0;i<p1.Pointer.size();i++){
        enf.Pointer.push_back(i-1);
        if(i!=0){
            enf.Chromosome.push_back(-i);
        }

    }

    for(int i=end-1;i>=start;i--){
        if(p1.Chromosome[i]>0 && inserted[p1.Chromosome[i]] ==0){
            inserted[p1.Chromosome[i]] = 1;
            enf.DayChoose[p1.Chromosome[i]]=p1.DayChoose[p1.Chromosome[i]];
            choice=p1.DayChoose[p1.Chromosome[i]];
            for(int j=0;j<CDP[p1.Chromosome[i]].Frequence;j++){
                enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p1.Chromosome[i]].JourCombinaison[choice][j]+1],p1.Chromosome[i] );
                for(int k=CDP[p1.Chromosome[i]].JourCombinaison[choice][j]+1;k<enf.Pointer.size();k++){
                    enf.Pointer[k]++;
                }
            }
        }
    }

    for(int i=p2.Chromosome.size()-1;i>=0;i--){// Conservation de la combinaison de P2 avec insertion aléatoire des clients dans l'enfant
        if(inserted[p2.Chromosome[i]]==0 and p2.Chromosome[i]>0){
            inserted[p2.Chromosome[i]]=1;
            enf.DayChoose[p2.Chromosome[i]]=p2.DayChoose[p2.Chromosome[i]];
            choice=p2.DayChoose[p2.Chromosome[i]];
            for(int j=0;j<CDP[p2.Chromosome[i]].Frequence;j++){
                int taille= enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][j]+1]-enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][j]];
                int position=rand() % taille;// position d'insertion aléatoire
                enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][j]+1]-position,p2.Chromosome[i] );
                for(int k=CDP[p2.Chromosome[i]].JourCombinaison[choice][j]+1;k<enf.Pointer.size();k++){
                    enf.Pointer[k]++;
                }
            }
        }
    }
    return 0;
}

bool crois_position_optimale(solution &p1, solution &p2, solution &enf, cdp CDP[], int numClient) {
    int start = rand() % p1.Chromosome.size();
    int end= rand() % p1.Chromosome.size();
    while(p1.Chromosome[start]<0){
        start++;
    }
    while(p1.Chromosome[end]<0){
        end++;
    }
    int n=0;
    if(start>end){
        n=start;
        start=end;
        end=n;
    }

    //bool exist;
    int choice;
    vector<int>().swap(enf.Chromosome);
    vector<int>().swap(enf.Pointer);
    vector<int>::iterator it;
    std::vector<int> inserted;
    for (int i = 0; i < numClient; ++i) inserted.push_back(0);

    for(int i=0;i<p1.Pointer.size();i++){
        enf.Pointer.push_back(i-1);
        if(i!=0){
            enf.Chromosome.push_back(-i);
        }

    }

    for(int i=end-1;i>=start;i--){
        if(p1.Chromosome[i]>0){
            inserted[p1.Chromosome[i]] = 1;
            enf.DayChoose[p1.Chromosome[i]]=p1.DayChoose[p1.Chromosome[i]];
            choice=p1.DayChoose[p1.Chromosome[i]];
            for(int j=0;j<CDP[p1.Chromosome[i]].Frequence;j++){
                enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p1.Chromosome[i]].JourCombinaison[choice][j]+1],p1.Chromosome[i] );
                for(int k=CDP[p1.Chromosome[i]].JourCombinaison[choice][j]+1;k<enf.Pointer.size();k++){
                    enf.Pointer[k]++;
                }
            }
        }
    }

    for(int i=p2.Chromosome.size()-1;i>=0;i--){
        if(inserted[p2.Chromosome[i]]==0 and p2.Chromosome[i]>0){
            inserted[p2.Chromosome[i]]=1;
            enf.DayChoose[p2.Chromosome[i]]=p2.DayChoose[p2.Chromosome[i]];
            choice=p2.DayChoose[p2.Chromosome[i]];
            for(int j=0;j<CDP[p2.Chromosome[i]].Frequence;j++){
                enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][j]+1],p2.Chromosome[i] );
                for(int k=CDP[p2.Chromosome[i]].JourCombinaison[choice][j]+1;k<enf.Pointer.size();k++){
                    enf.Pointer[k]++;
                }
            }
        }
    }
return 0;
}

bool CELOX_rapide_1jr(solution &p1,solution &p2,solution &enf, cdp CDP[], int numClient) {
    int start = rand() % p1.Chromosome.size();
    int end= rand() % p1.Chromosome.size();
    while(p1.Chromosome[start]<0){
        start++;
    }
    while(p1.Chromosome[end]<0){
        end++;
    }
    int n=0;
    if(start>end){
        n=start;
        start=end;
        end=n;
    }

    //bool exist;
    int choice;
    vector<int>().swap(enf.Chromosome);
    vector<int>().swap(enf.Pointer);
    vector<int>::iterator it;
    std::vector<int> inserted;
    for (int i = 0; i < numClient+1; ++i) inserted.push_back(0);

    for(int i=0;i<p1.Pointer.size();i++) {
        enf.Pointer.push_back(i - 1);
        if (i != 0) {
            enf.Chromosome.push_back(-i);
        }
    }

    for(int i=end-1;i>=start;i--){
        if(p1.Chromosome[i]>0 and inserted[p1.Chromosome[i]]==0){
            inserted[p1.Chromosome[i]]=1;;
                enf.Chromosome.insert(enf.Chromosome.begin(),p1.Chromosome[i] );
                enf.Pointer[1]++;
                }
        }


    for(int i=p2.Chromosome.size()-1;i>=0;i--){
        if(inserted[p2.Chromosome[i]]==0 && p2.Chromosome[i]>0){
            inserted[p2.Chromosome[i]]=1;
                enf.Chromosome.insert(enf.Chromosome.begin(),p2.Chromosome[i] );
                    enf.Pointer[1]++;
                }

        }




//
//    cout<<"La chromosome d'enfant est"<<endl;
//    for (it = enf.Chromosome.begin(); it != enf.Chromosome.end(); it++) {
//        cout << *it << endl;
//    }

    return 0;
}

    bool CELOX_rapide(solution &p1,solution &p2,solution &enf, cdp CDP[], int numClient){
    int start = rand() % p1.Chromosome.size();
    int end= rand() % p1.Chromosome.size();
    while(p1.Chromosome[start]<0){
        start++;
    }
    while(p1.Chromosome[end]<0){
        end++;
    }
    int n=0;
    if(start>end){
        n=start;
        start=end;
        end=n;
    }

    //bool exist;
    int choice;
    vector<int>().swap(enf.Chromosome);
    vector<int>().swap(enf.Pointer);
    vector<int>::iterator it;
    std::vector<int> inserted;
    for (int i = 0; i < numClient+1; ++i) inserted.push_back(0);

    for(int i=0;i<p1.Pointer.size();i++) {
        enf.Pointer.push_back(i - 1);
        if (i != 0) {
            enf.Chromosome.push_back(-i);
        }
    }

    for(int i=end-1;i>=start;i--){
        if(p1.Chromosome[i]>0 and inserted[p1.Chromosome[i]]==0){
            inserted[p1.Chromosome[i]]=1;
            enf.DayChoose[p1.Chromosome[i]]=p1.DayChoose[p1.Chromosome[i]];
            choice=p1.DayChoose[p1.Chromosome[i]];
            for(int j=0;j<CDP[p1.Chromosome[i]].Frequence;j++){
                double geoi=p1.Chromosome[i];
                double zgz=CDP[p1.Chromosome[i]].NumJourCombinaison;
                double ehe=CDP[p1.Chromosome[i]].JourCombinaison[choice][j];
                double aotie=enf.Pointer[CDP[p1.Chromosome[i]].JourCombinaison[choice][j]+1];
                enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p1.Chromosome[i]].JourCombinaison[choice][j]+1],p1.Chromosome[i] );
                for(int k=CDP[p1.Chromosome[i]].JourCombinaison[choice][j]+1;k<enf.Pointer.size();k++){
                    enf.Pointer[k]++;
                }
            }
        }
    }

    for(int i=p2.Chromosome.size()-1;i>=0;i--){
        if(inserted[p2.Chromosome[i]]==0 && p2.Chromosome[i]>0){
            enf.DayChoose[p2.Chromosome[i]]=p2.DayChoose[p2.Chromosome[i]];
            choice=p2.DayChoose[p2.Chromosome[i]];
            inserted[p2.Chromosome[i]]=1;
            for(int j=0;j<CDP[p2.Chromosome[i]].Frequence;j++){
                enf.Chromosome.insert(enf.Chromosome.begin()+enf.Pointer[CDP[p2.Chromosome[i]].JourCombinaison[choice][j]+1],p2.Chromosome[i] );
                for(int k=CDP[p2.Chromosome[i]].JourCombinaison[choice][j]+1;k<enf.Pointer.size();k++){
                    enf.Pointer[k]++;
                }
            }
        }
    }



//
//    cout<<"La chromosome d'enfant est"<<endl;
//    for (it = enf.Chromosome.begin(); it != enf.Chromosome.end(); it++) {
//        cout << *it << endl;
//    }
    return 0;
}

int roulette_russe(vector<double> weight){
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
    return 0;
}

void weight_adjustment(vector<double> &weight,int choix,vector <solution> pop,solution p1, solution p2,double poids){
    if (poids<pop[0].Fitness){weight[choix]+=1;}
    if (poids<p1.Fitness or poids<p1.Fitness){weight[choix]+=0.5;}
    //__wrap_iter<solution *> it =std::find(pop.begin(), pop.end(), p1);
}

void adaptive_LNS_crossovers(solution p1, solution p2, cdp CDP[], vector <solution> &pop,solution enfant,int numClient){
    std::vector<double> weight;
    for (int i = 0; i < 4; ++i) weight.push_back(1);
    for (int j = 0; j <14 ; ++j) {
        int choix = roulette_russe(weight);
        cout<<"Choix "<<choix<<endl;
        if (choix == 0) {CELOX_rapide(p1, p2, enfant, CDP, numClient);}
        else if (choix == 1) {crossover1(p1, p2, enfant,  CDP, numClient);}
        else if (choix == 2) {crois_position_optimale(p1, p2, enfant,  CDP, numClient);}
        else if (choix == 3) {crois2(p1, p2, enfant,  CDP, numClient);}
        double poids = enfant.Fitness;
        weight_adjustment(weight, choix, pop, p1, p2, poids);
    }
    for (int k = 0; k <weight.size() ; ++k) {
        cout<<"Poids "<<weight[k]<<endl;
    }
}

double average(vector <solution> pop){
    double sum=0;
    for (int i = 0; i < pop.size(); ++i) {
        sum+=pop[i].Fitness;
    }
    return sum/pop.size();
}

double ecart(vector <solution> pop, solution sol){
    double ecart_min=10000000;
    for (int i = 0; i < pop.size() ; ++i) {
        if (abs(sol.Fitness-pop[i].Fitness)<ecart_min){
            ecart_min=abs(sol.Fitness-pop[i].Fitness);
        }
    }
}

bool nouvelle_solution(vector <solution> pop, solution sol){
    for (int i = 0; i <pop.size() ; ++i) {
        if (pop[i].Fitness==sol.Fitness){return false;}
    }
}

void weight_adjustment_alns(vector<double> &weight,vector<double> &weight1,int choix, int choix1,vector <solution> pop,double poids){
    if (poids<pop[0].Fitness){weight[choix]+=3;weight1[choix1]+=3;}
    else if (poids<average(pop)){weight[choix]+=2;weight1[choix1]+=2;}
    else {weight[choix]+=1;weight1[choix1]+=1;};
}

void weight_adjustment_alns_intensification(vector<double> &weight,vector<double> &weight1,int choix, int choix1,vector <solution> pop,double poids){
    if (poids<pop[0].Fitness){weight[choix]+=10;weight1[choix1]+=10;}
    else if (poids<average(pop)){weight[choix]+=5;weight1[choix1]+=5;}
    else {weight[choix]+=1;weight1[choix1]+=1;};
}

void weight_adjustment_alns_diversification(vector<double> &weight,vector<double> &weight1,int choix, int choix1,vector <solution> pop,double poids, solution sol, double seuil1, double seuil2){
    if (poids<pop[0].Fitness and ecart(pop,sol)>seuil1){weight[choix]+=10;weight1[choix1]+=10;}
    else if (nouvelle_solution(pop,sol) and ecart(pop,sol)<seuil1 and ecart(pop,sol)>seuil2){weight[choix]+=5;weight1[choix1]+=5;}
    else {weight[choix]+=1;weight1[choix1]+=1;};
}
//
//void best_combinaison(solution sol1,solution sol2, cdp CDP[],int numClient, double P_mutation,int numRechoose,double P_choose,double Qmax, double Tmax, double Dmax, double Vmoy, double Vrecharge,
//                      double CoutRecharge,long double Distence[][30], double Alpha, double Beta, int &best_croisement,int &best_mutation) {
//    solution p1 = sol1;
//    solution p2 = sol2;
//    solution enfant;
//    double poids=1000000;
//    best_croisement = 0;
//    best_mutation = 0;
//    for (int i = 0; i < 4; ++i) {
//        vector<solution> Enfant;
//        if (i == 0) {
//            CELOX_rapide(p1, p2, enfant, CDP, numClient);
//            Enfant.push_back(enfant);
//            CELOX_rapide(p2, p1, enfant, CDP, numClient);
//            Enfant.push_back(enfant);
//        } else if (i == 1) {
//            crossover1(p1, p2, enfant, CDP, numClient);
//            Enfant.push_back(enfant);
//            crossover1(p2, p1, enfant, CDP, numClient);
//            Enfant.push_back(enfant);
//        } else if (i == 2) {
//            crois_position_aleatoire(p1, p2, enfant, CDP, numClient);
//            Enfant.push_back(enfant);
//            crois_position_aleatoire(p2, p1, enfant, CDP, numClient);
//            Enfant.push_back(enfant);
//        } else if (i == 3) {
//            crois2(p1, p2, enfant, CDP, numClient);
//            Enfant.push_back(enfant);
//            crois2(p2, p1, enfant, CDP, numClient);
//            Enfant.push_back(enfant);
//        }
//        for (int l = 0; l <8; ++l) {
//            for (int j = 0; j < Enfant.size(); j++) {
//                if (l == 0) {
//                    Mmove(Enfant[j], CDP);
//                } else if (l == 1) {
//                    MoveNclients(Enfant[j], CDP, numRechoose, int(numClient));
//                } else if (l == 2) {
//                    double p = (rand() % 101) / 100.0;
//                    //cout <<"La probabilite de mutation est " <<p << endl;
//                    if (p < P_mutation) {
//                        double p_choose = (rand() % 101) / 100.0;
//                        if (p_choose >= P_choose) {
//                            Mmove(Enfant[j], CDP);
//                        } else {
//                            MoveNclients(Enfant[j], CDP, numRechoose, int(numClient));
//                        }
//                    }
//                } else if (l == 3) {
//                    boucle_LNS2(Enfant[j], CDP, 1, numClient, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge,
//                                Distence, Alpha, Beta);
//                } else if (l == 4) {
//                    boucle_LNS2(Enfant[j], CDP, 3, numClient, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge,
//                                Distence, Alpha, Beta);
//                } else if (l == 5) {
//                    boucle_LNS2(Enfant[j], CDP, 5, numClient, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge,
//                                Distence, Alpha, Beta);
//                } else if (l == 6) {
//                    boucle_LNS2(Enfant[j], CDP, 7, numClient, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge,
//                                Distence, Alpha, Beta);
//                } else if (l == 7) {
//                    LNS2opt(Enfant[j], CDP, 7, numClient, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge,
//                            Distence, Alpha, Beta);
//                }
//                EvaluerOption4(Enfant[j], CDP, Qmax, Tmax, Dmax, Vmoy, Vrecharge, CoutRecharge, Distence, Alpha,
//                               Beta);
//                if (Enfant[j].Fitness<poids){best_croisement=i;best_mutation=l;poids=Enfant[j].Fitness;}
//            }
//        }
//    }
//}

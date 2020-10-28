#include <algorithm>
#include <random>


void rand_array(int a[],int b[],int num){
    int i=0,t =0;
    while(t<num) {
        i = rand()%num;
        if(a[i] == 0) {
            a[i] = 1;
            b[t]=i;
            //printf("%d\n",b[t]);
            t++;}

    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Generate_Chromosome(solution &sol, int numClient, int numPeriod, int numPointRecharge,cdp CDP[]){
    // Definir et initialiser les variables
    sol.DayChoose[0]=0;
    vector<int>::iterator it;
    for(int i=0;i<numPeriod;i++){    //插入分隔符-1和-2
        sol.Chromosome.push_back(-(i+1));
    }
    int day=0;//记录选择的日子
    vector<int> pr;
    sol.Pointer.push_back(-1);  //初始化指针数组 [-1,0,1]
    for (int i = 0; i <numPeriod; i++) {
        sol.Pointer.push_back(i);
    }
    std::vector<int> RandOrder;
    for (int i=0; i<numClient; ++i) RandOrder.push_back(i);
    //auto rng = std::default_random_engine {};
    std::random_shuffle(std::begin(RandOrder), std::end(RandOrder)); //Vecteur aléatoire
    std::vector<int> RandOrderPR;
    for (int i=0; i<numPointRecharge; ++i) RandOrderPR.push_back(i);
    std::random_shuffle(std::begin(RandOrderPR), std::end(RandOrderPR));

    for (int i = 0; i < numClient; i++) {
        //CDP[RandOrder[i]+1].CombinaisonChoose.push_back(num); //记录每一个染色体中该客户随机选择的JourCombinaison
           sol.Chromosome.insert(sol.Chromosome.begin(), CDP[RandOrder[i] + 1].Name);
              //移动指针
                sol.Pointer[1]++;

        }

    //随机插入充电站
//    for (int i = 1; i <= numPeriod; i++) {
//        int nnum = rand() % int(numPointRecharge);nnum=9;
//        for (int j = 0; j < nnum; j++) {
//            int nl = rand() % (pointerPR[i] - pointerPR[i - 1]-1) + pointerPR[i - 1] + 1;//+pointerPR[i-1];
//            Chromosome.insert(Chromosome.begin() + nl, CDP[RandOrderPR[j] + numClient + 1].Name);//在第i+nl个元素前面插入a;
//            for (int k = i; k <= numPeriod; k++) {//移动指针
//                pointerPR[k]++;
//            }
//        }
//    }
    for (int i = 1; i <= numPeriod; i++) {
        int nnum = rand() % int(numPointRecharge);
        for (int j = 0; j < nnum; j++) {
            pr.push_back(CDP[RandOrderPR[j] + numClient + 1].Name);
        }
        sol.list_pointrecharge.push_back(pr);
    }

//    cout << "Chromosome est " << endl;// output the chromosome
//    for (it = sol.Chromosome.begin(); it != sol.Chromosome.end(); it++) {
//        cout << *it << endl;
//    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Generate_Population(int numClient, int numPeriod, int numPointRecharge,cdp CDP[], int MaxPopulation, vector<solution> &Pop){
    solution sol[MaxPopulation];
    vector<solution> ().swap(Pop);
    for(int i=0;i<MaxPopulation;i++) {
        sol[i].Name=i;
        Generate_Chromosome(sol[i], numClient, numPeriod, numPointRecharge, CDP);
        Pop.push_back(sol[i]);
    }
    return true;
}

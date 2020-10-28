//
// Created by shaon on 2018/8/17.
//

bool VerifierChromosome(solution &sol,int numclient){
    int a[numclient];
    a[numclient]={0};
    for(int i=0;i<sol.Chromosome.size();i++){
        for(int j=1;j<=numclient;j++){
            if(sol.Chromosome[i]==j){
                a[sol.Chromosome[i]-1]++;
            }
        }
    }
    for(int i=0;i<numclient;i++){
        //cout<<a[i]<<endl;
    }
    return 0;
}

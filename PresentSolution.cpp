//
// Created by shaon on 2018/7/9.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PresentSolution(solution &sol){
    int nbr_tour=0;
    vector<int> pr;
    pr.push_back(0);
    bool J=true;
    double time=0;
    double cout1=0;
    double cout2=0;
    double cout3=0;


    for(int i=0;i<sol.R.size();i++){
        if(sol.R[i].size()>=nbr_tour){
            nbr_tour=sol.R[i].size();
        }
    }
//    cout<<"nbr Tour  "<<nbr_tour<<endl;
 //   cout<<nbr_tour<<endl;

    for(int i=0;i<sol.S.size();i++){
        for(int j=0;j<sol.S[i].size();j++){
            for(int n=0;n<sol.S[i][j].Chromosome.size();n++){
                for(int k=0;k<pr.size();k++){
                    if(pr[k]!=sol.S[i][j].Chromosome[n]){
                        J=true;
                    } else{
                        J=false;
                        break;
                    }
                }
                if(J){
                    pr.push_back(sol.S[i][j].Chromosome[n]);
                }
            }

        }
    }
//    cout<<"nbr PR  "<<pr.size()-1<<endl;
//    cout<<pr.size()-1<<endl;
    for(int i=0;i<sol.S.size();i++){
        for(int j=0;j<sol.S[i].size();j++){
            cout1=cout1+sol.S[i][j].cout1;
            cout2=cout2+sol.S[i][j].cout2;
            cout3=cout3+sol.S[i][j].cout3;
        }
    }
//    cout<<"Cout 1  "<<cout1+sol.Fitness<<endl;
//    cout<<"Cout 2  "<<cout2+sol.Fitness<<endl;
//    cout<<"Cout 3  "<<cout3+sol.Fitness<<endl;
//    cout<<cout1+sol.Fitness<<endl;
//    cout<<cout2+sol.Fitness<<endl;
//    cout<<cout3+sol.Fitness<<endl;

    cout<<nbr_tour<<"    "<<pr.size()-1<<"    "<<cout1+sol.Fitness<<"    "<<cout2+sol.Fitness<<"    "<<cout3+sol.Fitness<<endl;
    //cout<<cout1<<"    "<<cout2<<"    "<<cout3<<endl;
}
//
//Tournament Selection : 随机抽取2个，将这10个里面选一个最好的解放进下一代
// input : NbSelect
// Output : TabSelect

bool Selection(int numSelection, vector<solution> &Population,vector<solution> &TabSelect){
    vector<solution>().swap(TabSelect);
    std::vector<int> a;
    for (int i=0; i<Population.size(); ++i) a.push_back(i);;
    std::vector<int> b;
    for (int i=0; i<Population.size(); ++i) b.push_back(i);
    for(int i=0;i<numSelection;i++){
        if(Population[b[2*i]].Fitness<=Population[b[2*i+1]].Fitness){
            TabSelect.push_back(Population[b[2*i+1]]);
        }
        else{
            TabSelect.push_back(Population[b[2*i]]);
        }
    }
    return true;
}

#include <iostream>
#include <algorithm>
#include <cmath>
#include<random>
#include<numeric>
#include<vector>
using namespace std;

double mc(int S, int K, float r, float vol, float T, int sim, int N){
mt19937 rng;
normal_distribution<>ND(0,1);
ND(rng);
std::vector<double> s(sim);
float dt = T/N;
for(int i =0;i<sim;i++) //Loop for number of simulations
{
    std::vector<double> p(N+1); //storing pathwise simulated values
    p[0]=S; //setting first value to spot price
    for(int k = 0;k<N;k++)  //Loop of a single path
    {
        double phi = ND(rng);
        double temp = (1+(r*dt)+(vol*phi*sqrt(dt)));
        p[k+1] = (p[k]*temp); //update the asset price with asset price X SDE
    }
    s[i] = std::max(p[N]-K,0.0); //payoff of a Call Option

}
float sm = 0;
for(int i=0;i<sim;i++){sm = sm + s[i];}
float avg = sm/sim;
float payoff = avg*exp(-r*T);// Payoff of an option is the discounted average of final simulated price
return payoff;
}

int main(){
    cout << mc(100,100,0.05,0.2,1.0,50000,10000) << endl;
    return 0;
}
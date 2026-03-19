#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

int main() {
    int size;
    cout << "Enter size: ";
    cin >> size;

    vector<int> V(size);

    cout << "Enter elements:\n";
    for (int i = 0; i < size; i++) {
        cin >> V[i];
    }

    int S1 = 0, S2 = 0;

    for (int i = 0; i < size; i++) {
        if (i % 2 == 0)
            S1 += V[i];
        else
            S2 += V[i];
    }

    int S3 = S1 - S2;

    sort(V.begin(), V.end()); // ASC

    // запис у txt
    ofstream txt("result.txt");
    txt << "S1 = " << S1 << endl;
    txt << "S2 = " << S2 << endl;
    txt << "S3 = " << S3 << endl;
    txt.close();

    // JSON
    json j;
    j["array"] = V;
    j["S1"] = S1;
    j["S2"] = S2;
    j["S3"] = S3;

    ofstream jsonFile("result.json");
    jsonFile << j.dump(4);
}
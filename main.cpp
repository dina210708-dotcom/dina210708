#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <map>
#include "json.hpp" // Переконайся, що цей файл у тій же папці

using namespace std;
using json = nlohmann::json;

int main() {
    // 1) Введення розміру та елементів
    int size;
    cout << "Enter size: ";
    cin >> size;
    vector<int> V(size);
    cout << "Enter elements: ";
    for (int i = 0; i < size; i++) cin >> V[i];

    ofstream txt("result.txt");
    txt << "Initial vector V: ";
    for (int x : V) txt << x << " ";
    txt << endl;

    // 2) Групування по n елементів та суми груп
    int n;
    cout << "Enter group size n: ";
    cin >> n;
    
    vector<int> groupSums;
    for (int i = 0; i < size; i += n) {
        int currentSum = 0;
        for (int j = i; j < i + n && j < size; j++) {
            currentSum += V[j];
        }
        groupSums.push_back(currentSum);
    }

    txt << "Sums of groups: ";
    for (int s : groupSums) txt << s << " ";
    txt << endl;

    // Визначаємо S1, S2, S3 для подальших кроків
    int S1 = groupSums.size() > 0 ? groupSums[0] : 0;
    int S2 = groupSums.size() > 1 ? groupSums[1] : 0;
    int S3 = S1 - S2;
    txt << "S1=" << S1 << ", S2=" << S2 << ", S3=S1-S2=" << S3 << endl;

    // 3) Сортування та суми
    sort(V.begin(), V.end()); // ASC
    int sumASC = accumulate(V.begin(), V.end(), 0);
    txt << "Sorted ASC, Total Sum: " << sumASC << endl;

    sort(V.rbegin(), V.rend()); // DESC
    int sumDESC = accumulate(V.begin(), V.end(), 0);
    txt << "Sorted DESC, Total Sum: " << sumDESC << endl;

    // 4) Виділити повтори (дублікати)
    map<int, int> counts;
    for (int x : V) counts[x]++;
    
    vector<int> repeats;
    for (auto const& [val, count] : counts) {
        if (count > 1) repeats.push_back(val);
    }
    
    txt << "Repeated elements: ";
    for (int r : repeats) txt << r << " ";
    txt << endl;

    // 5) Збереження у JSON
    json j;
    j["S2"] = S2;
    j["S3"] = S3;

    // Формуємо V1 та V2 для JSON (перші дві групи)
    vector<int> V1, V2, V_diff;
    for (int i = 0; i < n && i < size; i++) V1.push_back(V[i]); // тут V вже відсортований DESC
    for (int i = n; i < 2 * n && i < size; i++) V2.push_back(V[i]);

    // Обчислення різниці V1 - V2 (поелементно)
    for (size_t i = 0; i < V1.size() && i < V2.size(); i++) {
        V_diff.push_back(V1[i] - V2[i]);
    }

    j["V1"] = V1;
    j["V2"] = V2;
    j["V1-V2"] = V_diff; // Різниця як вектор
    j["Repeats"] = repeats;

    ofstream jsonFile("result.json");
    jsonFile << j.dump(4);
    
    txt.close();
    jsonFile.close();

    cout << "Done! Files result.txt and result.json updated according to the board." << endl;
    return 0;
}

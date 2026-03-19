#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric> // Для підрахунку суми
#include "json.hpp" // Не забудь покласти цей файл у папку!

using namespace std;
using json = nlohmann::json;

int main() {
    // 1) Введення розміру та масиву
    int size;
    cout << "Enter size: ";
    cin >> size;
    vector<int> V(size);
    for (int i = 0; i < size; i++) cin >> V[i];

    // 2) Погрупувати по n елементів
    int n;
    cout << "Enter group size n: ";
    cin >> n;

    int S1 = 0, S2 = 0;
    // Сума першої групи (V1)
    for (int i = 0; i < n && i < size; i++) S1 += V[i];
    // Сума другої групи (V2)
    for (int i = n; i < 2 * n && i < size; i++) S2 += V[i];

    // 4) Різниця
    int S3 = S1 - S2;

    // 3) Сортування
    sort(V.begin(), V.end()); // ASC
    int sumASC = accumulate(V.begin(), V.end(), 0);

    sort(V.rbegin(), V.rend()); // DESC
    int sumDESC = accumulate(V.begin(), V.end(), 0);

    // Запис у TXT
    ofstream txt("result.txt");
    txt << "S1=" << S1 << " S2=" << S2 << " S3=" << S3 << endl;
    txt << "Sum ASC: " << sumASC << ", DESC: " << sumDESC << endl;
    txt.close();

    // 5) Збереження у JSON (за структурою з дошки)
    json j;
    j["S1"] = S1;
    j["S2"] = S2;
    j["S3"] = S3;
    
    // Створюємо вектори-групи для JSON
    vector<int> V1, V2;
    for (int i = 0; i < n && i < size; i++) V1.push_back(V[i]);
    for (int i = n; i < 2 * n && i < size; i++) V2.push_back(V[i]);
    
    j["V1"] = V1;
    j["V2"] = V2;
    j["V1-V2"] = S3; // різниця з дошки

    ofstream jsonFile("result.json");
    jsonFile << j.dump(4);
    jsonFile.close();

    cout << "Done! Files result.txt and result.json created." << endl;
    return 0;
}

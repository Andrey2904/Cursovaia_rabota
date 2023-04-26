// kursac_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//C:\Users\HP\Desktop\prog

#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

void show(vector<int>a) {
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
}
int partition(vector<int>& arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int main()
{   
    int fbite, ebite;
    string path;
    cout << "Enter path" << endl;
    cin >> path;
    fstream file(path,fstream::in|fstream::out ,ios_base::binary);
    long nFileLen = 0;
    int size_user;
    cout << "Enter size of fail"<<endl;
    cin >> size_user;
    if (file)
    {
        file.seekg(0, ios_base::end);
        nFileLen = file.tellg();
        file.close();
    }
    else {
        cout << "Autosize is not define"<<endl;
        cout << "Probably the file is not in this repository" << endl;
        nFileLen = -1;
    }
    cout << "Autosize is " << nFileLen << endl;
    cout << "Enter first bite and last bite" << endl;
    cin >> fbite>>ebite;
    if (fbite > ebite) {
        cout << "The first byte cannot be larger than the last one. Therefore, the first and last bytes will be swapped." << endl;
        swap(fbite, ebite);
    }
    if (fbite < 0) {
        cout << " The first byte cannot be less than 0"<<endl;
        fbite = 0;
    }
    if (ebite > nFileLen) {
        cout << "The end byte connot be greater than size file"<<endl;
        ebite = nFileLen;
    }
    
    file.open(path);
    string start,midle,ends;
    int pos = 0;
    if (size_user != nFileLen) {
        cout << "The file size determined by the program does not match the one entered by the user."<<endl;
        cout << "The file size will be determined by the program" << endl;
    }
    if (!file.is_open()) {
        cout << "Error. File is not open" << endl;
        return -1;
    }
    else {
        
        char ch;
        
        while (file.get(ch)) {
            
            if (pos == fbite) {
                break;
            }
            start += ch;
            pos++;

        }
        cout << endl;
        while (file.get(ch)) {
            midle += ch;
            if (pos == ebite) {
                break;
            }
            
            pos++;
        }
        cout << endl;
        while (file.get(ch)) {
            if (pos == nFileLen)
                break;
            ends += ch;
            pos++;
        }
    }
    vector<char> mas;
    pos = 0;
    file.close();
    for (int i = 0; i < midle.size(); i++) {
        mas.push_back(midle[i]);
    }
    vector<int> num;
    for (int i = 0; i < mas.size(); i++) {
        int tm = int(mas[i]);
        num.push_back(tm);

    }
    vector<int> id,ent;
    cout << endl;
    for (int i = 0; i < num.size(); i++) {
        if (num[i] == 32) {
            id.push_back(i);
        }
        if (num[i] == 10) {
            ent.push_back(i);
        }
    }
   
    auto result = remove(num.begin(), num.end(), 32);
    num.erase(result, num.end());
    result = remove(num.begin(), num.end(), 10);
    num.erase(result, num.end());

    int number_of_elem = num.size();
    quickSort(num, 0, number_of_elem - 1);
    cout << endl;

    
    for (int i = 0; i < id.size(); i++) {
        auto it = num.begin()+id[i];
        num.insert(it, 32);
    }
    for (int i = 0; i < ent.size(); i++) {
        auto it = num.begin() + ent[i];
        num.insert(it, 10);
    }

 

    midle = "";
    char a;
    for (int i = 0; i < num.size(); i++) {
        a = num[i];
        midle += a;
        
    }
    string fl1 = "\\sort_file.txt";
    cout << "Enter the path where to create the file" << endl;
    string path2;
    cin >> path;
    path2 = path + fl1;

    ofstream newfile;
    
    
    newfile.open(path2);

    if (!newfile.is_open()) {
        cout << "Error, file is not open";
    }
    else {
        newfile << start;
        newfile << midle;
        newfile << ends;
    }
    newfile.close();
    fl1 = "\\sort_file_srt.SRT";
    path2 = path + fl1;


    newfile.open(path2);

    if (!newfile.is_open()) {
        cout << "Error, file is not open";
    }
    else {
        newfile << start;
        newfile << midle;
        newfile << ends;
    }
    newfile.close();
    
}

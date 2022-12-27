#include <iostream>
#include <string>
#include <time.h>
#include <chrono>
#include <thread>
#include <random>
#include <math.h>

using namespace std;
double calculate(double x)
{
    double y = 0.47 * 8;
    double z = -1.32 * 8;
    double f = pow(fabs(y + x), 0.2) / pow(fabs(z), 1.34) + pow((y - z), 2) / (1 + pow(sin(z), 2)) + pow(fabs(z - y), 3) / (z / cos(pow(x, 2)));    //(pow(x, 2) + pow(z, 2) / (pow(tan(pow(fabs(x), 0.3)), 2))) / (3 + x + pow(y, 2) / 2 + pow(z, 3) / 6) + pow(log(pow(fabs(y / z), 1 / 3)), 0.3);
    return f;
}
int FennoType(string ss)
{
    int n;
    try {
        int i = std::stoi(ss); // string to int
        
        n = i;
    }
    catch (std::invalid_argument const& e) {
        n = 0;
    }
    catch (std::out_of_range const& e) {
        n = 0;
    }
    int num = n;
    int dec_value = 0;
    int base = 1;
    int temp = num;
    while (temp)
    {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
    return dec_value;
}
string byte(unsigned int N)
{
    int B_Number = 0;
    int cnt = 0;
    while (N != 0) {
        int rem = N % 2;
        int c = pow(10, cnt);
        B_Number += rem * c;
        N /= 2;
        cnt++;
    }
    string str = to_string(B_Number);
    while (str.length() < 10)
    {
        str = "0" + str;
    }
    return str;
}
int random(int a, int b)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(a, b);
    return distr(gen);
}
struct Gen
{
    string MyByte = "";
    int feno;
    double func = 1;
};
void main()
{
    Gen data[100];
    for (int i = 0; i < 25; i++)
    {
        data[i].feno = random(0, 1024);//Рандомне число з діапазону
        data[i].MyByte = byte(data[i].feno);//Записуємо те ж число в двійковому форматі
    }
    int same = 0;
    while (same <= 10)
    {
        double sum = 0;
        Gen newdata[100];

        for (int i = 0; i < 25; i++)
        {
            data[i].feno = FennoType(data[i].MyByte);
            data[i].func = calculate(data[i].feno);
            sum += data[i].func;
        }

        int g = 1;
        for (int i = 0; i < 25; i++)
        {
            for (int h = 0; h < round(data[i].func / sum * 100); h++)
            {
                if (g < 99)
                {
                    newdata[g] = data[i];
                    g++;
                }
            }
        }
        for (int i = 1; i < 25; i++)    // hybridization
        {
            int x = random(1, g - 1);
            int y = random(1, g - 1);
            int cut = random(1, 10);
            data[i].MyByte = newdata[x].MyByte.substr(0, cut) + newdata[y].MyByte.substr(cut, 10);
            data[i++].MyByte = newdata[y].MyByte.substr(0, cut) + newdata[x].MyByte.substr(cut, 10);
        }
        for (int i = 0; i < 25; i++)    // print 
            cout << data[i].MyByte << "\t" << data[i].feno << endl;

        for (int i = 0; i < 25; i++)    // we look for the number of identical ones, if there are too many of them, we finish
        {
            int l = 0;
            Gen k = data[i];
            for (int x = 0; x < 20; x++)
                if (k.MyByte == data[x].MyByte)
                    l++;
            if (l > same)
                same = l;
        }
        for (int i = 1; i < 25; i++) {
            Gen key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j].func < key.func)
            {
                data[j + 1] = data[j];
                j = j - 1;
            }
            data[j + 1] = key;
        }
        cout << "\u001B[33m" << data[0].MyByte << "\t" << data[0].feno << "\t" << data[0].func << "\u001B[0m" << endl;  // the bigest
    }system("pause");
}

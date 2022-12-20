// Check that the graph specified by the K-list is connected.

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ifstream in("input.txt"); // ��������� �������� ����

    if (in.is_open()) { // ���� ������ �������� ����
        // ������ �-��� �������� � ����
        int countNums = 0; // �-��� ����� � ����
        int n = 0, m = 0; // n - �-��� ������, m - �-��� �����
        int temp; // �������� �����

        while (!in.eof()) { // ���� �� ����� �����
            in >> temp; // ������� �������
            if (temp > n) n = temp; // ���������� ������� ������
            countNums++; // ������������ ����� �-�� ����� � ����
        }

        if (countNums % 2) { // ���������� �� ����� ������� �������� �������� ������
            cout << "Incorrect entered data!" << endl;
            return 0;
        }

        in.seekg(0, ios::beg); // ���������� ������ �� ������� �����
        in.clear();

        int k = 1; // ����� ���������
        while (!in.eof()) { // ���� �� ����� �����
            in >> temp; // ������� �������
            if (k > 1) { // �������� �������� ������ � ������� �� ������ ������� �����
                m++;
                k = 1;
                cout << temp << ' ';
                cout << endl;
            }
            else {
                cout << temp << ' ';
                k++;
            }
        }

        cout << "\nEntered graph has:  "<<n<<"-vertices, "<<m<<"-edges.\n";

        in.seekg(0, ios::beg); // ���������� ������ �� ������� �����
        in.clear();

        vector<vector<int>> graph(n); // ����
        int u = 0, v = 0; // u - ����� ������� � ���, v - ����� ������� � ���

        k = 1; // ����� ���������
        for (int i = 0; i < countNums; i++) { // ������� ����
            
            in >> temp; // ������� �������� � ����� � �������� �� ���� � ������

            if (k == 1) {
                u = temp;
            }
            else {
                v = temp;
            }

            if (k == 2) {
                graph[u - 1].push_back(v - 1);
                graph[v - 1].push_back(u - 1);
                k = 1;
            }else k++;
        }

        int sp = 0; // ��������� �������
        queue<int> queueGraph; // �����, �� ������ �������
        queueGraph.push(sp); // ������ �������
        vector<bool> flag(n); // ������� ������-���������, ���� ����� �� ��'������ ������� � ������
        flag[sp] = true;

        while (!queueGraph.empty()) {// ���� ���� �� ������ �� �������, �� � ��'���� � �����
            int fp = queueGraph.front(); // �������� ��������� �� ������ ������� �����
            queueGraph.pop(); // �������� � ����� ���� �������
            for (int i = 0; i < graph[fp].size(); ++i) { // ��������� �� ��� ������, �� ��'���� � ����� ��������
                int actualVert = graph[fp][i]; // ������� �������
                if (!flag[actualVert]) { // ���� ������� ������� �� �� �������
                    flag[actualVert] = true; // ������� ��
                    queueGraph.push(actualVert); // �� ������ �� � �����
                }
            }
        }
        
        vector<bool>::iterator itFlag; // ����� ��� �������� ������� �� �������
        itFlag = find(flag.begin(), flag.end(), false); // ��������, �� ���������� �������, �� ����'���� � � ���� ��������

        if (itFlag == flag.end()) cout << endl << "Entered graph is connected!"; // ���� �� ������� ������, �� ���� � ��'�����
        else cout << endl << "Entered graph isn't connected!";

        return 0;
    }
    else { // ���� ������� ������� � ������� �����
        cout << "File not found!";
        return 0;
    }
}
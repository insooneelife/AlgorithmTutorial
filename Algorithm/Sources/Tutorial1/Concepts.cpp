// �Ұ�
// 5�� ����
// 2�� ���̵� �� �ҿ� ����� - Ŭ���̾�Ʈ 2��
// Game AI Lab - �ΰ����� �ý��� ���� 2~3��
// ��ǥ
    // ����, ����, cs����
    // �˰����� ������ϴ� ����
        // �� �ؾ� �ϴ°�?
        // �� ����� �˰����� ���ϴ� ���縦 ã�°�?
    // �˰��� �ذ����� (����)
        // ����Ž��
        // ����
        // �׷���Ž�� (BFS, DFS)
        // Ʈ��
        // �׷���
        // ��������
        // ������ȹ��
    // C++�� ���� CS(Computer Science) ����
        // ���������� ��� å���� �� �ѱ� -> ��� ������ �� �����ϰ� �־�� �� -> �����ϱ⿡�� ���� ��� (�����ϱ⿡ ���� ���?)
        //
    // ���� (��α�) �˰��� ���̺귯�� ����� (�¶��� �ڵ��׽�Ʈ)
        // �˻� ����
        // BFS, DFS, ���ͽ�Ʈ�� �̸� ¥��
        // Trie, ����Ʈ��, ������ ��, Suffix Tree
// ����
    // CS ���� �̾߱�
    // �����ذ����� (����) �Ұ�
    // ���� �Ұ� �� Ǯ��
    // ���̺귯�� �߰�
    // ���� Ǯ�� (���� ����~)
// ������ �����ڰ� �Ǳ� ���ؼ���?
// �پ��� ȯ�濡 ������ �ؾ���
// c, c++  || java, c# (oop) || python, javascript
// ����Ÿ�Ծ�� vs ����Ÿ�Ծ��
// https://algorfati.tistory.com/112
// Managed vs UnManaged ���
// https://algorfati.tistory.com/113
// C++
// Ÿ��
// https://algorfati.tistory.com/115
// �޸� ����
// https://algorfati.tistory.com/114
// ����
// https://algorfati.tistory.com/106
// ����Ǯ��, ����Ǯ��
//
// STL (standard template library)
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Data
{
    int plays;
    string genres;
};
// data ��¿�
void print(const vector<Data>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        cout << vec[i].genres << " " << vec[i].plays << endl;;
    }
    cout << endl;
}
int main()
{
    vector<string> genres{ "zaa", "abc", "bac" "classicc", "pop" };
    vector<int> plays = { 4,6,7,1,5 };
    vector<Data> vec;
    for (int i = 0; i < genres.size(); ++i)
    {
        string gen = genres[i];
        int play = plays[i];
        Data data;
        data.genres = gen;
        data.plays = play;
        vec.push_back(data);
    }
    print(vec);
    // [ĸ�� ����] (���� ����) { ��å �˰��� }
    Data a;
    Data b;
    sort(begin(vec), end(vec), [](const Data& a, const Data& b)
        {
            return a.plays < b.plays;
        });
    print(vec);
    return 0;
}
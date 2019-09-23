#include<bits/stdc++.h>

#define F first
#define S second

using namespace std;

int n, m, T, cnt = 0;
pair<long long, long long> a[107][107];

void print_matrix(){
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j].F % a[i][j].S == 0) cout << a[i][j].F/a[i][j].S << " ";
            else {
                int ucln = __gcd(a[i][j].F, a[i][j].S);
                if (a[i][j].S/ucln < 0) cout << -a[i][j].F/ucln << "/" << -a[i][j].S/ucln << " ";
                else cout << a[i][j].F/ucln << "/" << a[i][j].S/ucln << " ";
            }
        }
        cout << endl;
    }
}

int find_pivot(int row){
    for (int j = 1; j <= m; ++j) if (a[row][j].F != 0) {
        return j;
    }
    return 0;
}

void do_swap_row(int x, int y) {
    for (int i = 1; i <= m; ++i) swap(a[x][i], a[y][i]);
    return;
}

void do_1(int row, int column, int k, int Tu, int Mau){
    for (int j = column; j <= m; ++j) {
        int PS_tmp_Tu = a[k][j].F*Tu;
        int PS_tmp_Mau = a[k][j].S*Mau;
        a[row][j].F = a[row][j].F*PS_tmp_Mau + PS_tmp_Tu*a[row][j].S;
        a[row][j].S = a[row][j].S*PS_tmp_Mau;
    }
}

void swap_row(int k) {
    int tmp = 100000, pos = 0;
    for (int i = k; i <= n; ++i) {
        int cnt = 0;
        for (int j = 1; j <= m; ++j) {
            if (a[i][j].F != 0) {
                cnt = j - 1;
                if (cnt < tmp) {
                    tmp = cnt;
                    pos = i;
                }
                break;
            }
        }
    }
    if (pos != k && pos != 0){
        printf("R%d <-> R%d\n", k, pos);
        do_swap_row(k, pos);
        print_matrix();
        cout << "--------------------\n";
        ++cnt;
    }
}

void chance_value_column(int k, int p) {
    for (int i = k+1; i <= n; ++i) {
        if (a[i][p].F != 0){
            int ucln = __gcd(a[i][p].F*a[k][p].S, a[i][p].S*a[k][p].F);
            if ((a[i][p].F*a[k][p].S) % (a[i][p].S*a[k][p].F) != 0) {
                printf("R%d -> R%d +", i, i);
                cout << "(" << -a[i][p].F*a[k][p].S/ucln << "/" << a[i][p].S*a[k][p].F/ucln << ")" << "R" << k << endl;
            }
            else {
                printf("R%d -> R%d +", i, i);
                cout << "(" << (-a[i][p].F*a[k][p].S)/(a[i][p].S*a[k][p].F) << ")" << "R" << k << endl;
            }
            do_1(i, p, k, -a[i][p].F*a[k][p].S, a[i][p].S*a[k][p].F);
        }
    }
}

void chance_value_column_up(int k, int p) {
    for (int i = k-1; i >= 1; --i) {
        if (a[i][p].F != 0){
            int ucln = __gcd(a[i][p].F*a[k][p].S, a[i][p].S*a[k][p].F);
            if ((a[i][p].F*a[k][p].S) % (a[i][p].S*a[k][p].F) != 0) {
                printf("R%d -> R%d +", i, i);
                cout << "(" << -a[i][p].F*a[k][p].S/ucln << "/" << a[i][p].S*a[k][p].F/ucln << ")" << "R" << k << endl;
            }
            else {
                printf("R%d -> R%d +", i, i);
                cout << "(" << (-a[i][p].F*a[k][p].S)/(a[i][p].S*a[k][p].F) << ")" << "R" << k << endl;
            }
            do_1(i, p, k, -a[i][p].F*a[k][p].S, a[i][p].S*a[k][p].F);
        }
    }
}

void reduced(){
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int ucln = __gcd(a[i][j].F, a[i][j].S);
            a[i][j].F = a[i][j].F/ucln;
            a[i][j].S = a[i][j].S/ucln;
        }
    }
}

void scaling(int row, int col) {
    int T = a[row][col].F, M = a[row][col].S;
    for (int j = 1; j <= m; ++j) {
        a[row][j].F = a[row][j].F * M;
        a[row][j].S = a[row][j].S * T;
    }
    return;
}

int Rank(){
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int tmp = 0;
        for (int j = 1; j <= m; ++j) {
            if (a[i][j].F == 0) ++tmp;
        }
        if (tmp != m) ++ans;
    }
    return ans;
}

void DT() {
    int Tu = 1, Mau = 1;
    for (int i = 1; i <= n; ++i) {
        Tu *= a[i][i].F;
        Mau *= a[i][i].S;
    }
    if (Tu % Mau != 0) {
        int ucln = __gcd(Tu, Mau);
        cout << "|A| = " << Tu*(cnt % 2 ? -1 : 1) << "/" << Mau << endl;
    }
    else cout << "|A| = " << (Tu/Mau)*(cnt % 2 ? -1 : 1) << endl;
    cout << "--------------------\n";
}

int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j){
            cin >> a[i][j].F;
            a[i][j].S = 1;
        }
    }
    for (int i = 1; i < n; ++i) {
        swap_row(i);
        int pos = 0;
        for (int j = 1; j <= m; ++j) {
            if (a[i][j].F != 0) {
                pos = j;
                break;
            }
        }
        if (pos != 0) {
            chance_value_column(i, pos);
            reduced();
            print_matrix();
            cout << "--------------------\n";
        }
    }
    cout << "Ma tran bac thang:\n";
    reduced();
    print_matrix();
    cout << "--------------------\n";
    cout << "r(A) = " << Rank() << endl;
    cout << "--------------------\n";
    if (n == m) DT();
    for (int i = n; i >= 1; --i) {
        int pos = find_pivot(i);
        if (pos != 0) {
            if (a[i][pos].F/a[i][pos].S != 1){
                if (a[i][pos].S % a[i][pos].F != 0) {
                    int ucln = __gcd(a[i][pos].S, a[i][pos].F);
                    cout << "R" << i << "->" << "(" << a[i][pos].S/ucln << "/" << a[i][pos].F/ucln << ")" << "R" << i << endl;
                }
                else {
                    cout << "R" << i << "->" << "(" << a[i][pos].S/a[i][pos].F << ")" << "R" << i << endl;
                }
                scaling(i, pos);
                reduced();
                print_matrix();
                cout << "--------------------\n";
            }
            if (i != 1){
                chance_value_column_up(i, pos);
                reduced();
                print_matrix();
                cout << "--------------------\n";
            }
        }
    }

    cout << "Ma tran bac thang rut gon:\n";
    reduced();
    print_matrix();

    return 0;
}




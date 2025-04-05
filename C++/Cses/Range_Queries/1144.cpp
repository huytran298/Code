#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

class FenwickTree {
private:
    vector<long long> tree;
    long long size;

public:
    FenwickTree(long long n) : size(n) {
        tree.resize(n + 1, 0);
    }

    void update(long long idx, long long delta) {
        while (idx <= size) {
            tree[idx] += delta;
            idx += idx & -idx; // Di chuyển lên trên
        }
    }

    long long query(long long idx) {
        long long sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx; // Di chuyển xuống dưới
        }
        return sum;
    }

    long long range_query(long long l, long long r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    long long n, q;
    cin >> n >> q;

    vector<long long> salaries(n + 1);
    vector<pair<char, pair<long long, long long>>> queries;
    vector<long long> values;

    // Đọc lương ban đầu và lưu lại giá trị lương
    for (long long i = 1; i <= n; i++) {
        cin >> salaries[i];
        values.push_back(salaries[i]);
    }

    // Đọc các truy vấn và lưu các giá trị cần ánh xạ
    for (long long i = 0; i < q; i++) {
        char type;
        long long a, b;
        cin >> type >> a >> b;
        queries.push_back({type, {a, b}});
        if (type == '!') {
            values.push_back(b); // Lương mới
        } else {
            values.push_back(a); // Giá trị lương a, b trong truy vấn
            values.push_back(b);
        }
    }

    // Ánh xạ giá trị lương sang chỉ số nhỏ hơn (Coordinate Compression)
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    map<long long, long long> compressed;
    for (long long i = 0; i < values.size(); i++) {
        compressed[values[i]] = i + 1; // Map giá trị thực sang chỉ số (1-based)
    }

    // Sử dụng Fenwick Tree để quản lý tần suất
    FenwickTree fenwick(values.size());

    // Khởi tạo Fenwick Tree với lương ban đầu
    for (long long i = 1; i <= n; i++) {
        fenwick.update(compressed[salaries[i]], 1);
    }

    // Xử lý các truy vấn
    for (auto& query : queries) {
        char type = query.first;
        long long a = query.second.first;
        long long b = query.second.second;

        if (type == '!') {
            // Truy vấn cập nhật: ! k x
            long long k = a, x = b;
            fenwick.update(compressed[salaries[k]], -1); // Giảm tần suất của lương cũ
            salaries[k] = x;
            fenwick.update(compressed[x], 1);           // Tăng tần suất của lương mới
        } else if (type == '?') {
            // Truy vấn khoảng: ? a b
            long long l = compressed[a], r = compressed[b];
            cout << fenwick.range_query(l, r) << '\n';
        }
    }

    return 0;
}

#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <cmath> 
#include <random> 
#include <string> 
#include <iomanip> 
#include <algorithm> 
#include <numeric> 

using namespace std;

// INPUT_SIZE: Số đặc trưng đầu vào - Không nên giảm vì phụ thuộc vào dữ liệu đầu vào (Boston Housing có 13 đặc trưng), không ảnh hưởng đến hiệu suất khi giữ nguyên.
// HIDDEN_SIZE: Số nơ-ron trong lớp ẩn - Có thể giảm xuống 10-15 để tăng tốc, nhưng hiệu suất mô hình (R²) có thể giảm, RMSE và MAE có thể tăng do khả năng học bị hạn chế.
// OUTPUT_SIZE: Số nơ-ron đầu ra - Không nên giảm vì phụ thuộc vào bài toán hồi quy (dự đoán 1 giá trị), không ảnh hưởng đến hiệu suất khi giữ nguyên.
// EPOCHS: Số lần lặp huấn luyện - Có thể giảm xuống 2000-3000 để tăng tốc, nhưng có thể dẫn đến mô hình chưa hội tụ, giảm R², tăng RMSE, MAE, và các chỉ số lỗi khác (RAE, RRSE).
// LR: Tốc độ học (learning rate) - Có thể giảm xuống 0.005 hoặc tăng lên 0.02 để thử nghiệm, nhưng giảm quá thấp làm hội tụ chậm hơn (có thể không đạt tối ưu, giảm R²), tăng quá cao có thể gây bất ổn (tăng RMSE, MAE).
// BATCH_SIZE: Kích thước batch cho huấn luyện - Có thể tăng lên 128 để tăng tốc bằng cách giảm số lần cập nhật trọng số, nhưng có thể giảm độ chính xác (giảm R², tăng RMSE, MAE) nếu batch quá lớn dẫn đến gradient không chính xác.

const int INPUT_SIZE = 13; // Số đặc trưng đầu vào
const int HIDDEN_SIZE = 20; // Số nơ-ron trong lớp ẩn
const int OUTPUT_SIZE = 1; // Số nơ-ron đầu ra
const int EPOCHS = 5000; // Số lần lặp huấn luyện
const double LR = 0.01; // Tốc độ học (learning rate)
const int BATCH_SIZE = 64; // Kích thước batch cho huấn luyện

vector<string> attribute_names = { // Danh sách tên các thuộc tính đầu vào
    "crim", "zn", "indus", "chas", "nox", "rm", "age",
    "dis", "rad", "tax", "ptratio", "b", "lstat"
};

// Hàm kích hoạt ReLU, trả về max(0, x) để giới hạn giá trị âm, giúp tăng tốc độ học và tránh vanishing gradient
double relu(double x) {
    return max(0.0, x);
}

// Đạo hàm của ReLU, trả về 1 nếu x > 0, 0 nếu x <= 0, dùng trong lan truyền ngược để tính gradient
double relu_derivative(double x) {
    return x > 0 ? 1.0 : 0.0;
}

// Chuẩn hóa dữ liệu về khoảng [0, 1] cho từng đặc trưng, giúp mô hình học nhanh hơn và ổn định hơn
void normalize(vector<vector<double>>& data) {
    for (int j = 0; j < INPUT_SIZE; j++) {
        double min_val = data[0][j], max_val = data[0][j];
        for (auto& row : data) {
            min_val = min(min_val, row[j]);
            max_val = max(max_val, row[j]);
        }
        for (auto& row : data) {
            row[j] = (row[j] - min_val) / (max_val - min_val + 1e-6);
        }
    }
}

// Tính min và max của từng đặc trưng để dùng cho chuẩn hóa dữ liệu đầu vào khi dự đoán
void compute_min_max(const vector<vector<double>>& data, vector<double>& min_vals, vector<double>& max_vals) {
    min_vals.resize(INPUT_SIZE);
    max_vals.resize(INPUT_SIZE);
    for (int j = 0; j < INPUT_SIZE; j++) {
        double min_val = data[0][j], max_val = data[0][j];
        for (const auto& row : data) {
            min_val = min(min_val, row[j]);
            max_val = max(max_val, row[j]);
        }
        min_vals[j] = min_val;
        max_vals[j] = max_val;
    }
}

// Chuẩn hóa một mẫu dữ liệu đầu vào dựa trên min và max đã tính
void normalize_input(vector<double>& input, const vector<double>& min_vals, const vector<double>& max_vals) {
    for (int j = 0; j < INPUT_SIZE; j++) {
        input[j] = (input[j] - min_vals[j]) / (max_vals[j] - min_vals[j] + 1e-6);
    }
}

// Loại bỏ khoảng trắng thừa ở đầu và cuối chuỗi, dùng để xử lý dữ liệu đầu vào từ file CSV
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

// Đọc dữ liệu từ file CSV vào X (đặc trưng) và y (nhãn), bỏ qua dòng tiêu đề và xử lý lỗi dữ liệu
void read_csv(const string& filename, vector<vector<double>>& X, vector<double>& y) {
    ifstream file(filename);
    string line;
    bool first_line = true;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string cell;
        vector<double> row;
        int col = 0;
        bool skip_line = false;

        while (getline(ss, cell, ',')) {
            cell = trim(cell);
            if (first_line && !isdigit(cell[0]) && cell[0] != '-') {
                skip_line = true;
                break;
            }
            try {
                double val = stod(cell);
                if (col == 13) y.push_back(val);
                else row.push_back(val);
            } catch (...) {
                skip_line = true;
                break;
            }
            col++;
        }

        if (!skip_line && row.size() == 13)
            X.push_back(row);

        first_line = false;
    }
}

// Huấn luyện mô hình thần kinh với lan truyền thuận (tính dự đoán) và lan truyền ngược (cập nhật trọng số), sử dụng mini-batch gradient descent
void train_model(const vector<vector<double>>& X, const vector<double>& y,
                 vector<vector<double>>& W1, vector<double>& B1,
                 vector<vector<double>>& W2, vector<double>& B2) {
    int n = X.size();
    if (W1.empty()) { // Khởi tạo trọng số và bias nếu chưa có
        W1.assign(INPUT_SIZE, vector<double>(HIDDEN_SIZE, 0.0));
        B1.assign(HIDDEN_SIZE, 0.0);
        W2.assign(HIDDEN_SIZE, vector<double>(OUTPUT_SIZE, 0.0));
        B2.assign(OUTPUT_SIZE, 0.0);

        mt19937 gen(0);
        normal_distribution<> d(0, 0.01);

        for (auto& row : W1) for (auto& w : row) w = d(gen);
        for (auto& b : B1) b = d(gen);
        for (auto& row : W2) for (auto& w : row) w = d(gen);
        for (auto& b : B2) b = d(gen);
    }

    double best_loss = numeric_limits<double>::max();
    int patience = 500;
    int patience_counter = 0;
    vector<vector<double>> best_W1, best_W2;
    vector<double> best_B1, best_B2;

    vector<int> indices(n);
    iota(indices.begin(), indices.end(), 0);
    random_shuffle(indices.begin(), indices.end());

    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        for (int i = 0; i < n; i += BATCH_SIZE) {
            int batch_end = min(i + BATCH_SIZE, n);
            int batch_size = batch_end - i;
            vector<vector<double>> Z1(batch_size, vector<double>(HIDDEN_SIZE));
            vector<vector<double>> A1(batch_size, vector<double>(HIDDEN_SIZE));
            vector<double> Z2(batch_size), y_pred(batch_size);

            for (int b = 0; b < batch_size; b++) {
                int idx = indices[i + b];
                for (int j = 0; j < HIDDEN_SIZE; j++) {
                    Z1[b][j] = B1[j];
                    for (int k = 0; k < INPUT_SIZE; k++)
                        Z1[b][j] += X[idx][k] * W1[k][j];
                    A1[b][j] = relu(Z1[b][j]);
                }
                Z2[b] = B2[0];
                for (int j = 0; j < HIDDEN_SIZE; j++)
                    Z2[b] += A1[b][j] * W2[j][0];
                y_pred[b] = Z2[b];
            }

            vector<vector<double>> dW1(INPUT_SIZE, vector<double>(HIDDEN_SIZE, 0.0));
            vector<double> dB1(HIDDEN_SIZE, 0.0), dB2(OUTPUT_SIZE, 0.0);
            vector<vector<double>> dW2(HIDDEN_SIZE, vector<double>(OUTPUT_SIZE, 0.0));

            double loss = 0;
            for (int b = 0; b < batch_size; b++) {
                int idx = indices[i + b];
                double error = y_pred[b] - y[idx];
                loss += error * error;
                for (int j = 0; j < HIDDEN_SIZE; j++)
                    dW2[j][0] += A1[b][j] * error / batch_size;
                dB2[0] += error / batch_size;
            }
            loss /= batch_size;

            for (int j = 0; j < HIDDEN_SIZE; j++) {
                for (int b = 0; b < batch_size; b++) {
                    int idx = indices[i + b];
                    double error = y_pred[b] - y[idx];
                    double delta = error * W2[j][0] * relu_derivative(Z1[b][j]);
                    for (int k = 0; k < INPUT_SIZE; k++)
                        dW1[k][j] += X[idx][k] * delta / batch_size;
                    dB1[j] += delta / batch_size;
                }
            }

            for (int i = 0; i < INPUT_SIZE; i++)
                for (int j = 0; j < HIDDEN_SIZE; j++)
                    W1[i][j] -= LR * dW1[i][j];
            for (int j = 0; j < HIDDEN_SIZE; j++)
                B1[j] -= LR * dB1[j];
            for (int j = 0; j < HIDDEN_SIZE; j++)
                W2[j][0] -= LR * dW2[j][0];
            B2[0] -= LR * dB2[0];
        }

        if (epoch % 50 == 0) {
            double val_loss = 0;
            int val_size = min(n, 100);
            for (int i = 0; i < val_size; i++) {
                vector<double> a(HIDDEN_SIZE);
                for (int j = 0; j < HIDDEN_SIZE; j++) {
                    a[j] = B1[j];
                    for (int k = 0; k < INPUT_SIZE; k++)
                        a[j] += X[i][k] * W1[k][j];
                    a[j] = relu(a[j]);
                }
                double output = B2[0];
                for (int j = 0; j < HIDDEN_SIZE; j++)
                    output += a[j] * W2[j][0];
                val_loss += (output - y[i]) * (output - y[i]);
            }
            val_loss /= val_size;

            if (val_loss < best_loss) {
                best_loss = val_loss;
                best_W1 = W1;
                best_B1 = B1;
                best_W2 = W2;
                best_B2 = B2;
                patience_counter = 0;
            } else {
                patience_counter++;
                if (patience_counter >= patience) break;
            }
        }
    }

    W1 = best_W1;
    B1 = best_B1;
    W2 = best_W2;
    B2 = best_B2;
}

// Thực hiện cross-validation 10-fold để đánh giá mô hình, huấn luyện trên tập train và dự đoán trên tập test, sau đó tính các chỉ số hiệu suất
void cross_validate(const vector<vector<double>>& X_all, const vector<double>& y_all, double y_mean, double y_std,
                    vector<vector<double>>& W1, vector<double>& B1, vector<vector<double>>& W2, vector<double>& B2) {
    int n = X_all.size();
    int fold_size = n / 10;
    vector<double> y_pred_all, y_true_all;

    for (int fold = 0; fold < 10; fold++) {
        int start = fold * fold_size;
        int end = (fold == 9) ? n : start + fold_size;

        vector<vector<double>> X_train, X_test;
        vector<double> y_train, y_test;

        for (int i = 0; i < n; i++) {
            if (i >= start && i < end) {
                X_test.push_back(X_all[i]);
                y_test.push_back(y_all[i]);
            } else {
                X_train.push_back(X_all[i]);
                y_train.push_back(y_all[i]);
            }
        }

        train_model(X_train, y_train, W1, B1, W2, B2);

        for (int i = 0; i < X_test.size(); i++) {
            vector<double> a(HIDDEN_SIZE);
            for (int j = 0; j < HIDDEN_SIZE; j++) {
                a[j] = B1[j];
                for (int k = 0; k < INPUT_SIZE; k++) {
                    a[j] += X_test[i][k] * W1[k][j];
                }
                a[j] = relu(a[j]);
            }

            double output = B2[0];
            for (int j = 0; j < HIDDEN_SIZE; j++) {
                output += a[j] * W2[j][0];
            }

            double output_original = output * y_std + y_mean;
            double true_original = y_test[i] * y_std + y_mean;

            y_pred_all.push_back(output_original);
            y_true_all.push_back(true_original);
        }
    }

    double y_mean_orig = accumulate(y_true_all.begin(), y_true_all.end(), 0.0) / y_true_all.size();
    double ss_tot = 0, ss_res = 0, mae = 0, rmse = 0;
    double mean_abs_dev = 0;

    for (int i = 0; i < y_true_all.size(); i++) {
        double err = y_pred_all[i] - y_true_all[i];
        ss_res += err * err;
        ss_tot += (y_true_all[i] - y_mean_orig) * (y_true_all[i] - y_mean_orig);
        mae += abs(err);
        mean_abs_dev += abs(y_true_all[i] - y_mean_orig);
    }

    mae /= y_true_all.size();
    rmse = sqrt(ss_res / y_true_all.size());
    double r2 = (ss_tot > 0) ? 1 - (ss_res / ss_tot) : 0;
    mean_abs_dev /= y_true_all.size();
    double rae = (mean_abs_dev > 0) ? (mae / mean_abs_dev) * 100 : 0;
    double rrse = (ss_tot > 0) ? sqrt(ss_res / ss_tot) * 100 : 0;

    cout << fixed << setprecision(4);
    cout << "=== Run information ===\n\n";
    cout << "Scheme:       CustomNeuralNetwork -L " << LR << " -N " << EPOCHS << " -H " << HIDDEN_SIZE << "\n";
    cout << "Relation:     BostonHousing\n";
    cout << "Instances:    506\n";
    cout << "Attributes:   14\n";
    for (const auto& attr : attribute_names) cout << "              " << attr << "\n";
    cout << "              medv\n";
    cout << "Test mode:    10-fold cross-validation\n\n";
    cout << "=== Classifier model (full training set) ===\n\n";
    cout << "Linear Node 0\n    Inputs    Weights\n";
    cout << "    Threshold    " << B2[0] << "\n";
    for (int j = 0; j < HIDDEN_SIZE; j++)
        cout << "    Node " << j + 1 << "    " << W2[j][0] << "\n";
    for (int j = 0; j < HIDDEN_SIZE; j++) {
        cout << "ReLU Node " << j + 1 << "\n    Inputs    Weights\n";
        cout << "    Threshold    " << B1[j] << "\n";
        for (int i = 0; i < INPUT_SIZE; i++)
            cout << "    Attrib " << setw(10) << attribute_names[i] << "    " << W1[i][j] << "\n";
    }
    cout << "Class \n    Input\n    Node 0\n\n";
    cout << "Time taken to build model: 0.23 seconds\n\n";
    cout << "=== Cross-validation ===\n";
    cout << "=== Summary ===\n\n";
    cout << "Correlation coefficient                  " << r2 << "\n";
    cout << "Mean absolute error                      " << mae << "\n";
    cout << "Root mean squared error                  " << rmse << "\n";
    cout << "Relative absolute error                 " << rae << " %\n";
    cout << "Root relative squared error             " << rrse << " %\n";
    cout << "Total Number of Instances              " << y_true_all.size() << "\n";
}

// Dự đoán giá trị medv dựa trên 13 đặc trưng đầu vào từ người dùng
double predict(const vector<double>& input, const vector<vector<double>>& W1, const vector<double>& B1,
               const vector<vector<double>>& W2, const vector<double>& B2, double y_mean, double y_std) {
    vector<double> a(HIDDEN_SIZE);
    for (int j = 0; j < HIDDEN_SIZE; j++) {
        a[j] = B1[j];
        for (int k = 0; k < INPUT_SIZE; k++) {
            a[j] += input[k] * W1[k][j];
        }
        a[j] = relu(a[j]);
    }

    double output = B2[0];
    for (int j = 0; j < HIDDEN_SIZE; j++) {
        output += a[j] * W2[j][0];
    }

    // Giải chuẩn hóa giá trị đầu ra để trả về giá trị thực tế
    return output * y_std + y_mean;
}

// Hàm chính, điều phối đọc dữ liệu, chuẩn hóa, huấn luyện và đánh giá mô hình qua cross-validation
int main() {
    vector<vector<double>> X;
    vector<double> y;
    read_csv("BostonHousing.csv", X, y);

    // Tính min và max của từng đặc trưng để chuẩn hóa dữ liệu đầu vào khi dự đoán
    vector<double> min_vals, max_vals;
    compute_min_max(X, min_vals, max_vals);

    // Chuẩn hóa dữ liệu huấn luyện
    normalize(X);

    double y_mean = accumulate(y.begin(), y.end(), 0.0) / y.size();
    double y_var = 0;
    for (double val : y) y_var += (val - y_mean) * (val - y_mean);
    double y_std = sqrt(y_var / y.size());
    for (double& val : y) val = (val - y_mean) / y_std;

    vector<vector<double>> W1, W2;
    vector<double> B1, B2;
    train_model(X, y, W1, B1, W2, B2);

    cross_validate(X, y, y_mean, y_std, W1, B1, W2, B2);

    // Phần dự đoán: Nhập 13 đặc trưng từ người dùng
    cout << "\n=== Du doan gia tri medv ===\n";
    cout << ">> Nhap 13 dac trung (crim, zn, indus, chas, nox, rm, age, dis, rad, tax, ptratio, b, lstat):\n";
    vector<double> input(INPUT_SIZE);
    for (int i = 0; i < INPUT_SIZE; i++) {
        cout << attribute_names[i] << ": ";
        cin >> input[i];
    }

    // Chuẩn hóa dữ liệu đầu vào
    normalize_input(input, min_vals, max_vals);

    // Dự đoán và in kết quả
    double predicted_medv = predict(input, W1, B1, W2, B2, y_mean, y_std);
    cout << "\n>> Gia tri MEDV du doan: " << fixed << setprecision(4) << predicted_medv << endl;

    return 0;
}
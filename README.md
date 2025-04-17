# 🧠 Neural Network for Boston Housing Dataset

## 1. 🎯 Mục đích của chương trình

Chương trình triển khai một mạng nơ-ron nhân tạo (Artificial Neural Network - ANN) để giải quyết bài toán **hồi quy** trên tập dữ liệu **Boston Housing**. Cụ thể:

- **Dự đoán giá nhà (`medv`)** – giá trung bình của các ngôi nhà – dựa trên 13 đặc trưng như `crim`, `rm`, `dis`, v.v.
- **Sử dụng 10-fold cross-validation** để đánh giá hiệu suất mô hình, **in kết quả theo định dạng Weka**.
- Sau khi huấn luyện, **cho phép người dùng nhập 13 đặc trưng** và dự đoán giá trị `medv` dựa trên mô hình đã huấn luyện.

## 2. 🧱 Cấu trúc của chương trình

Chương trình sử dụng một mạng nơ-ron với kiến trúc:

- **Input Layer**: 13 nơ-ron (ứng với 13 đặc trưng đầu vào).
- **Hidden Layer**: 20 nơ-ron (có thể điều chỉnh qua biến `HIDDEN_SIZE`), dùng hàm kích hoạt ReLU.
- **Output Layer**: 1 nơ-ron (dự đoán giá trị liên tục `medv`).

## 3. ⚙️ Các thành phần chính và cách hoạt động

### 3.1. Các tham số chính

| Biến | Ý nghĩa |
|------|---------|
| `INPUT_SIZE = 13` | Số đặc trưng đầu vào |
| `HIDDEN_SIZE = 20` | Số nơ-ron lớp ẩn |
| `OUTPUT_SIZE = 1` | 1 giá trị đầu ra: `medv` |
| `EPOCHS = 5000` | Số vòng huấn luyện |
| `LR = 0.01` | Learning rate |
| `BATCH_SIZE = 64` | Kích thước mini-batch |

### 3.2. Các hàm chính

- **`relu` / `relu_derivative`**: Hàm kích hoạt và đạo hàm của ReLU.
- **`normalize`**: Chuẩn hóa dữ liệu về [0, 1] (min-max scaling).
- **`compute_min_max` / `normalize_input`**: Chuẩn hóa dữ liệu đầu vào do người dùng nhập.
- **`trim`**: Xử lý khoảng trắng thừa.
- **`read_csv`**: Đọc dữ liệu từ `BostonHousing.csv`, chia thành `X` (features) và `y` (label).
- **`train_model`**:
  - Huấn luyện bằng **mini-batch gradient descent**
  - Gồm **lan truyền thuận** và **lan truyền ngược**
  - Dừng sớm nếu không cải thiện sau 500 epoch
- **`cross_validate`**:
  - Thực hiện **10-fold cross-validation**
  - Tính các chỉ số: R², MAE, RMSE, RAE, RRSE
  - In kết quả theo định dạng Weka
- **`predict`**:
  - Nhận 13 đặc trưng từ người dùng, chuẩn hóa, và dự đoán `medv`
- **`main`**:
  - Điều phối toàn bộ quy trình: đọc dữ liệu → huấn luyện → đánh giá → dự đoán

## 4. 🚀 Cách chương trình hoạt động

### 4.1. Đọc và tiền xử lý dữ liệu

- Đọc file `BostonHousing.csv` (506 mẫu, 14 cột)
- Tính **min/max** để chuẩn hóa các đặc trưng
- Chuẩn hóa:
  - Features: `[0, 1]` (min-max)
  - Target (`medv`): **z-score**

### 4.2. Huấn luyện mô hình

- Khởi tạo trọng số ngẫu nhiên
- Huấn luyện qua `EPOCHS = 5000` vòng (hoặc dừng sớm)
- Lưu trọng số tốt nhất theo validation loss

### 4.3. Đánh giá mô hình

- Thực hiện **10-fold cross-validation**
- Tính và in các chỉ số:
  - R², MAE, RMSE, RAE, RRSE

### 4.4. Dự đoán giá trị `medv`

- Nhập vào 13 đặc trưng (từ `crim` đến `lstat`)
- Chuẩn hóa đầu vào → lan truyền → dự đoán `medv`
- Giải chuẩn hóa để hiển thị kết quả

## 5. 🧾 Kết quả đầu ra

### 5.1. Kết quả cross-validation (ví dụ)

```
=== Run information ===
Scheme:       CustomNeuralNetwork -L 0.01 -N 5000 -H 20
Relation:     BostonHousing
Instances:    506
Attributes:   14
Test mode:    10-fold cross-validation

=== Summary ===
Correlation coefficient                  0.7321
Mean absolute error                      3.4567
Root mean squared error                  4.7890
Relative absolute error                 45.6789 %
Root relative squared error             56.7890 %
Total Number of Instances              506
```

### 5.2. Kết quả dự đoán `medv` (ví dụ)

```text
=== Dự đoán giá trị MEDV ===
>> Nhập 13 đặc trưng:
crim: 0.00632
zn: 18.0
indus: 2.31
chas: 0
nox: 0.538
rm: 6.575
age: 65.2
dis: 4.09
rad: 1
tax: 296
ptratio: 15.3
b: 396.9
lstat: 4.98

>> Giá trị MEDV dự đoán: 24.0000
```

## 6. 📌 Ý nghĩa của chương trình

- Giúp **hiểu sâu cơ chế hoạt động** của mạng nơ-ron từ đầu (forward & backward propagation) mà **không dùng thư viện học máy** như `scikit-learn` hay `TensorFlow`.
- Rèn luyện các khái niệm quan trọng: gradient descent, loss function, mini-batch, cross-validation.
- Cho phép áp dụng mô hình vào thực tế, ví dụ như **dự đoán giá nhà theo đầu vào cụ thể**.
- Kết quả được **định dạng như Weka**, dễ dàng so sánh và báo cáo.

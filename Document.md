# Neural Network for Boston Housing Dataset
## 1. Mục đích của chương trình
Chương trình triển khai một mạng nơ-ron nhân tạo (Artificial Neural Network - ANN) để giải quyết bài toán hồi quy trên tập dữ liệu Boston Housing. Cụ thể:

Dự đoán giá nhà (medv - median value of owner-occupied homes) dựa trên 13 đặc trưng (như tỷ lệ tội phạm crim, số phòng trung bình rm, khoảng cách đến trung tâm dis, v.v.).
Sử dụng 10-fold cross-validation để đánh giá hiệu suất mô hình và in kết quả theo định dạng của Weka (một công cụ máy học phổ biến).
Sau khi huấn luyện, chương trình cho phép người dùng nhập 13 đặc trưng và dự đoán giá trị medv dựa trên mô hình đã huấn luyện.

## 2. Cấu trúc của chương trình
Chương trình sử dụng một mạng nơ-ron với kiến trúc:

Lớp đầu vào (Input Layer): 13 nơ-ron, tương ứng với 13 đặc trưng của dữ liệu.
Lớp ẩn (Hidden Layer): 20 nơ-ron (có thể điều chỉnh qua HIDDEN_SIZE), sử dụng hàm kích hoạt ReLU.
Lớp đầu ra (Output Layer): 1 nơ-ron, dự đoán giá trị liên tục medv.


## 3. Các thành phần chính và cách hoạt động
### 3.1. Các tham số chính

INPUT_SIZE = 13: Số đặc trưng đầu vào (không thay đổi được vì phụ thuộc vào dữ liệu).
HIDDEN_SIZE = 20: Số nơ-ron trong lớp ẩn, quyết định độ phức tạp của mô hình.
OUTPUT_SIZE = 1: Số nơ-ron đầu ra (dự đoán 1 giá trị liên tục).
EPOCHS = 5000: Số lần lặp huấn luyện trên toàn bộ dữ liệu.
LR = 0.01: Tốc độ học (learning rate), điều chỉnh mức độ cập nhật trọng số.
BATCH_SIZE = 64: Kích thước batch cho mini-batch gradient descent, giúp huấn luyện nhanh hơn.

### 3.2. Các hàm chính
- relu và relu_derivative:
  - relu: Hàm kích hoạt ReLU, chuyển các giá trị âm thành 0, giúp mô hình học nhanh hơn và tránh vấn đề vanishing gradient.
  - relu_derivative: Đạo hàm của ReLU, dùng để tính gradient trong lan truyền ngược.
- normalize: Chuẩn hóa dữ liệu huấn luyện về khoảng [0, 1] (min-max scaling) để đảm bảo các đặc trưng có cùng thang đo, giúp mô hình học ổn định và nhanh hơn.
- compute_min_max và normalize_input:
  - compute_min_max: Tính giá trị min và max của từng đặc trưng từ dữ liệu huấn luyện, dùng để chuẩn hóa dữ liệu đầu vào do người dùng cung cấp.
  - normalize_input: Chuẩn hóa dữ liệu đầu vào của người dùng (13 đặc trưng) dựa trên min/max đã tính từ tập huấn luyện.
- trim: Loại bỏ khoảng trắng thừa trong dữ liệu khi đọc từ file CSV.
- read_csv: Đọc dữ liệu từ file BostonHousing.csv (506 mẫu, 14 cột), lưu đặc trưng vào X (13 cột đầu) và nhãn vào y (cột cuối medv).
- train_model:
  - Huấn luyện mô hình bằng thuật toán mini-batch gradient descent:
  - Lan truyền thuận (Forward Propagation): Tính giá trị dự đoán từ đầu vào qua lớp ẩn (ReLU) đến đầu ra.
  - Lan truyền ngược (Backward Propagation): Tính gradient của hàm mất mát (loss) để cập nhật trọng số và bias.
  - Sử dụng cơ chế early stopping (dừng sớm nếu không cải thiện sau 500 lần lặp) để tránh huấn luyện quá mức.
- cross_validate:
  - Thực hiện 10-fold cross-validation:
  - Chia dữ liệu thành 10 phần, huấn luyện trên 9 phần và kiểm tra trên 1 phần, lặp lại 10 lần.
  - Tính các chỉ số hiệu suất như R² (Correlation Coefficient), MAE (Mean Absolute Error), RMSE (Root Mean Squared Error), RAE (Relative Absolute Error), và RRSE (Root Relative Squared Error).
  - In kết quả theo định dạng của Weka, bao gồm thông tin mô hình và các chỉ số đánh giá.
- predict:
  - Dự đoán giá trị medv dựa trên 13 đặc trưng đầu vào do người dùng cung cấp:
  - Thực hiện lan truyền thuận qua mạng nơ-ron.
  - Giải chuẩn hóa giá trị đầu ra để trả về giá trị thực tế (dùng y_mean và y_std).
- main:
  - Điều phối toàn bộ quy trình:
  - Đọc dữ liệu, chuẩn hóa dữ liệu huấn luyện, huấn luyện mô hình, thực hiện cross-validation.
  - Sau đó, yêu cầu người dùng nhập 13 đặc trưng, chuẩn hóa dữ liệu đầu vào, và dự đoán giá trị medv.
## 4. Cách chương trình hoạt động
- Đọc và tiền xử lý dữ liệu:
  - Đọc file BostonHousing.csv (506 mẫu, 14 cột).
  - Tính min/max của từng đặc trưng để chuẩn hóa dữ liệu đầu vào sau này.
  - Chuẩn hóa dữ liệu huấn luyện về [0, 1] và chuẩn hóa nhãn y theo phương pháp z-score (trừ trung bình, chia độ lệch chuẩn).
- Huấn luyện mô hình:
  - Khởi tạo trọng số và bias ngẫu nhiên.
  - Huấn luyện bằng mini-batch gradient descent qua 5000 epoch (hoặc dừng sớm nếu không cải thiện).
  - Lưu trọng số tốt nhất dựa trên validation loss.


Đánh giá mô hình:

Thực hiện 10-fold cross-validation để đảm bảo đánh giá công bằng.
Tính các chỉ số hiệu suất và in ra theo định dạng Weka.


Dự đoán giá trị medv:

Yêu cầu người dùng nhập 13 đặc trưng (từ crim đến lstat).
Chuẩn hóa dữ liệu đầu vào dựa trên min/max của tập huấn luyện.
Thực hiện lan truyền thuận để dự đoán giá trị medv và giải chuẩn hóa để trả về giá trị thực tế.
In kết quả dự đoán.




5. Kết quả đầu ra
Kết quả đầu ra bao gồm hai phần chính:
5.1. Kết quả cross-validation

Run Information: Thông tin về cấu hình mô hình (learning rate, số epoch, số nơ-ron ẩn).
Classifier Model: Chi tiết trọng số và bias của mô hình (theo định dạng Weka).
Cross-validation Summary: Các chỉ số hiệu suất:
Correlation Coefficient (R²): Độ tương quan giữa dự đoán và thực tế.
MAE: Sai số tuyệt đối trung bình.
RMSE: Sai số bình phương trung bình.
RAE, RRSE: Sai số tương đối so với giá trị trung bình.



Ví dụ:
=== Run information ===

Scheme:       CustomNeuralNetwork -L 0.01 -N 5000 -H 20
Relation:     BostonHousing
Instances:    506
Attributes:   14
              crim
              zn
              indus
              chas
              nox
              rm
              age
              dis
              rad
              tax
              ptratio
              b
              lstat
              medv
Test mode:    10-fold cross-validation

=== Classifier model (full training set) ===

Linear Node 0
    Inputs    Weights
    Threshold    0.1234
    Node 1    0.5678
    Node 2    -0.2345
    ...

=== Cross-validation ===
=== Summary ===

Correlation coefficient                  0.7321
Mean absolute error                      3.4567
Root mean squared error                  4.7890
Relative absolute error                 45.6789 %
Root relative squared error             56.7890 %
Total Number of Instances              506

5.2. Kết quả dự đoán giá trị medv

Sau khi in kết quả cross-validation, chương trình yêu cầu người dùng nhập 13 đặc trưng và in ra giá trị medv dự đoán.

Ví dụ:
=== Du doan gia tri medv ===
>> Nhap 13 dac trung (crim, zn, indus, chas, nox, rm, age, dis, rad, tax, ptratio, b, lstat):
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

>> Gia tri MEDV du doan: 24.0000


6. Ý nghĩa của chương trình

Chương trình là một triển khai thủ công của mạng nơ-ron để hiểu cách hoạt động của nó mà không cần thư viện máy học (như TensorFlow hay scikit-learn).
Giúp học và thực hành các khái niệm như lan truyền thuận, lan truyền ngược, gradient descent, cross-validation, và dự đoán trên dữ liệu mới.
Đầu ra theo định dạng Weka giúp dễ so sánh với các công cụ máy học khác, đồng thời phần dự đoán cho phép áp dụng mô hình vào thực tế.


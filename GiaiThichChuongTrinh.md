# Kiến thức về Mạng Nơ-ron Nhân tạo (Neural Network)

## 1. Tổng quan về Mạng Nơ-ron Nhân tạo (Neural Network)

Mạng nơ-ron nhân tạo (Neural Network - NN) là một mô hình tính toán lấy cảm hứng từ cách hoạt động của hệ thần kinh trong não bộ con người. Nó được sử dụng rộng rãi trong các bài toán học máy (machine learning) để mô phỏng mối quan hệ phi tuyến giữa đầu vào và đầu ra.

### 1.1. Học giám sát hay không giám sát?

#### Học giám sát (Supervised Learning)

- Mạng nơ-ron được huấn luyện trên một tập dữ liệu có nhãn (labeled data), nghĩa là mỗi mẫu dữ liệu đầu vào đi kèm với một giá trị đầu ra mong muốn (nhãn).
- Mục tiêu là học một hàm ánh xạ từ đầu vào đến đầu ra, sao cho mô hình có thể dự đoán chính xác trên dữ liệu mới.
- Ví dụ: Trong bài toán Boston Housing, mạng nơ-ron học từ dữ liệu có 13 đặc trưng (crim, zn, ..., lstat) để dự đoán giá nhà medv. Đây là một bài toán hồi quy thuộc học giám sát.

#### Học không giám sát (Unsupervised Learning)

- Mạng nơ-ron không được cung cấp nhãn, mà tự động tìm kiếm cấu trúc hoặc mẫu trong dữ liệu (như phân cụm hoặc giảm chiều dữ liệu).
- Ví dụ: Sử dụng mạng nơ-ron tự mã hóa (Autoencoder) để giảm chiều dữ liệu mà không cần nhãn.

**Trong chương trình đã viết:** Mạng nơ-ron thuộc loại học giám sát, vì chương trình sử dụng tập dữ liệu Boston Housing có nhãn (medv) để huấn luyện mô hình.

## 2. Các thành phần chính của Mạng Nơ-ron và ý nghĩa

### 2.1. Lớp đầu vào (Input Layer)

- Là nơi nhận dữ liệu đầu vào (các đặc trưng).
- Mỗi nơ-ron tương ứng với một đặc trưng.
- Trong chương trình: 13 nơ-ron tương ứng với 13 đặc trưng, dữ liệu được chuẩn hóa về [0, 1].

### 2.2. Lớp ẩn (Hidden Layer)

- Thực hiện biến đổi phi tuyến, giúp học mối quan hệ phức tạp.
- Mỗi nơ-ron thực hiện phép nhân trọng số, cộng bias, áp dụng hàm kích hoạt.
- Trong chương trình: có 20 nơ-ron, dùng hàm ReLU.

### 2.3. Lớp đầu ra (Output Layer)

- Tạo ra kết quả cuối cùng.
- Số lượng nơ-ron phụ thuộc bài toán: 1 nơ-ron cho hồi quy.
- Trong chương trình: 1 nơ-ron đầu ra dự đoán giá trị medv.

### 2.4. Trọng số (Weights) và Bias

- Trọng số: quyết định ảnh hưởng giữa các nơ-ron.
- Bias: dịch chuyển hàm kích hoạt.
- Trong chương trình: W1, W2 là trọng số; B1, B2 là bias. Được khởi tạo ngẫu nhiên.

### 2.5. Hàm kích hoạt (Activation Function)

- Tạo phi tuyến cho mô hình.
- Nếu không có, mạng chỉ tương đương mô hình tuyến tính.
- Trong chương trình: dùng ReLU, đạo hàm dùng trong lan truyền ngược.

### 2.6. Hàm mất mát (Loss Function)

- Đo sai số giữa dự đoán và giá trị thực.
- Mục tiêu huấn luyện là giảm loss.
- Trong chương trình: dùng MSE = (1/n) Σ(y_pred - y_true)^2

## 3. Cách huấn luyện mạng nơ-ron trong chương trình

### 3.1. Quy trình huấn luyện

- **Khởi tạo:** W1, W2, B1, B2 khởi tạo ngẫu nhiên từ phân phối chuẩn.
- **Epochs:** Lặp 5000 lần, hoặc dừng sớm nếu không cải thiện sau 500 lần.
- **Mini-batch:** Batch size = 64.
    - Lan truyền thuận → Tính y_pred.
    - Tính loss.
    - Lan truyền ngược → Cập nhật trọng số & bias.
- **Cập nhật:** weight = weight - LR × gradient
- **Early stopping:** theo dõi validation loss mỗi 50 epoch.

### 3.2. Cách học từ dữ liệu

- **Đọc dữ liệu:** từ BostonHousing.csv gồm 506 mẫu.
- **Chuẩn hóa đặc trưng:** min-max scaling.
- **Chuẩn hóa nhãn:** z-score.
- **Huấn luyện:** mô hình học từ sai số để cập nhật W1, W2, B1, B2.
- **Đánh giá:** dùng cross-validation để tính R², MAE, RMSE, RAE, RRSE.
- **Dự đoán:** nhập 13 đặc trưng → chuẩn hóa → predict → giải chuẩn hóa.

## 4. Ý nghĩa của việc huấn luyện và học từ dữ liệu

- **Huấn luyện:** tối ưu W và B để dự đoán đúng medv.
    - Mini-batch giúp cân bằng tốc độ và hiệu quả.
    - Early stopping tránh overfitting.
- **Học từ dữ liệu:**
    - Dữ liệu cung cấp các yếu tố ảnh hưởng đến giá nhà.
    - Mô hình học ánh xạ từ 13 đặc trưng đến medv.
    - Chuẩn hóa đảm bảo mô hình học ổn định.

## 5. Kết luận

- Mạng nơ-ron trong chương trình là học giám sát.
- Cấu trúc gồm nhiều lớp với trọng số và bias điều chỉnh qua lan truyền ngược.
- Huấn luyện bằng mini-batch gradient descent và early stopping.
- Kết hợp chuẩn hóa và đánh giá chéo giúp mô hình hiệu quả và có khả năng ứng dụng thực tế.

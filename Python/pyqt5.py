import sys
from PyQt5.QtWidgets import (
    QApplication, QWidget,
    QVBoxLayout, QLineEdit,
    QPushButton, QLabel
)

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Demo TextBox & Button")
        self.showMaximized()

        # 1. Tạo layout để chứa các widget
        layout = QVBoxLayout(self)

        # 2. Tạo ô nhập liệu
        self.text_input = QLineEdit(self)
        self.text_input.setPlaceholderText("Gõ gì đó vào đây…")
        layout.addWidget(self.text_input)

        # 3. Tạo nút
        self.btn = QPushButton("Hiển thị nội dung", self)
        layout.addWidget(self.btn)

        # 4. Tạo nhãn để hiện kết quả
        self.result_label = QLabel("", self)
        layout.addWidget(self.result_label)

        # 5. Kết nối signal → slot
        #    Khi btn.clicked phát ra, gọi hàm self.show_text
        self.btn.clicked.connect(self.show_text)

    def show_text(self):
        # Lấy chuỗi từ QLineEdit và đặt vào QLabel
        entered = self.text_input.text()
        if entered:
            self.result_label.setText(f"Nội dung bạn vừa gõ: {entered}")
        else:
            self.result_label.setText("Bạn chưa gõ gì cả!")

def main():
    # Bắt buộc: khởi tạo QApplication trước khi tạo bất cứ widget nào
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())

if __name__ == "__main__":
    main()

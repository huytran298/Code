import sys
from PyQt5.QtWidgets import (
    QApplication, QWidget,
    QVBoxLayout, QPushButton,
    QLineEdit, QPlainTextEdit
)

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Demo Log Box")
        self.resize(500, 300)

        layout = QVBoxLayout(self)

        # Ô nhập liệu và nút để minh họa
        self.input = QLineEdit(self)
        self.input.setPlaceholderText("Gõ nội dung và bấm nút…")
        layout.addWidget(self.input)

        btn = QPushButton("Thêm vào log", self)
        layout.addWidget(btn)
        btn.clicked.connect(self.on_clicked)

        # Ô log chỉ để hiện thông báo, chế độ read-only
        self.log_box = QPlainTextEdit(self)
        self.log_box.setReadOnly(True)
        self.log_box.setPlaceholderText("Các thông báo sẽ hiện ở đây…")
        layout.addWidget(self.log_box)

    def on_clicked(self):
        text = self.input.text().strip()
        self.log_box.clear()
        if text:
            # append dòng mới vào log
            self.log_box.appendPlainText(f"[INFO] Bạn vừa gõ: {text}")
            self.input.clear()
        else:
            self.log_box.appendPlainText("[WARN] Bạn chưa nhập gì cả!")

def main():
    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()

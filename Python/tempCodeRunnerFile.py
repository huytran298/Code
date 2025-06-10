self.log_box = QPlainTextEdit(self)
        self.log_box.setReadOnly(True)
        self.log_box.setPlaceholderText("Các thông báo sẽ hiện ở đây…")
        layout.addWidget(self.log_box)
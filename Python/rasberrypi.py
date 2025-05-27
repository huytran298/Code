import sys 
from PyQt5.QtWidgets import(
    QApplication, QWidget, QFormLayout, QLineEdit, QPushButton, QLabel, QMessageBox
)

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Rabbit Cave")
        self.showMaximized()

        layout = QFormLayout(self)
        
        self.text_max = QLabel("Add maximum voltage for GM tube", self)
        layout.addRow(self.text_max)
        self.maximum = QLineEdit(self)
        self.maximum.setPlaceholderText(' ')
        layout.addRow(self.maximum)

        self.text_min = QLabel("Add minimum voltage for GM tube", self)
        layout.addRow(self.text_min)
        self.minimum = QLineEdit(self)
        self.minimum.setPlaceholderText(' ')
        layout.addRow(self.minimum)

        
        self.text_step = QLabel("Add step voltage for GM tube", self)
        layout.addRow(self.text_step)
        self.step = QLineEdit(self)
        self.step.setPlaceholderText(' ')
        layout.addRow(self.step)

        
        self.text_interval = QLabel("Add time for GM tube", self)
        layout.addRow(self.text_interval)
        self.interval = QLineEdit(self)
        self.interval.setPlaceholderText(' ')
        layout.addRow(self.interval)

        self.btn = QPushButton("Run", self)
        layout.addRow(self.btn)
        self.btn.clicked.connect(self.getValue)
    def getValue(self):
        try : 
            maximum = float(self.text_max.text())
            minimum = float(self.text_min.text())
            step = float(self.text_min.text())
            interval = int(self.interval.text())

        except ValueError : 
            QMessageBox.critical(self, "Error", "Error of input number. Please input again")
    def process(maximum, minimum, step, interval):
        p
def main():
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())

if __name__ == "__main__":
    main()
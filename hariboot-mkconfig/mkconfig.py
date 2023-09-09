# Icons: https://icons8.com

from PyQt6.uic import loadUi
from PyQt6.QtWidgets import QApplication, QMainWindow


class MkConfig(QMainWindow):

    def __init__(self):

        super().__init__()
        self.exitButton = None
        self.maximizeButton = None
        self.reduceButton = None
        self.state = False

        loadUi("ui/form.ui", self)
        self.exitButton.clicked.connect(QApplication.quit)
        self.maximizeButton.clicked.connect(self.maxminwin)
        self.reduceButton.clicked.connect(self.reduce)

    def maxminwin(self):

        if self.state == False:

            QMainWindow().showMaximized()
            self.state = True
        else:

            self.state = False
            QMainWindow().showNormal()

    def reduce(self):

        QMainWindow().showMinimized()

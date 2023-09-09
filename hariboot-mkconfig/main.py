# Icons: https://icons8.com

import sys

from PyQt6.QtCore import Qt
from PyQt6.uic import loadUi
from mkconfig import MkConfig
from PyQt6.QtWidgets import QApplication, QMainWindow, QStackedWidget


class MainWindow(QMainWindow):

    def __init__(self):

        super().__init__()
        self.exitButton = None
        self.maximizeButton = None
        self.reduceButton = None
        self.state = False

        loadUi("ui/main.ui", self)
        self.exitButton.clicked.connect(QApplication.quit)
        self.maximizeButton.clicked.connect(self.maxminwin)
        self.reduceButton.clicked.connect(self.reduce)

        self.darkModeButton.clicked.connect(self.setDarkMode)
        self.lightModeButton.clicked.connect(self.setLightMode)
        self.customModeButton.clicked.connect(self.setCustomMode)

    def setDarkMode(self):

        with open("config.hariboot", "a") as file:

            file.write(
                """HARIBOOT\nDARK  \n000 000 000 000\n000 000 000 000\n000 000 000 000\n000 000 000 000\n000 000 000 000\n
                """)

            file.close()

    def setLightMode(self):

        with open("config.hariboot", "a") as file:
            file.write(
                """HARIBOOT\nLIGHT \n000 000 000 000\n000 000 000 000\n000 000 000 000\n000 000 000 000\n000 000 000 000\n
                """)

            file.close()

    def setCustomMode(self):

        mkconfig = MkConfig()
        widget.addWidget(mkconfig)
        widget.setCurrentWidget(mkconfig)

    def maxminwin(self):

        if self.state == False:

            self.showMaximized()
            self.state = True
        else:

            self.state = False
            self.showNormal()

    def reduce(self):

        self.showMinimized()


if __name__ == "__main__":

    app = QApplication(sys.argv)
    widget = QStackedWidget()
    main = MainWindow()
    mkconfig = MkConfig()

    widget.setAttribute(Qt.WidgetAttribute.WA_TranslucentBackground)
    widget.setWindowFlag(Qt.WindowType.FramelessWindowHint)
    widget.addWidget(main)
    widget.addWidget(mkconfig)
    widget.show()
    sys.exit(app.exec())

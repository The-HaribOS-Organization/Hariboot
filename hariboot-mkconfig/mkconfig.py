# Icons: https://icons8.com

from PyQt6.uic import loadUi
from PyQt6.QtWidgets import QApplication, QMainWindow
from PyQt6.QtGui import *
from tkinter.colorchooser import askcolor


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

        self.backgroundImageButton.clicked.connect(QApplication.quit)
        self.logoSelectImage.clicked.connect(QApplication.quit)
        self.openColorChooserBackground.clicked.connect(self.openColorChooser)
        self.violetButton.clicked.connect(QApplication.quit)
        self.redButton.clicked.connect(QApplication.quit)
        self.yellowButton.clicked.connect(QApplication.quit)
        self.greenButton.clicked.connect(QApplication.quit)
        self.blueButton.clicked.connect(QApplication.quit)
        self.buttonValide.clicked.connect(QApplication.quit)
        self.openColorChooserBootSelected.clicked.connect(self.openColorChooser)
        self.violetButtonBootSelected.clicked.connect(QApplication.quit)
        self.blueButtonBootSelected.clicked.connect(QApplication.quit)
        self.greenButtonBootSelected.clicked.connect(QApplication.quit)
        self.yellowButtonBootSelected.clicked.connect(QApplication.quit)
        self.redButtonBootSelected.clicked.connect(QApplication.quit)
        self.openColorChooserBoot.clicked.connect(QApplication.quit)
        self.violetButtonBoot.clicked.connect(QApplication.quit)
        self.blueButtonsBoot.clicked.connect(QApplication.quit)
        self.greenButtonBoot.clicked.connect(QApplication.quit)
        self.yellowButtonBoot.clicked.connect(QApplication.quit)
        self.redButtonBoot.clicked.connect(QApplication.quit)
        self.openColorChooserMenu.clicked.connect(self.openColorChooser)
        self.violetButtonMenu.clicked.connect(QApplication.quit)
        self.blueButtonsMenu.clicked.connect(QApplication.quit)
        self.greenButtonMenu.clicked.connect(QApplication.quit)
        self.yellowButtonMenu.clicked.connect(QApplication.quit)
        self.redButtonMenu.clicked.connect(QApplication.quit)

    def maxminwin(self):

        if self.state == False:

            QMainWindow().showMaximized()
            self.state = True
        else:

            self.state = False
            QMainWindow().showNormal()

    def reduce(self):

        QMainWindow().showMinimized()

    def openColorChooser(self):

        colors = askcolor(title="Choisir une couleur")
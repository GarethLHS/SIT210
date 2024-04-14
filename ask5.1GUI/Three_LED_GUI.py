import RPi.GPIO as GPIO
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QDialog

RED_LED = 40
BLUE_LED = 38
GREEN_LED = 36

GPIO.setmode(GPIO.BOARD)
GPIO.setup(RED_LED,GPIO.OUT)
GPIO.setup(BLUE_LED,GPIO.OUT)
GPIO.setup(GREEN_LED,GPIO.OUT)
GPIO.output(RED_LED, GPIO.LOW)
GPIO.output(BLUE_LED, GPIO.LOW)
GPIO.output(GREEN_LED, GPIO.LOW)

class Ui_MainWindow_LED(object):
    def setupUi(self, MainWindow_LED):
        self.MainWindow_LED = MainWindow_LED
        MainWindow_LED.setObjectName("MainWindow_LED")
        MainWindow_LED.resize(385, 372)
        self.centralwidget = QtWidgets.QWidget(MainWindow_LED)
        self.centralwidget.setObjectName("centralwidget")
        self.RED_RADIO_BUTTON = QtWidgets.QRadioButton(self.centralwidget)
        self.RED_RADIO_BUTTON.setGeometry(QtCore.QRect(120, 60, 96, 23))
        font = QtGui.QFont()
        font.setFamily("Cantarell")
        font.setPointSize(14)
        font.setBold(True)
        self.RED_RADIO_BUTTON.setFont(font)
        self.RED_RADIO_BUTTON.setObjectName("RED_RADIO_BUTTON")
    
        self.RED_RADIO_BUTTON.toggled.connect(self.radio_button_red)

        self.BLUE_RADIO_BUTTON = QtWidgets.QRadioButton(self.centralwidget)
        self.BLUE_RADIO_BUTTON.setGeometry(QtCore.QRect(120, 110, 121, 23))
        font = QtGui.QFont()
        font.setFamily("Cantarell")
        font.setPointSize(14)
        font.setBold(True)
        self.BLUE_RADIO_BUTTON.setFont(font)
        self.BLUE_RADIO_BUTTON.setObjectName("BLUE_RADIO_BUTTON")

        self.BLUE_RADIO_BUTTON.toggled.connect(self.radio_button_blue)

        self.GREEN_RADIO_BUTTON = QtWidgets.QRadioButton(self.centralwidget)
        self.GREEN_RADIO_BUTTON.setGeometry(QtCore.QRect(120, 160, 131, 23))
        font = QtGui.QFont()
        font.setFamily("Cantarell")
        font.setPointSize(14)
        font.setBold(True)
        self.GREEN_RADIO_BUTTON.setFont(font)
        self.GREEN_RADIO_BUTTON.setObjectName("GREEN_RADIO_BUTTON")

        self.GREEN_RADIO_BUTTON.toggled.connect(self.radio_button_green)


        self.exitButton = QtWidgets.QPushButton(self.centralwidget)
        self.exitButton.setGeometry(QtCore.QRect(120, 220, 151, 81))
        font = QtGui.QFont()
        font.setFamily("Cantarell")
        font.setPointSize(16)
        font.setBold(True)
        self.exitButton.setFont(font)
        self.exitButton.setObjectName("exitButton")
        
        self.exitButton.clicked.connect(self.exitProgram)

        MainWindow_LED.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow_LED)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 385, 22))
        self.menubar.setObjectName("menubar")
        MainWindow_LED.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow_LED)
        self.statusbar.setObjectName("statusbar")
        MainWindow_LED.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow_LED)
        QtCore.QMetaObject.connectSlotsByName(MainWindow_LED)
   

    def radio_button_red(self):
        radio_btn = self.MainWindow_LED.sender()
        if radio_btn.isChecked():
            print("RED LED IS ON")
            GPIO.output(RED_LED,GPIO.HIGH)
        else:
            print("RED LED IS OFF")
            GPIO.output(RED_LED,GPIO.LOW)
    
    def radio_button_blue(self):
        radio_btn = self.MainWindow_LED.sender()
        if radio_btn.isChecked():
            print("BLUE LED IS ON")
            GPIO.output(BLUE_LED,GPIO.HIGH)
        else:
            print("BLUE LED IS OFF")
            GPIO.output(BLUE_LED,GPIO.LOW)
    
    def radio_button_green(self):
        radio_btn = self.MainWindow_LED.sender()
        if radio_btn.isChecked():
            print("GREEN LED IS ON")
            GPIO.output(GREEN_LED,GPIO.HIGH)
        else:
            print("GREEN LED IS OFF")
            GPIO.output(GREEN_LED,GPIO.LOW)

    def exitProgram(self):
        print("Exiting Program")
        GPIO.output(RED_LED,GPIO.LOW)
        GPIO.output(BLUE_LED,GPIO.LOW)
        GPIO.output(GREEN_LED,GPIO.LOW)
        GPIO.cleanup()
        app.quit()

    def retranslateUi(self, MainWindow_LED):
        _translate = QtCore.QCoreApplication.translate
        MainWindow_LED.setWindowTitle(_translate("MainWindow_LED", "MainWindow"))
        self.RED_RADIO_BUTTON.setText(_translate("MainWindow_LED", "RED LED"))
        self.BLUE_RADIO_BUTTON.setText(_translate("MainWindow_LED", "BLUE LED"))
        self.GREEN_RADIO_BUTTON.setText(_translate("MainWindow_LED", "GREEN LED"))
        self.exitButton.setText(_translate("MainWindow_LED", "EXIT"))




if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow_LED = QtWidgets.QMainWindow()
    ui = Ui_MainWindow_LED()
    ui.setupUi(MainWindow_LED)
    MainWindow_LED.show()
    sys.exit(app.exec_())

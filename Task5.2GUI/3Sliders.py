import RPi.GPIO as GPIO
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QDialog

RED_LED = 40
BLUE_LED = 38
GREEN_LED = 36
HERTZ = 100

GPIO.setmode(GPIO.BOARD)
GPIO.setup(RED_LED,GPIO.OUT)
GPIO.setup(BLUE_LED,GPIO.OUT)
GPIO.setup(GREEN_LED,GPIO.OUT)

RED_PWM = GPIO.PWM(RED_LED,HERTZ)
BLUE_PWM = GPIO.PWM(BLUE_LED,HERTZ)
GREEN_PWM = GPIO.PWM(GREEN_LED,HERTZ)

RED_PWM.start(0)
BLUE_PWM.start(0)
GREEN_PWM.start(0)


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(234, 322)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.RED_horizontalSlider = QtWidgets.QSlider(self.centralwidget)
        self.RED_horizontalSlider.setGeometry(QtCore.QRect(30, 60, 160, 16))
        self.RED_horizontalSlider.setMaximum(100)
        self.RED_horizontalSlider.setSingleStep(5)
        self.RED_horizontalSlider.setPageStep(1)
        self.RED_horizontalSlider.setOrientation(QtCore.Qt.Horizontal)
        self.RED_horizontalSlider.setObjectName("RED_horizontalSlider")
        self.RED_label = QtWidgets.QLabel(self.centralwidget)
        self.RED_label.setGeometry(QtCore.QRect(40, 40, 54, 17))
        self.RED_label.setObjectName("RED_label")

        self.RED_horizontalSlider.valueChanged.connect(self.read_red_slider)

        self.BLUE_horizontalSlider = QtWidgets.QSlider(self.centralwidget)
        self.BLUE_horizontalSlider.setGeometry(QtCore.QRect(30, 120, 160, 16))
        self.BLUE_horizontalSlider.setMaximum(100)
        self.BLUE_horizontalSlider.setSingleStep(5)
        self.BLUE_horizontalSlider.setPageStep(1)
        self.BLUE_horizontalSlider.setOrientation(QtCore.Qt.Horizontal)
        self.BLUE_horizontalSlider.setObjectName("BLUE_horizontalSlider")
        self.BLUE_label = QtWidgets.QLabel(self.centralwidget)
        self.BLUE_label.setGeometry(QtCore.QRect(40, 100, 54, 17))
        self.BLUE_label.setObjectName("BLUE_label")

        self.BLUE_horizontalSlider.valueChanged.connect(self.read_blue_slider)

        self.GREEN_horizontalSlider = QtWidgets.QSlider(self.centralwidget)
        self.GREEN_horizontalSlider.setGeometry(QtCore.QRect(30, 180, 160, 16))
        self.GREEN_horizontalSlider.setMaximum(100)
        self.GREEN_horizontalSlider.setSingleStep(5)
        self.GREEN_horizontalSlider.setPageStep(1)
        self.GREEN_horizontalSlider.setOrientation(QtCore.Qt.Horizontal)
        self.GREEN_horizontalSlider.setObjectName("GREEN_horizontalSlider")
        self.GREEN_label = QtWidgets.QLabel(self.centralwidget)
        self.GREEN_label.setGeometry(QtCore.QRect(40, 160, 71, 17))
        self.GREEN_label.setObjectName("GREEN_label")


        self.GREEN_horizontalSlider.valueChanged.connect(self.read_green_slider)

        self.ExitpushButton = QtWidgets.QPushButton(self.centralwidget)
        self.ExitpushButton.setGeometry(QtCore.QRect(30, 230, 151, 41))
        self.ExitpushButton.setObjectName("ExitpushButton")
        self.ExitpushButton.clicked.connect(self.exitProgram)





        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def read_red_slider(self):
        red_value = self.RED_horizontalSlider.value();
        RED_PWM.ChangeDutyCycle(red_value)
    
    def read_blue_slider(self):
        blue_value = self.BLUE_horizontalSlider.value();
        BLUE_PWM.ChangeDutyCycle(blue_value)

    def read_green_slider(self):
        green_value = self.GREEN_horizontalSlider.value();
        GREEN_PWM.ChangeDutyCycle(green_value)


    def exitProgram(self):
        print("Exiting Program")
        GPIO.output(RED_LED,GPIO.LOW)
        GPIO.output(BLUE_LED,GPIO.LOW)
        GPIO.output(GREEN_LED,GPIO.LOW)
        GPIO.cleanup()
        app.quit()

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.ExitpushButton.setText(_translate("MainWindow", "Exit"))
        self.RED_label.setText(_translate("MainWindow", "RED LED"))
        self.BLUE_label.setText(_translate("MainWindow", "BLUE LED"))
        self.GREEN_label.setText(_translate("MainWindow", "GREEN LED"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

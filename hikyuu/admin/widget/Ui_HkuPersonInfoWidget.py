# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Ui_HkuPersonInfoWidget.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_PersonInfoForm(object):
    def setupUi(self, PersonInfoForm):
        PersonInfoForm.setObjectName("PersonInfoForm")
        PersonInfoForm.resize(400, 300)
        self.formLayout_2 = QtWidgets.QFormLayout(PersonInfoForm)
        self.formLayout_2.setObjectName("formLayout_2")
        self.formLayout = QtWidgets.QFormLayout()
        self.formLayout.setObjectName("formLayout")
        self.change_password_pushButton = QtWidgets.QPushButton(PersonInfoForm)
        self.change_password_pushButton.setObjectName("change_password_pushButton")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.change_password_pushButton)
        self.formLayout_2.setLayout(0, QtWidgets.QFormLayout.LabelRole, self.formLayout)

        self.retranslateUi(PersonInfoForm)
        QtCore.QMetaObject.connectSlotsByName(PersonInfoForm)

    def retranslateUi(self, PersonInfoForm):
        _translate = QtCore.QCoreApplication.translate
        PersonInfoForm.setWindowTitle(_translate("PersonInfoForm", "Form"))
        self.change_password_pushButton.setText(_translate("PersonInfoForm", "Change Password"))

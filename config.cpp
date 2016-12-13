#include "config.h"
#include "ui_config.h"
#include <QSettings>
#include <QMessageBox>

Config::Config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Config)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    controlConnections();

    QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
    settings.setValue("LangSelection","eng");
}

Config::~Config()
{
    delete ui;
}

void Config::controlConnections()
{
    connect(ui->btnCancelar,SIGNAL(clicked(bool)),this,SLOT(accept()));
    connect(ui->btnSalvarConfig,SIGNAL(clicked(bool)),this,SLOT(SalvarConfig()));
}

void Config::SalvarConfig()
{
    if(ui->rbModoJanela->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("WindowMode",00000001);
    }
    if(ui->rbTelaCheia->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("WindowMode",00000000);
    }
    if(ui->rb640x480->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("Resolution",00000000);
    }
    if(ui->rb800x600->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("Resolution",00000001);
    }
    if(ui->rb1024x768->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("Resolution",00000002);
    }
    if(ui->rb1280x1024->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("Resolution",00000003);
    }
    if(ui->rb1366x768->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("Resolution",00000005);
    }
    if(ui->rb1600x1280->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("Resolution",00000004);
    }
    if(ui->rb1920x1080->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("Resolution",8);
    }
    if(ui->rbMusicOff->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("MusicOnOFF",00000000);
        settings.setValue("VolumeLevel",00000000);
    }
    if(ui->rbMusicOn->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("MusicOnOFF",00000001);
        settings.setValue("VolumeLevel",00000001);
    }
    if(ui->rbSoundOn->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("SoundOnOFF",00000001);
        settings.setValue("VolumeLevel",00000001);
    }
    if(ui->rbSoundOff->isChecked()){
        QSettings settings("HKEY_CURRENT_USER\\Software\\Webzen\\Mu\\Config",QSettings::NativeFormat);
        settings.setValue("SoundOnOFF",00000000);
    }
    QMessageBox::about(0,"Atenção!!!","Você salvou suas configurações com sucesso!");

    this->accept();
}

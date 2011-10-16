#include <QtGui/QApplication>
#include <QPluginLoader>
#include "main_window.h"
#include "plugin_interface.h"
#include "settings_parser.h"
#include "iostream"

ShellInterface *shell_interface;

void LoadPlugins(QList<QString> *paths){
    if (paths==NULL) return;
    for(int i=0; i<paths->length(); i++){
        QString path=paths->at(i);
        QPluginLoader loader(path);
        if (PluginInterface *plugin =
                qobject_cast<PluginInterface* >(loader.instance())){
            int result;
            if (result=plugin->Init(shell_interface)){
                std::cerr<<"Error while loading plagin from "<<qPrintable(path)<<
                           "Number = "<<result<<endl;
            }
        }
    }
}

void LoadPlugins(QString path){
    QList<QString> *paths = new QList<QString>();
    paths->push_back(path);
    LoadPlugins(paths);
}


int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainWindow main_window;
    SettingsParser * settings = new SettingsParser();
    shell_interface = new ShellInterface(&main_window, settings);
    LoadPlugins(settings->GetPluginsPaths());
    main_window.show();
    return application.exec();
}

#ifndef SEARCH_BY_REGION_H
#define SEARCH_BY_REGION_H

#include "Search_By_Region_global.h"

#include "../includes/plugin_interface.h"

// �������� ����� �������
class SearchByRegion: public QObject, public PluginInterface{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)

private:
    // ��������� ��� ������ � �������� ������� ���������
    ShellInterface* f_shell;
    // �������� �������� ������ - ����� ������ � �������� ������� ��������
    QAction* cafe_dialog;

private slots:
    // ������� ������ ������ �� �����
    void Cafe();

public:
    // �������������� �������� ������ ����������
    int Init(ShellInterface*);
    int Stop();
};

#endif // SEARCH_BY_REGION_H

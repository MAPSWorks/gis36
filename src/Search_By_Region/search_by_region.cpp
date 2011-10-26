
#include "search_by_region.h"
#include "search_by_region_window.h"


#include <QtGui>
/*
  ���� ������
*/
          // �� ������ �������.
const int RES_OK = 0;
          // �� ������� ������� ��������
const int ERR_UNABLE_CREATE_ACTION = RES_OK + 1;
          // ���������� �������� ������ �� ������ ������������
const int ERR_UNABLE_ADD_ACTION_TO_TOOLBAR = RES_OK + 2;
          // ���������� �������� ����� � ����
const int ERR_UNABLE_ADD_ACTION_TO_MENU = RES_OK + 3;


int SearchByRegion::Init(ShellInterface * shell)
{
    // ������������� ��������� ��������
    cafe_dialog = NULL;

    // ���������� ��������� �� ������� ��������� �� ���������� ����������
    f_shell = shell;

    // ��������� ���������� �� Toolbar � Menu, ��� ������������
    // ���������� � ��� ����� �������
    QToolBar* main_toolbar = f_shell->GetPluginsToolBar();
    QMenu* main_menu = f_shell->GetPluginsMenu();

    // �������� �������� ��� ������ ������ ������
    try{
        cafe_dialog = new QAction(tr("Cafe"), this);
        //cafe_dialog->setShortcut(tr("Ctrl+H"));
        cafe_dialog->setStatusTip(tr("Cafe"));
        connect(cafe_dialog, SIGNAL(triggered()), this, SLOT(Cafe()));
    }catch(...){
        return ERR_UNABLE_CREATE_ACTION;
    }

    // ��������� ������ �� ������ ������������
    try{
        main_toolbar->addAction(cafe_dialog);
    }catch(...){
        return ERR_UNABLE_ADD_ACTION_TO_TOOLBAR;
    }

    // ��������� ���� ����� � ����
    try{
        main_menu->addAction(cafe_dialog);
    }catch(...){
        return ERR_UNABLE_ADD_ACTION_TO_MENU;
    }

    return RES_OK;
}

int SearchByRegion::Stop()
{
    if(cafe_dialog != NULL)
        delete cafe_dialog;

    return RES_OK;
}

void SearchByRegion::Cafe()
{
    SearchByRegionWindow *window = new SearchByRegionWindow();
    window->show();
}

Q_EXPORT_PLUGIN2(gis36_SearchByRegion, SearchByRegion)

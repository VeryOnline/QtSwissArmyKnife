﻿/****************************************************************************************
 * Copyright 2018-2021 Qter(qsaker@qq.com). All rights reserved.
 *
 * The file is encoded using "utf8 with bom", it is a part
 * of QtSwissArmyKnife project.
 *
 * QtSwissArmyKnife is licensed according to the terms in
 * the file LICENCE in the root of the source code directory.
 ***************************************************************************************/
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QSettings>
#include <QMetaEnum>
#include <QTabWidget>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QTranslator>
#include <QSqlDatabase>

namespace Ui {
    class SAKMainWindow;
}

class SAKUpdateManager;
class SAKMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SAKMainWindow(QSettings *settings,
                           QSqlDatabase *sqlDatabase,
                           QWidget *parent = Q_NULLPTR);
    ~SAKMainWindow();

    // Debug page type supported by QtSwissArmyKnife
    enum SAKEnumDebugPageType {
#ifdef QT_DEBUG
#ifdef SAK_IMPORT_MODULE_TEST
        DebugPageTypeTest,
#endif
#endif
#ifdef SAK_IMPORT_MODULE_SERIALPORT
        DebugPageTypeCOM,
#endif
#ifdef SAK_IMPORT_HID_MODULE
        DebugPageTypeHID,
#endif
#ifdef SAK_IMPORT_MODULE_UDP
#ifdef SAK_IMPORT_MODULE_UDP_CLIENT
        DebugPageTypeUdpClient,
#endif
#ifdef SAK_IMPORT_MODULE_UDP_SERVER
        DebugPageTypeUdpServer,
#endif
#endif
#ifdef SAK_IMPORT_MODULE_TCP
#ifdef SAK_IMPORT_MODULE_TCP_CLIENT
        DebugPageTypeTCPClient,
#endif
#ifdef SAK_IMPORT_MODULE_TCP_SERVER
        DebugPageTypeTCPServer,
#endif
#endif
#ifdef SAK_IMPORT_MODULE_WEBSOCKET
#ifdef SAK_IMPORT_MODULE_WEBSOCKET_CLIENT
        DebugPageTypeWebSocketClient,
#endif
#ifdef SAK_IMPORT_MODULE_WEBSOCKET_SERVER
        DebugPageTypeWebSocketServer,
#endif
#endif
#ifdef SAK_IMPORT_MODULE_SERIALBUS
        DebugPageTypeModbus
#endif
    };
    Q_ENUM(SAKEnumDebugPageType);

    enum SAKEnumToolType {
#ifdef SAK_IMPORT_MODULE_FILECHECKER
        ToolTypeFileChecker,
#endif
#ifdef SAK_IMPORT_MODULE_QRCODE
        ToolTypeQRCodeCreator,
#endif
        ToolTypeCRCCalculator
    };
    Q_ENUM(SAKEnumToolType);
protected:
    void closeEvent(QCloseEvent *event);
private:
    struct SettingsKeyContext {
        QString enableTestPage;
        QString currentTabPage;
        QString exitToSystemTray;
    }mSettingsKeyContext;

    struct SAKDebugPageMetaInfo {
        int debugPageType;
        QMetaObject metaObject;
        QString defaultTitle;
    };
    QList<SAKDebugPageMetaInfo> mDebugPageMetaInfoList;

    struct SAKToolMetaObjectInfo {
        QMetaObject metaObject;
        QString title;
    };
    QList<SAKToolMetaObjectInfo> mToolMetaObjectInfoList;

    QMenu *mWindowsMenu;
    QAction *mTestPageAction;
    SAKUpdateManager *mUpdateManager;
    const QString mSettingKeyEnableTestPage;
    QSettings *mSettings;
    QSqlDatabase *mSqlDatabase;
    QActionGroup *mActionGroup;
    QActionGroup *mLanguagesActionGroup;
private:
    void initMenuBar();
    void initFileMenu();
    void initToolMenu();
    void initOptionMenu();
    void initOptionMenuAppStyleMenu(QMenu *optionMenu);
    void initOptionMenuMainWindowMenu(QMenu *optionMenu);
    void initOptionMenuSettingsMenu(QMenu *optionMenu);
    void initOptionMenuTestPageAction(QMenu *optionMenu);
    void initWindowMenu();
    void initLanguageMenu();
    void initHelpMenu();
    void initLinksMenu();
    void initDemoMenu();
#ifdef SAK_IMPORT_MODULE_USER
    void initUserMenu();
#endif

    void aboutQsak();
    void removeRemovableDebugPage(int index);
    void appendWindowAction(QWidget *page);
    void testPageActionTriggered();
    void clearConfiguration();
    void rebootRequestion();
    void initializingMetaObject();
    void initToosMetaObjectInfoList();
    void showReleaseHistoryActionDialog();
    QString tabPageName(int type);
    QWidget *debugPage(QObject *sender);
    void showQrCodeDialog();
private slots:
    /**
     * @brief activePage: Active the debugging page,
     * the interface must be called by signal,
     * which is emited by actions of windows menu.
     */
    void activePage();

    /**
     * @brief installLanguage: Change the language packet of application,
     * the interface must be called by signal,
     * which is emited by actions of language menu.
     */
    void installLanguage();

    /**
     * @brief openDebugPageWidget: Show a deugging window,
     * the interface must be called by singal,
     * which is emited by actions of new debugging window menu.
     */
    void openDebugPageWidget();

    /**
     * @brief appendRemovablePage: append a page to tab widget, t
     * he interface must be called by signal,
     * which is emited by actions of new debugging page menu.
     */
    void appendRemovablePage();
private:
    /**
     * @brief debugPageFromDebugPageType: Create a debuge page from specified type
     * @param type: Debug page type, look at the SAKEnumToolType for more information
     * @return A pointer of debug page instance
     */
    QWidget *debugPageFromDebugPageType(int type);

    /**
     * @brief debugPageTitleFromDebugPageType: Get the default name of debuge page
     * from specified type
     * @param type: Debug page type, look at the SAKEnumToolType for more information
     * @return The default debug page name
     */
    QString debuggerNameFromDebugPageType(int type);
private:
    Ui::SAKMainWindow *mUi;
    QTabWidget *mTabWidget;
};

extern SAKMainWindow *sakMainWindow;

#endif // MAINWINDOW_H

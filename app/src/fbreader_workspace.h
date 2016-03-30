#ifndef FBREADER_WORKSPACE_H
#define FBREADER_WORKSPACE_H

#include <QtQuick>
#include <QQuickWindow>
#include <QQmlEngine>
#include <QQmlComponent>
#include <SyberosGuiCache>
#include <cgui_application.h>
#include <cworkspace.h>

using namespace SYBEROS;

class FBReader_Workspace : public CWorkspace
{
    Q_OBJECT

public:
    FBReader_Workspace(int argc, char **argv);

    // 应用启动结束时，回调此函数。根据传入的option，应用可以区分启动的方式。
    void onLaunchComplete(Option option, const QStringList& params);
};

#endif // FBREADER_WORKSPACE_H

#include "fbreader_workspace.h"

Q_DECL_EXPORT int main(int argc, char **argv)
{
    return SYBEROS::SyberosGuiCache::qApplication(argc, argv, new FBReader_Workspace(argc, argv));
}

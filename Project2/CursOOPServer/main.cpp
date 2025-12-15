#include "application.h"

int main(int argc, char* argv[])
{
    ServerApplication app(argc, argv);
    return app.exec();
}

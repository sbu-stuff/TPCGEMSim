#include <qapplication.h>
#include "tpcsim.h"

int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    TPCSim *w = new TPCSim;
    a.setMainWidget(w);	    
    w->show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}

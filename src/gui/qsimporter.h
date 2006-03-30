#ifndef __QSIMPORTER_H__
#define __QSIMPORTER_H__

#include <qobject.h>
#include <qstring.h>
#include <qsproject.h>
#include <qsinterpreter.h>
#include "qscobject.h"
#include <cobject.h>
#include <cpage.h>
#include <cpdf.h>

using namespace pdfobjects;

class QSImporter : public QObject {
 Q_OBJECT
public:
 QSImporter(QSProject *_qp,QObject *_context);
 virtual ~QSImporter();
 void addQSObj(QObject *obj,const QString &name);
 //factory-style functions
 QSCObject* createQSObject(CDict* dict);
 QSCObject* createQSObject(boost::shared_ptr<CPage> page);
 QSCObject* createQSObject(CPdf* pdf);
public slots:
 QObject* getQSObj();
private:
 /** Current QObject to import */
 QObject *qobj;
 /** context in which objects will be imported */
 QObject *context;
 /** Interpreter from QProject qp. All objects will be imported in it. */
 QSInterpreter *qs;
 /** QSProject in which this importer is installed. */
 QSProject *qp;
};
#endif

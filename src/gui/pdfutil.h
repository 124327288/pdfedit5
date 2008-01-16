/*                                                                              
 * PDFedit - free program for PDF document manipulation.                        
 * Copyright (C) 2006, 2007  PDFedit team:      Michal Hocko, 
 *                                              Miroslav Jahoda,       
 *                                              Jozef Misutka, 
 *                                              Martin Petricek                                             
 *
 * Project is hosted on http://sourceforge.net/projects/pdfedit                                                                      
 */ 
#ifndef __PDFUTIL_H__
#define __PDFUTIL_H__
/** @file
 \brief PDF manipulation utility functions header
*/

#include <kernel/iproperty.h>
#include <kernel/cobject.h>
#include <kernel/cannotation.h>
class QString;
namespace pdfobjects {
class CPdf;
}

namespace util {

using namespace pdfobjects;

QString getTypeId(PropertyType typ);
QString getTypeId(IProperty *obj);
QString getTypeId(boost::shared_ptr<IProperty> obj);
QString getTypeName(PropertyType typ);
QString getTypeName(IProperty *obj);
QString getTypeName(boost::shared_ptr<IProperty> obj);
IndiRef getRef(IProperty *ref);
IndiRef getRef(boost::shared_ptr<IProperty> ref);
bool isRefValid(CPdf *pdf,IndiRef ref);
bool isSimple(IProperty* prop);
bool isSimple(boost::shared_ptr<IProperty> prop);
boost::shared_ptr<IProperty> dereference(boost::shared_ptr<IProperty> obj);
bool saveCopy(CPdf *obj,const QString &name);
boost::shared_ptr<IProperty> getObjProperty(boost::shared_ptr<CDict> obj,const QString &name);
boost::shared_ptr<IProperty> getObjProperty(boost::shared_ptr<CArray> obj,const QString &name);
boost::shared_ptr<IProperty> recursiveProperty(boost::shared_ptr<CDict> obj,const QString &name);
boost::shared_ptr<IProperty> recursiveProperty(boost::shared_ptr<CArray> obj,const QString &name);
QString propertyPreview(boost::shared_ptr<IProperty> obj);
QString annotType(CAnnotation::AnnotType at);
QString annotType(boost::shared_ptr<CAnnotation> anot);
QString annotTypeName(boost::shared_ptr<CAnnotation> anot);

} // namespace util

#endif

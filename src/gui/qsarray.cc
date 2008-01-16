/*                                                                              
 * PDFedit - free program for PDF document manipulation.                        
 * Copyright (C) 2006, 2007  PDFedit team:      Michal Hocko, 
 *                                              Miroslav Jahoda,       
 *                                              Jozef Misutka, 
 *                                              Martin Petricek                                             
 *
 * Project is hosted on http://sourceforge.net/projects/pdfedit                                                                      
 */ 
/** @file
 QObject wrapper around CArray<br>
 Export some functions to scripting.<br>
 See doc/user/scripting.xml or kernel documentation for more informations about these functions
 @author Martin Petricek
*/

#include "qsarray.h"
#include "qsimporter.h"
#include <kernel/cobject.h>
#include "pdfutil.h"
#include "util.h"

namespace gui {

using namespace pdfobjects;

/**
 Construct wrapper with given CArray
 @param _array Array
 @param _base scripting base
*/
QSArray::QSArray(boost::shared_ptr<CArray> _array,BaseCore *_base) : QSIProperty (_array,"Array",_base) {
}

/**
 Copy constructor
 @param source Source item
*/
QSArray::QSArray(QSArray &source) : QSIProperty (source.obj,"Array",source.base) {
}

/** destructor */
QSArray::~QSArray() {
}

/**
 get CArray held inside this class. Not exposed to scripting
 @return CArray shared pointer
*/
boost::shared_ptr<CArray> QSArray::get() {
 return boost::dynamic_pointer_cast<CArray>(obj);
}

/**
 Return number of array elements
 \see CArray::getPropertyCount
 @return number of elements
*/
int QSArray::count() {
 CArray *array=dynamic_cast<CArray*>(obj.get());
 return array->getPropertyCount();
}

/**
 Return property at specified index
 \see CArray::getProperty(int)
 @param index Index of element in array
 @return property at given index
*/
QSCObject* QSArray::property(int index) {
 CArray *array=dynamic_cast<CArray*>(obj.get());
 boost::shared_ptr<IProperty> property=array->getProperty(index);
 return QSImporter::createQSObject(property,base);
}

/**
 Delete property at specified index
 \see CArray::delProperty(int)
 @param index Index of element in array
*/
void QSArray::delProperty(int index) {
 CArray *array=dynamic_cast<CArray*>(obj.get());
 try {
  array->delProperty(index);
 } catch (ReadOnlyDocumentException &e) {
  base->errorException("Array","delProperty",QObject::tr("Document is read-only"));
 }
}

/**
 Return text representation of array
 \see CArray::getStringRepresentation
 @return string representation
*/
QString QSArray::getText() {
 CArray *array=dynamic_cast<CArray*>(obj.get());
 std::string text;
 array->getStringRepresentation(text);
 return util::convertToUnicode(text,util::PDF);
}

/**
 Add given property to array at specified index
 @param index Index of element in array
 @param ip property to add 
 \see CArray::addProperty
*/
void QSArray::add(int index,QSIProperty *ip) {
 CArray *array=dynamic_cast<CArray*>(obj.get());
 try {
  array->addProperty(index,*(ip->get().get()));
 } catch (ReadOnlyDocumentException &e) {
  base->errorException("Array","add",QObject::tr("Document is read-only"));
 }
}

/** \copydoc add(int,QSIProperty *) */
void QSArray::add(int index,QObject *ip) {
 //QSA-bugfix variant of this method
 CArray *array=dynamic_cast<CArray*>(obj.get());
 QSIProperty *ipx=dynamic_cast<QSIProperty*>(ip);
 try {
  if (ipx) array->addProperty(index,*(ipx->get().get()));
 } catch (ReadOnlyDocumentException &e) {
  base->errorException("Array","add",QObject::tr("Document is read-only"));
 }
}

/**
 Add String property to array at specified index
 @param index Index of element in array
 @param ip string to add 
 \see CArray::addProperty
*/
void QSArray::add(int index,const QString &ip) {
 CArray *array=dynamic_cast<CArray*>(obj.get());
 CString property(util::convertFromUnicode(ip,util::PDF));
 try {
  array->addProperty(index,property);
 } catch (ReadOnlyDocumentException &e) {
  base->errorException("Array","add",QObject::tr("Document is read-only"));
 }
}

/**
 Add Int property to array at specified index
 @param index Index of element in array
 @param ip integer to add 
 \see CArray::addProperty
*/
void QSArray::add(int index,int ip) {
 CArray *array=dynamic_cast<CArray*>(obj.get());
 CInt property(ip);
 try {
  array->addProperty(index,property);
 } catch (ReadOnlyDocumentException &e) {
  base->errorException("Array","add",QObject::tr("Document is read-only"));
 }
}

/**
 Append given property to array
 @param ip property to add 
 \see CArray::addProperty
*/
void QSArray::add(QSIProperty *ip) {
 CArray *array=dynamic_cast<CArray*>(obj.get());
 try {
  array->addProperty(*(ip->get().get()));
 } catch (ReadOnlyDocumentException &e) {
  base->errorException("Array","add",QObject::tr("Document is read-only"));
 }
}

/** \copydoc add(QSIProperty *) */
void QSArray::add(QObject *ip) {
 //QSA-bugfix variant of this method
 CArray *array=dynamic_cast<CArray*>(obj.get());
 QSIProperty *ipx=dynamic_cast<QSIProperty*>(ip);
 try {
  if (ipx) array->addProperty(*(ipx->get().get()));
 } catch (ReadOnlyDocumentException &e) {
  base->errorException("Array","add",QObject::tr("Document is read-only"));
 }
}

/**
 Append given String property to array
 @param ip string to add 
 \see CArray::addProperty
*/
void QSArray::add(const QString &ip) {
 CArray *array=dynamic_cast<CArray*>(obj.get());
 CString property(util::convertFromUnicode(ip,util::PDF));
 try {
  array->addProperty(property);
 } catch (ReadOnlyDocumentException &e) {
  base->errorException("Array","add",QObject::tr("Document is read-only"));
 }
}

/**
 Append given Int property to array
 @param ip integer to add 
 \see CArray::addProperty
*/
void QSArray::add(int ip) {
 CArray *array=dynamic_cast<CArray*>(obj.get());
 CInt property(ip);
 try {
  array->addProperty(property);
 } catch (ReadOnlyDocumentException &e) {
  base->errorException("Array","add",QObject::tr("Document is read-only"));
 }
}

/**
 recursive CDict/CArray getProperty(...)
 Will take the name as slash-separated list of childs to traverse to get to target property.
 References on the way are automatically dereferenced
 @param name Path to property
 @return specified property
*/
QSCObject* QSArray::child(const QString &name) {
 try {
  boost::shared_ptr<CArray> array=boost::dynamic_pointer_cast<CArray>(obj);
  boost::shared_ptr<IProperty> property=util::recursiveProperty(array,name);
  return QSImporter::createQSObject(property,base);
 } catch (...) { 
  //Some error, probably the property does not exist
  return NULL;
 }
}

} // namespace gui

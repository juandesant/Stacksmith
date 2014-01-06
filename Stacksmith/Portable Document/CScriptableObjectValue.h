//
//  CScriptableObjectValue.h
//  Stacksmith
//
//  Created by Uli Kusterer on 16.04.11.
//  Copyright 2011 Uli Kusterer. All rights reserved.
//

/*!
	@header CScriptableObjectValue
	This file contains everything that is needed to interface Stacksmith's
	CConcreteObject-based object hierarchy (buttons, fields, cards) with the
	Leonie bytecode interpreter. This allows performing common operations on
	them (like retrieve property values, change their value, call handlers
	in their scripts, add user properties etc.
	
	So that the Leonie bytecode interpreter can deal with objects of this type,
	it also defines kLeoValueTypeScriptableObject, which is like a native object,
	but guarantees that the object conforms to the CScriptableObject protocol.
	
	You can create such a value using the <tt>CInitScriptableObjectValue</tt> function,
	just like any other values.
*/

#ifndef __Stacksmith__CScriptableObjectValue__
#define __Stacksmith__CScriptableObjectValue__

#include "LEOValue.h"
#include "CRefCountedObject.h"
#include <string>
#include <functional>
#include "LEOScript.h"
#include "LEOInterpreter.h"



extern struct LEOValueType	kLeoValueTypeScriptableObject;


namespace Carlson
{

class CStack;
class CDocument;


class CScriptableObject : public CRefCountedObject
{
public:
	virtual ~CScriptableObject() {};
	
// The BOOL returns on these methods indicate whether the given object can do
//	what was asked (as in, ever). So if a property doesn't exist, they'd return
//	NO. If an object has no contents, the same.

	virtual bool				GetTextContents( std::string& outString )		{ return false; };
	virtual bool				SetTextContents( std::string inString)			{ return false; };

	virtual bool				GoThereInNewWindow( bool inNewWindow )			{ return false; };

	virtual bool				GetPropertyNamed( const char* inPropertyName, size_t byteRangeStart, size_t byteRangeEnd, LEOValuePtr outValue )						{ return false; };
	virtual bool				SetValueForPropertyNamed( LEOValuePtr inValue, const char* inPropertyName, size_t byteRangeStart, size_t byteRangeEnd )	{ return false; };

	virtual LEOScript*			GetScriptObject( std::function<void(const char*,size_t,size_t,CScriptableObject*)> errorHandler )								{ return NULL; };
	virtual CScriptableObject*	GetParentObject()								{ return NULL; };

	virtual CStack*				GetStack()			{ return NULL; };
	virtual bool				DeleteObject()		{ return false; };

	virtual void				OpenScriptEditorAndShowOffset( size_t byteOffset )	{};
	virtual void				OpenScriptEditorAndShowLine( size_t lineIndex )		{};

	virtual bool				AddUserPropertyNamed( const char* userPropName )	{ return false; };
	virtual bool				DeleteUserPropertyNamed( const char* userPropName )	{ return false; };
	virtual size_t				GetNumUserProperties()								{ return 0; };
	virtual std::string			GetUserPropertyNameAtIndex( size_t inIndex )		{ return std::string(); };
	virtual bool				SetUserPropertyNameAtIndex( const char* inNewName, size_t inIndex )	{ return false; };
	virtual bool				GetUserPropertyValueForName( const char* inPropName, LEOValuePtr outValue )	{ return false; };
	virtual bool				SetUserPropertyValueForName( LEOValuePtr inValue, const char* inPropName )	{ return false; };
	
	virtual void				SendMessage( LEOValuePtr outValue, std::function<void(const char*,size_t,size_t,CScriptableObject*)> errorHandler, const char* fmt, ... );
	
	virtual LEOContextGroup*	GetScriptContextGroupObject()				{ return NULL; };
	
	static void			InitScriptableObjectValue( LEOValueObject* inStorage, CScriptableObject* wildObject, LEOKeepReferencesFlag keepReferences, LEOContext* inContext );
	static LEOScript*	GetParentScript( LEOScript* inScript, LEOContext* inContext );

	static CScriptableObject*	GetOwnerScriptableObjectFromContext( LEOContext * inContext );
	static void					PreInstructionProc( LEOContext* inContext );
};


class CScriptContextUserData
{
public:
	CScriptContextUserData( CStack* currStack, CScriptableObject* target );
	~CScriptContextUserData();
	
	void				SetStack( CStack* currStack );
	CStack*				GetStack()						{ return mCurrentStack; };
	void				SetTarget( CScriptableObject* target );
	CScriptableObject*	GetTarget()						{ return mTarget; };
	CDocument*			GetDocument();

	static void			CleanUp( void* inData );
	
protected:
	CStack				*	mCurrentStack;
	CScriptableObject	*	mTarget;
};

}

#endif /* defined(__Stacksmith__CScriptableObjectValue__) */

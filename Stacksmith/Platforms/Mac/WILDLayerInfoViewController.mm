//
//  WILDLayerInfoViewController.m
//  Stacksmith
//
//  Created by Uli Kusterer on 18.03.11.
//  Copyright 2011 Uli Kusterer. All rights reserved.
//

#import "WILDLayerInfoViewController.h"
#import "WILDScriptEditorWindowController.h"
#import "CLayer.h"
#import "UKHelperMacros.h"
#import "WILDUserPropertyEditorController.h"


using namespace Carlson;


@interface WILDLayerInfoViewController () <NSTextFieldDelegate>

@end


@implementation WILDLayerInfoViewController

@synthesize layer = mLayer;

@synthesize nameField = mNameField;
@synthesize numberField = mNumberField;
@synthesize IDField = mIDField;
@synthesize fieldCountField = mFieldCountField;
@synthesize buttonCountField = mButtonCountField;
@synthesize editScriptButton = mEditScriptButton;
@synthesize dontSearchSwitch = mDontSearchSwitch;
@synthesize cantDeleteSwitch = mCantDeleteSwitch;
@synthesize userPropertyEditButton = mUserPropertyEditButton;


-(id)	initWithLayer: (CLayer*)inCard
{
	if(( self = [super initWithNibName: NSStringFromClass([self class]) bundle: nil] ))
	{
		mLayer = (CLayer*) inCard->Retain();
	}
	
	return self;
}

-(void)	dealloc
{
	mLayer->Release();
	
	DESTROY_DEALLOC( mEditScriptButton );
	DESTROY_DEALLOC( mDontSearchSwitch );
	DESTROY_DEALLOC( mCantDeleteSwitch );
	DESTROY_DEALLOC( mNameField );
	DESTROY_DEALLOC( mNumberField );
	DESTROY_DEALLOC( mIDField );
	DESTROY_DEALLOC( mFieldCountField );
	DESTROY_DEALLOC( mButtonCountField );
	
	[super dealloc];
}


-(void)	awakeFromNib
{
	[super awakeFromNib];
	
	[self.userPropertyEditor setPropertyContainer: mLayer];
		
	[mNameField setStringValue: [NSString stringWithUTF8String: mLayer->GetName().c_str()]];
	[mCantDeleteSwitch setState: mLayer->GetCantDelete() ? NSOnState : NSOffState];
	[mDontSearchSwitch setState: mLayer->GetDontSearch() ? NSOnState : NSOffState];
		
	unsigned long	numFields = mLayer->GetPartCountOfType( CPart::GetPartCreatorForType("field") );
	[mFieldCountField setStringValue: [NSString stringWithFormat: @"Contains %ld card fields", numFields]];

	unsigned long	numButtons = mLayer->GetPartCountOfType( CPart::GetPartCreatorForType("button") );
	[mButtonCountField setStringValue: [NSString stringWithFormat: @"Contains %ld card buttons", numButtons]];
}


-(IBAction)	doEditScriptButton: (id)sender
{
	mLayer->OpenScriptEditorAndShowLine(SIZE_T_MAX);
}


-(IBAction)	doCantDeleteSwitchChanged: (id)sender
{
	mLayer->SetCantDelete( [mCantDeleteSwitch state] == NSOnState );
}


-(IBAction)	doDontSearchSwitchChanged: (id)sender
{
	mLayer->SetDontSearch( [mDontSearchSwitch state] == NSOnState );
}


-(void)	controlTextDidChange: (NSNotification *)notif
{
	if( [notif object] == mNameField )
	{
		mLayer->SetName( mNameField.stringValue.UTF8String);
	}
}

@end

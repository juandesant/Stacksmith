//
//  WILDScriptEditorWindowController.h
//  Propaganda
//
//  Created by Uli Kusterer on 13.03.10.
//  Copyright 2010 The Void Software. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#include "CConcreteObject.h"


@class UKSyntaxColoredTextViewController;
@class ULISyntaxColoredTextView;
@class WILDScriptEditorRulerView;


@interface WILDScriptEditorWindowController : NSWindowController
{
	Carlson::CConcreteObject*					mContainer;			// Not retained, this is our owner!
	IBOutlet NSScrollView*						mTextScrollView;	// Scroll view around mTextView.
	IBOutlet ULISyntaxColoredTextView*			mTextView;			// Script text.
	WILDScriptEditorRulerView	*				mTextBreakpointsRulerView;	// View at left of text that the user can click in to set/remove breakpoints.
	IBOutlet NSPopUpButton*						mPopUpButton;		// Handlers popup.
	IBOutlet UKSyntaxColoredTextViewController*	mSyntaxController;	// Provides some extra functionality like syntax coloring.
	NSRect										mGlobalStartRect;	// For opening animation.
	IBOutlet NSView	*							mTopNavAreaView;	// The top area above the text (becomes fullscreen accessory view).
}

@property (assign) IBOutlet NSCollectionView	*	codeBlocksListView;

-(id)		initWithScriptContainer: (Carlson::CConcreteObject*)inContainer;

-(IBAction)	handlerPopupSelectionChanged: (id)sender;

-(void)		setGlobalStartRect: (NSRect)theBox;

-(void)		goToLine: (NSUInteger)lineNum;
-(void)		goToCharacter: (NSUInteger)charNum;

@end

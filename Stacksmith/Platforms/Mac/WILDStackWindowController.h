//
//  WILDStackWindowController.h
//  Stacksmith
//
//  Created by Uli Kusterer on 2014-01-13.
//  Copyright (c) 2014 Uli Kusterer. All rights reserved.
//

#ifndef __Stacksmith__WILDStackWindowController__
#define __Stacksmith__WILDStackWindowController__

#import <Cocoa/Cocoa.h>
#include "CScriptableObjectValue.h"


namespace Carlson {

class CStackMac;
class CPart;

}


@class WILDFlippedContentView;


@interface WILDStackWindowController : NSWindowController <NSWindowDelegate,NSMenuDelegate>
{
	Carlson::CStackMac	*	mStack;
	CALayer				*	mSelectionOverlay;	// Draw "peek" outline and selection rectangles in this layer.
	NSImageView			*	mBackgroundImageView;
	NSImageView			*	mCardImageView;
	BOOL					mWasVisible;
	NSPopover			*	mPopover;			// If this stack is of style 'popover', this is the popover it is shown in.
	NSPopover			*	mCurrentPopover;	// Whatever current info popover is shown on the toolbar.
	WILDFlippedContentView*	mContentView;
}

-(id)	initWithCppStack: (Carlson::CStackMac*)inStack;

-(void)	removeAllViews;
-(void)	createAllViews;
-(void) setVisualEffectType: (NSString*)inEffectType speed: (Carlson::TVisualEffectSpeed)inSpeed;

-(void)	drawBoundingBoxes;
-(void)	refreshExistenceAndOrderOfAllViews;
-(void)	updateStyle;

-(IBAction)	goFirstCard: (id)sender;
-(IBAction)	goPrevCard: (id)sender;
-(IBAction)	goNextCard: (id)sender;
-(IBAction)	goLastCard: (id)sender;

-(Carlson::CStackMac*)	cppStack;

-(void)	showWindowOverPart: (Carlson::CPart*)overPart;

-(IBAction)	newPart: (id)sender;

-(void)		showContextualMenuForSelection;
-(IBAction)	showPartInfoWindow: (id)sender;

-(IBAction)	delete: (id)sender;
-(IBAction)	deleteCard: (id)sender;
-(IBAction)	deleteStack: (id)sender;

-(IBAction)	takeToolFromTag: (id)sender;

-(NSData*)	currentCardSnapshotData;

-(void)	reflectFontOfSelectedParts;

-(IBAction)	projectMenuItemSelected: (id)sender;

@end


@interface WILDFlippedContentView : NSView <NSTextFinderBarContainer>
{
	NSView				*		lastHitView;
	Carlson::CStackMac	*		mStack;
	WILDStackWindowController *	mOwningStackWindowController;
	NSTextFinder		*		mTextFinder;
}

@property (assign,nonatomic) Carlson::CStackMac*		stack;
@property (assign,nonatomic) WILDStackWindowController*	owningStackWindowController;
@property (strong) NSView 							*	findBarView;
@property (getter=isFindBarVisible) BOOL 				findBarVisible;

@end

extern NSRect	WILDFlippedScreenRect( NSRect inBox );

#endif /* defined(__Stacksmith__WILDStackWindowController__) */
